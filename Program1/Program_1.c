#include <avr/io.h>
#include <util/delay.h>

#define LED      PB0
#define LED_DDR  DDRB
#define LED_PORT PORTB

#define DELAYTIME 200

#define setBit(sfr, bit)     ((sfr) |= (1 << bit))
#define clearBit(sfr, bit)   ((sfr) &= ~(1 << bit))
 
int main(void) {
  setBit(LED_DDR, LED);

  while (1) {

      for(uint8_t n = 0; n < 5; n++){
        setBit(LED_PORT, LED);
        _delay_ms(DELAYTIME);
  
        clearBit(LED_PORT, LED);
        _delay_ms(DELAYTIME);
      }

      _delay_ms(8 * DELAYTIME);

  }
  return 0;
}