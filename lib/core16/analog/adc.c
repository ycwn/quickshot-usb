

#include "core/core.h"
#include "core/gpio.h"

#include "analog/adc.h"


static u16 analog_pins;



void adc_mode(u16 mode)
{

	PIR1bits.ADIF = 0;
	PIE1bits.ADIE = 0;
	IPR1bits.ADIP = 0;

	ADCON0 = 0;
	ADCON1 = 0;
	ADCON2 = 0;

	if ((mode & ADC_ENABLE) == 0)
		return;

	if (mode & ADC_CLK_FOSC_4)  ADCON2bits.ADCS2 = 1;
	if (mode & ADC_CLK_FOSC_32) ADCON2bits.ADCS1 = 1;
	if (mode & ADC_CLK_FOSC_8)  ADCON2bits.ADCS0 = 1;

	if (mode & ADC_TACQ_8CY) ADCON2bits.ACQT2 = 1;
	if (mode & ADC_TACQ_4CY) ADCON2bits.ACQT1 = 1;
	if (mode & ADC_TACQ_2CY) ADCON2bits.ACQT0 = 1;

	if (mode & ADC_FORMAT_RJUST) ADCON2bits.ADFM = 1;

	if (mode & ADC_NVREF_EXT) ADCON1bits.VCFG1 = 1;
	if (mode & ADC_PVREF_EXT) ADCON1bits.VCFG0 = 1;

	if (mode & ADC_INTERRUPT) {

		PIE1bits.ADIE = 1;

		if (mode & ADC_INTERRUPT_HIGH)
			IPR1bits.ADIP = 1;

	}

	analog_pins = 0;

	adc_select(0);

	ADCON0bits.ADON = 1;

}



u16 adc_read(u16 chpin)
{

	if (chpin != ADC_SELECTED_PIN)
		adc_select(chpin);

	PIR1bits.ADIF = 0;
	ADCON0bits.GO = 1;

	while (ADCON0bits.GO);

	return WORD2(ADRESL, ADRESH);

}



void adc_set_analog(u16 pin, bool value)
{

	const u16 mask = 1 << BYTE(GPIO_PIN_ANALOG(pin), 1);

	if (value) analog_pins |= mask;
	else       analog_pins &= ~mask;

	gpio_set_input(pin, value);
}



bool adc_get_analog(u16 pin)
{

	const u16 mask = 1 << BYTE(GPIO_PIN_ANALOG(pin), 1);

	return (analog_pins & mask) != 0;

}



void adc_select(u16 chpin)
{

	u16 ch;
	i8 idx = 16;

	ADCON1bits.PCFG3 = 0;
	ADCON1bits.PCFG2 = 0;
	ADCON1bits.PCFG1 = 0;
	ADCON1bits.PCFG0 = 0;

	while (--idx >= 0)
		if (analog_pins & (1 << idx)) {

			if ((idx & 8) == 0) ADCON1bits.PCFG3 = 1;
			if ((idx & 4) == 0) ADCON1bits.PCFG2 = 1;
			if ((idx & 2) == 0) ADCON1bits.PCFG1 = 1;
			if ((idx & 1) == 0) ADCON1bits.PCFG0 = 1;
			break;

		}

	ADCON0bits.CHS3 = 0;
	ADCON0bits.CHS2 = 0;
	ADCON0bits.CHS1 = 0;
	ADCON0bits.CHS0 = 0;

	ch = (chpin < AN1)? chpin: BYTE(chpin, 1);

	if (ch & 8) ADCON0bits.CHS3 = 1;
	if (ch & 4) ADCON0bits.CHS2 = 1;
	if (ch & 2) ADCON0bits.CHS1 = 1;
	if (ch & 1) ADCON0bits.CHS0 = 1;

}



void adc_start()
{

	PIR1bits.ADIF = 0;
	ADCON0bits.GO = 1;

}



byte adc_ready()
{

	return ADCON0bits.GO == 0;

}



word adc_sample()
{

	return WORD2(ADRESL, ADRESH);

}

