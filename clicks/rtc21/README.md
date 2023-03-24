\mainpage Main Page

---
# RTC 21 click

> RTC 21 Click is a compact add-on board that accurately keeps the time of the day. This board features the PT7C4311, an I2C-configurable real-time clock module with programmable square-wave output from Diodes Incorporated. The PT7C4311 includes time and calendar functions providing various information such as hour, minute, second, day, date, month, year, and century. It operates in a 24-hour format indicator, has automatic leap year compensation, and low power consumption, allowing it to be used with a single button cell battery for an extended period.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc21_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rtc-21-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the RTC 21 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RTC 21 Click driver.

#### Standard key functions :

- `rtc21_cfg_setup` Config Object Initialization function.
```c
void rtc21_cfg_setup ( rtc21_cfg_t *cfg );
```

- `rtc21_init` Initialization function.
```c
err_t rtc21_init ( rtc21_t *ctx, rtc21_cfg_t *cfg );
```

#### Example key functions :

- `rtc21_set_time` This function sets the starting time values - second, minute and hour.
```c
err_t rtc21_set_time ( rtc21_t *ctx, rtc21_time_t *time );
```

- `rtc21_set_date` This function sets the starting date values - day of week, day, month and year.
```c
err_t rtc21_set_date ( rtc21_t *ctx, rtc21_date_t *date );
```

- `rtc21_read_time` This function reads the current time values - second, minute and hour.
```c
err_t rtc21_read_time ( rtc21_t *ctx, rtc21_time_t *time );
```

## Example Description

> This example demonstrates the use of RTC 21 click board by reading and displaying the time and date values.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and then sets the starting time and date.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc21_cfg_t rtc21_cfg;  /**< Click config object. */

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
    rtc21_cfg_setup( &rtc21_cfg );
    RTC21_MAP_MIKROBUS( rtc21_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc21_init( &rtc21, &rtc21_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    time.hour = 23;
    time.minute = 59;
    time.second = 50;
    if ( RTC21_OK == rtc21_set_time ( &rtc21, &time ) )
    {
        log_printf( &logger, " Set time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    date.day_of_week = RTC21_SATURDAY;
    date.day = 31;
    date.month = 12;
    date.year = 22;
    if ( RTC21_OK == rtc21_set_date ( &rtc21, &date ) )
    {
        log_printf( &logger, " Set date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc21_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays on the USB UART the current time and date values once per second.

```c
void application_task ( void )
{
    if ( RTC21_OK == rtc21_read_time ( &rtc21, &time ) )
    {
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    if ( RTC21_OK == rtc21_read_date ( &rtc21, &date ) )
    {
        log_printf( &logger, " Date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc21_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC21

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
