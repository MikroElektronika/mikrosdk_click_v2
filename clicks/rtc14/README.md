
---
# RTC 14 Click

> [RTC 14 Click](https://www.mikroe.com/?pid_product=MIKROE-4799) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4799&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This is an example that demonstrates the use of the RTC 14 Click board&trade;.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC14

### Example Key Functions

- `rtc14_cfg_setup` Config Object Initialization function.
```c
void rtc14_cfg_setup ( rtc14_cfg_t *cfg );
```

- `rtc14_init` Initialization function.
```c
err_t rtc14_init ( rtc14_t *ctx, rtc14_cfg_t *cfg );
```

- `rtc14_default_cfg` Click Default Configuration function.
```c
err_t rtc14_default_cfg ( rtc14_t *ctx );
```

- `rtc14_get_time` RTC 14 get time function.
```c
err_t rtc14_get_time ( rtc14_t *ctx, rtc14_time_t *rtc_time );
```

- `rtc14_set_time` RTC 14 set time function.
```c
err_t rtc14_set_time ( rtc14_t *ctx, rtc14_time_t rtc_time );
```

- `rtc14_get_date` RTC 14 get date function.
```c
err_t rtc14_get_date ( rtc14_t *ctx, rtc14_date_t *rtc_date );
```

### Application Init

> Initialization of I2C module, log UART and additional pins.
> After driver initialization and default settings,
> the app set the time to 11:59:50 PM ( 12-hour format ) 
> and set date to Thursday 05.08.2021.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    rtc14_cfg_t rtc14_cfg;  /**< Click config object. */

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
    rtc14_cfg_setup( &rtc14_cfg );
    RTC14_MAP_MIKROBUS( rtc14_cfg, MIKROBUS_1 );
    err_t init_flag = rtc14_init( &rtc14, &rtc14_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    rtc14_default_cfg ( &rtc14 );
    Delay_ms ( 100 );
    
    time.hours_format = RTC14_SET_HOURS_FORMAT_12;
    time.am_pm = RTC14_SET_HOURS_FORMAT_12_PM;
    time.hours = 11;
    time.min = 59;
    time.sec = 50;
    rtc14_set_time( &rtc14, time );
    Delay_ms ( 100 );
    
    date.day_of_week = RTC14_DW_THURSDAY;
    date.day = 5;
    date.month = 8;
    date.year = 21;
    rtc14_set_date( &rtc14, date );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "- - - - - - - - - - -\r\n" );
}
```

### Application Task

> This is an example that shows the use of a RTC 14 Click board&trade;.
> In this example, we read and display the current time ( AM or PM ) 
> and date ( day of the week ), which we also previously set.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB changes every 1 sec.

```c
void application_task ( void ) 
{    
    rtc14_get_time( &rtc14, &time );
    Delay_ms ( 1 );
    rtc14_get_date( &rtc14, &date );
    Delay_ms ( 1 );
    
    if ( time.sec != new_sec ) 
    {       
        log_printf( &logger, "  Date : %.2d-%.2d-%.2d ", ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
        display_day_of_week( );
        log_printf( &logger, "%cM\r\n", ( time.am_pm == RTC14_SET_HOURS_FORMAT_12_PM ? 'P' : 'A' ) );
        log_printf( &logger, "- - - - - - - - - - -\r\n" );
        new_sec = time.sec;
        Delay_ms ( 1 );
    }
}
```

## Additional Function
- `display_day_of_week` The function displays the day of the week.
```c
static void display_day_of_week ( void );
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
