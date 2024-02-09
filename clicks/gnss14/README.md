\mainpage Main Page

---
# GNSS 14 click

> GNSS 14 Click is a compact add-on board that provides fast positioning capability to your application. This board features the MIA-M10Q, a standard precision GNSS module from u-blox. It has an exceptional sensitivity and acquisition time for all L1 GNSS signals, attributed to its integrated M10 standard precision low-power platform. The M10 platform supports concurrent reception of four GNSS (GPS, GLONASS, Galileo, and BeiDou). The high number of visible satellites enables the receiver to select the best signals. This maximizes position availability, particularly under challenging conditions like deep urban canyons.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnss14_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gnss-14-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : UART/I2C type


# Software Support

We provide a library for the GNSS 14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GNSS 14 Click driver.

#### Standard key functions :

- `gnss14_cfg_setup` Config Object Initialization function.
```c
void gnss14_cfg_setup ( gnss14_cfg_t *cfg );
```

- `gnss14_init` Initialization function.
```c
err_t gnss14_init ( gnss14_t *ctx, gnss14_cfg_t *cfg );
```

#### Example key functions :

- `gnss14_parse_gngga` This function parses the GNGGA data from the read response buffer.
```c
err_t gnss14_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );
```

- `gnss14_reset_device` This function resets the device by toggling the RST pin.
```c
void gnss14_reset_device ( gnss14_t *ctx );
```

## Example Description

> This example demonstrates the use of GNSS 14 click board by reading and displaying
> the GNSS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and resets the click board.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss14_cfg_t gnss14_cfg;  /**< Click config object. */

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
    gnss14_cfg_setup( &gnss14_cfg );
    GNSS14_MAP_MIKROBUS( gnss14_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gnss14_init( &gnss14, &gnss14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    gnss14_reset_device( &gnss14 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the received data, parses the GNGGA info from it, and once it receives the position fix
> it will start displaying the coordinates on the USB UART.

```c
void application_task ( void ) 
{
    if ( GNSS14_OK == gnss14_process( &gnss14 ) ) 
    {
        if ( app_buf_len > ( sizeof ( GNSS14_RSP_GNGGA ) + GNSS14_GNGGA_ELEMENT_SIZE ) ) 
        {
            gnss14_parser_application( app_buf );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
