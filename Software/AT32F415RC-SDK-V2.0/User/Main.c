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
        Mode_User.TIME.Get_TIME();
        
        if(temp != SYS_Time.Watch.second)       //
        {
            temp = SYS_Time.Watch.second;
//            printf("Time - %2d:%2d:%2d \r\n",SYS_Time.Watch.hour,SYS_Time.Watch.minutes,SYS_Time.Watch.second);
//            temp_f = DS18B20_Get_Temp();
//            printf("Get_Temp - %5.2f \r\n",temp_f);
            
//            ADC_Get_List(temp_list);
//            printf("str[A0]: %d\r\n str[A1]: %d\r\n str[A2]: %d\r\n \r\n",temp_list[0],temp_list[1],temp_list[2]);
//            printf("str[B0]: %d\r\n str[B1]: %d\r\n \r\n",temp_list[3],temp_list[4]);
//            printf("temp : %5.2f \r\n",ADC_Get_Temperature());

        }
        if(SYS_Time.Watch.second % 2)
        {
            Mode_User.LED.LED_SET(2,DISABLE);
        }
        else
        {
            Mode_User.LED.LED_SET(2,ENABLE);
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
        
//        IIC_Send_DATA(0X5A,"123456789",0,sizeof("123456789"),1);

        
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
    
    Mode_Init.TIME(ENABLE);
    Mode_Init.LED(ENABLE);

//    Mode_Init.Steering_Engine(ENABLE);
    Mode_Init.UART(2,115200,ENABLE);

    Mode_Init.LCD(ENABLE);
    DS18B20_Init (ENABLE);
    

    Mode_User.LED.LED_SET(1,DISABLE);
    Mode_User.LED.LED_SET(2,DISABLE);
//    Mode_User.Steering_Engine.Set_Angle(1,90);
    Mode_User.Delay.Delay_ms(100);
    Mode_User.LCD.Show_Picture(0,0,60,60,gImage_am_60);
//    ADC_Start_Init(ENABLE);

    Mode_User.TIME.Set_TIME(SYS_Time.Watch);

    Mode_User.UART.Send_String(2,"s: hello world !\r\n");
    printf("p: Nice to meet you > WQing !\r\n");
    printf("p: Created by Cavendish \r\n");

//    Mode_User.UART.Send_String(2,"U2: hello world !\r\n");
//    Mode_User.UART.Send_String(3,"U3: hello world !\r\n");

}
