
---
# USB MUX Click

> [USB MUX Click](https://www.mikroe.com/?pid_product=MIKROE-5748) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5748&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the USB MUX Click board.
  This driver provides functions for device configurations 
  and for the selection of the output.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.USBMUX

### Example Key Functions

- `usbmux_cfg_setup` Config Object Initialization function.
```c
void usbmux_cfg_setup ( usbmux_cfg_t *cfg );
```

- `usbmux_init` Initialization function.
```c
err_t usbmux_init ( usbmux_t *ctx, usbmux_cfg_t *cfg );
```

- `usbmux_default_cfg` Click Default Configuration function.
```c
void usbmux_default_cfg ( usbmux_t *ctx );
```

- `usbmux_set_oe_pin` USB MUX set OE pin output function.
```c
void usbmux_set_oe_pin ( usbmux_t *ctx, uint8_t pin_state );
```

- `usbmux_enable_output` USB MUX enable output function.
```c
void usbmux_enable_output ( usbmux_t *ctx );
```

- `usbmux_set_output` USB MUX select output function.
```c
void usbmux_set_output ( usbmux_t *ctx, uint8_t out_sel );
```

### Application Init

> Initialization of the log UART, performing default configuration which disables the output.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbmux_cfg_t usbmux_cfg;  /**< Click config object. */

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
    usbmux_cfg_setup( &usbmux_cfg );
    USBMUX_MAP_MIKROBUS( usbmux_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == usbmux_init( &usbmux, &usbmux_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    usbmux_default_cfg( &usbmux );
    
    log_info( &logger, " Application Task " );
    display_selection( );
}
```

### Application Task

> Reading user input from UART Terminal and using it for the selection of the output of 
  disabling output of the USB MUX Click board.

```c
void application_task ( void ) 
{
    static char index;
    
    if ( 1 == log_read( &logger, &index, 1 ) ) 
    {
        switch ( index )
        {
            case ( '0' ):
            {
                log_printf( &logger, " Turning output off. \r\n" );
                usbmux_disable_output( &usbmux );
                break;
            }
            case ( '1' ):
            {
                log_printf( &logger, " USB1 Enabled and selected. \r\n" );
                usbmux_set_output( &usbmux, USBMUX_USB1_SELECT );
                usbmux_enable_output( &usbmux );
                break;
            }
            case ( '2' ):
            {
                log_printf( &logger, " USB2 Enabled and selected. \r\n" );
                usbmux_set_output( &usbmux, USBMUX_USB2_SELECT );
                usbmux_enable_output( &usbmux );
                break;
            }
            default:
            {
                display_selection( );
            }
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
