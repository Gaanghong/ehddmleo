#include "ADC.h"

int MODE = FREE_RUNNING;

void ADC_init(unsigned char channel, int mode = FREE_RUNNING){
  MODE = mode;

  ADMUX |= (1<<REFS0);

  ADMUX = ((ADMUX & 0xE0) | (channel & 0x07));
  if(channel > 8) ADCSRB |= (1 << MUX5);

  ADCSRA |= ( 1<< ADPS2) | ( 1<< ADPS0);

  ADCSRA |= (1<<ADEN);

  if(MODE == FREE_RUNNING){
    ADCSRA |= ( 1<<ADATE);

    ADCSRB &= ~(1<<ADTS2) & ~(1<<ADTS1) & ~(1 << ADTS0);

    ADCSRA |= (1<<ADSC);
  }
}

int read_ADC(void){
  if(MODE == SINGLE_CONVERSION){
    ADCSRA |= (1<<ADSC);
    
  }
  while(!(ADCSRA & (1<< ADIF)));

  return ADC;
}
