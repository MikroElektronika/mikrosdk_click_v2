
---
# RTC2 click

< RTC2 Click is an accessory board in mikroBus™ form factor. It features the DS1307 serial real-time clock (RTC). It is a low-power, full binary-coded decimal (BCD) clock/calendar with programmable square-wave output signal. >

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc2_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/rtc-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Rtc2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rtc2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rtc2_cfg_setup ( rtc2_cfg_t *cfg ); 
 
- Initialization function.
> RTC2_RETVAL rtc2_init ( rtc2_t *ctx, rtc2_cfg_t *cfg );

#### Example key functions :

- Generic read byte of data function.
> uint8_t rtc2_read_byte ( rtc2_t *ctx, uint8_t reg_address );
 
- Generic write byte of data function.
> void rtc2_write_byte ( rtc2_t *ctx, uint8_t reg_address, uint8_t write_data );

- Enable counting function.
> void rtc2_enable_counting ( rtc2_t *ctx );

## Examples Description

> This application give time and day information. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C,set start time and date, enable counting and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc2_cfg_t cfg;

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

    rtc2_cfg_setup( &cfg );
    RTC2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc2_init( &rtc2, &cfg );

    rtc2_set_time( &rtc2, 23, 59, 50 );
    rtc2_set_date( &rtc2, 1, 31, 12, 2018 );
    rtc2_enable_counting( &rtc2 );
}
  
```

### Application Task

> This is a example which demonstrates the use of RTC 2 Click board.
    RTC 2 Click communicates with register via I2C by write to register and read from register,
    set time and date, get time and date, enable and disable counting
    and set frequency by write configuration register.
    Results are being sent to the Usart Terminal where you can track their changes.
    All data logs write on usb uart changes for every 1 sec.

```c

void application_task ( void )
{
    rtc2_get_time( &rtc2, &time_hours, &time_minutes, &time_seconds );

    rtc2_get_date( &rtc2, &day_of_the_week, &date_day, &date_month, &date_year );

    if ( time_seconds_new !=  time_seconds )
    {
        log_printf( &logger, " Time : " );

        display_log_uart( time_hours );
        log_printf( &logger, ":" );

        display_log_uart( time_minutes );
        log_printf( &logger, ":" );

        display_log_uart( time_seconds );
        log_printf( &logger, "" );

        display_day_of_the_week( day_of_the_week );

        log_printf( &logger, " Date: " );

        display_log_uart( date_day );
        log_printf( &logger, "." );

        display_log_uart( date_month );
        log_printf( &logger, "." );

        log_printf( &logger, "20" );

        display_log_uart( date_year );
        log_printf( &logger, "." );

        log_printf( &logger, "-------------------" );

        time_seconds_new =  time_seconds;
    }
}  

```

## Note

> Additional Functions :

 - void displayDayOfTheWeek( uint8_t dayOfTheWeek ) - Write day of the week log on USART terminal.
 - void displayLogUart( uint8_t value ) - Write the value ( time or date ) of a two-digit number.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc2

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
