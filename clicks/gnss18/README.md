\mainpage Main Page

---
# GNSS 18 Click

> GNSS 18 Click is a compact add-on board designed for high-precision GNSS applications. This board features the SAM-M10Q-00B-00B, M10 standard precision GNSS module from u-blox, known for exceptional sensitivity and rapid acquisition of L1 GNSS signals. It supports concurrent reception of GPS, Galileo, GLONASS, and BeiDou B1C, with additional support for QZSS and SBAS. Featuring u-blox Super-S technology for improved dynamic position accuracy and low power consumption of 37mW in continuous tracking mode, it is ideal for battery-operated devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnss18_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/gnss-18-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Mar 2024.
- **Type**          : UART type


# Software Support

We provide a library for the GNSS 18 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GNSS 18 Click driver.

#### Standard key functions :

- `gnss18_cfg_setup` Config Object Initialization function.
```c
void gnss18_cfg_setup ( gnss18_cfg_t *cfg );
```

- `gnss18_init` Initialization function.
```c
err_t gnss18_init ( gnss18_t *ctx, gnss18_cfg_t *cfg );
```

#### Example key functions :

- `gnss18_generic_read` This function reads a desired number of data bytes from the module.
```c
err_t gnss18_generic_read ( gnss18_t *ctx, uint8_t *data_out, uint8_t len );
```

- `gnss18_reset_device` This function resets the device by toggling the RST pin.
```c
void gnss18_reset_device ( gnss18_t *ctx );
```

- `gnss18_parse_gpgga` This function parses the GPGGA data from the read response buffer.
```c
err_t gnss18_parse_gpgga ( uint8_t *rsp_buf, uint8_t gpgga_element, uint8_t *element_data );
```

## Example Description

> This example demonstrates the use of GNSS 18 Click by reading and displaying the GNSS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and resets the Click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss18_cfg_t gnss18_cfg;  /**< Click config object. */

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
    gnss18_cfg_setup( &gnss18_cfg );
    GNSS18_MAP_MIKROBUS( gnss18_cfg, MIKROBUS_1 );
    err_t init_flag = gnss18_init( &gnss18, &gnss18_cfg );
    if ( ( UART_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the received data, parses the GPGGA info from it, and once it receives the position fix
 it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    if ( GNSS18_OK == gnss18_process( &gnss18 ) )
    {
        if ( PROCESS_BUFFER_SIZE == app_buf_len )
        {
            gnss18_parser_application( app_buf );
        }
    }
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS18

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
