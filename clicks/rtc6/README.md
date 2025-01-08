
---
# RTC6 Click

> [RTC 6 Click](https://www.mikroe.com/?pid_product=MIKROE-948) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-948&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application enables usage of Real-TIme clock and calendar with alarm on RTC 6 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc6

### Example Key Functions

- `rtc6_cfg_setup` Config Object Initialization function. 
```c
void rtc6_cfg_setup ( rtc6_cfg_t *cfg );
``` 
 
- `rtc6_init` Initialization function. 
```c
err_t rtc6_init ( rtc6_t *ctx, rtc6_cfg_t *cfg );
```

- `rtc6_default_cfg` Click Default Configuration function. 
```c
void rtc6_default_cfg ( rtc6_t *ctx );
```

- `rtc6_battery_enable` This function enables automatic switch to battery on VCC failure. 
```c
void rtc6_battery_enable ( rtc6_t *ctx );
```
 
- `rtc6_get_gmt_time` This function gets current GMT time and sets it in the RTC. 
```c
void rtc6_get_gmt_time ( rtc6_t *ctx, rtc6_time_t *gmt_time );
```

- `rtc6_get_local_time` his function calculates current local time. 
```c
void rtc6_get_local_time ( rtc6_t *ctx, rtc6_time_t *local_time );
```

### Application Init

> Initializes driver init, sets time zone, sets UTC-GMT time and alarm time

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc6_cfg_t cfg;
    int8_t time_zone = 2;

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

    rtc6_cfg_setup( &cfg );
    RTC6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc6_init( &rtc6, &cfg );

    // Set UTC time

    utc_time.seconds  = 40;
    utc_time.minutes  = 59;
    utc_time.hours    = 23;
    utc_time.monthday = 14;
    utc_time.month    = 12;
    utc_time.year     = 18;
    
    // Set alarm time
    
    alarm_time.seconds  = 0;
    alarm_time.minutes  = 0;
    alarm_time.hours    = 0;
    alarm_time.weekdays  = 0;
    alarm_time.monthday = 15;
    alarm_time.month    = 12;
    alarm_time.year     = 18;

    rtc6_default_cfg( &rtc6, time_zone, &utc_time, &alarm_time );
    log_info( &logger, " ----- Init successfully ----- " );
}
```

### Application Task

> Reads GMT time and Local time. Checks if the alarm is activated. 
> If the alarm is active, it disable alarm and adjusts the new one within 20 seconds.
> Logs this data on USBUART every 900ms.

```c
void application_task ( void )
{
    //  Task implementation.

    rtc6_get_gmt_time( &rtc6, &utc_time );
    rtc6_get_local_time( &rtc6, &local_time );
    
    log_printf( &logger, "--- UTC time ---\r\nTime : %d %d %d\r\n", utc_time.hours, utc_time.minutes, utc_time.seconds );
    
    log_printf( &logger, "Date : %d %d %d\r\n", utc_time.monthday, utc_time.month, utc_time.year );
    
    log_printf( &logger, "--- Local time ---\r\nTime : %d %d %d\r\n", local_time.hours, local_time.minutes, local_time.seconds );

    log_printf( &logger, "Date : %d %d %d\r\n \r\n", local_time.monthday, local_time.month, local_time.year );
    
    if ( rtc6_is_active_alarm( &rtc6 ) != 0 )
    {
        log_printf( &logger, " ----- Active alarm ----- \r\n" );
        rtc6_disable_alarm( &rtc6, RTC6_ALARM_0 );
        rtc6_repeat_alarm( &rtc6, RTC6_ALARM_0, 20 );
    }

    Delay_ms ( 900 );
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
