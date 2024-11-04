\mainpage Main Page

---
# GNSS 15 Click

> GNSS 15 Click is a compact add-on board for advanced automotive navigation and tracking applications. This board features the TESEO-VIC3DA, an automotive GNSS dead-reckoning module from STMicroelectronics. This module combines a 6-axis IMU with multi-constellation satellite reception, offering exceptional accuracy and dead-reckoning capabilities. It stands out for its rapid time-to-first-fix and the ability to receive firmware updates for enhanced performance. Designed for flexibility, it supports both UART and I2C communications, includes pins for precise odometer readings, and features an SMA antenna connector for superior signal quality.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gnss15_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/gnss-15-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : UART type


# Software Support

We provide a library for the GNSS 15 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GNSS 15 Click driver.

#### Standard key functions :

- `gnss15_cfg_setup` Config Object Initialization function.
```c
void gnss15_cfg_setup ( gnss15_cfg_t *cfg );
```

- `gnss15_init` Initialization function.
```c
err_t gnss15_init ( gnss15_t *ctx, gnss15_cfg_t *cfg );
```

#### Example key functions :

- `gnss15_parse_gpgga` This function parses the GPGGA data from the read response buffer.
```c
err_t gnss15_parse_gpgga ( uint8_t *rsp_buf, uint8_t gpgga_element, uint8_t *element_data )
```

- `gnss15_reset_device` This function resets the device by toggling the RST pin.
```c
void gnss15_reset_device ( gnss15_t *ctx );
```

## Example Description

> This example demonstrates the use of GNSS 15 Click board by processing
> the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and resets the Click board.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss15_cfg_t gnss15_cfg;  /**< Click config object. */

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
    gnss15_cfg_setup( &gnss15_cfg );
    GNSS15_MAP_MIKROBUS( gnss15_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gnss15_init( &gnss15, &gnss15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the received data, parses the GPGGA info from it, and once it receives the position fix
> it will start displaying the coordinates on the USB UART.

```c
void application_task ( void ) 
{
    if ( GNSS15_OK == gnss15_process( &gnss15 ) )
    {
        if ( app_buf_len > ( sizeof ( GNSS15_RSP_GPGGA ) + GNSS15_GPGGA_ELEMENT_SIZE ) ) 
        {
            gnss15_parser_application( app_buf );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS15

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
