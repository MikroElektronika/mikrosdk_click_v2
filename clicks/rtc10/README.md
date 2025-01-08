
---
# Rtc 10 Click

> [RTC 10 Click](https://www.mikroe.com/?pid_product=MIKROE-3770) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3770&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application is a real-time clock module. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtc10

### Example Key Functions

- `rtc10_cfg_setup` Config Object Initialization function. 
```c
void rtc10_cfg_setup ( rtc10_cfg_t *cfg );
``` 
 
- `rtc10_init` Initialization function. 
```c
err_t rtc10_init ( rtc10_t *ctx, rtc10_cfg_t *cfg );
```

- `rtc10_default_cfg` Click Default Configuration function. 
```c
void rtc10_default_cfg ( rtc10_t *ctx );
```

- `rtc10_generic_write` Generic write function. 
```c
oid rtc10_generic_write ( rtc10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```
 
- `rtc10_generic_read` Generic read function. 
```c
void rtc10_generic_read ( rtc10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

- `rtc10_hw_reset` Hardware reset function. 
```c
void rtc10_hw_reset ( rtc10_t *ctx );
```

### Application Init

> Initialization driver enable's - I2C, hardware reset, set start time and date, enable counting also, write log. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc10_cfg_t cfg;

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

    rtc10_cfg_setup( &cfg );
    RTC10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc10_init( &rtc10, &cfg );

    Delay_ms ( 1000 );
    
    sec_flag = 0xFF;

    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "  Hardware  Reset   \r\n" );
    rtc10_hw_reset(  &rtc10 );
    Delay_ms ( 1000 );

    // Set Time: 23h, 59 min and 50 sec
    rtc10_set_time(  &rtc10, 23, 59, 50 );
    Delay_ms ( 10 );

    // Set Date: 6 ( Day of the week: Saturday ), 31 ( day ), 8 ( month ) and 2019 ( year )
    rtc10_set_date(  &rtc10,  6, 31, 8, 2019 );
    Delay_ms ( 100 );

    log_printf( &logger, "-------------------  \r\n" );
    log_printf( &logger, "  Enable Counting  \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "     Start RTC      \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    rtc10_enable_counting(  &rtc10 );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example which demonstrates the use of RTC 10 Click board.
  RTC 10 Click communicates with register via I2C interface,
  set time and date, enable counting and display time and date values,
  also, display temperature value for every 1 sec.
  Results are being sent to the Usart Terminal where you can track their changes.
  All data logs write on Usart Terminal changes for every 1 sec. 

```c
void application_task ( void )
{
    uint8_t i;
    uint8_t time_hours = 0;
    uint8_t time_minutes = 0;
    uint8_t time_seconds = 0;

    uint8_t day_of_the_week = 0;
    uint8_t date_day = 0;
    uint8_t date_month = 0;
    uint8_t date_year = 0;
    
    float temperature;
    
    rtc10_get_time( &rtc10, &time_hours, &time_minutes, &time_seconds );
    Delay_ms ( 100 );

    rtc10_get_date( &rtc10, &day_of_the_week, &date_day, &date_month, &date_year );
    Delay_ms ( 100 );

    if ( sec_flag !=  time_seconds )
    {
        log_printf( &logger, " \r\n\n Time: %u:%u:%u  ", (uint16_t)time_hours, (uint16_t)time_minutes, (uint16_t)time_seconds );
        
        log_printf( &logger, "Date: %u. %u. 20%u. ", (uint16_t)date_day, (uint16_t)date_month, (uint16_t)date_year );
        display_day_of_the_week( day_of_the_week );
        
        if ( time_seconds == 0 )
        {
            temperature = rtc10_get_temperature( &rtc10 );

            log_printf( &logger, "\r\n\n Temp.:%.2f C", temperature);
        }
        log_printf( &logger, "--------------------------------------------" );

        sec_flag =  time_seconds;
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
