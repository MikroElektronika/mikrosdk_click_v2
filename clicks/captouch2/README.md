
---
# Cap Touch 2 Click

> [Cap Touch 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2964) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2964&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> The demo application shows the button reading and checking.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CapTouch2

### Example Key Functions

- `captouch2_cfg_setup` Config Object Initialization function. 
```c
void captouch2_cfg_setup ( captouch2_cfg_t *cfg );
``` 
 
- `captouch2_init` Initialization function. 
```c
err_t captouch2_init ( captouch2_t *ctx, captouch2_cfg_t *cfg );
```

- `captouch2_default_cfg` Click Default Configuration function. 
```c
void captouch2_default_cfg ( captouch2_t *ctx );
```

- `captouch2_detect_touch` Touch Detect function. 
```c
void captouch2_detect_touch ( captouch2_t *ctx, uint8_t *in_sens );
```
 
- `captouch2_check_interrupt` Interrupt Check function. 
```c
uint8_t captouch2_check_interrupt ( captouch2_t *ctx );
```

- `captouch2_reset` Reset function. 
```c
void captouch2_reset ( captouch2_t *ctx );
```

### Application Init

> Configuring Clicks and log objects.
> Reset device and settings the Click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    captouch2_cfg_t cfg;

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

    captouch2_cfg_setup( &cfg );
    CAPTOUCH2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    captouch2_init( &captouch2, &cfg );

    captouch2_reset( &captouch2 );
    Delay_ms ( 200 );
    captouch2_default_cfg( &captouch2 );
    Delay_ms ( 100 );
    log_info( &logger, ">> Cap Touch 2 is initialized " );
}
```

### Application Task

> Calls function to check touch detection (is interrupt occured) and shows message on
> USB UART on which input touch is detected or on which input touch is released. 
> Also turns on LED on which linked input interrupt occured.

```c
void application_task ( void )
{
    uint8_t cnt;
    uint8_t sensor_results[ 6 ];

    captouch2_detect_touch( &captouch2, &sensor_results[ 0 ] );
    for ( cnt = 0; cnt < 6; cnt++ )
    {
        if ( sensor_results[ cnt ] == 1 )
        {
            log_printf( &logger, "Input %d is touchedr\r\n", cnt + 1 );
        }
        else if ( sensor_results[ cnt ] == 2 )
        {
            log_printf( &logger, "Input %d is released\r\n", cnt + 1 );
        }
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
