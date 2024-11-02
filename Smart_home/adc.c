 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega16 ADC driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_init(void)
{
	//Choose Internal 2.56 V as reference
	SET_BIT(ADMUX,REFS0);
	SET_BIT(ADMUX,REFS1);
	//Turn off left adjust
	CLEAR_BIT(ADMUX,ADLAR);
	//Assume channel zero single ended
	CLEAR_BIT(ADMUX,MUX0);
	CLEAR_BIT(ADMUX,MUX1);
	CLEAR_BIT(ADMUX,MUX2);
	CLEAR_BIT(ADMUX,MUX3);
	CLEAR_BIT(ADMUX,MUX4);
	//Enable ADC
	SET_BIT(ADCSRA,ADEN);
	//Disable Interrupt
	CLEAR_BIT(ADCSRA,ADIE);
	//Choose prescaler (128) from 50 to 200 KHZ
	SET_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
}

uint16 ADC_readChannel(uint8 channel_num)
{
	//Insert ch_num in ADMUX
	ADMUX = (ADMUX & 0xE0) | (channel_num & 0x7);
	//Start conversion
	SET_BIT(ADCSRA,ADSC);
	//Polling until ADIF=1
	while(BIT_IS_CLEAR(ADCSRA,ADIF)){}
	//Clear ADIF flag
	SET_BIT(ADCSRA,ADIF);
	//Return digital value
	return ADC;
}
