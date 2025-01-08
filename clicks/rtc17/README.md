
---
# RTC 17 Click

> [RTC 17 Click](https://www.mikroe.com/?pid_product=MIKROE-5129) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5129&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of RTC 17 Click board by reading and displaying the time and date values.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC17

### Example Key Functions

- `rtc17_cfg_setup` Config Object Initialization function.
```c
void rtc17_cfg_setup ( rtc17_cfg_t *cfg );
```

- `rtc17_init` Initialization function.
```c
err_t rtc17_init ( rtc17_t *ctx, rtc17_cfg_t *cfg );
```

- `rtc17_default_cfg` Click Default Configuration function.
```c
err_t rtc17_default_cfg ( rtc17_t *ctx );
```

- `rtc17_set_time` This function sets the starting time values - second, minute and hour.
```c
err_t rtc17_set_time ( rtc17_t *ctx, rtc17_time_t *time );
```

- `rtc17_read_time` This function reads the current time values - second, minute and hour.
```c
err_t rtc17_read_time ( rtc17_t *ctx, rtc17_time_t *time );
```

- `rtc17_read_date` This function reads the current date values - day of week, day, month and year.
```c
err_t rtc17_read_date ( rtc17_t *ctx, rtc17_date_t *date );
```

### Application Init

> Initializes the driver and logger and performs the Click default configuration which sets 24h time mode and interrupt to be synchronized with second count-up.
And after that setting the starting time and date.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc17_cfg_t rtc17_cfg;  /**< Click config object. */

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
    rtc17_cfg_setup( &rtc17_cfg );
    RTC17_MAP_MIKROBUS( rtc17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc17_init( &rtc17, &rtc17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTC17_ERROR == rtc17_default_cfg ( &rtc17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    time.hour = 23;
    time.minute = 59;
    time.second = 50;
    if ( RTC17_OK == rtc17_set_time ( &rtc17, &time ) )
    {
        log_printf( &logger, " Set time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    date.day_of_week = RTC17_SATURDAY;
    date.day = 31;
    date.month = 12;
    date.year = 22;
    if ( RTC17_OK == rtc17_set_date ( &rtc17, &date ) )
    {
        log_printf( &logger, " Set date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc17_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the second count-up interrupt and then reads and displays the current time and date values on the USB UART.

```c
void application_task ( void )
{
    // Wait for interrupt which is synchronized with second count-up
    while ( rtc17_get_int_pin ( &rtc17 ) );
    
    rtc17_clear_interrupts ( &rtc17 );
    if ( RTC17_OK == rtc17_read_time ( &rtc17, &time ) )
    {
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    if ( RTC17_OK == rtc17_read_date ( &rtc17, &date ) )
    {
        log_printf( &logger, " Date: %s, %.2u.%.2u.20%.2u.\r\n\n", 
                    rtc17_get_day_of_week_name ( date.day_of_week ),
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
