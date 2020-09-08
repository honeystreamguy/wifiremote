#include "provision.h"
#include "discovery.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void app_main(void)
{
	provision();

	discoverTV();

	while(1){
		// wait until something to process
		ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
		// TODO: process events
	}
}

