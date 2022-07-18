

#ifndef ANALOG_ADC_H
#define ANALOG_ADC_H


enum {

	ADC_DISABLE = 0 << 0,
	ADC_ENABLE  = 1 << 0,

	ADC_POLLING   = 0 << 1,
	ADC_INTERRUPT = 1 << 1,

	ADC_INTERRUPT_LOW  = 0 << 2,
	ADC_INTERRUPT_HIGH = 1 << 2,

	ADC_NVREF_GND = 0 << 4,
	ADC_NVREF_EXT = 1 << 4,

	ADC_PVREF_VCC = 0 << 5,
	ADC_PVREF_EXT = 1 << 5,

	ADC_FORMAT_LJUST = 0 << 6,
	ADC_FORMAT_RJUST = 1 << 6,

	ADC_TACQ_0CY  = 0 << 8,
	ADC_TACQ_2CY  = 1 << 8,
	ADC_TACQ_4CY  = 2 << 8,
	ADC_TACQ_6CY  = 3 << 8,
	ADC_TACQ_8CY  = 4 << 8,
	ADC_TACQ_12CY = 5 << 8,
	ADC_TACQ_16CY = 6 << 8,
	ADC_TACQ_20CY = 7 << 8,

	ADC_CLK_FOSC_2  = 0 << 12,
	ADC_CLK_FOSC_8  = 1 << 12,
	ADC_CLK_FOSC_32 = 2 << 12,
	ADC_CLK_FOSC_4  = 4 << 12,
	ADC_CLK_FOSC_16 = 5 << 12,
	ADC_CLK_FOSC_64 = 6 << 12,
	ADC_CLK_FRC     = 7 << 12

};


void adc_mode(word mode, byte channels);
word adc_read(byte ch);

void adc_select(byte ch);
void adc_start();
byte adc_ready();
word adc_sample();


#endif

