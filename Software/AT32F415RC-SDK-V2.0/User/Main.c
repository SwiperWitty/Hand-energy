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
				Mode_User.LED.LED_SET(1,DISABLE);
				printf("on hot \r\n");
				temp_f = DS18B20_Get_Temp();
				printf("temp : %5.2f \r\n",temp_f);
			}
			else
			{
				Mode_User.LED.LED_SET(1,ENABLE);
				printf("off hot \r\n");
			}
			Mode_User.UART.Send_Data(2,CV_UART[2]->UART_RxdBuff,CV_UART[2]->DATA.Length);
			Destroy(CV_UART[2],sizeof(*CV_UART[2])); 
		}
		
        if(temp != SYS_Time.Watch.second)       //
        {
            temp = SYS_Time.Watch.second;
        }
        if(SYS_Time.Watch.second % 2)
        {

        }
        else
        {
        }
        
        temp_1 ++;
        if(temp_1 > 100) 
        {temp_1 = 0;}
        
        for(int a = 0;a < 100;a ++)
        {
            temp_String[a] = temp_1;
        }
        SPI_Send_String(temp_String,100);
        
        for(int a = 0;a < 100;a ++)
        {
            temp1_String[a] = temp_1 % 0x10;
        }
        SPI_Send_String(temp1_String,200);
        
        Mode_User.Delay.Delay_ms(10);
        
        
//        TIM4_PWMx_SetValue(1,110);
//        TIM4_PWMx_SetValue(2,110);
        Mode_User.Delay.Delay_ms(20);
        
    }
}

void Main_Init(void)
{
    system_clock_config();
    Mode_Index();
    API_Index();
    
    Mode_Init.Sys_Clock(ENABLE);
    Mode_Init.LED(ENABLE);

    Mode_Init.UART(2,115200,ENABLE);
	Mode_Init.KEY(1,ENABLE); 
    Mode_Init.LCD(ENABLE); 
    DS18B20_Init (ENABLE); 
    
    Mode_User.LED.LED_SET(1,ENABLE);
	Mode_User.LED.LED_SET(2,DISABLE);		//12V
	
//    Mode_User.Steering_Engine.Set_Angle(1,90);
    Mode_User.Delay.Delay_ms(100);
    Mode_User.LCD.Show_Picture(0,0,60,60,gImage_am_60);
//    ADC_Start_Init(ENABLE);

    Mode_User.Sys_Clock.Set_TIME(SYS_Time.Watch);

    Mode_User.UART.Send_String(2,"s: hello world !\r\n");
    printf("p: Nice to meet you > WQing !\r\n");
    printf("p: Created by Cavendish \r\n");

}
