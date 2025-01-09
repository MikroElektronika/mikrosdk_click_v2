
---
# H-Bridge Driver Click

> [H-Bridge Driver Click](https://www.mikroe.com/?pid_product=MIKROE-4696) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4696&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This is an example that demonstrates the use of the H-Bridge Driver Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridgeDriver

### Example Key Functions

- `hbridgedriver_cfg_setup` Config Object Initialization function.
```c
void hbridgedriver_cfg_setup ( hbridgedriver_cfg_t *cfg );
```

- `hbridgedriver_init` Initialization function.
```c
err_t hbridgedriver_init ( hbridgedriver_t *ctx, hbridgedriver_cfg_t *cfg );
```

- `hbridgedriver_glo_enable` Global enable function.
```c
void hbridgedriver_glo_enable ( hbridgedriver_t *ctx, uint8_t state );
```

- `hbridgedriver_reverse` H-Bridge mode reverse function.
```c
void hbridgedriver_reverse ( hbridgedriver_t *ctx );
```

- `hbridgedriver_forward` H-Bridge mode forward function.
```c
void hbridgedriver_forward ( hbridgedriver_t *ctx );
```

### Application Init

> Initializes GPIO and LOG structures, and sets AN, RST, CS, PWM and INT pins as output and start to write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridgedriver_cfg_t hbridgedriver_cfg;  /**< Click config object. */

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
    hbridgedriver_cfg_setup( &hbridgedriver_cfg );
    HBRIDGEDRIVER_MAP_MIKROBUS( hbridgedriver_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == hbridgedriver_init( &hbridgedriver, &hbridgedriver_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    hbridgedriver_glo_enable( &hbridgedriver, HBRIDGEDRIVER_PROP_EN );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Demonstrates use of the H-Bridge Driver Click board by turning connected MOSFETs 
> gates high or low in order to drive the motor forward, in reverse, brake or coast.

```c
void application_task ( void ) 
{
    log_printf( &logger, "The motor turns forward! \r\n" );
    hbridgedriver_forward( &hbridgedriver );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "The motor brakes! \r\n" );
    hbridgedriver_braking( &hbridgedriver );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "The motor turns in reverse \r\n" );
    hbridgedriver_reverse( &hbridgedriver );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "The motor coasting \r\n" );
    hbridgedriver_coasting( &hbridgedriver );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
