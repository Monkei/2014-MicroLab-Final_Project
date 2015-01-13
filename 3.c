#include<REG_MPC82G516.H>

#define PWMPIN1 P30

void delay_ms(int t){
	int i;
	while(t--)
		for(i=0;i<1000;++i);
}

unsigned char read_min;

unsigned char pwm_width1;
bit pwm_flag1 = 0;


void pwm_setup1(unsigned char speed){
	TMOD = 0;
	pwm_width1 = speed;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
}

void timer0() interrupt 1 {
		
	if(!pwm_flag1) {	//Start of High level
		pwm_flag1 = 1;	//Set flag
		PWMPIN1 = 1;	//Set PWM o/p pin
		TH0 = 255 - pwm_width1;	//Load timer
		TF0 = 0;		//Clear interrupt flag
		return;		//Return
	}
	else {	//Start of Low level
		pwm_flag1 = 0;	//Clear flag
		PWMPIN1 = 0;	//Clear PWM o/p pin
		TH0 = pwm_width1;	//Load timer
		TF0 = 0;	//Clear Interrupt flag
		return;		//return
	}
}



void display(void)
{
	read_min = 123;
		P04 = 1;
		P05 = 1;
		P06 = 1;
		P07 = 1;
		
		P0 = read_min%10;
		P04 = 0;
		P05 = 1;
		P06 = 1;
		P07 = 1;
		delay_ms(1);
		
		
		read_min/=10;
		P0 = read_min%10;
		P04 = 1;
		P05 = 0;
		P06 = 1;
		P07 = 1;
		delay_ms(1);
		
		
		read_min/=10;
		P0 = read_min;
		P04 = 1;
		P05 = 1;
		P06 = 0;
		P07 = 1;
		delay_ms(1);
}

void main()
{
	P0 = 0xff;
	
	P31 = 0;//MOTOR
	P32 = 1;
	pwm_setup1(30);
	
	
	while(1)
	{
		P22 = 1;//MUX
		P23 = 1;
		
		delay_ms(1);
		P21 = 0;//ADC
		P21 = 1;
		while(P20 == 1);
		
		read_min = P1;
		display();
		
		
		pwm_width1 = 30;
		/*
		if(P31)
		{
			
				if(pwm_width1>0){
					--pwm_width;
						if(pwm_width == 0)
						{
							P20 = 0;
							P21 = 1;
						}
					}
				}else{
					if(pwm_width<255)
						++pwm_width;
				}
		
		if(P20){
					if(pwm_width<255)
						++pwm_width;
				}else{
					if(pwm_width>0){
						--pwm_width;
						if(pwm_width == 0)
						{
							P20 = 1;
							P21 = 0;
						}
					}
				}
		
		*/
		
	}
}
