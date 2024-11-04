\mainpage Main Page

---
# GNSS RTK 3 DA Click

> GNSS RTK 3 Click is a compact add-on board that enhances the precision of position data derived from satellite-based positioning systems. This board features the LC29HDA, a dual-band, multi-castellation GNSS module from Quectel. This module supports the concurrent reception of all five global GNSS constellations: GPS, BDS, Galileo, GZSS, and GLONASS. It can receive and track many visible satellites in multi-bands, significantly mitigating the multipath effect in deep urban canyons and improving positioning accuracy.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnssrtk3da_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/gnss-rtk-3-click-lc29hda)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2023.
- **Type**          : UART/I2C type


# Software Support

We provide a library for the GNSS RTK 3 DA Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GNSS RTK 3 DA Click driver.

#### Standard key functions :

- `gnssrtk3da_cfg_setup` Config Object Initialization function.
```c
void gnssrtk3da_cfg_setup ( gnssrtk3da_cfg_t *cfg );
```

- `gnssrtk3da_init` Initialization function.
```c
err_t gnssrtk3da_init ( gnssrtk3da_t *ctx, gnssrtk3da_cfg_t *cfg );
```

#### Example key functions :

- `gnssrtk3da_enable_device` This function enables the device by setting the CEN pin to high logic state.
```c
void gnssrtk3da_enable_device ( gnssrtk3da_t *ctx );
```

- `gnssrtk3da_generic_read` This function reads a desired number of data bytes by using UART or I2C serial interface.
```c
err_t gnssrtk3da_generic_read ( gnssrtk3da_t *ctx, uint8_t *data_out, uint16_t len );
```

- `gnssrtk3da_parse_gga` This function parses the GGA data from the read response buffer.
```c
err_t gnssrtk3da_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );
```

## Example Description

> This example demonstrates the use of GNSS RTK 3 DA Click by reading and displaying the GNSS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables the Click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnssrtk3da_cfg_t gnssrtk3da_cfg;  /**< Click config object. */

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
    gnssrtk3da_cfg_setup( &gnssrtk3da_cfg );
    GNSSRTK3DA_MAP_MIKROBUS( gnssrtk3da_cfg, MIKROBUS_1 );
    if ( GNSSRTK3DA_OK != gnssrtk3da_init( &gnssrtk3da, &gnssrtk3da_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    gnssrtk3da_enable_device ( &gnssrtk3da );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the received data, parses the NMEA GGA info from it, and once it receives the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    if ( GNSSRTK3DA_OK == gnssrtk3da_process( &gnssrtk3da ) ) 
    {
        gnssrtk3da_parser_application( app_buf );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSSRTK3DA

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
