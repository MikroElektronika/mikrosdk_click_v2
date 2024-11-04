
---
# GNSS Click

GNSS Click carries Quectel’s L86 GNSS module with a patch antenna along with an external antenna connector.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnss_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/gnss-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2022.
- **Type**          : UART type


# Software Support

We provide a library for the GNSS Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GNSS Click driver.

#### Standard key functions :

- `gnss_cfg_setup` Config Object Initialization function.
```c
void gnss_cfg_setup ( gnss_cfg_t *cfg );
```

- `gnss_init` Initialization function.
```c
err_t gnss_init ( gnss_t *ctx, gnss_cfg_t *cfg );
```

#### Example key functions :

- `gnss_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t gnss_generic_read ( gnss_t *ctx, char *data_out, uint16_t len );
```

- `gnss_clear_ring_buffers` This function clears UART tx and rx ring buffers.
```c
void gnss_clear_ring_buffers ( gnss_t *ctx );
```

- `gnss_parse_gpgga` This function parses the GPGGA data from the read response buffer.
```c
err_t gnss_parse_gpgga ( char *rsp_buf, uint8_t gpgga_element, char *element_data );
```

## Example Description

> This example demonstrates the use of GNSS Click by reading and displaying the GPS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss_cfg_t gnss_cfg;  /**< Click config object. */

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
    gnss_cfg_setup( &gnss_cfg );
    GNSS_MAP_MIKROBUS( gnss_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gnss_init( &gnss, &gnss_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the received data, parses the GPGGA info from it, and once it receives the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    if ( GNSS_OK == gnss_process( &gnss ) )
    {
        if ( PROCESS_BUFFER_SIZE == app_buf_len )
        {
            gnss_parser_application( &gnss, app_buf );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
