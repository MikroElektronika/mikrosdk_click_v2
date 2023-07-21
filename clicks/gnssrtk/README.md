\mainpage Main Page

---
# GNSS RTK click

> GNSS RTK Click is a compact add-on board used to enhance the precision of position data derived from satellite-based positioning systems. This board features the ZED-F9P, a multi-band GNSS module with integrated multi-band Real Time Kinematics (RTK) technology offering centimeter-level accuracy from U-blox. This module concurrently uses GNSS signals from all four GNSS constellations (GPS, GLONASS, Galileo, and BeiDou), and provides multi-band RTK with fast convergence times, reliable performance, and easy integration. It also includes moving base support, allowing both base and rover to move while computing a centimeter-level accurate position between them.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnssrtk_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gnss-rtk-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2023.
- **Type**          : UART/I2C/SPI type


# Software Support

We provide a library for the GNSS RTK Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GNSS RTK Click driver.

#### Standard key functions :

- `gnssrtk_cfg_setup` Config Object Initialization function.
```c
void gnssrtk_cfg_setup ( gnssrtk_cfg_t *cfg );
```

- `gnssrtk_init` Initialization function.
```c
err_t gnssrtk_init ( gnssrtk_t *ctx, gnssrtk_cfg_t *cfg );
```

- `gnssrtk_default_cfg` Click Default Configuration function.
```c
err_t gnssrtk_default_cfg ( gnssrtk_t *ctx );
```

#### Example key functions :

- `gnssrtk_reset_device` This function resets the device by toggling the RST pin.
```c
void gnssrtk_reset_device ( gnssrtk_t *ctx );
```

- `gnssrtk_generic_read` This function reads a desired number of data bytes from the module.
```c
err_t gnssrtk_generic_read ( gnssrtk_t *ctx, uint8_t *data_out, uint8_t len );
```

- `gnssrtk_parse_gngga` This function parses the GNGGA data from the read response buffer.
```c
err_t gnssrtk_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );
```

## Example Description

> This example demonstrates the use of GNSS RTK click by reading and displaying the GNSS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and resets the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnssrtk_cfg_t gnssrtk_cfg;  /**< Click config object. */

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
    gnssrtk_cfg_setup( &gnssrtk_cfg );
    GNSSRTK_MAP_MIKROBUS( gnssrtk_cfg, MIKROBUS_1 );
    err_t init_flag = gnssrtk_init( &gnssrtk, &gnssrtk_cfg );
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
    gnssrtk_process( &gnssrtk );
    if ( app_buf_len > ( sizeof ( GNSSRTK_RSP_GNGGA ) + GNSSRTK_GNGGA_ELEMENT_SIZE ) ) 
    {
        gnssrtk_parser_application( app_buf );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSSRTK

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
