
---
# USB MUX click

> USB MUX Click is a compact add-on board with a high-bandwidth switch designed for switching and isolating high-speed USB 2.0 signals in systems with limited USB I/Os. This board features the TS3USB30E, a USB 2.0 1:2 multiplexer/demultiplexer switch with a single enable from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/usbmux_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/usb-mux-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the USB MUX Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for USB MUX Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of the USB MUX Click board.
  This driver provides functions for device configurations 
  and for the selection of the output.

**The demo application is composed of two sections :**

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


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.USBMUX

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
