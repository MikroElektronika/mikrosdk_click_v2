\mainpage Main Page

---

# IRNSS Click

> IRNSS Click is a compact add-on board that provides fast positioning capability. This board features the L89H, a high-performance IRNSS-enabled GNSS module capable of acquiring and tracking GPS, IRNSS, GLONASS, BeiDou, Galileo, and QZSS signals from Quectel Wireless Solutions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irnss_click.png">
</p>

[Click Product page](https://www.mikroe.com/irnss-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2022.
- **Type**          : UART type


# Software Support

We provide a library for the IRNSS Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IRNSS Click driver.

#### Standard key functions :

- `irnss_cfg_setup` Config Object Initialization function.
```c
void irnss_cfg_setup ( irnss_cfg_t *cfg );
```

- `irnss_init` Initialization function.
```c
err_t irnss_init ( irnss_t *ctx, irnss_cfg_t *cfg );
```

#### Example key functions :

- `irnss_set_rst_pin_state` This function sets rst pin output to state setting.
```c
void irnss_set_rst_pin_state ( irnss_t *ctx, uint8_t state );
```

- `irnss_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t irnss_generic_read ( irnss_t *ctx, char *data_buf, uint16_t max_len );
```

- `irnss_parse_gngga` This function parses the GNGGA data from the read response buffer.
```c
err_t irnss_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );
```

## Example Description

> This example demonstrates the use of IRNSS Click by reading and displaying the GPS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and resets the Click board.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irnss_cfg_t irnss_cfg;  /**< Click config object. */

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
    irnss_cfg_setup( &irnss_cfg );
    IRNSS_MAP_MIKROBUS( irnss_cfg, MIKROBUS_1 );
    if ( UART_ERROR == irnss_init( &irnss, &irnss_cfg ) ) 
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
    irnss_process( &irnss );
    if ( app_buf_len > ( sizeof ( ( char * ) IRNSS_RSP_GNGGA ) + IRNSS_GNGGA_ELEMENT_SIZE ) ) 
        {
        irnss_parser_application( app_buf );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IRNSS

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
