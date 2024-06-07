\mainpage Main Page

---
# GNSS 16 click

> GNSS 16 Click is a compact add-on board that delivers meter-level accuracy in urban environments. This Click board™ features the NEO-F10N-00B, a professional-grade L1/L5 dual-band GNSS receiver from u-blox. It features dual-band multipath mitigation technology to ensure robust signal reception and supports multiple GNSS systems, including GPS, Galileo, and BeiDou. Configurable for specific constellations, it optimizes power consumption while maintaining high performance.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnss16_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gnss-16-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2024.
- **Type**          : UART type


# Software Support

We provide a library for the GNSS 16 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GNSS 16 Click driver.

#### Standard key functions :

- `gnss16_cfg_setup` Config Object Initialization function.
```c
void gnss16_cfg_setup ( gnss16_cfg_t *cfg );
```

- `gnss16_init` Initialization function.
```c
err_t gnss16_init ( gnss16_t *ctx, gnss16_cfg_t *cfg );
```

#### Example key functions :

- `gnss16_parse_gngga` This function parses the GNGGA data from the read response buffer.
```c
err_t gnss16_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );
```

- `gnss16_reset_device` This function resets the device by toggling the RST pin.
```c
void gnss16_reset_device ( gnss16_t *ctx );
```

## Example Description

> This example demonstrates the use of GNSS 16 click board by processing
> the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and resets the click board.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss16_cfg_t gnss16_cfg;  /**< Click config object. */

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
    gnss16_cfg_setup( &gnss16_cfg );
    GNSS16_MAP_MIKROBUS( gnss16_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gnss16_init( &gnss16, &gnss16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    gnss16_reset_device( &gnss16 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and processes all incoming data and displays them on the USB UART.

```c
void application_task ( void ) 
{
    gnss16_process( &gnss16 );
    if ( app_buf_len > ( sizeof ( GNSS16_RSP_GNGGA ) + GNSS16_GNGGA_ELEMENT_SIZE ) ) 
    {
        gnss16_parser_application( app_buf );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS16

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
