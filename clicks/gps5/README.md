\mainpage Main Page

---
# GPS 5 click

> GPS 5 Click is a compact add-on board that provides users with positioning, navigation, and timing services. This board features the M20050-1, a compact GPS module receiver using the MediaTek MT3333 flash chip, providing a complete GNSS receiver for optimum performance from Antenova. The receiver tracks 3 GNSS constellations concurrently (GPS+Galileo+GLONASS or GPS+Beidou) to considerably enhance location and TTFF (Time-to-first-fix) and has configurable low power modes operating from a 3.3V power supply. In addition to the possibility of using an external antenna, backup power, and various visual indicators, the M20050-1 also has an accurate 0.5ppm TXCO ensuring short TTFF alongside multi-path algorithms, which improves position accuracy in inner-city environments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gps5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gps-5-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : UART type


# Software Support

We provide a library for the GPS 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GPS 5 Click driver.

#### Standard key functions :

- `gps5_cfg_setup` Config Object Initialization function.
```c
void gps5_cfg_setup ( gps5_cfg_t *cfg );
```

- `gps5_init` Initialization function.
```c
err_t gps5_init ( gps5_t *ctx, gps5_cfg_t *cfg );
```

#### Example key functions :

- `gps5_set_rst_pin` This function sets the RST pin logic state.
```c
void gps5_set_rst_pin ( gps5_t *ctx, uint8_t state );
```

- `gps5_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t gps5_generic_read ( gps5_t *ctx, char *data_buf, uint16_t max_len );
```

- `gps5_parse_gngga` This function parses the GNGGA data from the read response buffer.
```c
err_t gps5_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );
```

## Example Description

> This example demonstrates the use of GPS 5 click by reading and displaying the GPS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and resets the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gps5_cfg_t gps5_cfg;  /**< Click config object. */

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
    gps5_cfg_setup( &gps5_cfg );
    GPS5_MAP_MIKROBUS( gps5_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gps5_init( &gps5, &gps5_cfg ) ) 
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
    gps5_process( &gps5 );
    if ( app_buf_len > ( sizeof ( ( char * ) GPS5_RSP_GNGGA ) + GPS5_GNGGA_ELEMENT_SIZE ) ) 
    {
        gps5_parser_application( app_buf );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GPS5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
