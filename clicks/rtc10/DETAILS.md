

---
# Rtc 10 click

RTC 10 Click is a real-time clock module which has an extremely low power consumption, allowing it to be used with a single button cell battery, for an extended period of time.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rtc-10-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Rtc10 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rtc10 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rtc10_cfg_setup ( rtc10_cfg_t *cfg ); 
 
- Initialization function.
> RTC10_RETVAL rtc10_init ( rtc10_t *ctx, rtc10_cfg_t *cfg );

- Click Default Configuration function.
> void rtc10_default_cfg ( rtc10_t *ctx );


#### Example key functions :

- Generic write function.
> oid rtc10_generic_write ( rtc10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
 
- Generic read function.
> void rtc10_generic_read ( rtc10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

- Hardware reset function.
> void rtc10_hw_reset ( rtc10_t *ctx );

## Examples Description 

> This application is a real-time clock module. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C, hardware reset, set start time and date, enable counting also, write log. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc10_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rtc10_cfg_setup( &cfg );
    RTC10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc10_init( &rtc10, &cfg );

    Delay_ms( 1000 );
    
    sec_flag = 0xFF;

    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "  Hardware  Reset   \r\n" );
    rtc10_hw_reset(  &rtc10 );
    Delay_ms( 1000 );

    // Set Time: 23h, 59 min and 50 sec
    rtc10_set_time(  &rtc10, 23, 59, 50 );
    Delay_ms( 10 );

    // Set Date: 6 ( Day of the week: Saturday ), 31 ( day ), 8 ( month ) and 2019 ( year )
    rtc10_set_date(  &rtc10,  6, 31, 8, 2019 );
    Delay_ms( 100 );

    log_printf( &logger, "-------------------  \r\n" );
    log_printf( &logger, "  Enable Counting  \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "     Start RTC      \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    rtc10_enable_counting(  &rtc10 );
    Delay_ms( 100 );
}
  
```

### Application Task

> This is an example which demonstrates the use of RTC 10 Click board.
  RTC 10 Click communicates with register via I2C interface,
  set time and date, enable counting and display time and date values,
  also, display temperature value for every 1 sec.
  Results are being sent to the Usart Terminal where you can track their changes.
  All data logs write on Usart Terminal changes for every 1 sec. 

```c
void application_task ( void )
{
    uint8_t i;
    uint8_t time_hours = 0;
    uint8_t time_minutes = 0;
    uint8_t time_seconds = 0;

    uint8_t day_of_the_week = 0;
    uint8_t date_day = 0;
    uint8_t date_month = 0;
    uint8_t date_year = 0;
    
    float temperature;
    
    rtc10_get_time( &rtc10, &time_hours, &time_minutes, &time_seconds );
    Delay_ms( 100 );

    rtc10_get_date( &rtc10, &day_of_the_week, &date_day, &date_month, &date_year );
    Delay_ms( 100 );

    if ( sec_flag !=  time_seconds )
    {
        log_printf( &logger, " \r\n\n Time: %u:%u:%u  ", (uint16_t)time_hours, (uint16_t)time_minutes, (uint16_t)time_seconds );
        
        log_printf( &logger, "Date: %u. %u. 20%u. ", (uint16_t)date_day, (uint16_t)date_month, (uint16_t)date_year );
        display_day_of_the_week( day_of_the_week );
        
        if ( time_seconds == 0 )
        {
            temperature = rtc10_get_temperature( &rtc10 );

            log_printf( &logger, "\r\n\n Temp.:%.2f C", temperature);
        }
        log_printf( &logger, "--------------------------------------------" );

        sec_flag =  time_seconds;
    }
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc10

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
