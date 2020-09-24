#include "discovery.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "mdns.h"

uint32_t discoverTV(){
	// check nvs for last tv location
	printf("Checking nvs for ipaddr\n");
	nvs_handle_t my_handle;
	ESP_ERROR_CHECK ( nvs_open("storage", NVS_READWRITE, &my_handle));
	uint32_t ipaddr = 0;
	esp_err_t err = nvs_get_u32(my_handle, "ipaddr", &ipaddr);
	if (err==ESP_OK && ipaddr != 0){
		nvs_close (my_handle);
		return ipaddr;
	}
	if (err != ESP_ERR_NVS_NOT_FOUND){
		ESP_ERROR_CHECK (err);
	}

	printf("Checking mdns for _hsremote\n");
	// none found, use mDns to locate TV IP
	ESP_ERROR_CHECK(mdns_init());
#if 0
	esp_ip4_addr_t return_addr;
	ESP_ERROR_CHECK ( mdns_query_a("HSRemote._hsremote._tcp.local",3000,&return_addr));
	ipaddr = return_addr.addr;
#else
	mdns_result_t * results = NULL;
#if 0
	ESP_ERROR_CHECK ( mdns_query_ptr("_hsremote", "_tcp", 3000, 1,  &results));
#else
	ESP_ERROR_CHECK ( mdns_query("HSRemote","_hsremote", "_tcp",MDNS_TYPE_ANY, 3000, 1,  &results));
#endif
	if (results) {
		mdns_ip_addr_t * a = results->addr;
		printf("found service at host %s\n", results->hostname);
		while (a){
			printf("found address of type %d\n", a->addr.type);
			if (a->addr.type==IPADDR_TYPE_V4){
				ipaddr = a->addr.u_addr.ip4.addr;
				break;
			}
			a = a->next;
		}
	}

	mdns_query_results_free(results);
#endif
	mdns_free();

	//write to nvs
	ESP_ERROR_CHECK ( nvs_set_u32 (my_handle, "ipaddr", ipaddr));

	nvs_close (my_handle);
	return ipaddr;
}
