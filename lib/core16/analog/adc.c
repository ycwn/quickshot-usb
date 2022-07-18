

#include "core/core.h"

#include "analog/adc.h"



void adc_mode(word mode, byte channels)
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

	if ((channels & 8) == 0) ADCON1bits.PCFG3 = 1;
	if ((channels & 4) == 0) ADCON1bits.PCFG2 = 1;
	if ((channels & 2) == 0) ADCON1bits.PCFG1 = 1;
	if ((channels & 1) == 0) ADCON1bits.PCFG0 = 1;

	if (mode & ADC_NVREF_EXT) ADCON1bits.VCFG1 = 1;
	if (mode & ADC_PVREF_EXT) ADCON1bits.VCFG0 = 1;

	if (mode & ADC_INTERRUPT) {

		PIE1bits.ADIE = 1;

		if (mode & ADC_INTERRUPT_HIGH)
			IPR1bits.ADIP = 1;

	}

	ADCON0bits.ADON = 1;

}



word adc_read(byte ch)
{

	if (ch != 255) {

		if (ch & 8) ADCON0bits.CHS3 = 1;
		if (ch & 4) ADCON0bits.CHS2 = 1;
		if (ch & 2) ADCON0bits.CHS1 = 1;
		if (ch & 1) ADCON0bits.CHS0 = 1;

	}

	PIR1bits.ADIF = 0;
	ADCON0bits.GO = 1;

	while (ADCON0bits.GO);

	return WORD2(ADRESL, ADRESH);

}



void adc_select(byte ch)
{

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

