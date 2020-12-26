#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
/* Sets up system hardware */
static void prvSetupHardware(void) {
	SystemCoreClockUpdate();
	Board_Init();
	/* Initial LEDs state is off */
	Board_LED_Set(0, true);
	Board_LED_Set(1, true);
	Board_LED_Set(2, true);
	3
}
/* LED1 toggle thread */
static void vLEDTask1(void *pvParameters) {
	bool LedState = false;
	while (1) {
		/* red light wait for 3s for all the other led task to complete */
		Board_LED_Set(0, false);
		LedState = (bool) !LedState;
		vTaskDelay(1000);
		Board_LED_Set(0, true);
		/* red light wait for 3.5s for all the other led task to complete */
		vTaskDelay(3500);
	}
}
static void vLEDTask2(void *pvParameters) {
	bool LedState = false;
	/*green light wait for 3s for all the other led task to complete */
	vTaskDelay(1500);
	while (1) {
		/* blue LED lights for 1s*/
		Board_LED_Set(1, false);
		vTaskDelay(1000);
		Board_LED_Set(1, true);
		vTaskDelay(3500);
	}
}
static void vLEDTask3(void *pvParameters) {
	bool LedState = false;
	/* blue light wait for 3s for all the other led task to complete */
	vTaskDelay(3000);
	while (1) {
		Board_LED_Set(2, false);
		LedState = (bool) !LedState;
		/* blue light turn on for 1s */
		vTaskDelay(1000);
		Board_LED_Set(2, true);
		4
		vTaskDelay(3500);
	}
}
int main(void) {
	prvSetupHardware();
	/* RED LED toggle thread */
	xTaskCreate(vLEDTask1, (signed char* ) "vTaskLed1",
			configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
			(xTaskHandle *) NULL);
	/* GREEN LED toggle thread */
	xTaskCreate(vLEDTask2, (signed char* ) "vTaskLed2",
			configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
			(xTaskHandle *) NULL);
	/* BLUE LED toggle thread */
	xTaskCreate(vLEDTask3, (signed char* ) "vTaskLed3",
			configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 10UL),
			(xTaskHandle *) NULL);
	/* Start the scheduler */
	vTaskStartScheduler();
	/* Should never arrive here */
	return 1;
}
