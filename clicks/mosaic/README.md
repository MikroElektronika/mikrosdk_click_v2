\mainpage Main Page

---
# Mosaic click

> Mosaic Click is a compact add-on board for precision navigation and location-based applications. This board features the Mosaic-X5, a compact global navigation satellite system (GNSS) receiver from Septentrio. The Mosaic-X5 stands out for its multi-band and multi-constellation tracking ability, ensuring robust and comprehensive global coverage. It features Septentrio's AIM+ technology for superior interference mitigation, enabling it to counteract a wide range of signal disruptions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mosaic_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/mosaic-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2024.
- **Type**          : UART type


# Software Support

We provide a library for the Mosaic Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Mosaic Click driver.

#### Standard key functions :

- `mosaic_cfg_setup` Config Object Initialization function.
```c
void mosaic_cfg_setup ( mosaic_cfg_t *cfg );
```

- `mosaic_init` Initialization function.
```c
err_t mosaic_init ( mosaic_t *ctx, mosaic_cfg_t *cfg );
```

#### Example key functions :

- `mosaic_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t mosaic_generic_read ( mosaic_t *ctx, uint8_t *data_out, uint16_t len );
```

- `mosaic_enable_nmea_output` This function enables the NMEA output with the selected message parameters and an output interval.
```c
void mosaic_enable_nmea_output ( mosaic_t *ctx, uint8_t *msg_param, uint8_t *interval );
```

- `mosaic_parse_gga` This function parses the GGA data from the read response buffer.
```c
err_t mosaic_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );
```

## Example Description

> This example demonstrates the use of Mosaic click by reading and displaying the GNSS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, reads the NMEA version, and enables the NMEA output.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mosaic_cfg_t mosaic_cfg;  /**< Click config object. */

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
    mosaic_cfg_setup( &mosaic_cfg );
    MOSAIC_MAP_MIKROBUS( mosaic_cfg, MIKROBUS_1 );
    if ( UART_ERROR == mosaic_init( &mosaic, &mosaic_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( MOSAIC_OK != mosaic_wait_prompt( &mosaic ) )
    {
        log_error( &logger, " No connection prompt detected." );
        for ( ; ; );
    }
    mosaic_log_app_buf( );
    mosaic_clear_app_buf( );
    Delay_ms ( 100 );

    mosaic_send_cmd( &mosaic, MOSAIC_CMD_GET_NMEA_VERSION );
    mosaic_wait_prompt( &mosaic );
    mosaic_log_app_buf( );
    mosaic_clear_app_buf( );
    Delay_ms ( 100 );

    mosaic_enable_nmea_output( &mosaic, MOSAIC_SNO_MESSAGES_GGA, MOSAIC_SNO_INTERVAL_SEC1 );
    mosaic_wait_prompt( &mosaic );
    mosaic_log_app_buf( );
    mosaic_clear_app_buf( );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the received data, parses the NMEA GGA info from it, and once it receives the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    mosaic_process( &mosaic );
    if ( app_buf_len > ( sizeof ( MOSAIC_NMEA_GGA ) + MOSAIC_GGA_ELEMENT_SIZE ) ) 
    {
        mosaic_parser_application( app_buf );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Mosaic

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
