#include "discovery.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

uint32_t discoverTV(){
	// check nvs for last tv location

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
	return ipaddr;
}
