
---
# GNSS ZOE Click

GNSS ZOE Click is a evaluation board for ultra small ZOE-M8Q GNSS SiP receiver from u-blox. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnsszoe_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/gnss-zoe-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : UART/I2C/SPI type


# Software Support

We provide a library for the GNSS ZOE Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GNSS ZOE Click driver.

#### Standard key functions :

- `gnsszoe_cfg_setup` Config Object Initialization function.
```c
void gnsszoe_cfg_setup ( gnsszoe_cfg_t *cfg );
```

- `gnsszoe_init` Initialization function.
```c
err_t gnsszoe_init ( gnsszoe_t *ctx, gnsszoe_cfg_t *cfg );
```

- `gnsszoe_default_cfg` Click Default Configuration function.
```c
err_t gnsszoe_default_cfg ( gnsszoe_t *ctx );
```

#### Example key functions :

- `gnsszoe_reset_device` This function resets the device by toggling the RST pin.
```c
void gnsszoe_reset_device ( gnsszoe_t *ctx );
```

- `gnsszoe_generic_read` This function reads a desired number of data bytes from the module.
```c
err_t gnsszoe_generic_read ( gnsszoe_t *ctx, uint8_t *data_out, uint8_t len );
```

- `gnsszoe_parse_gngga` This function parses the GNGGA data from the read response buffer.
```c
err_t gnsszoe_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );
```

## Example Description

> This example demonstrates the use of GNSS ZOE Click by reading and displaying the GNSS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and resets the Click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnsszoe_cfg_t gnsszoe_cfg;  /**< Click config object. */

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
    gnsszoe_cfg_setup( &gnsszoe_cfg );
    GNSSZOE_MAP_MIKROBUS( gnsszoe_cfg, MIKROBUS_1 );
    err_t init_flag = gnsszoe_init( &gnsszoe, &gnsszoe_cfg );
    if ( ( UART_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
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
    gnsszoe_process( &gnsszoe );
    if ( app_buf_len > ( sizeof ( GNSSZOE_RSP_GNGGA ) + GNSSZOE_GNGGA_ELEMENT_SIZE ) ) 
    {
        gnsszoe_parser_application( app_buf );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSSZOE

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
