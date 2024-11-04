\mainpage Main Page

---
# RTC 18 Click

> RTC 18 Click is a compact add-on board that accurately keeps the time of a day. This board features the RV-3032-C7, an I2C-configurable real-time clock module that incorporates an integrated CMOS circuit and an XTAL from Micro Crystal AG. The RV-3032-C7 is a temperature compensated RTC with premium accuracy (0.22 sec/day) and extremely low power consumption, allowing it to be used with a single button cell battery for an extended period. It can measure temperature with a typical accuracy of ±1°C and a resolution of 0.0625°C/step with a programmable alarm on top and bottom temperature limits. It features standard RTC functions with automatic leap year correction, and standard interrupt for Periodic Countdown Timer and Periodic Time Update (seconds, minutes), date/hour/minute alarm, and an external event.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc18_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rtc-18-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the RTC 18 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RTC 18 Click driver.

#### Standard key functions :

- `rtc18_cfg_setup` Config Object Initialization function.
```c
void rtc18_cfg_setup ( rtc18_cfg_t *cfg );
```

- `rtc18_init` Initialization function.
```c
err_t rtc18_init ( rtc18_t *ctx, rtc18_cfg_t *cfg );
```

- `rtc18_default_cfg` Click Default Configuration function.
```c
err_t rtc18_default_cfg ( rtc18_t *ctx );
```

#### Example key functions :

- `rtc18_read_time` This function reads the current time values - second, minute and hour.
```c
err_t rtc18_read_time ( rtc18_t *ctx, rtc18_time_t *time );
```

- `rtc18_read_date` This function reads the current date values - day of week, day, month and year.
```c
err_t rtc18_read_date ( rtc18_t *ctx, rtc18_date_t *date );
```

- `rtc18_read_temperature` This function reads temperature measurements in Celsius.
```c
err_t rtc18_read_temperature ( rtc18_t *ctx, float *temperature );
```

## Example Description

> This example demonstrates the use of RTC 18 Click board by reading and displaying the time and date values as well as the temperature measurements in Celsius.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and performs the Click default configuration which enables the periodic interrupt on seconds count-up, and sets the starting time and date.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc18_cfg_t rtc18_cfg;  /**< Click config object. */

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
    rtc18_cfg_setup( &rtc18_cfg );
    RTC18_MAP_MIKROBUS( rtc18_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc18_init( &rtc18, &rtc18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTC18_ERROR == rtc18_default_cfg ( &rtc18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    time.hour = 23;
    time.minute = 59;
    time.second = 50;
    if ( RTC18_OK == rtc18_set_time ( &rtc18, &time ) )
    {
        log_printf( &logger, " Set time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    date.day_of_week = RTC18_SATURDAY;
    date.day = 31;
    date.month = 12;
    date.year = 22;
    if ( RTC18_OK == rtc18_set_date ( &rtc18, &date ) )
    {
        log_printf( &logger, " Set date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc18_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the second count-up interrupt and then reads and displays on the USB UART the current time and date values as well as the temperature measurements in Celsius.

```c
void application_task ( void )
{
    float temperature;
    
    // Wait for a second count-up interrupt
    while ( rtc18_get_int_pin ( &rtc18 ) );
    
    Delay_ms ( 10 );
    rtc18_clear_periodic_interrupt ( &rtc18 );
    
    if ( RTC18_OK == rtc18_read_time ( &rtc18, &time ) )
    {
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    if ( RTC18_OK == rtc18_read_date ( &rtc18, &date ) )
    {
        log_printf( &logger, " Date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc18_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    if ( RTC18_OK == rtc18_read_temperature ( &rtc18, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC18

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
