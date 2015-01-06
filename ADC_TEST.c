*#include<REG_MPC82G516.H>

void delay_ms(int t){
	int i;
	while(t--)
		for(i=0;i<1000;++i);
}

unsigned char read_min;

void main()
{
	P0 = 0xff;
	while(1)
	{
		
		P05=0;
		P06=0;
		P07=0;
		delay_ms(10);
		P21 = 0;
		P21 = 1;
		while(P20 == 1);
		
		read_min = P1;
		P02 = 1;
		P00 = 0;
		P3 = read_min%10;
		delay_ms(1);
		
		P00 = 1;
		P01 = 0;
		read_min/=10;
		P3 = read_min%10;
		delay_ms(1);
		
		P01 = 1;
		P02 = 0;
		read_min/=10;
		P3 = read_min;
		delay_ms(1);
	}
}
