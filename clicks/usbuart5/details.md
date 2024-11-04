
---
# USB UART 5 Click

> USB UART 5 Click is a compact add-on board with a general-purpose USB to UART serial interface. This board features the CP2110, a highly-integrated USB-to-UART bridge controller from Silicon Labs. The CP2110 uses the standard USB HID device class, requiring no custom driver and a UART interface that implements all RS-232 signals, including control and hardware handshaking, so existing system firmware does not need to be modified. The UART capabilities of the CP2110 also include baud rate support from 300 to 1Mbps, hardware flow control, RS-485 support, and GPIO signals that are user-defined for status and control information.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/usbuart5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/usb-uart-5-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2023.
- **Type**          : UART type


# Software Support

We provide a library for the USB UART 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for USB UART 5 Click driver.

#### Standard key functions :

- `usbuart5_cfg_setup` Config Object Initialization function.
```c
void usbuart5_cfg_setup ( usbuart5_cfg_t *cfg );
```

- `usbuart5_init` Initialization function.
```c
err_t usbuart5_init ( usbuart5_t *ctx, usbuart5_cfg_t *cfg );
```

- `usbuart5_default_cfg` Click Default Configuration function.
```c
void usbuart5_default_cfg ( usbuart5_t *ctx );
```

#### Example key functions :

- `usbuart5_generic_write`  USB UART 5 data writing function.
```c
err_t usbuart5_generic_write ( usbuart5_t *ctx, char *data_in, uint16_t len )
```

- `usbuart5_generic_read` USB UART 5 data reading function.
```c
err_t usbuart5_generic_read ( usbuart5_t *ctx, char *data_out, uint16_t len );
```

- `usbuart5_reset_device` USB UART 5 reset the device function.
```c
void usbuart5_reset_device ( usbuart5_t *ctx );
```

## Example Description

> This example reads and processes data from USB UART 5 Click board™.
> The library initializes and defines the UART bus drivers 
> to transmit or receive data.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver, wake-up module, and performs the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbuart5_cfg_t usbuart5_cfg;  /**< Click config object. */

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
    usbuart5_cfg_setup( &usbuart5_cfg );
    USBUART5_MAP_MIKROBUS( usbuart5_cfg, MIKROBUS_1 );
    if ( UART_ERROR == usbuart5_init( &usbuart5, &usbuart5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    usbuart5_default_cfg ( &usbuart5 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Any data which the host PC sends via HidUartExample 
> will be sent over USB to the Click board and then it will be read and 
> echoed back by the MCU to the PC where the terminal program will display it.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    char rx_data = 0;
    if ( usbuart5_generic_read ( &usbuart5, &rx_data, 1 ) )
    {
        if ( usbuart5_generic_write ( &usbuart5, &rx_data, 1 ) )
        {
            log_printf( &logger, "%c", rx_data );
        }
    }
}
```

## Note

> Make sure to download and install 
> CP2110/4 Software package for Windows/Mac/Linux on the host PC.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.USBUART5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
