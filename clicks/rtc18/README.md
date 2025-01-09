
---
# RTC 18 Click

> [RTC 18 Click](https://www.mikroe.com/?pid_product=MIKROE-5192) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5192&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of RTC 18 Click board by reading and displaying the time and date values as well as the temperature measurements in Celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC18

### Example Key Functions

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
