
---
# RTC 9 Click

> [RTC 9 Click](https://www.mikroe.com/?pid_product=MIKROE-4121) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4121&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of RTC 9 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc9

### Example Key Functions

- `rtc9_cfg_setup` Config Object Initialization function. 
```c
void rtc9_cfg_setup ( rtc9_cfg_t *cfg );
``` 
 
- `rtc9_init` Initialization function. 
```c
err_t rtc9_init ( rtc9_t *ctx, rtc9_cfg_t *cfg );
```

- `rtc9_set_time` Set new time - 24 hour format. 
```c
void rtc9_set_time ( rtc9_t *ctx, uint8_t hour, uint8_t min, uint8_t sec );
```
 
- `rtc9_get_time` Get new time - 24 hour format. 
```c
rtc9_get_time ( rtc9_t *ctx, rtc9_get_time_t *get_time  );
```

- `rtc9_get_date` Get new date. 
```c
rtc9_get_date ( rtc9_t *ctx, rtc9_get_date_t *get_data  );
```

### Application Init

> Initializes the driver, wakes up the module, and sets the time and date.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc9_cfg_t cfg;
    rtc9_set_data_t set_data;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rtc9_cfg_setup( &cfg );
    RTC9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc9_init( &rtc9, &cfg );

    Delay_ms ( 500 );

    rtc9_wakeup( &rtc9 );

    rtc9_set_time( &rtc9, 23, 59, 50 );

    set_data.day = 22;
    set_data.day_of_week = RTC9_DAY_MONDAY;
    set_data.month = RTC9_MONTH_MARCH;
    set_data.year = 21;
    rtc9_set_date ( &rtc9, &set_data );
    
    rtc9_wakeup( &rtc9 );
}
```

### Application Task

> Reads the current time and date and displays the results on the USB UART each second.

```c
void application_task ( void )
{
    rtc9_get_time_t get_time;
    rtc9_get_date_t get_date;

    char *week_string;
    char *month_string;

    rtc9_get_time( &rtc9, &get_time );
    rtc9_get_date( &rtc9, &get_date );
    
    if ( get_time.sec != seconds_old )
    {
        seconds_old = get_time.sec;
        log_printf( &logger, "- Time [ %.2u:%.2u:%.2u ] \r\n", ( uint16_t ) get_time.hour, 
                                                               ( uint16_t ) get_time.min, 
                                                               ( uint16_t ) get_time.sec );

        week_string = rtc9_current_day_of_week( get_date.day_of_week );
        month_string = rtc9_current_month( get_date.month );

        log_printf( &logger, "- Date [ %s, %s %.2u, %u ] \r\n", week_string, month_string, 
                                                               ( uint16_t ) get_date.day, 
                                                               ( uint16_t ) get_date.year + 2000 );
        log_printf( &logger, "---------------------------------------- \r\n" );
    }
    Delay_ms ( 10 );
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
