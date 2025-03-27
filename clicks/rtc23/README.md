
---
# RTC 23 Click

> [RTC 23 Click](https://www.mikroe.com/?pid_product=MIKROE-6281) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6281&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of RTC 23 Click board by reading and displaying the time and date values.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC23

### Example Key Functions

- `rtc23_cfg_setup` Config Object Initialization function.
```c
void rtc23_cfg_setup ( rtc23_cfg_t *cfg );
```

- `rtc23_init` Initialization function.
```c
err_t rtc23_init ( rtc23_t *ctx, rtc23_cfg_t *cfg );
```

- `rtc23_set_time` This function sets the starting time values - second 100th, second, minute and hour.
```c
err_t rtc23_set_time ( rtc23_t *ctx, rtc23_time_t *time );
```

- `rtc23_read_time` This function reads the current time values - second 100th, second, minute and hour.
```c
err_t rtc23_read_time ( rtc23_t *ctx, rtc23_time_t *time );
```

- `rtc23_set_date` This function sets the starting date values - day of week, day, month and year.
```c
err_t rtc23_set_date ( rtc23_t *ctx, rtc23_date_t *date );
```

### Application Init

> Initializes the driver, checks the communication, and sets the starting time and date.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc23_cfg_t rtc23_cfg;  /**< Click config object. */

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
    rtc23_cfg_setup( &rtc23_cfg );
    RTC23_MAP_MIKROBUS( rtc23_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == rtc23_init( &rtc23, &rtc23_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTC23_ERROR == rtc23_check_communication ( &rtc23 ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }

    time.hour = 23;
    time.minute = 59;
    time.second = 50;
    time.second_100th = 0;
    if ( RTC23_OK == rtc23_set_time ( &rtc23, &time ) )
    {
        log_printf( &logger, " Set time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    date.day_of_week = RTC23_TUESDAY;
    date.day = 31;
    date.month = 12;
    date.year = 24;
    if ( RTC23_OK == rtc23_set_date ( &rtc23, &date ) )
    {
        log_printf( &logger, " Set date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc23_get_day_of_week_name ( date.day_of_week ),
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
    if ( RTC23_OK == rtc23_read_time ( &rtc23, &time ) )
    {
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    if ( RTC23_OK == rtc23_read_date ( &rtc23, &date ) )
    {
        log_printf( &logger, " Date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc23_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    Delay_ms ( 1000 );
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
