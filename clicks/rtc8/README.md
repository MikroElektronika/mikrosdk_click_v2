\mainpage Main Page
 
---
# RTC 8 Click

> RTC 8 Click is a real time clock module which has an extremely low power consumption, allowing it to be used with a single button cell battery, for an extended period of time. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc8_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rtc-8-click)

---


#### Click library 

- **Author**        : MikroE Team
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

- `rtc8_cfg_setup` Config Object Initialization function.
```c
void rtc8_cfg_setup ( rtc8_cfg_t *cfg ); 
```

- `rtc8_init` Initialization function.
```c
err_t rtc8_init ( rtc8_t *ctx, rtc8_cfg_t *cfg );
```

- `rtc8_default_cfg` Click Default Configuration function.
```c
err_t rtc8_default_cfg ( rtc8_t *ctx );
```

#### Example key functions :

- `rtc8_set_time` Set new time - 24 hour format
```c
err_t rtc8_set_time ( rtc8_t *ctx, rtc8_time_t *time_s );
```

- `rtc8_set_date` Set new date
```c
err_t rtc8_set_date ( rtc8_t *ctx, rtc8_date_t *date_s );
```

- `rtx8_get_time_and_date` Get RTC data ( Time and Data )
```c
err_t rtx8_get_time_and_date ( rtc8_t *ctx, rtc8_time_t *time_s, rtc8_date_t *date_s );
```

## Examples Description

> Demo application shows the operation of RTC 8 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Settings the Click in the default configuration.
> Sets new: Time, Date, UNIX time and alarm data.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc8_cfg_t rtc8_cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    rtc8_cfg_setup( &rtc8_cfg );
    RTC8_MAP_MIKROBUS( rtc8_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc8_init( &rtc8, &rtc8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( RTC8_ERROR == rtc8_default_cfg ( &rtc8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    // 24h format - HH,MM,SS
    time_s.hours = 23;
    time_s.minutes = 59;
    time_s.seconds = 50;

    rtc8_set_time( &rtc8, &time_s );

    // Set date format
    date_s.weekdays = 5;
    date_s.day = 31;
    date_s.month = 12;
    date_s.year = 22;

    rtc8_set_date( &rtc8, &date_s );

    // Set UNIX time
    rtc8_set_unix_time( &rtc8, 1672527590ul );

    // Set alarm format
    alarm_s.weekdays = 6;
    alarm_s.hours = 0;
    alarm_s.minutes = 0;

    rtc8_set_alarm( &rtc8, &alarm_s );

    log_info( &logger, " Application Task " );
} 
```

### Application Task

> Read current Time, Date and UNIX time and checks if the alarm is active.

```c
void application_task ( void )
{
    static uint8_t time_seconds = 0xFF;
    uint8_t alarm = 0;
    uint32_t unix_time = 0;
    
    err_t error_flag = rtx8_get_time_and_date( &rtc8, &time_s, &date_s );
    error_flag |= rtc8_get_uinx_time( &rtc8, &unix_time );
    error_flag |= rtc8_get_alarm_flag( &rtc8, &alarm );

    if ( ( RTC8_OK == error_flag ) && ( time_seconds != time_s.seconds ) )
    {
        display_weekday ( date_s.weekdays );
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n Date: %.2u.%.2u.20%.2u.\r\n", 
                    ( uint16_t ) time_s.hours, ( uint16_t ) time_s.minutes,
                    ( uint16_t ) time_s.seconds, ( uint16_t ) date_s.day, 
                    ( uint16_t ) date_s.month, ( uint16_t ) date_s.year );
        log_printf( &logger, " UNIX: %lu\r\n", unix_time );
        if ( RTC8_ALARM_IS_ACTIVE == alarm )
        {
            log_info( &logger, " Alarm Activated!!! " );
            rtc8_reset_alarm_flag( &rtc8 );
        }
        log_printf( &logger, "------------------\r\n" );
        time_seconds = time_s.seconds;
    }
    Delay_ms ( 200 );
}
```

## Note

> Comment out the lines for setting date and time if you would like the 
> module to keep counting time after a reset or shut down.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc8

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
