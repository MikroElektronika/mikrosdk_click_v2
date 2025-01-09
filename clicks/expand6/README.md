
---
# Expand 6 Click

> [Expand 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4243) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4243&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of EXPAND 6 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand6

### Example Key Functions

- `expand6_cfg_setup` Config Object Initialization function. 
```c
void expand6_cfg_setup ( expand6_cfg_t *cfg );
``` 
 
- `expand6_init` Initialization function. 
```c
err_t expand6_init ( expand6_t *ctx, expand6_cfg_t *cfg );
```

- `expand6_write_port` Set all OUTPUT pins' logic levels in one port function. 
```c
void expand6_write_port ( expand6_t *ctx, uint8_t port, uint8_t value );
```
 
- `expand6_reset` Reset function. 
```c
void expand6_reset ( expand6_t *ctx );
```

- `expand6_write_pin` Set a single OUTPUT pin's logic level function. 
```c
void expand6_write_pin ( expand6_t *ctx, uint16_t pin, uint8_t pin_val );
```

### Application Init

> Initalizes I2C driver and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    expand6_cfg_t cfg;

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

    expand6_cfg_setup( &cfg );
    EXPAND6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand6_init( &expand6, &cfg );

    expand6_reset ( &expand6 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "   EXPAND 6 Click   \r\n" );
    log_printf( &logger, "------------------- \r\n" );
}
```

### Application Task

> This example shows the capabilities of the EXPAND 6 Click by toggling each of the 20 available pins.

```c
void application_task ( void )
{
    expand6_write_port( &expand6, EXPAND6_PORT_0, 0xFF );
    expand6_write_port( &expand6, EXPAND6_PORT_1, 0xFF );
    expand6_write_port( &expand6, EXPAND6_PORT_2, 0xFF );
    
    log_printf( &logger, "All pins set to HIGH logic level!\r\n" );
    log_printf( &logger, "---------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    for ( pin_num = 0; pin_num < 20; pin_num++ )
    {
        expand6_write_pin( &expand6, pin_num, EXPAND6_LOW );
        log_printf( &logger, "Pin %u is set to LOW logic level!\r\n", ( uint16_t) pin_num );
        Delay_ms ( 300 );
    }

    log_printf( &logger, "---------------------------------\r\n" );
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
