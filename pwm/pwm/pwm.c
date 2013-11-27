
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
/*
ISR(TIMER0_OVF_vect){

	PORTA=PORTA^0x02;
}
ISR(TIMER1_OVF_vect){
	PORTA=PORTA^0x02;
}
*/
SETUP_PWM(){
	TCCR0|= (1 << CS00) | (0 << CS01) | (0 << CS02) | (1 << WGM01) | (1 << WGM00) | (1 << COM01) | (1 << COM00);
}

int main(void)
{   SETUP_PWM();
	DDRB = (1 << PB3);
	
int x=0;
  while(1)
    {
		if(x==0){
        OCR0++;
		_delay_ms(100);
		}
		else{
			OCR0--;
			_delay_ms(100);
		}
		if(OCR0==0 || OCR0==255) x=1-x;
	}

   
}