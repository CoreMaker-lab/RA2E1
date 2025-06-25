/***********************************************************************
*
* FILE : qe_touch_sample.c
* DESCRIPTION : Main Program for RA
*
* NOTE:THIS IS A TYPICAL EXAMPLE.
*
***********************************************************************/
#include "qe_touch_config.h"
#include <stdio.h>
#define TOUCH_SCAN_INTERVAL_EXAMPLE (20)    /* milliseconds */

void qe_touch_main(void);



uint64_t button_status;
#if (TOUCH_CFG_NUM_SLIDERS != 0)
uint16_t slider_position[TOUCH_CFG_NUM_SLIDERS];
#endif
#if (TOUCH_CFG_NUM_WHEELS != 0)
uint16_t wheel_position[TOUCH_CFG_NUM_WHEELS];
#endif

fsp_err_t err = FSP_SUCCESS;
volatile bool uart_send_complete_flag = false;
void user_uart_callback (uart_callback_args_t * p_args)
{
    if(p_args->event == UART_EVENT_TX_COMPLETE)
    {
        uart_send_complete_flag = true;
    }
}

#ifdef __GNUC__                                 //串口重定向
    #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else

#endif


PUTCHAR_PROTOTYPE
{
        err = R_SCI_UART_Write(&g_uart9_ctrl, (uint8_t *)&ch, 1);
        if(FSP_SUCCESS != err) __BKPT();
        while(uart_send_complete_flag == false){}
        uart_send_complete_flag = false;
        return ch;
}

int _write(int fd,char *pBuffer,int size)
{
    for(int i=0;i<size;i++)
    {
        __io_putchar(*pBuffer++);
    }
    return size;
}


//RTC变量
/* rtc_time_t is an alias for the C Standard time.h struct 'tm' */
rtc_time_t set_time =
{
    .tm_sec  = 50,      /* 秒，范围从 0 到 59 */
    .tm_min  = 59,      /* 分，范围从 0 到 59 */
    .tm_hour = 23,      /* 小时，范围从 0 到 23*/
    .tm_mday = 28,      /* 一月中的第几天，范围从 1 到 31*/
    .tm_mon  = 1,       /* 月份，范围从 0 到 11*/
    .tm_year = 125,     /* 自 1900 起的年数，2025为125*/
    .tm_wday = 5,       /* 一周中的第几天，范围从 0 到 6*/
//    .tm_yday=0,       /* 一年中的第几天，范围从 0 到 365*/
//    .tm_isdst=0;      /* 夏令时*/
};

//RTC闹钟变量
rtc_alarm_time_t set_alarm_time=
{
     .time.tm_sec  = 10,      /* 秒，范围从 0 到 59 */
     .time.tm_min  = 30,      /* 分，范围从 0 到 59 */
     .time.tm_hour = 12,      /* 小时，范围从 0 到 23*/
     .time.tm_mday = 1,       /* 一月中的第几天，范围从 1 到 31*/
     .time.tm_mon  = 2,       /* 月份，范围从 0 到 11*/
     .time.tm_year = 125,     /* 自 1900 起的年数，2025为125*/
     .time.tm_wday = 6,       /* 一周中的第几天，范围从 0 到 6*/

     .sec_match        =  1,
     .min_match        =  0,
     .hour_match       =  0,
     .mday_match       =  0,
     .mon_match        =  0,
     .year_match       =  0,
     .dayofweek_match  =  0,
    };

//RTC回调函数
volatile bool rtc_flag = 0;//RTC延时1s标志位
volatile bool rtc_alarm_flag = 0;//RTC闹钟
/* Callback function */
void rtc_callback(rtc_callback_args_t *p_args)
{
    /* TODO: add your own code here */
    if(p_args->event == RTC_EVENT_PERIODIC_IRQ)
        rtc_flag=1;
    else if(p_args->event == RTC_EVENT_ALARM_IRQ)
        rtc_alarm_flag=1;
}


void qe_touch_main(void)
{


    /* Open the transfer instance with initial configuration. */
    err = R_SCI_UART_Open(&g_uart9_ctrl, &g_uart9_cfg);
    assert(FSP_SUCCESS == err);
    printf("hello!\n");

    /**********************RTC开启***************************************/
     /* Initialize the RTC module*/
     err = R_RTC_Open(&g_rtc0_ctrl, &g_rtc0_cfg);

     /* Handle any errors. This function should be defined by the user. */
     assert(FSP_SUCCESS == err);

     /* Set the RTC clock source. Can be skipped if "Set Source Clock in Open" property is enabled. */
     R_RTC_ClockSourceSet(&g_rtc0_ctrl);
     /* R_RTC_CalendarTimeSet must be called at least once to start the RTC */
     R_RTC_CalendarTimeSet(&g_rtc0_ctrl, &set_time);
     /* Set the periodic interrupt rate to 1 second */
     R_RTC_PeriodicIrqRateSet(&g_rtc0_ctrl, RTC_PERIODIC_IRQ_SELECT_1_SECOND);

     R_RTC_CalendarAlarmSet(&g_rtc0_ctrl, &set_alarm_time);
     uint8_t rtc_second= 0;      //秒
     uint8_t rtc_minute =0;      //分
     uint8_t rtc_hour =0;         //时
     uint8_t rtc_day =0;          //日
     uint8_t rtc_month =0;      //月
     uint16_t rtc_year =0;        //年
     uint8_t rtc_week =0;        //周
     rtc_time_t get_time;


    /* Open Touch middleware */
    err = RM_TOUCH_Open(g_qe_touch_instance_config01.p_ctrl, g_qe_touch_instance_config01.p_cfg);
    if (FSP_SUCCESS != err)
    {
        while (true) {}
    }





    /* Main loop */
    while (true)
    {
        bsp_io_level_t p_port_value_pin_000;
        R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_00, &p_port_value_pin_000);
        if(p_port_value_pin_000)
            R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_02_PIN_08, BSP_IO_LEVEL_LOW);
        else
            R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_02_PIN_08, BSP_IO_LEVEL_HIGH);

        bsp_io_level_t p_port_value_pin_001;
        R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_01, &p_port_value_pin_001);
        if(p_port_value_pin_001)
            R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_11, BSP_IO_LEVEL_LOW);
        else
            R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_11, BSP_IO_LEVEL_HIGH);

        /* for [CONFIG01] configuration */
        err = RM_TOUCH_ScanStart(g_qe_touch_instance_config01.p_ctrl);
        if (FSP_SUCCESS != err)
        {
            while (true) {}
        }
        while (0 == g_qe_touch_flag) {}
        g_qe_touch_flag = 0;

        err = RM_TOUCH_DataGet(g_qe_touch_instance_config01.p_ctrl, &button_status, NULL, NULL);
        if (FSP_SUCCESS == err)
        {
            /* TODO: Add your own code here. */

            if(button_status & (0b1 ) )
            {
                R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_09_PIN_13, BSP_IO_LEVEL_HIGH);
            }
            else
            {
                R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_09_PIN_13, BSP_IO_LEVEL_LOW);
            }

            if(button_status & (0b10) )
            {
                R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_09_PIN_14, BSP_IO_LEVEL_HIGH);
            }
            else
            {
                R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_09_PIN_14, BSP_IO_LEVEL_LOW);
            }
        }

        if(rtc_flag)
        {
            R_RTC_CalendarTimeGet(&g_rtc0_ctrl, &get_time);//获取RTC计数时间
            rtc_flag=0;
            rtc_second=get_time.tm_sec;//秒
            rtc_minute=get_time.tm_min;//分
            rtc_hour=get_time.tm_hour;//时
            rtc_day=get_time.tm_mday;//日
            rtc_month=get_time.tm_mon;//月
            rtc_year=get_time.tm_year; //年
            rtc_week=get_time.tm_wday;//周
            printf(" %d y %d m %d d %d h %d m %d s %d w\n",rtc_year+1900,rtc_month+1,rtc_day,rtc_hour,rtc_minute,rtc_second,rtc_week);


            }
        if(rtc_alarm_flag)
        {
            rtc_alarm_flag=0;
            printf("/************************Alarm Clock********************************/\n");
            }



        /* FIXME: Since this is a temporary process, so re-create a waiting process yourself. */
        R_BSP_SoftwareDelay(TOUCH_SCAN_INTERVAL_EXAMPLE, BSP_DELAY_UNITS_MILLISECONDS);
    }
}


