/*
 * DHT22 for Raspberry Pi with WiringPi
 * Author: Hyun Wook Choi
 * Version: 0.0.2
 * https://github.com/ccoong7/DHT22
 */


#include <stdio.h>
#include <wiringPi.h>

static const unsigned char signal = 18;



// This function just display signal state
// LOW = 0, HIGH = 1
void readSignalBinary()
{
	unsigned short bin = 0;
	unsigned short binCount = 0;
	unsigned short pbin = 0;
	unsigned short row = 0;

	while (1)
	{
		if (digitalRead(signal) == LOW)
		{
			bin = 0;
		}

		else
		{
			bin = 1;
		}


		// Just for readability
		binCount++;

		if (binCount%5 == 0)
		{
			printf(" ");
		}

		if (bin != pbin)
		{
			pbin = bin;
			printf("\n");

			binCount = 0;
		}

		if (binCount >= 100)
		{
			break;
		}

		printf("%u", bin);
		delayMicroseconds(1);
	}

	printf("\n\n\n");
}



int main(void)
{
	// GPIO Initialization
	if (wiringPiSetupGpio() == -1)
	{
		printf("[x_x] GPIO Initialization FAILED.\n");
		return -1;
	}

	for (unsigned char i = 0; i < 10; i++)
	{
		pinMode(signal, OUTPUT);

		// Send out start signal
		digitalWrite(signal, LOW);
		delay(20);					// Stay LOW for 5~30 milliseconds
		pinMode(signal, INPUT);		// 'INPUT' equals 'HIGH' level. And signal read mode

		readSignalBinary();
		delay(2000);				// DHT22 average sensing period is 2 seconds
	}

	return 0;
}
