\mainpage Main Page

---
# GNSS 10 click

> GNSS 10 Click is a compact add-on board that provides fast positioning capability. This board features the NEO-M8J, a standard precision GNSS module built on the high-performing M8 GNSS engine in the industry-proven NEO form factor from u-blox. This module utilizes concurrent reception of up to three GNSS systems (GPS/Galileo together with BeiDou or GLONASS), recognizes multiple constellations simultaneously, and provides outstanding positioning accuracy in scenarios where urban canyon or weak signals are involved. It supports all satellite augmentation systems for even better and faster positioning improvement, comes with a configurable host interface, and advanced jamming and spoofing detection. This Click board™ is ideally suited for industrial and automotive applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnss10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gnss-10-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : UART/I2C/SPI type


# Software Support

We provide a library for the GNSS 10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GNSS 10 Click driver.

#### Standard key functions :

- `gnss10_cfg_setup` Config Object Initialization function.
```c
void gnss10_cfg_setup ( gnss10_cfg_t *cfg );
```

- `gnss10_init` Initialization function.
```c
err_t gnss10_init ( gnss10_t *ctx, gnss10_cfg_t *cfg );
```

#### Example key functions :

- `gnss10_reset_device` This function resets the device by toggling the RST pin.
```c
void gnss10_reset_device ( gnss10_t *ctx );
```

- `gnss10_generic_read` This function reads a desired number of data bytes from the module.
```c
err_t gnss10_generic_read ( gnss10_t *ctx, uint8_t *data_out, uint8_t len );
```

- `gnss10_parse_gngga` This function parses the GNGGA data from the read response buffer.
```c
err_t gnss10_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );
```

## Example Description

> This example demonstrates the use of GNSS 10 click by reading and displaying the GNSS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and resets the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss10_cfg_t gnss10_cfg;  /**< Click config object. */

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
    gnss10_cfg_setup( &gnss10_cfg );
    GNSS10_MAP_MIKROBUS( gnss10_cfg, MIKROBUS_1 );
    err_t init_flag = gnss10_init( &gnss10, &gnss10_cfg );
    if ( ( UART_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    gnss10_reset_device ( &gnss10 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the received data, parses the GNGGA info from it, and once it receives the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    gnss10_process( &gnss10 );
    if ( app_buf_len > ( sizeof ( GNSS10_RSP_GNGGA ) + GNSS10_GNGGA_ELEMENT_SIZE ) ) 
    {
        gnss10_parser_application( app_buf );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
