
---
# Timer Click

> [Timer Click](https://www.mikroe.com/?pid_product=MIKROE-2333) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2333&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application is multifunctional 3-axis digital accelerometer that can also be configured as a 45-degree Tilt sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Timer

### Example Key Functions

- `timer_cfg_setup` Config Object Initialization function. 
```c
void timer_cfg_setup ( timer_cfg_t *cfg );
``` 
 
- `timer_init` Initialization function. 
```c
err_t timer_init ( timer_t *ctx, timer_cfg_t *cfg );
```

- `timer_get_etc_data` Get elapsed time counter (ETC) data function. 
```c
uint32_t timer_get_etc_data ( timer_t *ctx );
```
 
- `timer_get_etc_seconds` Get elapsed time counter (ETC) seconds function. 
```c
uint32_t timer_get_etc_seconds ( timer_t *ctx );
```

- `timer_get_time` Set elapsed time counter (ETC) time function. 
```c
void timer_get_time ( timer_t *ctx, uint16_t *time_days, uint8_t *time_hours, uint8_t *time_minutes, uint8_t *time_seconds );
```

### Application Init

> Initialization driver enable's - I2C,
> soft reset, sets ETC and EC start ( seconds ), hardwere reset and > start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    timer_cfg_t cfg;

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

    timer_cfg_setup( &cfg );
    TIMER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    timer_init( &timer, &cfg );
    Delay_ms ( 200 );

    log_printf( &logger, "   Driver  Init   \r\n" );
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "    Soft Reset    \r\n" );
    
    timer_soft_reset( &timer );
    Delay_ms ( 500 );
    
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "  Set ETC and EC  \r\n" );
    
    timer_set_etc_seconds( &timer, 86390 );
    timer_set_ec_seconds( &timer, 0 );
    
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "  Hardwere Reset  \r\n" );
    
    timer_hw_reset( &timer );
    Delay_ms ( 500 );
    
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "        ETC       \r\n" );
    log_printf( &logger, "------------------\r\n" );
}
```

### Application Task

> This is a example which demonstrates the use of Timer Click board.
> Timer Click communicates with register via I2C by write to 
> register and read from register,
> display time ( days, hours, minutes and seconds ) which we  
> received reading from the target register address of DS1682 total > elapsed time recorder.
> Results are being sent to the Usart Terminal where you can track  > their changes.
> All data logs write on usb uart changes for every 1 sec.

```c
void application_task ( )
{
    static uint8_t time_seconds_new = 0xFF;
    uint8_t time_hours;
    uint8_t time_minutes;
    uint8_t time_seconds;
    uint16_t time_days;

    timer_get_time( &timer, &time_days, &time_hours, &time_minutes, &time_seconds );
   
    if ( time_seconds_new != time_seconds )
    {
        log_printf
        ( 
            &logger, " %d days    %d:%d:%d \r\n", 
            time_days, 
            time_hours, 
            time_minutes, 
            time_seconds
        );
        log_printf( &logger, "------------------\r\n" );
        time_seconds_new = time_seconds;
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
