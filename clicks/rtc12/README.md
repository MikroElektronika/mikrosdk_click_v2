\mainpage Main Page

---
# RTC 12 click

RTC 12 Click is a compact add-on board that measures the passage of time. This board features the DS1343, a low-current SPI-configurable real-time clock (RTC) from Maxim Integrated. This timekeeping device provides an extremely low standby current permitting longer life from a backup supply source. Its clock/calendar feature provides seconds, minutes, hours, day, date, month, and year information.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc_12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rtc-12-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : May 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Rtc12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Rtc12 Click driver.

#### Standard key functions :

- `rtc12_cfg_setup` Config Object Initialization function.
```c
void rtc12_cfg_setup ( rtc12_cfg_t *cfg );
```

- `rtc12_init` Initialization function.
```c
err_t rtc12_init ( rtc12_t *ctx, rtc12_cfg_t *cfg );
```

- `rtc12_default_cfg` Click Default Configuration function.
```c
err_t rtc12_default_cfg ( rtc12_t *ctx );
```

#### Example key functions :

- `rtc12_set_time` RTC 12 set time function.
```c
err_t rtc12_set_time ( rtc12_t *ctx, rtc12_time_t rtc_time );
```

- `rtc12_get_time` RTC 12 get time function.
```c
err_t rtc12_get_time ( rtc12_t *ctx, rtc12_time_t *rtc_time );
```

- `rtc12_get_date` RTC 12 get date function.
```c
err_t rtc12_get_date ( rtc12_t *ctx, rtc12_date_t *rtc_date );
```

## Example Description

> This is an example that demonstrates the use of the RTC 12 click board™.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module, log UART and additional pins.
> After driver initialization and default settings,
> the app set the time to 23:59:50 and set the date to 27.05.'21.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;      /**< Logger config object. */
    rtc12_cfg_t rtc12_cfg;   /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    rtc12_cfg_setup( &rtc12_cfg );
    RTC12_MAP_MIKROBUS( rtc12_cfg, MIKROBUS_1 );
    err_t init_flag  = rtc12_init( &rtc12, &rtc12_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    rtc12_default_cfg ( &rtc12 );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
    
    date.day_of_week = 4;
    date.day = 27;
    date.month = 5;
    date.year = 21;
    rtc12_set_date( &rtc12, date );
    Delay_ms( 100 );
    
    time.hours = 23;
    time.min = 59;
    time.sec = 50;
    rtc12_set_time( &rtc12, time );
    Delay_ms( 100 );
}

```

### Application Task

> This is an example that shows the use of a RTC 12 click board™.
> In this example, we read and display the current time and date, 
> which we also previously set.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB changes every 1 sec.

```c

void application_task ( void ) {   
    rtc12_get_time( &rtc12, &time );
    Delay_ms( 1 );
    rtc12_get_date( &rtc12, &date );
    Delay_ms( 1 );
    
    if ( time.sec != new_sec ) {
        log_printf( &logger, "  Date      : %.2d-%.2d-%.2d\r\n", ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
        log_printf( &logger, "  Time      : %.2d:%.2d:%.2d\r\n", ( uint16_t ) time.hours, ( uint16_t ) time.min, ( uint16_t ) time.sec );
        log_printf( &logger, "- - - - - - - - - - - -\r\n" );
        new_sec = time.sec;
        Delay_ms( 1 );
     }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
