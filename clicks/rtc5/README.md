\mainpage Main Page
 
 

---
# RTC5 click

RTC5 click carries MCP79510, a real-time clock/calendar with an SPI interface (mikroBUS MISO, MOSI, SCK and CS pins); along with a programmable interrupt for system output.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rtc-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Rtc5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rtc5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rtc5_cfg_setup ( rtc5_cfg_t *cfg ); 
 
- Initialization function.
> RTC5_RETVAL rtc5_init ( rtc5_t *ctx, rtc5_cfg_t *cfg );

- Click Default Configuration function.
> void rtc5_default_cfg ( rtc5_t *ctx );


#### Example key functions :

- Set time hours, minutes and seconds function.
> void rtc5_set_time ( rtc5_t *ctx, uint8_t time_hours, uint8_t time_min, uint8_t time_sec );
 
- Set date hours, minutes and seconds function.
> void rtc5_set_date ( rtc5_t *ctx, uint8_t date_day, uint8_t date_month, uint16_t date_year );

- Get time and date function.
> void rtc5_get_time_and_date ( rtc5_t *ctx, rtc5_timedate_t *timedate_data );

## Examples Description

> 
> This is a example which demonstrates the use of RTC 5 Click board.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initializes GPIO, SPI and LOG structures, sets CS pin as output and INT pin as input.
> Initialization driver enable's - SPI, clear RTCC and SRAM memory, 
> sets starting time and date, enable counting and start write log.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc5_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "- Application Init -\r\n" );

    //  Click initialization.

    rtc5_cfg_setup( &cfg );
    RTC5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc5_init( &rtc5, &cfg );
    
    rtc5_default_cfg ( &rtc5);
    Delay_ms( 100 );
    
    rtc5_clear( &rtc5 );
    Delay_ms( 100 );
    
    time_sec_new = 255;

    // Set Time: 17h, 59 min and 50 sec
    rtc5_set_time( &rtc5, 23, 59, 50 );
    
    // Set Day of the week : Wednesday
    rtc5_set_day_of_the_week( &rtc5, RTC5_DAY_OF_THE_WEEK_TUESDAY );
    
    // Set Date: 31 ( day ), 12 ( month ) and 2019 ( year )
    rtc5_set_date( &rtc5, 31, 12, 2019 );
    
    // Start counting
    rtc5_set_counting( &rtc5, 1 );
    Delay_ms( 100 );

    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "    RTC 5  Click    \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    
}
  
```

### Application Task

>
> RTC 5 Click communicates with register via SPI 
> by write to register and read from register, display RTC time and date.
> 

```c

void application_task ( void )
{
    rtc5_get_time_and_date( &rtc5, &time_date_data );
    
    if ( time_sec_new != time_date_data.sec )
    {
        log_printf( &logger, " Time : %02d:%02d:%02d\r\n", time_date_data.hours, time_date_data.min, time_date_data.sec );
    
        display_log_day_of_the_week( time_date_data.w_day );
    
        log_printf( &logger, " Date : %02d.%02d.20%02d.\r\n", time_date_data.day, time_date_data.month, time_date_data.year );
        log_printf( &logger, "--------------------\r\n" );
    
        time_sec_new = time_date_data.sec;
    }
} 

```

## Note

> 
> Additional Functions: 
> void display_log_day_of_the_week( uint8_t w_day ) - Write day of the week log.
> 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc5

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
