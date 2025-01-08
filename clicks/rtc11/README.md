
---
# RTC 11 Click

> [RTC 11 Click](https://www.mikroe.com/?pid_product=MIKROE-4288) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4288&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the RTC 11 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC11

### Example Key Functions

- `rtc11_cfg_setup` Config Object Initialization function.
```c
void rtc11_cfg_setup ( rtc11_cfg_t *cfg );
```

- `rtc11_init` Initialization function.
```c
err_t rtc11_init ( rtc11_t *ctx, rtc11_cfg_t *cfg );
```

- `rtc11_set_time` Set time hours, minutes and seconds function
```c
err_t rtc11_set_time ( rtc11_t *ctx, rtc11_time_t rtc_time );
```

- `rtc11_get_time` Get time hours, minutes and seconds function
```c
void rtc11_get_time ( rtc11_t *ctx, rtc11_time_t *rtc_time );
```

- `rtc11_set_date` Set date day of the week, day, month and year function
```c
err_t rtc11_set_date ( rtc11_t *ctx, rtc11_date_t rtc_date );
```

### Application Init

> Initalizes SPI, performs software reset, sets system time and date, and starts clocking system.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc11_cfg_t rtc11_cfg;  /**< Click config object. */

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

    rtc11_cfg_setup( &rtc11_cfg );
    RTC11_MAP_MIKROBUS( rtc11_cfg, MIKROBUS_1 );
    err_t init_flag  = rtc11_init( &rtc11, &rtc11_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger,"------------------------\r\n" );
    log_printf( &logger," Software reset \r\n" );
    rtc11_soft_rst( &rtc11 );
    Delay_ms ( 100 );
    
    time.hours = 23;
    time.min = 59;
    time.sec = 55;
    log_printf( &logger,"------------------------\r\n" );
    log_printf( &logger," Setting time: %.2d:%.2d:%.2d \r\n", ( uint16_t ) time.hours, ( uint16_t ) time.min, ( uint16_t ) time.sec );
    rtc11_set_time ( &rtc11, time );
    Delay_ms ( 100 );
    
    date.day_of_week = 0;
    date.day = 19;
    date.month = 7;
    date.year = 21;
    log_printf( &logger,"------------------------\r\n" );
    log_printf( &logger," Setting date: %.2d/%.2d/%.2d \r\n", ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    rtc11_set_date( &rtc11, date );
    Delay_ms ( 100 );
    
    rtc11_stp_sys_slk ( &rtc11, RTC11_PROP_DIS );
    log_info( &logger, " Application Task " );
    log_printf( &logger,"------------------------\r\n" );
}
```

### Application Task

> Demonstrates use of RTC 11 Click board by reading and displaying time and date via USART terminal.

```c
void application_task ( void ) 
{
    rtc11_get_time ( &rtc11, &time );
    Delay_ms ( 10 );
    rtc11_get_date ( &rtc11, &date );
    Delay_ms ( 10 );
    
    if ( sec_flag != time.sec ) {
        log_printf( &logger, " Date: " );
        disp_day_of_the_week( date.day_of_week );
        log_printf( &logger, " %.2d/%.2d/20%.2d \r\n", ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
        log_printf( &logger, " Time: %.2d:%.2d:%.2d \r\n", ( uint16_t ) time.hours, ( uint16_t ) time.min, ( uint16_t ) time.sec );
        log_printf( &logger,"--------------------------\r\n" );
    }
    sec_flag = time.sec;
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
