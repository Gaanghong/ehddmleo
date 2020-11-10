#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include <UART0.h>
//#include <ADC.h>

#define set_bit(value, bit) ( _SFR_BYTE(value) |= _BV(bit) )
#define clear_bit(value, bit) ( _SFR_BYTE(value) &= ~_BV(bit) )
boolean chk_straight = 0;
boolean chk_reverse = 0;
void blinking_straight(){
   while(1){
      set_bit(PORTE, 4);
      _delay_ms(300);
      clear_bit(PORTE, 4);
      _delay_ms(300);
      set_bit(PORTE, 5);
      _delay_ms(300);
      clear_bit(PORTE, 5);
      _delay_ms(300);
      set_bit(PORTG, 5);
      _delay_ms(300);
      clear_bit(PORTG, 5);
      _delay_ms(300);
      set_bit(PORTE, 3);
      _delay_ms(300);
      clear_bit(PORTE, 3);
      _delay_ms(300);
      }
}

void blinking_reverse(){
  while(1){
      set_bit(PORTE, 3);
      _delay_ms(300);
      clear_bit(PORTE, 3);
      _delay_ms(300);
      set_bit(PORTG, 5);
      _delay_ms(300);
      clear_bit(PORTG, 5);
      _delay_ms(300);
      set_bit(PORTE, 5);
      _delay_ms(300);
      clear_bit(PORTE, 5);
      _delay_ms(300);
      set_bit(PORTE, 4);
      _delay_ms(300);
      clear_bit(PORTE, 4);
      _delay_ms(300);
      }
}
volatile uint8_t state = 0;

ISR(PCINT1_vect){
  state = !state;
}

void PCINT1_init(void){
  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << PCINT9);
  sei();
}

int main(void){
  init();
  Serial.begin(9600);
  PCINT1_init();
  clear_bit(DDRJ, 0); // PJ0 입력
  set_bit(DDRE, 5); // LED PE5
  //set_bit(DDRE, 4); // LED PE4
  //set_bit(DDRG, 5); // LED PG5
  //set_bit(DDRE, 3); // LED PE3

  while(1) {
    Serial.print("state =");
    Serial.println(state);
    Serial.print("chk_straight = ");
    Serial.println(chk_straight);
    Serial.print("chk_reverse = ");
    Serial.println(chk_reverse);
    if(state){
      set_bit(PORTE ,5);
      chk_straight = 0;
      
    }
    else {
      clear_bit(PORTE, 5);
      chk_straight = 1;
      chk_straight = chk_straight;
      chk_reverse = chk_reverse;
    }
  }
  return 0;
  
}
