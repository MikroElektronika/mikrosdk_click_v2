\mainpage Main Page

---
# RTC 13 Click

> RTC 13 Click is a compact add-on board that accurately keeps the time of a day. This board features the PCF2123, an SPI configurable real-time clock/calendar optimized for low power operations from NXP Semiconductors. The PCF2123 provides year, month, day, weekday, hours, minutes, and seconds based on a 32.768kHz quartz crystal. Data is transferred serially via an SPI interface with a maximum data rate of 6.25 Mbit/s. An alarm and timer function is also available, providing the possibility to generate a wake-up signal on an interrupt line, in addition to a programmable square-wave clock output.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc13_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rtc-13-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the RTC13 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RTC13 Click driver.

#### Standard key functions :

- `rtc13_cfg_setup` Config Object Initialization function.
```c
void rtc13_cfg_setup ( rtc13_cfg_t *cfg );
```

- `rtc13_init` Initialization function.
```c
err_t rtc13_init ( rtc13_t *ctx, rtc13_cfg_t *cfg );
```

- `rtc13_default_cfg` Click Default Configuration function.
```c
err_t rtc13_default_cfg ( rtc13_t *ctx );
```

#### Example key functions :

- `rtc13_get_time` RTC 13 get time function.
```c
err_t rtc13_get_time ( rtc13_t *ctx, rtc13_time_t *rtc_time );
```

- `rtc13_set_time` RTC 13 set time function.
```c
err_t rtc13_set_time ( rtc13_t *ctx, rtc13_time_t rtc_time );
```

- `rtc13_get_date` RTC 13 get date function.
```c
err_t rtc13_get_date ( rtc13_t *ctx, rtc13_date_t *rtc_date );
```

## Example Description

> This is an example that demonstrates the use of the RTC 13 Click board™.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module, log UART and additional pins.
> After driver initialization and default settings,
> the app set the time to 23:59:50 and set the date to 04.08.2021.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    rtc13_cfg_t rtc13_cfg;  /**< Click config object. */

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

    rtc13_cfg_setup( &rtc13_cfg );
    RTC13_MAP_MIKROBUS( rtc13_cfg, MIKROBUS_1 );
    err_t init_flag  = rtc13_init( &rtc13, &rtc13_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    rtc13_default_cfg ( &rtc13 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    date.weekday = 3;
    date.day = 4;
    date.month = 8;
    date.year = 21;
    rtc13_set_date( &rtc13, date );
    Delay_ms ( 100 );
    
    time.hours = 23;
    time.min = 59;
    time.sec = 50;
    rtc13_set_time( &rtc13, time );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that shows the use of a RTC 13 Click board™.
> In this example, we read and display the current time and date, 
> which we also previously set.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB changes every 1 sec.

```c

void application_task ( void )
{  
    rtc13_get_time( &rtc13, &time );
    Delay_ms ( 1 );
    rtc13_get_date( &rtc13, &date );
    Delay_ms ( 1 );
    
    if ( time.sec != new_sec ) 
	{
        log_printf( &logger, "  Date      : %.2d-%.2d-%.2d\r\n", ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
        log_printf( &logger, "  Time      : %.2d:%.2d:%.2d\r\n", ( uint16_t ) time.hours, ( uint16_t ) time.min, ( uint16_t ) time.sec );
        log_printf( &logger, "- - - - - - - - - - - -\r\n" );
        new_sec = time.sec;
        Delay_ms ( 1 );
     }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC13

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
