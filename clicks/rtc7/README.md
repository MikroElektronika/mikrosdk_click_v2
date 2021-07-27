\mainpage Main Page
 
 

---
# RTC 7 click

RTC 7 Click is a real time clock module which has an extremely low power consumption, allowing it to be used with a single button cell battery or a super capacitor, for an extended period of time. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rtc-7-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the RTC7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for RTC7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rtc7_cfg_setup ( rtc7_cfg_t *cfg ); 
 
- Initialization function.
> RTC7_RETVAL rtc7_init ( rtc7_t *ctx, rtc7_cfg_t *cfg );

- Click Default Configuration function.
> void rtc7_default_cfg ( rtc7_t *ctx );


#### Example key functions :

- This function performs the device initialization.
> uint8_t rtc7_init_time ( rtc7_t *ctx, int8_t time_zone, uint8_t time_mode );
 
- This function performs the oscillator to be configured and enabled.
> uint8_t rtc7_set_osc ( rtc7_t *ctx, uint8_t enable_osc, uint8_t clk_in, uint8_t clk_out );

- This function gets the gmt time data in both time formats.
> void rtc7_get_gmt_time ( rtc7_t *ctx, rtc7_time_t *gmt_time );

## Examples Description

> This app is used to accurately measure time with low power consumption.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc7_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    rtc7_cfg_setup( &cfg );
    RTC7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc7_init( &rtc7, &cfg );
    
    Delay_ms( 300 );

    time_set.seconds = 40;
    time_set.minutes = 59;
    time_set.hours = 1;
    time_set.weekdays = 1;
    time_set.monthday = 1;
    time_set.month = 1;
    time_set.year = 18;
    
    check_change = 0;
    check_year = 0;
    
    rtc7_reset( &rtc7 );
    rtc7_disable_dst( &rtc7 );
    rtc7_init_time ( &rtc7, -2, RTC7_12HR_FORMAT );
    rtc7_set_gmt_time( &rtc7, &time_set );
    log_printf( &logger, "RTC 7 is initialized \r\n" );
    Delay_ms( 1000 );
    rtc7_set_osc( &rtc7, RTC7_ENABLE_OSC, RTC7_INPUT_FREQ_32768HZ, RTC7_OUTPUT_FREQ_32768HZ );
    rtc7_set_timer( &rtc7, RTC7_TIMER_EN, RTC7_TIMER_FREQ_16HZ );

}
  
```

### Application Task

> Waits until device be stable and logs time after each second.

```c

void application_task ( void )
{
    rtc7_get_local_time( &rtc7, &time_date );
    
    if ( check_year == 0 )
    {
        log_printf( &logger, "Wait... \r\n" );
        while ( ( time_date.year != time_set.year ) && ( time_date.year != ( time_set.year + 1 ) ) && ( time_date.year != ( time_set.year - 1 ) ) )
        {
            rtc7_get_local_time( &rtc7, &time_date );
        }
        check_year = 1;
    }
    
    if ( check_change != time_date.seconds )
    {
        rtc7_display_results( &rtc7 );
        check_change = time_date.seconds;
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC7

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
