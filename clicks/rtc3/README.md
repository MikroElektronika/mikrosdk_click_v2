
---
# RTC 3 Click

> [RTC 3 Click](https://www.mikroe.com/?pid_product=MIKROE-1839) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1839&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of RTC 3 Click board by reading and displaying the time and date values.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc3

### Example Key Functions

- `rtc3_cfg_setup` Config Object Initialization function.
```c
void rtc3_cfg_setup ( rtc3_cfg_t *cfg ); 
```

- `rtc3_init` Initialization function.
```c
err_t rtc3_init ( rtc3_t *ctx, rtc3_cfg_t *cfg );
```

- `rtc3_set_time` Set time hours, minutes, seconds function
```c
void rtc3_set_time ( rtc3_t *ctx );
```

- `rtc3_get_time` Get time hours, minutes, seconds function
```c
void rtc3_get_time ( rtc3_t *ctx );
```

- `rtc3_get_date` Get day of the week, day, month and year function
```c
void rtc3_get_date ( rtc3_t *ctx );
```

### Application Init

> Initializes the driver and logger and then sets the starting time and date.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc3_cfg_t cfg;

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
    rtc3_cfg_setup( &cfg );
    RTC3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc3_init( &rtc3, &cfg );
    Delay_ms ( 100 );
    
    // Stop counting
    rtc3_set_counting( &rtc3, 0 );

    // Set Time: 23h, 59 min, 50 sec
    rtc3.time.time_hours = 23;
    rtc3.time.time_minutes = 59;
    rtc3.time.time_seconds = 50;

    rtc3_set_time( &rtc3 );

    // Set Date: 6 ( Day of the week ), 31 ( day ), 12 ( month ) and 2022 ( year )
    rtc3.date.day_of_the_week = 6;
    rtc3.date.date_day = 31;
    rtc3.date.date_month = 12;
    rtc3.date.date_year = 22;

    rtc3_set_date( &rtc3 );

    // Start counting
    rtc3_set_counting( &rtc3, 1 );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays on the USB UART the current time and date values once per second.

```c
void application_task ( void )
{
    static uint8_t time_seconds = 0xFF;

    rtc3_get_time( &rtc3 );

    rtc3_get_date( &rtc3 );

    if ( time_seconds != rtc3.time.time_seconds )
    {
        display_log_day_of_the_week ( rtc3.date.day_of_the_week );
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n Date: %.2u.%.2u.20%.2u.\r\n------------------\r\n", 
                    ( uint16_t ) rtc3.time.time_hours, ( uint16_t ) rtc3.time.time_minutes,
                    ( uint16_t ) rtc3.time.time_seconds, ( uint16_t ) rtc3.date.date_day, 
                    ( uint16_t ) rtc3.date.date_month, ( uint16_t ) rtc3.date.date_year );

        time_seconds = rtc3.time.time_seconds;
    }

    Delay_ms ( 200 );
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
