
---
# RTC 24 Click

> [RTC 24 Click](https://www.mikroe.com/?pid_product=MIKROE-6635) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6635&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the RTC 24 Click board by initializing
the device and setting up the current time and date. It continuously
reads and displays the updated time and date every second using the square wave pin.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC24

### Example Key Functions

- `rtc24_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void rtc24_cfg_setup ( rtc24_cfg_t *cfg );
```

- `rtc24_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t rtc24_init ( rtc24_t *ctx, rtc24_cfg_t *cfg );
```

- `rtc24_default_cfg` This function executes a default configuration of RTC 24 Click board.
```c
err_t rtc24_default_cfg ( rtc24_t *ctx );
```

- `rtc24_set_time` This function sets the current time (hours, minutes, seconds) in the RTC.
```c
err_t rtc24_set_time ( rtc24_t *ctx, rtc24_time_t *time );
```

- `rtc24_read_time` This function reads the current time (hours, minutes, seconds) from the RTC.
```c
err_t rtc24_read_time ( rtc24_t *ctx, rtc24_time_t *time );
```

- `rtc24_read_date` This function reads the current date (day, day of week, month, year) from the RTC.
```c
err_t rtc24_read_date ( rtc24_t *ctx, rtc24_date_t *date );
```

### Application Init

> Initializes the logger and the RTC 24 Click driver, applies the default configuration, and sets the starting time and date.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc24_cfg_t rtc24_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 124200
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
    rtc24_cfg_setup( &rtc24_cfg );
    RTC24_MAP_MIKROBUS( rtc24_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc24_init( &rtc24, &rtc24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTC24_ERROR == rtc24_default_cfg ( &rtc24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    time.hour = 23;
    time.minute = 59;
    time.second = 50;
    if ( RTC24_OK == rtc24_set_time ( &rtc24, &time ) )
    {
        log_printf( &logger, " Set time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    date.day_of_week = RTC24_TUESDAY;
    date.day = 31;
    date.month = 12;
    date.year = 24;
    if ( RTC24_OK == rtc24_set_date ( &rtc24, &date ) )
    {
        log_printf( &logger, " Set date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc24_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for a 1 Hz square wave signal and then reads and displays the current time and date.

```c
void application_task ( void )
{
    // Wait for a square wave output configured at 1 Hz
    while ( rtc24_get_sqw_pin ( &rtc24 ) );
    while ( !rtc24_get_sqw_pin ( &rtc24 ) );

    if ( RTC24_OK == rtc24_read_time ( &rtc24, &time ) )
    {
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    if ( RTC24_OK == rtc24_read_date ( &rtc24, &date ) )
    {
        log_printf( &logger, " Date: %s, %.2u.%.2u.20%.2u.\r\n\n", 
                    rtc24_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
}
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
