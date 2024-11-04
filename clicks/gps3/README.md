\mainpage Main Page
 
---
# GPS 3 Click

GPS3 Click carries Quectel’s L80 GPS module, a high-sensitivity ultra slim GPS module with a patch antenna.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gps3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/gps-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2022.
- **Type**          : UART type


# Software Support

We provide a library for the GPS 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GPS 3 Click driver.

#### Standard key functions :

- `gps3_cfg_setup` Config Object Initialization function.
```c
void gps3_cfg_setup ( gps3_cfg_t *cfg );
```

- `gps3_init` Initialization function.
```c
err_t gps3_init ( gps3_t *ctx, gps3_cfg_t *cfg );
```

#### Example key functions :

- `gps3_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t gps3_generic_read ( gps3_t *ctx, char *data_out, uint16_t len );
```

- `gps3_clear_ring_buffers` This function clears UART tx and rx ring buffers.
```c
void gps3_clear_ring_buffers ( gps3_t *ctx );
```

- `gps3_parse_gpgga` This function parses the GPGGA data from the read response buffer.
```c
err_t gps3_parse_gpgga ( char *rsp_buf, uint8_t gpgga_element, char *element_data );
```

## Example Description

> This example demonstrates the use of GPS 3 Click by reading and displaying the GPS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gps3_cfg_t gps3_cfg;  /**< Click config object. */

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
    gps3_cfg_setup( &gps3_cfg );
    GPS3_MAP_MIKROBUS( gps3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gps3_init( &gps3, &gps3_cfg ) ) 
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
    if ( GPS3_OK == gps3_process( &gps3 ) )
    {
        if ( PROCESS_BUFFER_SIZE == app_buf_len )
        {
            gps3_parser_application( &gps3, app_buf );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GPS3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
