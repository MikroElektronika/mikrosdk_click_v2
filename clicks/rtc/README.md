
---
# RTC Click

> [RTC Click](https://www.mikroe.com/?pid_product=MIKROE-947) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-947&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application enables setup and measurement of time with RTC Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc

### Example Key Functions

- `rtc_c_cfg_setup` Config Object Initialization function.
```c
void rtc_c_cfg_setup ( rtc_c_cfg_t *cfg ); 
```

- `rtc_c_init` Initialization function.
```c
err_t rtc_c_init ( rtc_c_t *ctx, rtc_c_cfg_t *cfg );
```

- `rtc_c_set_time` Function sets time: hours, minutes and seconds data to the target register address of PCF8583 chip on RTC Click.
```c
void rtc_c_set_time ( rtc_c_t *ctx );
```

- `rtc_c_get_time` Function gets time: hours, minutes and seconds data from the target register address of PCF8583 chip on RTC Click.
```c
void rtc_c_get_time ( rtc_c_t *ctx );
```

- `rtc_c_enable_disable_counting` Function that enables or disables counting on RTC Click.
```c
void rtc_c_enable_disable_counting ( rtc_c_t *ctx, uint8_t en_dis );
```

### Application Init

> Initialization driver enable's - I2C, set start time, enable counting and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc_c_cfg_t cfg;

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
    rtc_c_cfg_setup( &cfg );
    RTC_C_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc_c_init( &rtc_c, &cfg );

    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "     RTC Click    \r\n" );
    log_printf( &logger, "------------------\r\n" );

    // Set Time: 23h, 59 min, 50 sec and 10 ms
    rtc_c.time.time_hours = 23;
    rtc_c.time.time_minutes = 59;
    rtc_c.time.time_seconds = 50;
    rtc_c.time.time_hun_sec = 10;

    rtc_c_set_time( &rtc_c );
    Delay_100ms( );
    
    // Start counting
    rtc_c_enable_disable_counting( &rtc_c, 1 );
    Delay_100ms( );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This is an example which demonstrates the use of RTC Click board.
> RTC Click communicates with register via I2C by write to register and read from register.
> This example show time when the value of time_seconds is changed.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on usb uart changes for every 1 sec.

```c
void application_task ( void )
{
    static uint8_t time_seconds_new = 0xFF;

    rtc_c_get_time( &rtc_c );

    if ( time_seconds_new != rtc_c.time.time_seconds )
    {
        log_printf( &logger, " Time : %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) rtc_c.time.time_hours, 
                    ( uint16_t ) rtc_c.time.time_minutes, 
                    ( uint16_t ) rtc_c.time.time_seconds );

        log_printf( &logger, "------------------\r\n" );

        time_seconds_new = rtc_c.time.time_seconds;
    }

    Delay_ms ( 500 );
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
