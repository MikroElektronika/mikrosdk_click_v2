
---
# RTC 13 Click

> [RTC 13 Click](https://www.mikroe.com/?pid_product=MIKROE-4794) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4794&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the RTC 13 Click board&trade;.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC13

### Example Key Functions

- `rtc13_cfg_setup` Config Object Initialization function.
```c
void rtc13_cfg_setup ( rtc13_cfg_t *cfg );
```

- `rtc13_init` Initialization function.
```c
err_t rtc13_init ( rtc13_t *ctx, rtc13_cfg_t *cfg );
```

- `rtc13_default_cfg` Click Default Configuration function.
```c
err_t rtc13_default_cfg ( rtc13_t *ctx );
```

- `rtc13_get_time` RTC 13 get time function.
```c
err_t rtc13_get_time ( rtc13_t *ctx, rtc13_time_t *rtc_time );
```

- `rtc13_set_time` RTC 13 set time function.
```c
err_t rtc13_set_time ( rtc13_t *ctx, rtc13_time_t rtc_time );
```

- `rtc13_get_date` RTC 13 get date function.
```c
err_t rtc13_get_date ( rtc13_t *ctx, rtc13_date_t *rtc_date );
```

### Application Init

> Initialization of SPI module, log UART and additional pins.
> After driver initialization and default settings,
> the app set the time to 23:59:50 and set the date to 04.08.2021.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    rtc13_cfg_t rtc13_cfg;  /**< Click config object. */

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

    rtc13_cfg_setup( &rtc13_cfg );
    RTC13_MAP_MIKROBUS( rtc13_cfg, MIKROBUS_1 );
    err_t init_flag  = rtc13_init( &rtc13, &rtc13_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    rtc13_default_cfg ( &rtc13 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    date.weekday = 3;
    date.day = 4;
    date.month = 8;
    date.year = 21;
    rtc13_set_date( &rtc13, date );
    Delay_ms ( 100 );
    
    time.hours = 23;
    time.min = 59;
    time.sec = 50;
    rtc13_set_time( &rtc13, time );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that shows the use of a RTC 13 Click board&trade;.
> In this example, we read and display the current time and date, 
> which we also previously set.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB changes every 1 sec.

```c
void application_task ( void )
{  
    rtc13_get_time( &rtc13, &time );
    Delay_ms ( 1 );
    rtc13_get_date( &rtc13, &date );
    Delay_ms ( 1 );
    
    if ( time.sec != new_sec ) 
	{
        log_printf( &logger, "  Date      : %.2d-%.2d-%.2d\r\n", ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
        log_printf( &logger, "  Time      : %.2d:%.2d:%.2d\r\n", ( uint16_t ) time.hours, ( uint16_t ) time.min, ( uint16_t ) time.sec );
        log_printf( &logger, "- - - - - - - - - - - -\r\n" );
        new_sec = time.sec;
        Delay_ms ( 1 );
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
