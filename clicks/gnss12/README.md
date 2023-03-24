\mainpage Main Page

---
# GNSS 12 click

> GNSS 12 Click is a compact add-on board that provides fast positioning capability. This board features the CAM-M8C, a professional-grade GNSS module built on the high-performing M8 GNSS engine from u-blox. This module utilizes concurrent reception of up to three GNSS systems (GPS/Galileo together with either BeiDou or GLONASS), offering high sensitivity and strong signal levels. Besides internal, the CAM-M8C can use an optional external active antenna. It has a configurable host interface, advanced jamming/spoofing detection, and provides outstanding positioning accuracy even in GNSS-hostile environments. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnss12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gnss-12-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2022.
- **Type**          : UART/I2C/SPI type


# Software Support

We provide a library for the GNSS 12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GNSS 12 Click driver.

#### Standard key functions :

- `gnss12_cfg_setup` Config Object Initialization function.
```c
void gnss12_cfg_setup ( gnss12_cfg_t *cfg );
```

- `gnss12_init` Initialization function.
```c
err_t gnss12_init ( gnss12_t *ctx, gnss12_cfg_t *cfg );
```

#### Example key functions :

- `gnss12_reset_device` This function resets the device by toggling the RST pin.
```c
void gnss12_reset_device ( gnss12_t *ctx );
```

- `gnss12_generic_read` This function reads a desired number of data bytes from the module.
```c
err_t gnss12_generic_read ( gnss12_t *ctx, uint8_t *data_out, uint8_t len );
```

- `gnss12_parse_gngga` This function parses the GNGGA data from the read response buffer.
```c
err_t gnss12_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );
```

## Example Description

> This example demonstrates the use of GNSS 12 click by reading and displaying the GNSS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and resets the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss12_cfg_t gnss12_cfg;  /**< Click config object. */

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
    gnss12_cfg_setup( &gnss12_cfg );
    GNSS12_MAP_MIKROBUS( gnss12_cfg, MIKROBUS_1 );
    err_t init_flag = gnss12_init( &gnss12, &gnss12_cfg );
    if ( ( UART_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    gnss12_reset_device ( &gnss12 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the received data, parses the GNGGA info from it, and once it receives the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    gnss12_process( &gnss12 );
    if ( app_buf_len > ( sizeof ( GNSS12_RSP_GNGGA ) + GNSS12_GNGGA_ELEMENT_SIZE ) ) 
    {
        gnss12_parser_application( app_buf );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
