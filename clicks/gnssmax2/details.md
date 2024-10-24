
---
# GNSS MAX 2 click

> GNSS MAX 2 Click is a compact add-on board designed for precise positioning in urban environments. This board features the MAX-F10S, a professional-grade L1/L5 dual-band GNSS receiver from u-blox. This receiver uses dual-band GNSS technology to provide meter-level accuracy, even in challenging urban areas, by mitigating multipath effects. It supports concurrent GPS, Galileo, and BeiDou constellation tracking, offering robust performance with integrated filters and a low-noise amplifier for protection against RF interference. GNSS MAX 2 Click is ideal for vehicle tracking, fleet management, and micromobility solutions, even with small antennas.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnssmax2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gnss-max-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2024.
- **Type**          : UART/I2C type


# Software Support

We provide a library for the GNSS MAX 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GNSS MAX 2 Click driver.

#### Standard key functions :

- `gnssmax2_cfg_setup` Config Object Initialization function.
```c
void gnssmax2_cfg_setup ( gnssmax2_cfg_t *cfg );
```

- `gnssmax2_init` Initialization function.
```c
err_t gnssmax2_init ( gnssmax2_t *ctx, gnssmax2_cfg_t *cfg );
```

- `gnssmax2_default_cfg` Click Default Configuration function.
```c
err_t gnssmax2_default_cfg ( gnssmax2_t *ctx );
```

#### Example key functions :

- `gnssmax2_generic_read` This function reads a desired number of data bytes by using UART or I2C serial interface.
```c
err_t gnssmax2_generic_read ( gnssmax2_t *ctx, uint8_t *data_out, uint16_t len );
```

- `gnssmax2_parse_gga` This function parses the GGA data from the read response buffer.
```c
err_t gnssmax2_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );
```

- `gnssmax2_reset_device` This function resets the device by toggling the RST pin.
```c
void gnssmax2_reset_device ( gnssmax2_t *ctx );
```

## Example Description

> This example demonstrates the use of GNSS MAX 2 click by reading and displaying the GNSS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnssmax2_cfg_t gnssmax2_cfg;  /**< Click config object. */

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
    gnssmax2_cfg_setup( &gnssmax2_cfg );
    GNSSMAX2_MAP_MIKROBUS( gnssmax2_cfg, MIKROBUS_1 );
    if ( GNSSMAX2_OK != gnssmax2_init( &gnssmax2, &gnssmax2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the received data, parses the NMEA GGA info from it, and once it receives 
the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    if ( GNSSMAX2_OK == gnssmax2_process( &gnssmax2 ) ) 
    {
        gnssmax2_parser_application( app_buf );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSSMAX2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
