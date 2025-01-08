
---
# RTC 19 Click

> [RTC 19 Click](https://www.mikroe.com/?pid_product=MIKROE-5426) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5426&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of RTC 19 Click board by reading and displaying the time and date values.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC19

### Example Key Functions

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
