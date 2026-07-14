
---
# RTC 27 Click

> [RTC 27 Click](https://www.mikroe.com/?pid_product=MIKROE-6964) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6964&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the RTC 27 Click board by initializing
the device and setting up the current time and date. It continuously
reads and displays the updated time and date every second using the timer
countdown interrupt pin.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC27

### Example Key Functions

- `rtc27_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void rtc27_cfg_setup ( rtc27_cfg_t *cfg );
```

- `rtc27_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t rtc27_init ( rtc27_t *ctx, rtc27_cfg_t *cfg );
```

- `rtc27_default_cfg` This function executes a default configuration of RTC 27 Click board.
```c
err_t rtc27_default_cfg ( rtc27_t *ctx );
```

- `rtc27_get_int_pin` This function returns the logical state of the INT pin.
```c
uint8_t rtc27_get_int_pin ( rtc27_t *ctx );
```

- `rtc27_set_time_date` This function sets both time and date registers in a single operation.
```c
err_t rtc27_set_time_date ( rtc27_t *ctx, rtc27_time_t *time, rtc27_date_t *date );
```

- `rtc27_read_time_date` This function reads both time and date registers in a single operation.
```c
err_t rtc27_read_time_date ( rtc27_t *ctx, rtc27_time_t *time, rtc27_date_t *date );
```

### Application Init

> Initializes the logger and the RTC 27 Click driver, applies the default configuration, and sets the starting time and date.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc27_cfg_t rtc27_cfg;  /**< Click config object. */

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
    rtc27_cfg_setup( &rtc27_cfg );
    RTC27_MAP_MIKROBUS( rtc27_cfg, MIKROBUS_POSITION_RTC27 );
    if ( I2C_MASTER_ERROR == rtc27_init( &rtc27, &rtc27_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTC27_ERROR == rtc27_default_cfg ( &rtc27 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    time.hour = 23;
    time.minute = 59;
    time.second = 50;
    time.second_100th = 0;
    date.day_of_week = RTC27_THURSDAY;
    date.day = 31;
    date.month = 12;
    date.year = 26;
    if ( RTC27_OK == rtc27_set_time_date ( &rtc27, &time, &date ) )
    {
        log_printf( &logger, " Set time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
        log_printf( &logger, " Set date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc27_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for a 1 Hz interrupt signal and then reads and displays the current time and date.

```c
void application_task ( void )
{
    // Wait for a timer countdown flag configured at 1 Hz
    while ( rtc27_get_int_pin ( &rtc27 ) );

    if ( ( RTC27_OK == rtc27_clear_msf ( &rtc27 ) ) &&
         ( RTC27_OK == rtc27_read_time_date ( &rtc27, &time, &date ) ) )
    {
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
        log_printf( &logger, " Date: %s, %.2u.%.2u.20%.2u.\r\n\n", 
                    rtc27_get_day_of_week_name ( date.day_of_week ),
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
