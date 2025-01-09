
---
# RTC 20 Click

> [RTC 20 Click](https://www.mikroe.com/?pid_product=MIKROE-5600) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5600&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the RTC 20 Click board&trade;
> by reading and displaying the RTC time and date values.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC20

### Example Key Functions

- `rtc20_cfg_setup` Config Object Initialization function.
```c
void rtc20_cfg_setup ( rtc20_cfg_t *cfg );
```

- `rtc20_init` Initialization function.
```c
err_t rtc20_init ( rtc20_t *ctx, rtc20_cfg_t *cfg );
```

- `rtc20_set_time` RTC 20 set time function.
```c
err_t rtc20_set_time ( rtc20_t *ctx, rtc20_time_t rtc_time );
```

- `rtc20_set_date` RTC 20 set date function.
```c
err_t rtc20_set_date ( rtc20_t *ctx, rtc20_date_t rtc_date );
```

- `rtc20_get_time` RTC 20 get time function.
```c
err_t rtc20_get_time ( rtc20_t *ctx, rtc20_time_t *rtc_time );
```

### Application Init

> Initialization of I2C module, log UART and additional pins.
> After driver initialization the app set RTC time to 23:59:50
> and set date to Tuesday 28.02.2023.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc20_cfg_t rtc20_cfg;  /**< Click config object. */

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
    rtc20_cfg_setup( &rtc20_cfg );
    RTC20_MAP_MIKROBUS( rtc20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc20_init( &rtc20, &rtc20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    time.hour   = 23;
    time.minute = 59;
    time.second = 50;
    if ( RTC20_OK == rtc20_set_time( &rtc20, time ) )
    {
        log_printf( &logger, "  Set time : %.2d:%.2d:%.2d\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    
    date.day_of_week = RTC20_DW_TUESDAY;
    date.day         = 28;
    date.month       = 2;
    date.year        = 23;
    if ( RTC20_OK == rtc20_set_date( &rtc20, date ) )
    {
        log_printf( &logger, "  Set date : %.2d-%.2d-%.2d\r\n", 
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    Delay_ms ( 1000 );
    log_printf( &logger, "---------------------\r\n" );
}
```

### Application Task

> This is an example that shows the use of a RTC 20 Click board&trade;.
> In this example, we read and display the current time ( PM ) 
> and date ( day of the week ), which we also previously set.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB changes every 1 sec.

```c
void application_task ( void ) 
{
    if ( RTC20_OK == rtc20_get_time( &rtc20, &time ) )
    {
        if ( RTC20_OK == rtc20_get_date( &rtc20, &date ) )
        {
            if ( time.second != new_sec ) 
            {
                log_printf( &logger, "  Date : %.2d-%.2d-%.2d\r\n",
                            ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
                display_day_of_week( );
                log_printf( &logger, "  Time : %.2d:%.2d:%.2d\r\n",
                            ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
                log_printf( &logger, "- - - - - - - - - - -\r\n" );
                new_sec = time.second;
                Delay_ms ( 1 );
            }
        }
    }
    Delay_ms ( 1 );
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
