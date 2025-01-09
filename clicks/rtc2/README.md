
---
# RTC2 Click

> [RTC 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2063) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2063&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application give time and day information. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc2

### Example Key Functions

- `rtc2_cfg_setup` Config Object Initialization function. 
```c
void rtc2_cfg_setup ( rtc2_cfg_t *cfg );
``` 
 
- `rtc2_init` Initialization function. 
```c
err_t rtc2_init ( rtc2_t *ctx, rtc2_cfg_t *cfg );
```

- `rtc2_read_byte` Generic read byte of data function. 
```c
uint8_t rtc2_read_byte ( rtc2_t *ctx, uint8_t reg_address );
```
 
- `rtc2_write_byte` Generic write byte of data function. 
```c
void rtc2_write_byte ( rtc2_t *ctx, uint8_t reg_address, uint8_t write_data );
```

- `rtc2_enable_counting` Enable counting function. 
```c
void rtc2_enable_counting ( rtc2_t *ctx );
```

### Application Init

> Initialization driver enable's - I2C,set start time and date, enable counting and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc2_cfg_t cfg;

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

    rtc2_cfg_setup( &cfg );
    RTC2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc2_init( &rtc2, &cfg );

    rtc2_set_time( &rtc2, 23, 59, 50 );
    rtc2_set_date( &rtc2, 1, 31, 12, 2018 );
    rtc2_enable_counting( &rtc2 );
}
```

### Application Task

> This is a example which demonstrates the use of RTC 2 Click board.
    RTC 2 Click communicates with register via I2C by write to register and read from register,
    set time and date, get time and date, enable and disable counting
    and set frequency by write configuration register.
    Results are being sent to the Usart Terminal where you can track their changes.
    All data logs write on usb uart changes for every 1 sec.

```c
void application_task ( void )
{
    rtc2_get_time( &rtc2, &time_hours, &time_minutes, &time_seconds );

    rtc2_get_date( &rtc2, &day_of_the_week, &date_day, &date_month, &date_year );

    if ( time_seconds_new !=  time_seconds )
    {
        log_printf( &logger, " Time : " );

        display_log_uart( time_hours );
        log_printf( &logger, ":" );

        display_log_uart( time_minutes );
        log_printf( &logger, ":" );

        display_log_uart( time_seconds );
        log_printf( &logger, "" );

        display_day_of_the_week( day_of_the_week );

        log_printf( &logger, " Date: " );

        display_log_uart( date_day );
        log_printf( &logger, "." );

        display_log_uart( date_month );
        log_printf( &logger, "." );

        log_printf( &logger, "20" );

        display_log_uart( date_year );
        log_printf( &logger, "." );

        log_printf( &logger, "-------------------" );

        time_seconds_new =  time_seconds;
    }
}
```

### Note

> Additional Functions :

 - void displayDayOfTheWeek( uint8_t dayOfTheWeek ) - Write day of the week log on USART terminal.
 - void displayLogUart( uint8_t value ) - Write the value ( time or date ) of a two-digit number.

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
