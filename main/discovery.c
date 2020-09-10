#include "discovery.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "mdns.h"

uint32_t discoverTV(){
	// check nvs for last tv location
	// maybe close nvs handle?

	nvs_handle_t my_handle;
	ESP_ERROR_CHECK ( nvs_open("storage", NVS_READWRITE, &my_handle));
	uint32_t ipaddr = 0;
	esp_err_t err = nvs_get_u32(my_handle, "ipaddr", &ipaddr);
	if (err==ESP_OK){
		return ipaddr;
	}
	if (err != ESP_ERR_NVS_NOT_FOUND){
		ESP_ERROR_CHECK (err);
	}

	// none found, use mDns to locate TV IP
	ESP_ERROR_CHECK(mdns_init());
	esp_ip4_addr_t return_addr;
	ESP_ERROR_CHECK ( mdns_query_a("HSRemote",3000,&return_addr));
	ipaddr = return_addr.addr;
	mdns_free();

	//write to nvs


	return ipaddr;
}
