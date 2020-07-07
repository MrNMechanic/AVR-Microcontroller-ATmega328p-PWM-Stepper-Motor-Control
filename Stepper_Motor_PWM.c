#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
int adc_value;        //Variable used to store the value read from the ADC converter

#define	stepPin PD7            //Define Step pin
#define dirPin PD6             //Define Direction pin
#define Enable PD5              //Define Enable pin


int main(void){
	
	int x;
	DDRD |= (1<<5)|(1<<6)|(1<<7); ///Enable Driver,Step,Direction,Output
	PORTD &= ~(1<<5);
	
	
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));    //Prescaler at 128 so we have an 125Khz clock source
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);                //Avcc(+5v) as voltage reference
	ADCSRB &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));    //ADC in free-running mode
	ADCSRA |= (1<<ADATE);                //Signal source, in this case is the free-running
	ADCSRA |= (1<<ADEN);                //Power up the ADC
	ADCSRA |= (1<<ADSC);                //Start converting
	
	for(;;){            //The infinite loop
		adc_value = ADCW;    /
		if(300 < adc_value&& adc_value < 700 ){
			PORTD &= ~(1<<5);
			
		}
		
		
		else if(adc_value > 512){
			PORTD |= (1<<6);                //Make PORTD6 high to rotate motor in clockwise direction
			
			for(x=0; x<50; x++)              //Give 50 pulses to rotate stepper motor by 90 degree's in full step mode
			{
				PORTD |=(1<<7);
				_delay_us(50);
				PORTD &=~(1<<7);
				_delay_us(50);
				
				
			}
			
		}
		else {
			PORTD &= ~(1<<6);
			for(x=0; x<50; x++)             //Give 50 pulses to rotate stepper motor by 90 degree's in full step mode
			{
				PORTD |=(1<<7);
				_delay_us(50);
				PORTD &=~(1<<7);
				_delay_us(50);
			}
		}
	}
	
	return 0;
}
	
