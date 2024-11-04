
---
# Nano GPS 3 Click

> Nano GPS 3 Click is a compact add-on board that provides fast positioning capabilities. 
> This board features the ORG1511, a GPS/GNSS module with an integrated antenna from OriginGPS. 
> It is a miniature, multi-channel GPS, GLONASS, Galileo, SBAS, 
> and QZSS overlay system receiver that continuously tracks all satellites in view, 
> providing real-time positioning data in industry-standard NMEA format. 
> The module introduces the industry’s lowest energy per fix ratio, unparalleled accuracy, 
> and extremely fast fixes even under challenging.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nanogps3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/nano-gps-3-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2023.
- **Type**          : UART/I2C type


# Software Support

We provide a library for the Nano GPS 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Nano GPS 3 Click driver.

#### Standard key functions :

- `nanogps3_cfg_setup` Config Object Initialization function.
```c
void nanogps3_cfg_setup ( nanogps3_cfg_t *cfg );
```

- `nanogps3_init` Initialization function.
```c
err_t nanogps3_init ( nanogps3_t *ctx, nanogps3_cfg_t *cfg );
```

- `nanogps3_default_cfg` Click Default Configuration function.
```c
void nanogps3_default_cfg ( nanogps3_t *ctx );
```

#### Example key functions :

- `nanogps3_parse_gngga` Nano GPS 3 parse GNGGA function.
```c
err_t nanogps3_parse_gngga ( char *rsp,  uint8_t cmd, uint8_t element, char *element_data );
```

- `nanogps3_generic_read` Nano GPS 3 data reading function.
```c
err_t nanogps3_generic_read ( nanogps3_t *ctx, uint8_t *data_out, uint8_t len );
```

- `nanogps3_generic_write` Nano GPS 3 data writing function.
```c
err_t nanogps3_generic_write ( nanogps3_t *ctx, uint8_t *data_in, uint8_t len );
```

## Example Description

> This example demonstrates the use of Nano GPS 3 Click by reading and displaying
> the GPS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and resets the Click board.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nanogps3_cfg_t nanogps3_cfg;  /**< Click config object. */

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
    nanogps3_cfg_setup( &nanogps3_cfg );
    NANOGPS3_MAP_MIKROBUS( nanogps3_cfg, MIKROBUS_1 );
    err_t init_flag = nanogps3_init( &nanogps3, &nanogps3_cfg ); 
    if ( ( UART_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    nanogps3_default_cfg( &nanogps3 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the received data, parses the GNGGA info from it, and once it receives the position fix
> it will start displaying the coordinates on the USB UART.

```c
void application_task ( void ) 
{
    nanogps3_process( &nanogps3 );
    if ( app_buf_len > ( sizeof( NANOGPS3_RSP_GNGGA ) + NANOGPS3_NMEA_GNGGA_NUM_ELEMENT ) ) 
    {
        nanogps3_parser_application( app_buf );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.NanoGPS3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
