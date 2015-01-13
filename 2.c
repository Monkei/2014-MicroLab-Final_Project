#include<REG_MPC82G516.H>

void delay_ms(int t){
	int i;
	while(t--)
		for(i=0;i<1000;++i);
}

unsigned char read_min;

unsigned char pwm_width;
bit pwm_flag = 0;


void pwm_setup(unsigned char speed){
	TMOD = 0;
	pwm_width = speed;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
}

void display(void)
{
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
	while(1)
	{
		P22 = 1;
		P23 = 1;
		
		delay_ms(1);
		P21 = 0;
		P21 = 1;
		while(P20 == 1);
		
		read_min = P1;
		display();
		
	}
}
