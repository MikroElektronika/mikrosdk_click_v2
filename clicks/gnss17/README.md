\mainpage Main Page

---
# GNSS 17 Click

> GNSS 17 Click is a compact add-on board for precise and reliable global navigation and positioning. This board features the M20071, an integrated full-function GNSS receiver module from Antenova, which features the MediaTek AG3335MN flash chip. This module can concurrently track multiple GNSS constellations, including GPS, GLONASS, GALILEO, BEIDOU, and QZSS, ensuring accurate positioning even in dense urban environments. It includes advanced features like multi-path algorithms for enhanced accuracy, a high-performance onboard LNA for weak-signal environments, and power-saving modes to optimize energy consumption.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnss17_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/gnss-17-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : UART type


# Software Support

We provide a library for the GNSS 17 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GNSS 17 Click driver.

#### Standard key functions :

- `gnss17_cfg_setup` Config Object Initialization function.
```c
void gnss17_cfg_setup ( gnss17_cfg_t *cfg );
```

- `gnss17_init` Initialization function.
```c
err_t gnss17_init ( gnss17_t *ctx, gnss17_cfg_t *cfg );
```

#### Example key functions :

- `gnss17_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t gnss17_generic_read ( gnss17_t *ctx, uint8_t *data_out, uint16_t len );
```

- `gnss17_parse_gga` This function parses the GGA data from the read response buffer.
```c
err_t gnss17_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );
```

- `gnss17_reset_device` This function resets the device by toggling the EN and AON pins.
```c
void gnss17_reset_device ( gnss17_t *ctx );
```

## Example Description

> This example demonstrates the use of GNSS 17 Click by reading and displaying the GNSS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and resets the Click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss17_cfg_t gnss17_cfg;  /**< Click config object. */

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
    gnss17_cfg_setup( &gnss17_cfg );
    GNSS17_MAP_MIKROBUS( gnss17_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gnss17_init( &gnss17, &gnss17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the received data, parses the NMEA GGA info from it, and once it receives the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    if ( GNSS17_OK == gnss17_process( &gnss17 ) ) 
    {
        if ( app_buf_len > ( sizeof ( GNSS17_RSP_GGA ) + GNSS17_GGA_ELEMENT_SIZE ) ) 
        {
            gnss17_parser_application( app_buf );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS17

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
