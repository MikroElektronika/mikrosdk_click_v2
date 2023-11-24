
---
# GNSS 11 click

> GNSS 11 Click is a compact add-on board that provides fast positioning capability. This board features the EVA-M8M, a concurrent GNSS module from u-blox. The module provides a reception of GPS, GLONASS, Galileo, QZSS, SBAS, and BeiDou. It delivers high sensitivity and minimal acquisition times, with concurrent reception of up to three GNSS, achieved by a dual-frequency RF front-end architecture. This Click board™ makes the perfect solution for the development of both acquisition and tracking devices and represents an ideal product for automotive, consumer, and industrial tracking applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnss11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gnss-11-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2023.
- **Type**          : UART/I2C/SPI type


# Software Support

We provide a library for the GNSS 11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GNSS 11 Click driver.

#### Standard key functions :

- `gnss11_cfg_setup` Config Object Initialization function.
```c
void gnss11_cfg_setup ( gnss11_cfg_t *cfg );
```

- `gnss11_init` Initialization function.
```c
err_t gnss11_init ( gnss11_t *ctx, gnss11_cfg_t *cfg );
```

#### Example key functions :

- `gnss11_reset_device` This function resets the device by toggling the RST and ANT_ON pins.
```c
void gnss11_reset_device ( gnss11_t *ctx );
```

- `gnss11_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t gnss11_generic_read ( gnss11_t *ctx, uint8_t *data_out, uint16_t len );
```

- `gnss11_parse_gga` This function parses the GGA data from the read response buffer.
```c
err_t gnss11_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );
```

## Example Description

> This example demonstrates the use of GNSS 11 click by reading and displaying the GNSS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and resets the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss11_cfg_t gnss11_cfg;  /**< Click config object. */

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
    gnss11_cfg_setup( &gnss11_cfg );
    GNSS11_MAP_MIKROBUS( gnss11_cfg, MIKROBUS_1 );
    if ( GNSS11_OK != gnss11_init( &gnss11, &gnss11_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    gnss11_reset_device ( &gnss11 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the received data, parses the NMEA GGA info from it, and once it receives the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    gnss11_process( &gnss11 );
    if ( app_buf_len > ( sizeof ( GNSS11_RSP_GGA ) + GNSS11_GGA_ELEMENT_SIZE ) ) 
    {
        gnss11_parser_application( app_buf );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
