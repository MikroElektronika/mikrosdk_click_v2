\mainpage Main Page

---
# GNSS RTK 2 click

> GNSS RTK 2 Click is a compact add-on board used to enhance the precision of position data derived from satellite-based positioning systems. This board features the ZED-F9R, a multi-band professional-grade GNSS module with integrated multi-band Real Time Kinematics (RTK) technology offering centimeter-level accuracy from u-blox. This module concurrently uses GNSS signals from all four GNSS constellations (GPS/QZSS, GLONASS, Galileo, and BeiDou) and provides a reliable multi-band RTK turnkey solution with up to 30Hz real-time position update rate and full GNSS carrier raw data.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnssrtk2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gnss-rtk-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : UART/I2C/SPI type


# Software Support

We provide a library for the GNSS RTK 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GNSS RTK 2 Click driver.

#### Standard key functions :

- `gnssrtk2_cfg_setup` Config Object Initialization function.
```c
void gnssrtk2_cfg_setup ( gnssrtk2_cfg_t *cfg );
```

- `gnssrtk2_init` Initialization function.
```c
err_t gnssrtk2_init ( gnssrtk2_t *ctx, gnssrtk2_cfg_t *cfg );
```

- `gnssrtk2_default_cfg` Click Default Configuration function.
```c
err_t gnssrtk2_default_cfg ( gnssrtk2_t *ctx );
```

#### Example key functions :

- `gnssrtk2_reset_device` This function resets the device by toggling the RST pin.
```c
void gnssrtk2_reset_device ( gnssrtk2_t *ctx );
```

- `gnssrtk2_generic_read` This function reads a desired number of data bytes from the module.
```c
err_t gnssrtk2_generic_read ( gnssrtk2_t *ctx, uint8_t *data_out, uint8_t len );
```

- `gnssrtk2_parse_gngga` This function parses the GNGGA data from the read response buffer.
```c
err_t gnssrtk2_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );
```

## Example Description

> This example demonstrates the use of GNSS RTK 2 click by reading and displaying the GNSS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and resets the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnssrtk2_cfg_t gnssrtk2_cfg;  /**< Click config object. */

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
    gnssrtk2_cfg_setup( &gnssrtk2_cfg );
    GNSSRTK2_MAP_MIKROBUS( gnssrtk2_cfg, MIKROBUS_1 );
    err_t init_flag = gnssrtk2_init( &gnssrtk2, &gnssrtk2_cfg );
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
    gnssrtk2_process( &gnssrtk2 );
    if ( app_buf_len > ( sizeof ( GNSSRTK2_RSP_GNGGA ) + GNSSRTK2_GNGGA_ELEMENT_SIZE ) ) 
    {
        gnssrtk2_parser_application( app_buf );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSSRTK2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
