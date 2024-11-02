/*Include ECAL drivers*/
#include "lcd.h"
#include "ldr.h"
#include "leds.h"
#include "dc_motor.h"
#include "flame.h"
#include "lm35_sensor.h"
#include "buzzer.h"

//Create flags by using bitfield
	struct my_bitfield
	{
		uint8 alert :1; //used to print alert massage one time instead of clear and print
		uint8 Start:1;  //used to print text massage at first time and after alert massage
		uint8 :6;
	}flags;

//main Function
int main (void)
{
	//initial values
	flags.Start=1;
	flags.alert=1;

	/*call init functions*/
	LCD_init();
	ADC_init();
	LEDS_init();
	DcMotor_Init();
	FlameSensor_init();
	Buzzer_init();

	while(1)
	{
		//Lighting control
		{
			uint16 light=LDR_getLightIntensity();
			if(light>70)
			{
				LED_off(RED);
				LED_off(GREEN);
				LED_off(BLUE);
			}
			else if (light>50)
			{
				LED_on(RED);
				LED_off(GREEN);
				LED_off(BLUE);
			}
			else if (light>15)
			{
				LED_on(RED);
				LED_on(GREEN);
				LED_off(BLUE);
			}
			else
			{
				LED_on(RED);
				LED_on(GREEN);
				LED_on(BLUE);
			}
		}

		//Fan speed control
		DcMotor_Rotate(state,speed);
		{
			uint8 temp=LM35_getTemperature();
			if(temp>=40)
			{
				state=CW;
				speed=100;
			}
			else if (temp>=35)
			{
				state=CW;
				speed=75;
			}
			else if (temp>=30)
			{
				state=CW;
				speed=50;
			}
			else if (temp>=25)
			{
				state=CW;
				speed=25;
			}
			else
			{
				state=stop;
				speed=0;
			}
		}


		//Fire Detection
		if(FlameSensor_getValue())
		{
			Buzzer_on();
		}
		else
		{
			Buzzer_off();
		}

		//LCD display
		if(FlameSensor_getValue())
		{
			if(flags.alert)
			{
				//clear & print alert & make alert =0 & make start =1
				LCD_clearScreen();
				LCD_displayString("Critical alert!");
				flags.alert=0;
				flags.Start=1;
			}
		}
		else
		{
			//General case
			flags.alert=1;
			//For Start
			if(flags.Start)
			{
				//clear & print text massage & make start =0
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,3,"FAN is ");
				LCD_displayStringRowColumn(1,0,"Temp=   LDR=   %");
				flags.Start=0;
			}
			//print the readings
			if(state==stop)
			{
				LCD_displayStringRowColumn(0,10,"OFF");
			}
			else
			{
				LCD_displayStringRowColumn(0,10,"ON ");
			}
			//move to write temperature
			LCD_moveCursor(1,5);
			LCD_intgerToString(LM35_getTemperature());
			if (LM35_getTemperature()<100)
			{
				LCD_displayCharacter(' ');
			}
			//move to write LDR value
			LCD_moveCursor(1,12);
			LCD_intgerToString(LDR_getLightIntensity());
			if (LDR_getLightIntensity()<100)
			{
				LCD_displayCharacter(' ');
			}
		}
	}
}
