#include <LPC17xx.h>
#include <string.h>
//void delay(unsigned long int x);
void uart0_init(void);
	
int main()
{

	 char data[20];
	char str[3][13]= {"090082070589",
										"090084336CD2",
										"09008206C944"};
	unsigned char i,j,k,found;
	SystemInit();
	LPC_GPIO1->FIOMASK3=0XDF;
	LPC_GPIO1->FIODIR3=0X20;
	LPC_PINCON->PINSEL0|=0X00000050;
	uart0_init();
	
while(1)
{
	i=0;
 
		
for(i=0;i<12;i++)
{
    while((LPC_UART0->LSR & 0x01)==0);

    data[i]=LPC_UART0->RBR;
}

data[12]='\0';


	
	
	for(i=0; data[i]!='\0';i++)
	{
		LPC_UART0->THR=data[i];
		while((LPC_UART0->LSR&0X20) !=0X20);
		
	}

	for(k=0;k<3;k++){
		for(i=0;i<12;i++)
		{

		
			if(strcmp((char*)data[i], (char*)str[k][i]) == 0)
					{
					LPC_GPIO1->FIOSET3 = 0x20;
						break;
					}
					
//					else if(strcmp((char*)data, (char*)str[1]) == 0)
//				{
//					LPC_GPIO1->FIOSET3 = 0x20;
//						break;
//					}
//				 else if (strcmp((char*)data, (char*)str[2]) == 0)
//				{
//					LPC_GPIO1->FIOSET3 = 0x20;
//						break;
//					}
				else{
	 
							LPC_GPIO1->FIOCLR3 = 0x20;
						}
					}
				}
 }
}


void uart0_init(void)
{
	LPC_UART0->LCR=0X83;
	LPC_UART0->DLM=0X00;
	LPC_UART0->DLL=0X75;
	LPC_UART0->FDR=0X00000010;
	LPC_UART0->LCR=0X03;
}
//void delay(unsigned long int x)
//{
//	unsigned long int k=0;
//	for(k=0;k<x;k++);
//}