
---
# RTC 9 click

RTC 9 Click is a real-time clock module that has an extremely low power consumption, allowing it to be used with a single button cell battery, for an extended period of time. This board features the M41T82,  real-time clock (RTC) with battery switchover, from ST Microelectronics.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc9_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/rtc-9-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Rtc9 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rtc9 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rtc9_cfg_setup ( rtc9_cfg_t *cfg ); 
 
- Initialization function.
> RTC9_RETVAL rtc9_init ( rtc9_t *ctx, rtc9_cfg_t *cfg );

#### Example key functions :

- Set new time - 24 hour format
> void rtc9_set_time( rtc9_t *ctx, uint8_t hour, uint8_t min, uint8_t sec );
 
- Get new time - 24 hour format
> rtc9_get_time( rtc9_t *ctx, rtc9_get_time_t *get_time );

- Get new date
> rtc9_get_date( rtc9_t *ctx, rtc9_get_date_t *get_data );

## Examples Description

> This example demonstrates the use of RTC 9 click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver, wakes up the module, and sets the time and date.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc9_cfg_t cfg;
    rtc9_set_data_t set_data;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rtc9_cfg_setup( &cfg );
    RTC9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc9_init( &rtc9, &cfg );

    Delay_ms( 500 );

    rtc9_wakeup( &rtc9 );

    rtc9_set_time( &rtc9, 23, 59, 50 );

    set_data.day = 22;
    set_data.day_of_week = RTC9_DAY_MONDAY;
    set_data.month = RTC9_MONTH_MARCH;
    set_data.year = 21;
    rtc9_set_date ( &rtc9, &set_data );
    
    rtc9_wakeup( &rtc9 );
}
  
```

### Application Task

> Reads the current time and date and displays the results on the USB UART each second.

```c

void application_task ( void )
{
    rtc9_get_time_t get_time;
    rtc9_get_date_t get_date;

    char *week_string;
    char *month_string;

    rtc9_get_time( &rtc9, &get_time );
    rtc9_get_date( &rtc9, &get_date );
    
    if ( get_time.sec != seconds_old )
    {
        seconds_old = get_time.sec;
        log_printf( &logger, "- Time [ %.2u:%.2u:%.2u ] \r\n", ( uint16_t ) get_time.hour, 
                                                               ( uint16_t ) get_time.min, 
                                                               ( uint16_t ) get_time.sec );

        week_string = rtc9_current_day_of_week( get_date.day_of_week );
        month_string = rtc9_current_month( get_date.month );

        log_printf( &logger, "- Date [ %s, %s %.2u, %u ] \r\n", week_string, month_string, 
                                                               ( uint16_t ) get_date.day, 
                                                               ( uint16_t ) get_date.year + 2000 );
        log_printf( &logger, "---------------------------------------- \r\n" );
    }
    Delay_ms( 10 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc9

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
