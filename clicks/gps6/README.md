\mainpage Main Page

---
# GPS 6 click

> GPS 6 Click is a compact add-on board that provides users with positioning, navigation, and timing services. This board features the A2200-A, a GPS receiver module that enables fast acquisition and tracking with SiRFstar IV technology from Lantronix. This small-form-factor module operates with a frequency of 1,575GHz with accuracy from 2 up to 2.5m and fully addresses the demand for the lowest power consumption. The removal of jammers guarantees operation even in hostile environments. High sensitivity during acquisition or while tracking allows for use in many different backgrounds and under the most challenging operating conditions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gps6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gps-6-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : UART type


# Software Support

We provide a library for the GPS 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GPS 6 Click driver.

#### Standard key functions :

- `gps6_cfg_setup` Config Object Initialization function.
```c
void gps6_cfg_setup ( gps6_cfg_t *cfg );
```

- `gps6_init` Initialization function.
```c
err_t gps6_init ( gps6_t *ctx, gps6_cfg_t *cfg );
```

#### Example key functions :

- `gps6_enable_device` This function enables device by setting the RST pin to LOW logic state.
```c
void gps6_enable_device ( gps6_t *ctx );
```

- `gps6_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t gps6_generic_read ( gps6_t *ctx, char *data_buf, uint16_t max_len );
```

- `gps6_parse_gpgga` This function parses the GPGGA data from the read response buffer.
```c
err_t gps6_parse_gpgga ( char *rsp_buf, uint8_t gpgga_element, char *element_data );
```

## Example Description

> This example demonstrates the use of GPS 6 click by reading and displaying the GPS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and enables the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gps6_cfg_t gps6_cfg;  /**< Click config object. */

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
    gps6_cfg_setup( &gps6_cfg );
    GPS6_MAP_MIKROBUS( gps6_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gps6_init( &gps6, &gps6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the received data, parses the GPGGA info from it, and once it receives the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    gps6_process( &gps6 );
    if ( app_buf_len > ( sizeof ( ( char * ) GPS6_RSP_GPGGA ) + GPS6_GPGGA_ELEMENT_SIZE ) ) 
    {
        gps6_parser_application( app_buf );
    }
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GPS6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
