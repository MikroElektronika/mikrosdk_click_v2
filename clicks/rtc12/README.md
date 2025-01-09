
---
# RTC 12 Click

> [RTC 12 Click](https://www.mikroe.com/?pid_product=MIKROE-4697) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4697&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : May 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the RTC 12 Click board&trade;.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc12

### Example Key Functions

- `rtc12_cfg_setup` Config Object Initialization function.
```c
void rtc12_cfg_setup ( rtc12_cfg_t *cfg );
```

- `rtc12_init` Initialization function.
```c
err_t rtc12_init ( rtc12_t *ctx, rtc12_cfg_t *cfg );
```

- `rtc12_default_cfg` Click Default Configuration function.
```c
err_t rtc12_default_cfg ( rtc12_t *ctx );
```

- `rtc12_set_time` RTC 12 set time function.
```c
err_t rtc12_set_time ( rtc12_t *ctx, rtc12_time_t rtc_time );
```

- `rtc12_get_time` RTC 12 get time function.
```c
err_t rtc12_get_time ( rtc12_t *ctx, rtc12_time_t *rtc_time );
```

- `rtc12_get_date` RTC 12 get date function.
```c
err_t rtc12_get_date ( rtc12_t *ctx, rtc12_date_t *rtc_date );
```

### Application Init

> Initialization of SPI module, log UART and additional pins.
> After driver initialization and default settings,
> the app set the time to 23:59:50 and set the date to 27.05.'21.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    rtc12_cfg_t rtc12_cfg;   /**< Click config object. */

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

    rtc12_cfg_setup( &rtc12_cfg );
    RTC12_MAP_MIKROBUS( rtc12_cfg, MIKROBUS_1 );
    err_t init_flag  = rtc12_init( &rtc12, &rtc12_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    rtc12_default_cfg ( &rtc12 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    date.day_of_week = 4;
    date.day = 27;
    date.month = 5;
    date.year = 21;
    rtc12_set_date( &rtc12, date );
    Delay_ms ( 100 );
    
    time.hours = 23;
    time.min = 59;
    time.sec = 50;
    rtc12_set_time( &rtc12, time );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that shows the use of a RTC 12 Click board&trade;.
> In this example, we read and display the current time and date, 
> which we also previously set.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB changes every 1 sec.

```c
void application_task ( void ) 
{   
    rtc12_get_time( &rtc12, &time );
    Delay_ms ( 1 );
    rtc12_get_date( &rtc12, &date );
    Delay_ms ( 1 );
    
    if ( time.sec != new_sec ) {
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
