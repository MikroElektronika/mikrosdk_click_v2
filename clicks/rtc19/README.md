\mainpage Main Page

---
# RTC 19 Click

> RTC 19 Click is a compact add-on board that measures the passage of real-time. This board features the MAX31334, an I2C-configurable real-time clock with an integrated power switch from Analog Devices. The MAX31334 provides information like seconds, minutes, hours, days, months, years, and dates based on a 32.768kHz quartz crystal through an I2C serial interface to transmit time and calendar data to the MCU. It also has an alarm function that outputs an interrupt signal to the MCU when the day of the week, hour, or minute matches with the pre-set time, as well as a programmable square-wave output, event detection input with timestamping, and backup supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtc19_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rtc-19-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the RTC 19 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RTC 19 Click driver.

#### Standard key functions :

- `rtc19_cfg_setup` Config Object Initialization function.
```c
void rtc19_cfg_setup ( rtc19_cfg_t *cfg );
```

- `rtc19_init` Initialization function.
```c
err_t rtc19_init ( rtc19_t *ctx, rtc19_cfg_t *cfg );
```

- `rtc19_default_cfg` Click Default Configuration function.
```c
err_t rtc19_default_cfg ( rtc19_t *ctx );
```

#### Example key functions :

- `rtc19_set_time` This function sets the starting time values - second, minute and hour.
```c
err_t rtc19_set_time ( rtc19_t *ctx, rtc19_time_t *time );
```

- `rtc19_read_time` This function reads the current time values - second, minute and hour.
```c
err_t rtc19_read_time ( rtc19_t *ctx, rtc19_time_t *time );
```

- `rtc19_read_date` This function reads the current date values - day of week, day, month and year.
```c
err_t rtc19_read_date ( rtc19_t *ctx, rtc19_date_t *date );
```

## Example Description

> This example demonstrates the use of RTC 19 Click board by reading and displaying the time and date values.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and performs the Click default configuration which resets the device and sets the timer interrupt to 1 Hz. After that, it sets the starting time and date.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc19_cfg_t rtc19_cfg;  /**< Click config object. */

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
    rtc19_cfg_setup( &rtc19_cfg );
    RTC19_MAP_MIKROBUS( rtc19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc19_init( &rtc19, &rtc19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTC19_ERROR == rtc19_default_cfg ( &rtc19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    time.hour = 23;
    time.minute = 59;
    time.second = 50;
    if ( RTC19_OK == rtc19_set_time ( &rtc19, &time ) )
    {
        log_printf( &logger, " Set time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    date.day_of_week = RTC19_SATURDAY;
    date.day = 31;
    date.month = 12;
    date.year = 22;
    if ( RTC19_OK == rtc19_set_date ( &rtc19, &date ) )
    {
        log_printf( &logger, " Set date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc19_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for a timer countdown interrupt (1 Hz) and then reads and displays on the USB UART the current time and date values.

```c
void application_task ( void )
{
    // Wait for a timer countdown flag configured at 1 Hz
    while ( rtc19_get_inta_pin ( &rtc19 ) );

    Delay_ms ( 100 );
    rtc19_clear_interrupts ( &rtc19 );
    if ( RTC19_OK == rtc19_read_time ( &rtc19, &time ) )
    {
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    if ( RTC19_OK == rtc19_read_date ( &rtc19, &date ) )
    {
        log_printf( &logger, " Date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc19_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC19

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
