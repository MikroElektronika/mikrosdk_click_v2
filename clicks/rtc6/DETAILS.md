 
---
# RTC6 click

RTC6 click carries Microchip’s MCP79410 Real-Time Clock/Calendar IC with built-in 64 bytes of battery-backed SRAM an additional 1 Kbit of EEPROM.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rtc6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Rtc6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rtc6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rtc6_cfg_setup ( rtc6_cfg_t *cfg ); 
 
- Initialization function.
> RTC6_RETVAL rtc6_init ( rtc6_t *ctx, rtc6_cfg_t *cfg );

- Click Default Configuration function.
> void rtc6_default_cfg ( rtc6_t *ctx );


#### Example key functions :

- This function enables automatic switch to battery on VCC failure.
> void rtc6_battery_enable ( rtc6_t *ctx );
 
- This function gets current GMT time and sets it in the RTC.
> void rtc6_get_gmt_time ( rtc6_t *ctx, rtc6_time_t *gmt_time );

- his function calculates current local time.
> void rtc6_get_local_time ( rtc6_t *ctx, rtc6_time_t *local_time );

## Examples Description

> This application enables usage of Real-TIme clock and calendar with alarm on RTC 6 click.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init, sets time zone, sets UTC-GMT time and alarm time

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc6_cfg_t cfg;
    int8_t time_zone = 2;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rtc6_cfg_setup( &cfg );
    RTC6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc6_init( &rtc6, &cfg );

    // Set UTC time

    utc_time.seconds  = 40;
    utc_time.minutes  = 59;
    utc_time.hours    = 23;
    utc_time.monthday = 14;
    utc_time.month    = 12;
    utc_time.year     = 18;
    
    // Set alarm time
    
    alarm_time.seconds  = 0;
    alarm_time.minutes  = 0;
    alarm_time.hours    = 0;
    alarm_time.weekdays  = 0;
    alarm_time.monthday = 15;
    alarm_time.month    = 12;
    alarm_time.year     = 18;

    rtc6_default_cfg( &rtc6, time_zone, &utc_time, &alarm_time );
    log_info( &logger, " ----- Init successfully ----- " );
}
  
```

### Application Task

> Reads GMT time and Local time. Checks if the alarm is activated. 
> If the alarm is active, it disable alarm and adjusts the new one within 20 seconds.
> Logs this data on USBUART every 900ms.

```c

void application_task ( void )
{
    //  Task implementation.

    rtc6_get_gmt_time( &rtc6, &utc_time );
    rtc6_get_local_time( &rtc6, &local_time );
    
    log_printf( &logger, "--- UTC time ---\r\nTime : %d %d %d\r\n", utc_time.hours, utc_time.minutes, utc_time.seconds );
    
    log_printf( &logger, "Date : %d %d %d\r\n", utc_time.monthday, utc_time.month, utc_time.year );
    
    log_printf( &logger, "--- Local time ---\r\nTime : %d %d %d\r\n", local_time.hours, local_time.minutes, local_time.seconds );

    log_printf( &logger, "Date : %d %d %d\r\n \r\n", local_time.monthday, local_time.month, local_time.year );
    
    if ( rtc6_is_active_alarm( &rtc6 ) != 0 )
    {
        log_printf( &logger, " ----- Active alarm ----- \r\n" );
        rtc6_disable_alarm( &rtc6, RTC6_ALARM_0 );
        rtc6_repeat_alarm( &rtc6, RTC6_ALARM_0, 20 );
    }

    Delay_ms( 900 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc6

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---