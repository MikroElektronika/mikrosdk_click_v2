
---
# RTC 7 Click

> [RTC 7 Click](https://www.mikroe.com/?pid_product=MIKROE-2976) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2976&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This app is used to accurately measure time with low power consumption.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC7

### Example Key Functions

- `rtc7_cfg_setup` Config Object Initialization function.
```c
void rtc7_cfg_setup ( rtc7_cfg_t *cfg ); 
```

- `rtc7_init` Initialization function.
```c
err_t rtc7_init ( rtc7_t *ctx, rtc7_cfg_t *cfg );
```

- `rtc7_default_cfg` Click Default Configuration function.
```c
err_t rtc7_default_cfg ( rtc7_t *ctx );
```

- `rtc7_check_interrupt` This function returns the interrupt state, state of INTA pin.
```c
uint8_t rtc7_check_interrupt ( rtc7_t *ctx );
```

- `rtc7_read_reg` This function writes one byte data to the register.
```c
err_t rtc7_read_reg ( rtc7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );
```

- `rtc7_get_local_time` This function gets the local time data including the determined time zone in calculations.
```c
err_t rtc7_get_local_time ( rtc7_t *ctx, rtc7_time_t *local_time );
```

### Application Init

> Initializes device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc7_cfg_t cfg;

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

    //  Click initialization.
    rtc7_cfg_setup( &cfg );
    RTC7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc7_init( &rtc7, &cfg );
    Delay_ms ( 300 );
    
    time_set.seconds = 40;
    time_set.minutes = 59;
    time_set.hours = 23;
    time_set.weekdays = 1;
    time_set.monthday = 31;
    time_set.month = 12;
    time_set.year = 22;
    
    err_t error_flag = rtc7_reset( &rtc7 );
    error_flag |= rtc7_init_time ( &rtc7, 0 );
    error_flag |= rtc7_set_gmt_time( &rtc7, &time_set );
    error_flag |= rtc7_set_osc( &rtc7, RTC7_ENABLE_OSC, RTC7_INPUT_FREQ_32768HZ, RTC7_OUTPUT_FREQ_32768HZ );
    error_flag |= rtc7_write_reg( &rtc7, RTC7_TIMER_INIT_REG, 15 );
    error_flag |= rtc7_set_timer( &rtc7, RTC7_TIMER_EN, RTC7_TIMER_FREQ_16HZ );
    Delay_ms ( 100 );
    if ( RTC7_ERROR == error_flag )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for a second count-up interrupt and then reads and logs the current time and date on the USB UART.

```c
void application_task ( void )
{
    // Wait for timer count-down interrupt which is set to 1Hz
    while ( rtc7_check_interrupt ( &rtc7 ) );

    // Clear interrupt status
    uint8_t int_status = 0;
    rtc7_read_reg( &rtc7, RTC7_INT_STATUS_REG, &int_status, 1 );
    
    // Read time
    if ( RTC7_OK == rtc7_get_local_time( &rtc7, &time_date ) )
    {
        // Display time
        rtc7_display_results( &rtc7 );
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
