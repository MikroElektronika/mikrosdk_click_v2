
---
# GNSS 13 click

> GNSS 13 Click is a compact add-on board that provides positioning, navigation, and timing services. This board features the LG77LICMD, a global-region standard-precision GNSS module from Quectel Wireless Solutions. This module utilizes concurrent reception of up to three GNSS systems (GPS, GLONASS (or BeiDou), and Galileo), maximizing position availability, especially under challenging conditions such as deep urban canyons. By combining EASY™ (Embedded Assist System), an advanced AGNSS feature, with GLP (GNSS Low Power), a low-power mode, the LG77LICMD module achieves high performance, low power consumption, and fully meets industrial standards. It also has a configurable host interface, anti-jamming technology, and a multi-tone active interference canceller.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnss13_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gnss-13-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2023.
- **Type**          : UART/I2C type


# Software Support

We provide a library for the GNSS 13 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GNSS 13 Click driver.

#### Standard key functions :

- `gnss13_cfg_setup` Config Object Initialization function.
```c
void gnss13_cfg_setup ( gnss13_cfg_t *cfg );
```

- `gnss13_init` Initialization function.
```c
err_t gnss13_init ( gnss13_t *ctx, gnss13_cfg_t *cfg );
```

#### Example key functions :

- `gnss13_generic_read` This function reads a desired number of data bytes from the module.
```c
err_t gnss13_generic_read ( gnss13_t *ctx, uint8_t *data_out, uint8_t len );
```

- `gnss13_parse_gngga` This function parses the GNGGA data from the read response buffer.
```c
err_t gnss13_parse_gngga ( uint8_t *rsp_buf, uint8_t gngga_element, uint8_t *element_data );
```

- `gnss13_clear_ring_buffers` This function clears UART tx and rx ring buffers.
```c
void gnss13_clear_ring_buffers ( gnss13_t *ctx );
```

## Example Description

> This example demonstrates the use of GNSS 13 click by reading and displaying the GPS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss13_cfg_t gnss13_cfg;  /**< Click config object. */

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
    gnss13_cfg_setup( &gnss13_cfg );
    GNSS13_MAP_MIKROBUS( gnss13_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gnss13_init( &gnss13, &gnss13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the received data, parses the GNGGA info from it, and once it receives the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    if ( GNSS13_OK == gnss13_process( &gnss13 ) )
    {
        if ( PROCESS_BUFFER_SIZE == app_buf_len )
        {
            gnss13_parser_application( &gnss13, app_buf );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS13

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
