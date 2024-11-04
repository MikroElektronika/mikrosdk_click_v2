\mainpage Main Page

---
# RTC 20 Click

> RTC 20 Click is a compact add-on board that measures the passage of real-time. 
> This board features the AB0805, an I2C-configurable real-time clock 
> with a highly sophisticated feature set from Abracon LLC. 
> The AB0805 provides information like seconds, minutes, hours, days, months, years, 
> and dates based on a 32.768kHz quartz crystal through an I2C serial interface 
> to transmit time and calendar data to the MCU. It also has automatic leap year compensation, 
> low power consumption, and full RTC functions such as battery backup, programmable counters, 
> and alarms for timer and watchdog functions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc20_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rtc-20-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the RTC 20 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RTC 20 Click driver.

#### Standard key functions :

- `rtc20_cfg_setup` Config Object Initialization function.
```c
void rtc20_cfg_setup ( rtc20_cfg_t *cfg );
```

- `rtc20_init` Initialization function.
```c
err_t rtc20_init ( rtc20_t *ctx, rtc20_cfg_t *cfg );
```

#### Example key functions :

- `rtc20_set_time` RTC 20 set time function.
```c
err_t rtc20_set_time ( rtc20_t *ctx, rtc20_time_t rtc_time );
```

- `rtc20_set_date` RTC 20 set date function.
```c
err_t rtc20_set_date ( rtc20_t *ctx, rtc20_date_t rtc_date );
```

- `rtc20_get_time` RTC 20 get time function.
```c
err_t rtc20_get_time ( rtc20_t *ctx, rtc20_time_t *rtc_time );
```

## Example Description

> This example demonstrates the use of the RTC 20 Click board™
> by reading and displaying the RTC time and date values.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module, log UART and additional pins.
> After driver initialization the app set RTC time to 23:59:50
> and set date to Tuesday 28.02.2023.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc20_cfg_t rtc20_cfg;  /**< Click config object. */

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
    rtc20_cfg_setup( &rtc20_cfg );
    RTC20_MAP_MIKROBUS( rtc20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc20_init( &rtc20, &rtc20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    time.hour   = 23;
    time.minute = 59;
    time.second = 50;
    if ( RTC20_OK == rtc20_set_time( &rtc20, time ) )
    {
        log_printf( &logger, "  Set time : %.2d:%.2d:%.2d\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    
    date.day_of_week = RTC20_DW_TUESDAY;
    date.day         = 28;
    date.month       = 2;
    date.year        = 23;
    if ( RTC20_OK == rtc20_set_date( &rtc20, date ) )
    {
        log_printf( &logger, "  Set date : %.2d-%.2d-%.2d\r\n", 
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    Delay_ms ( 1000 );
    log_printf( &logger, "---------------------\r\n" );
}
```

### Application Task

> This is an example that shows the use of a RTC 20 Click board™.
> In this example, we read and display the current time ( PM ) 
> and date ( day of the week ), which we also previously set.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB changes every 1 sec.

```c
void application_task ( void ) 
{
    if ( RTC20_OK == rtc20_get_time( &rtc20, &time ) )
    {
        if ( RTC20_OK == rtc20_get_date( &rtc20, &date ) )
        {
            if ( time.second != new_sec ) 
            {
                log_printf( &logger, "  Date : %.2d-%.2d-%.2d\r\n",
                            ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
                display_day_of_week( );
                log_printf( &logger, "  Time : %.2d:%.2d:%.2d\r\n",
                            ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
                log_printf( &logger, "- - - - - - - - - - -\r\n" );
                new_sec = time.second;
                Delay_ms ( 1 );
            }
        }
    }
    Delay_ms ( 1 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC20

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
