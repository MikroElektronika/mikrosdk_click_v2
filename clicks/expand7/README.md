
---
# Expand 7 Click

> [Expand 7 Click](https://www.mikroe.com/?pid_product=MIKROE-4244) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4244&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the EXPAND 7 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand7

### Example Key Functions

- `expand7_cfg_setup` Config Object Initialization function.
```c
void expand7_cfg_setup ( expand7_cfg_t *cfg ); 
```

- `expand7_init` Initialization function.
```c
err_t expand7_init ( expand7_t *ctx, expand7_cfg_t *cfg );
```

- `expand7_reset` Reset function
```c
void expand7_reset ( expand7_t *ctx );
```

- `expand7_write_all` Set all OUTPUT pins' logic levels function
```c
void expand7_write_all ( expand7_t *ctx, uint8_t value );
```

- `expand7_write_pin` Set a single OUTPUT pin's logic level function
```c
void expand7_write_pin ( expand7_t *ctx, uint8_t pin, uint8_t pin_val );
```

### Application Init

> Initalizes I2C driver and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    expand7_cfg_t cfg;

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
    expand7_cfg_setup( &cfg );
    EXPAND7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand7_init( &expand7, &cfg );
    Delay_ms ( 100 );
    
    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "   EXPAND 7 Click   \r\n" );
    log_printf( &logger, "------------------- \r\n" );
}
```

### Application Task

> This example shows the capabilities of the EXPAND 7 Click by toggling each of the 40 available pins.

```c
void application_task ( void )
{
    expand7_write_all ( &expand7, 0xFF );
    log_printf( &logger, "All pins set to HIGH logic level!\r\n" );
    log_printf( &logger, "---------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    for ( uint8_t pin_num = 0; pin_num < 40; pin_num++ )
    {
        expand7_write_pin( &expand7, pin_num, EXPAND7_LOW );
        log_printf( &logger, "Pin %u is set to LOW logic level!\r\n", ( uint16_t ) pin_num );
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
