
---
# USB UART ISO click

> USB UART ISO Click is a compact add-on board that offers a completely isolated differential pair of lines of the USB physical interface. This board features the ISOUSB111, a full/low-speed isolated USB repeater from Texas Instruments. It is a USB 2.0-compliant device that supports low-speed (1.5Mbps) and full-speed (12Mbps) signaling, USB On-The-Go (OtG), and Type-C Dual Role Port (DRP). In addition, this Click board™ comes with the FT232R, a USB UART IC from FTDI, making it a complete USB-to-UART isolated solution.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/usbuartiso_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/usb-uart-iso-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2023.
- **Type**          : UART type


# Software Support

We provide a library for the USB UART ISO Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for USB UART ISO Click driver.

#### Standard key functions :

- `usbuartiso_cfg_setup` Config Object Initialization function.
```c
void usbuartiso_cfg_setup ( usbuartiso_cfg_t *cfg );
```

- `usbuartiso_init` Initialization function.
```c
err_t usbuartiso_init ( usbuartiso_t *ctx, usbuartiso_cfg_t *cfg );
```

- `usbuartiso_default_cfg` Click Default Configuration function.
```c
void usbuartiso_default_cfg ( usbuartiso_t *ctx );
```

#### Example key functions :

- `usbuartiso_generic_write` USB UART ISO data writing function.
```c
err_t usbuartiso_generic_write ( usbuartiso_t *ctx, uint8_t *data_in, uint16_t len );
```

- `usbuartiso_generic_read` USB UART ISO data reading function.
```c
err_t usbuartiso_generic_read ( usbuartiso_t *ctx, uint8_t *data_out, uint16_t len );
```

## Example Description

> This example demonstrates the use of USB UART ISO click board by processing
> the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbuartiso_cfg_t usbuartiso_cfg;  /**< Click config object. */

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
    usbuartiso_cfg_setup( &usbuartiso_cfg );
    USBUARTISO_MAP_MIKROBUS( usbuartiso_cfg, MIKROBUS_1 );
    if ( UART_ERROR == usbuartiso_init( &usbuartiso, &usbuartiso_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    usbuartiso_default_cfg ( &usbuartiso );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Any data which the host PC sends via UART Terminal
> will be sent over USB to the click board and then it will be read and 
> echoed back by the MCU to the PC where the terminal program will display it.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    char rx_data = 0;
    if ( usbuartiso_generic_read ( &usbuartiso, &rx_data, 1 ) )
    {
        if ( usbuartiso_generic_write ( &usbuartiso, &rx_data, 1 ) )
        {
            log_printf( &logger, "%c", rx_data );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.USBUARTISO

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
