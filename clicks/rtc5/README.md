
---
# RTC5 Click

> [RTC 5 Click](https://www.mikroe.com/?pid_product=MIKROE-1990) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1990&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> 
> This is a example which demonstrates the use of RTC 5 Click board.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc5

### Example Key Functions

- `rtc5_cfg_setup` Config Object Initialization function. 
```c
void rtc5_cfg_setup ( rtc5_cfg_t *cfg );
``` 
 
- `rtc5_init` Initialization function. 
```c
err_t rtc5_init ( rtc5_t *ctx, rtc5_cfg_t *cfg );
```

- `rtc5_default_cfg` Click Default Configuration function. 
```c
void rtc5_default_cfg ( rtc5_t *ctx );
```

- `rtc5_set_time` Set time hours, minutes and seconds function. 
```c
void rtc5_set_time ( rtc5_t *ctx, uint8_t time_hours, uint8_t time_min, uint8_t time_sec );
```
 
- `rtc5_set_date` Set date hours, minutes and seconds function. 
```c
void rtc5_set_date ( rtc5_t *ctx, uint8_t date_day, uint8_t date_month, uint16_t date_year );
```

- `rtc5_get_time_and_date` Get time and date function. 
```c
void rtc5_get_time_and_date ( rtc5_t *ctx, rtc5_timedate_t *timedate_data );
```

### Application Init

>
> Initializes GPIO, SPI and LOG structures, sets CS pin as output and INT pin as input.
> Initialization driver enable's - SPI, clear RTCC and SRAM memory, 
> sets starting time and date, enable counting and start write log.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc5_cfg_t cfg;

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
    log_printf( &logger, "- Application Init -\r\n" );

    //  Click initialization.

    rtc5_cfg_setup( &cfg );
    RTC5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc5_init( &rtc5, &cfg );
    
    rtc5_default_cfg ( &rtc5);
    Delay_ms ( 100 );
    
    rtc5_clear( &rtc5 );
    Delay_ms ( 100 );
    
    time_sec_new = 255;

    // Set Time: 17h, 59 min and 50 sec
    rtc5_set_time( &rtc5, 23, 59, 50 );
    
    // Set Day of the week : Wednesday
    rtc5_set_day_of_the_week( &rtc5, RTC5_DAY_OF_THE_WEEK_TUESDAY );
    
    // Set Date: 31 ( day ), 12 ( month ) and 2019 ( year )
    rtc5_set_date( &rtc5, 31, 12, 2019 );
    
    // Start counting
    rtc5_set_counting( &rtc5, 1 );
    Delay_ms ( 100 );

    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "    RTC 5  Click    \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    
}
```

### Application Task

>
> RTC 5 Click communicates with register via SPI 
> by write to register and read from register, display RTC time and date.
> 

```c
void application_task ( void )
{
    rtc5_get_time_and_date( &rtc5, &time_date_data );
    
    if ( time_sec_new != time_date_data.sec )
    {
        log_printf( &logger, " Time : %02d:%02d:%02d\r\n", time_date_data.hours, time_date_data.min, time_date_data.sec );
    
        display_log_day_of_the_week( time_date_data.w_day );
    
        log_printf( &logger, " Date : %02d.%02d.20%02d.\r\n", time_date_data.day, time_date_data.month, time_date_data.year );
        log_printf( &logger, "--------------------\r\n" );
    
        time_sec_new = time_date_data.sec;
    }
}
```

### Note

> 
> Additional Functions: 
> void display_log_day_of_the_week( uint8_t w_day ) - Write day of the week log.
> 

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
