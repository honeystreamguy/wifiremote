#include "provision.h"
#include "discovery.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void app_main(void)
{
	printf("hello world\n");
	provision();

	uint32_t ipaddr = discoverTV();
	printf("tv ip address is %x\n", ipaddr);

	while(1){
		// wait until something to process
		ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
		// TODO: process events
	}
}

