
---
# RTC 26 Click

> [RTC 26 Click](https://www.mikroe.com/?pid_product=MIKROE-6920) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6920&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Mar 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the RTC 26 Click board by initializing
the device and setting up the current time and date and alarm time. It continuously
reads and displays the updated time, date and temperature every second using the FOUT pin
and checks if the alarm condition is met.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RTC26

### Example Key Functions

- `rtc26_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void rtc26_cfg_setup ( rtc26_cfg_t *cfg );
```

- `rtc26_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t rtc26_init ( rtc26_t *ctx, rtc26_cfg_t *cfg );
```

- `rtc26_default_cfg` This function executes a default configuration of RTC 26 Click board.
```c
err_t rtc26_default_cfg ( rtc26_t *ctx );
```

- `rtc26_set_time` This function sets the desired time (hours, minutes, seconds) in the RTC.
```c
err_t rtc26_set_time ( rtc26_t *ctx, rtc26_time_t rtc_time );
```

- `rtc26_set_date` This function sets the desired date (day, day of week, month, year) in the RTC.
```c
err_t rtc26_set_date ( rtc26_t *ctx, rtc26_date_t rtc_date );
```

- `rtc26_set_alarm` This function sets the desired alarm time (hours, minutes, day/week) in the RTC.
```c
err_t rtc26_set_alarm ( rtc26_t *ctx, rtc26_alarm_t rtc_alarm );
```

### Application Init

> Initializes the logger and the RTC 26 Click driver, applies the default configuration,
and sets the starting time and date and alarm.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc26_cfg_t rtc26_cfg;  /**< Click config object. */

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
    rtc26_cfg_setup( &rtc26_cfg );
    RTC26_MAP_MIKROBUS( rtc26_cfg, MIKROBUS_POSITION_RTC26 );
    if ( I2C_MASTER_ERROR == rtc26_init( &rtc26, &rtc26_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTC26_ERROR == rtc26_default_cfg ( &rtc26 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    /* Set initial time: 23:59:50 */
    time.hour   = 23;
    time.minute = 59;
    time.second = 50;
    if ( RTC26_OK == rtc26_set_time( &rtc26, time ) )
    {
        log_printf( &logger, "  Set time : %.2d:%.2d:%.2d\r\n",
                    ( uint16_t ) time.hour,
                    ( uint16_t ) time.minute,
                    ( uint16_t ) time.second );
    }

    /* Set initial date: Thursday, 31.12.2026 */
    date.day_of_week = RTC26_WEEK_THURSDAY;
    date.day   = 31;
    date.month = 12;
    date.year  = 26;
    if ( RTC26_OK == rtc26_set_date( &rtc26, date ) )
    {
        log_printf( &logger, "Set date : %.2d-%.2d-20%.2d\r\n",
                    ( uint16_t ) date.day,
                    ( uint16_t ) date.month,
                    ( uint16_t ) date.year );
    }

    /* Configure alarm: trigger at 00:00 on Friday.
     * All three alarm fields enabled (AE=0): minute, hour, day-of-week. */
    alarm.minute      = 0;
    alarm.hour        = 0;
    alarm.day_week    = RTC26_WEEK_FRIDAY;
    alarm.minute_en   = RTC26_ALARM_ENABLE;
    alarm.hour_en     = RTC26_ALARM_ENABLE;
    alarm.day_week_en = RTC26_ALARM_ENABLE;

    if ( RTC26_OK == rtc26_set_alarm( &rtc26, alarm ) )
    {
        log_printf( &logger, "  Alarm set: Friday 00:00\r\n" );
    }

    /* Enable alarm interrupt (AIE) in control register.
     * Read-modify-write to preserve CSEL and other bits. */
    rtc26_generic_read( &rtc26, RTC26_REG_CONTROL, &ctrl_reg, 1 );
    ctrl_reg |= RTC26_CTRL_AIE;
    rtc26_generic_write( &rtc26, RTC26_REG_CONTROL, &ctrl_reg, 1 );

    log_printf( &logger, "---------------------\r\n" );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for a 1 Hz square wave signal and then reads and displays the current time, date 
and temperature and checks if the alarm condition is met.

```c
void application_task ( void )
{
    /* Wait for a rising edge on the FOUT pin. */
    while ( rtc26_get_out_pin( &rtc26 ) );
    while ( !rtc26_get_out_pin( &rtc26 ) );

    /* Read and display time */
    if ( RTC26_OK == rtc26_get_time( &rtc26, &time ) )
    {
        log_printf( &logger, "  Time : %.2d:%.2d:%.2d\r\n",
                    ( uint16_t ) time.hour,
                    ( uint16_t ) time.minute,
                    ( uint16_t ) time.second );
    }

    /* Read and display date */
    if ( RTC26_OK == rtc26_get_date( &rtc26, &date ) )
    {
        log_printf( &logger, "  Date : %.2d-%.2d-20%.2d ",
                    ( uint16_t ) date.day,
                    ( uint16_t ) date.month,
                    ( uint16_t ) date.year );
        display_day_of_week( );
    }

    /* Read and display temperature */
    if ( RTC26_OK == rtc26_get_temperature( &rtc26, &temperature ) )
    {
        log_printf( &logger, "  Temp  : %.2f degC\r\n", temperature );
    }

    log_printf( &logger, "- - - - - - - - - - -\r\n" );

    /* Poll INT pin for alarm an event */
    if ( !rtc26_get_int_pin( &rtc26 ) )
    {
        log_printf( &logger, ">>> ALARM TRIGGERED! Friday 00:00 <<<\r\n" );
        log_printf( &logger, "---------------------\r\n" );

        /* Clear AF flag to de-assert INT */
        rtc26_clear_flag( &rtc26, RTC26_FLAG_AF );
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
