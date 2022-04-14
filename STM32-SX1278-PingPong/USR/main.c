#include "DELAY/Delay.h"
#include "ADC/ADC.h"
#include "LED/LED.h"
#include "KEY/key.h"
#include "UART/uart.h"
#include "IIC/IIC.h"
#include "OLED/OLED.h"
#include "SPIx/SPIx.h"
#include "SX1278/SX1278.h"
#include "NodeBus.h"

int main(void)
{
	u8 rx, tx;
	u16 i = 0;
	u16 j = 0;

	/*初始化各外设*/
	initSysTick();

	initLED();
	initUART();
	sendString(USART2, "init ok");
	initSPIx();
	initSX1278();
	sendString(USART2, "initSX1278 ok");
	
#ifdef 0
	while (1)
	{
		if (receivePackets(&rx))
		{
			printf("receivePackets:%d\n", rx);
			toggleLED();
		}
		Delay_ms(100);
	}
#else
	while (1)
	{
		transmitPackets(&tx, 1);

		++tx;
		printf("transmitPackets is %d\n", tx);
		toggleLED();
		Delay_ms(2000);
	}
#endif
}
