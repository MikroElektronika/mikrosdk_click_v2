
 

---
# RTC 8 click

RTC 8 click is a real time clock module which has an extremely low power consumption, allowing it to be used with a single button cell battery, for an extended period of time. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc8_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/rtc-8-click>)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Rtc8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rtc8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rtc8_cfg_setup ( rtc8_cfg_t *cfg ); 
 
- Initialization function.
> RTC8_RETVAL rtc8_init ( rtc8_t *ctx, rtc8_cfg_t *cfg );

- Click Default Configuration function.
> void rtc8_default_cfg ( rtc8_t *ctx );


#### Example key functions :

- Get Alarm flag
> uint8_t rtc8_get_alarm_flag( rtc8_t *ctx );
 
- Get RTC data ( Time and Data )
> void rtx8_get_time_and_date ( rtc8_t *ctx, rtc8_time_t *time_s, rtc8_date_t *date_s );

- Set UNIX time
> void rtc8_set_unix_time ( rtc8_t *ctx, int32_t unix_time );

## Examples Description

> Demo application shows the operation of RTC 8 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the click in the default configuration.
> Sets new: Time, Date, UNIX time and alarm data.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc8_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rtc8_cfg_setup( &cfg );
    RTC8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc8_init( &rtc8, &cfg );

    rtc8_default_cfg( &rtc8 );

    // 24h format - HH,MM,SS

    time_s.hours = 23;
    time_s.minutes = 58;
    time_s.seconds = 30;

    rtc8_set_time( &rtc8, &time_s );

    // Set date format

    date_s.day = 31;
    date_s.month = 12;
    date_s.year = 18;

    rtc8_set_date( &rtc8, &date_s );

    // Set UNIX time

    rtc8_set_unix_time( &rtc8, 1545053360 );

    // Set alarm format

    alarm_s.weekdays = 3;
    alarm_s.hours = 0;
    alarm_s.minutes = 0;

    rtc8_set_alarm( &rtc8, &alarm_s );
    Delay_100ms();
} 
```

### Application Task

> Read current Time, Date and UNIX time and checks if the alarm is active.

```c
void application_task ( void )
{
    uint8_t alarm;
    uint32_t unix_time;

    //  Task implementation.

    rtx8_get_time_and_date( &rtc8, &time_s, &date_s );
    unix_time = rtc8_get_uinx_time( &rtc8 );

    log_printf( &logger, "\r\n>> ----------------------------- <<\r\n" );

    log_printf( &logger, ">> Time : %d : %d : %d \r\n", time_s.hours, time_s.minutes, time_s.seconds );
    log_printf( &logger, ">> Weekday : %d \r\n", date_s.weekdays );
    log_printf( &logger, ">> Date : %d : %d : %d \r\n", date_s.day, date_s.month, date_s.year );
    log_printf( &logger, ">> UNIX : %ld \r\n", unix_time );

    alarm  = rtc8_get_alarm_flag( &rtc8 );

    if ( alarm == RTC8_ALARM_IS_ACTIVE )
    {
        log_printf( &logger, " - Alarm Active!!! " );
        rtc8_reset_alarm_flag( &rtc8 );
    }
    else
    {
        log_printf( &logger, " - No Alarm." );
    }

    Delay_ms( 1000 );
}
```

## Note

> Comment the lines for setting date and time if you would like the 
> module to keep counting time after a reset or shut down.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc8

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
