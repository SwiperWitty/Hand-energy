#include "Mode.h"
#include "API.h"
#include "pic.h"


/*
            软件文件夹->AT32文件夹->Keil工程
项目文件->  
            云端库文件夹...
*/

int temp = 0;
U8 temp_1 = 0;
int temp_2 = 0;
int temp_3 = 0;
U8 temp_String[300];
U8 temp1_String[300];
int temp_list[18];
float temp_f;
int i;

void Main_Init(void);
int main (void)
{
    Main_Init();
    for(int a = 0;a < 100;a ++)
    {
        temp_String[a] = 0xfa;
    }
    while(1)
    {
        Mode_User.Sys_Clock.Get_TIME();
		if(CV_UART[2]->Rxd_Received)
		{
			CV_UART[2]->Rxd_Received = 0;
			if(CV_UART[2]->UART_RxdBuff[0] == '1')
			{
				Mode_User.LED.LED_SET(1,ENABLE);
				User_hot_on();
				printf("on hot \r\n");

			}
			else if(CV_UART[2]->UART_RxdBuff[0] == 1)
			{
				temp_2 = 1;
			}
			else
			{
				temp_f = ADC_Get_Temperature();
				printf("p: MCU_Temp %f \r\n",temp_f);
				Mode_User.LED.LED_SET(1,DISABLE);
				User_hot_off();
				temp_2 = 0;
				printf("off hot \r\n");
			}
			Mode_User.UART.Send_Data(2,CV_UART[2]->UART_RxdBuff,CV_UART[2]->DATA.Length);
			Destroy(CV_UART[2],sizeof(*CV_UART[2])); 
		}
		
        if(temp != SYS_Time.Watch.second)       //
        {
            temp = SYS_Time.Watch.second;
        }
		if(temp_2)
		{
			temp_f = DS18B20_Get_Temp();
			printf("temp : %5.2f \r\n",temp_f);
		}
        
        temp_1 ++;
        if(temp_1 > 100) 
        {temp_1 = 0;}
        
        Mode_User.Delay.Delay_ms(200);
//        ADC_Get_List(temp_list);
//		temp_f = temp_list[0];
//		temp_f = temp_f / 4096 * VDDA;
//		temp_f = temp_f * VCC_Cfc;
//		printf("p: vcc : %f \r\n", temp_f);
//		
//		temp_f = 4096 - temp_list[1];
//		temp_f = temp_f / 4096 * VDDA;
//		printf("p: temp : %f \r\n", temp_f);
//		printf("p: mcu : %f  \r\n\r\n", ADC_Get_Temperature());
    }
}

void Main_Init(void)
{
    system_clock_config();
    Mode_Index();
    API_Index();
    
    Mode_Init.Sys_Clock(ENABLE);
    Mode_Init.LED(ENABLE);
	User_GPIO_Init(ENABLE);
	
    Mode_Init.UART(2,115200,ENABLE);
	Mode_Init.KEY(1,ENABLE); 
    Mode_Init.LCD(ENABLE); 
	if(DS18B20_Init (ENABLE) == 1)
	{
		printf("p: DS18B20_Init sec !\r\n");
	}
    else
	{
		printf("p: DS18B20_Init error !\r\n");
	}
    
    User_hot_off();		//hot
	User_09V();		//12V
	
    Mode_User.Delay.Delay_ms(100);
//    Mode_User.LCD.Show_Picture(0,0,239,240,gImage_kk);
//	Mode_User.LCD.Show_String(0,12,"1-1234567890abcdefghijklmNOP",WHITE,BLACK,16);

    ADC_Start_Init(ENABLE);
    Mode_User.Sys_Clock.Set_TIME(SYS_Time.Watch);

    Mode_User.UART.Send_String(2,"s: hello world !\r\n");
    printf("p: Nice to meet you > WQing !\r\n");
    printf("p: Created by Cavendish \r\n");

	
	printf("p: mcu : %f  \r\n\r\n", ADC_Get_Temperature());
}
