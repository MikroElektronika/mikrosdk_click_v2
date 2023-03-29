
---
# RTK Rover click

> RTK Rover Click is a compact add-on board that enhances the precision of position data derived from compatible RTK Base Station. This board features Quectel’s LG69TAMMD, a dual-band multi-constellation GNSS module featuring a high-performance and high-reliability positioning engine. This module facilitates a fast and precise GNSS positioning capability for centimeter-level accuracy, featuring the fifth generation of STMicroelectronics® positioning receiver platform with 80 tracking and four fast acquisition channels. It supports up to 3 concurrent global constellations (GPS/QZSS, Galileo, and BDS) alongside NMEA 0183/RTCM 3.x protocol and commonly used UART interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtkrover_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rtk-rover-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2022.
- **Type**          : UART type


# Software Support

We provide a library for the RTK Rover Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RTK Rover Click driver.

#### Standard key functions :

- `rtkrover_cfg_setup` Config Object Initialization function.
```c
void rtkrover_cfg_setup ( rtkrover_cfg_t *cfg );
```

- `rtkrover_init` Initialization function.
```c
err_t rtkrover_init ( rtkrover_t *ctx, rtkrover_cfg_t *cfg );
```

#### Example key functions :

- `rtkrover_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t rtkrover_generic_read ( rtkrover_t *ctx, char *data_out, uint16_t len );
```

- `rtkrover_clear_ring_buffers` This function clears UART tx and rx ring buffers.
```c
void rtkrover_clear_ring_buffers ( rtkrover_t *ctx );
```

- `rtkrover_parse_gngga` This function parses the GNGGA data from the read response buffer.
```c
err_t rtkrover_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );
```

## Example Description

> This example demonstrates the use of RTK Rover click by reading and displaying the GPS coordinates.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtkrover_cfg_t rtkrover_cfg;  /**< Click config object. */

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
    rtkrover_cfg_setup( &rtkrover_cfg );
    RTKROVER_MAP_MIKROBUS( rtkrover_cfg, MIKROBUS_1 );
    if ( UART_ERROR == rtkrover_init( &rtkrover, &rtkrover_cfg ) ) 
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
    if ( RTKROVER_OK == rtkrover_process( &rtkrover ) )
    {
        if ( PROCESS_BUFFER_SIZE == app_buf_len )
        {
            rtkrover_parser_application( &rtkrover, app_buf );
        }
    }
}
```

## Note

> The click board comes with the default baud rate of 460800, but the baud rate is set to 115200
in the example due to code portability and speed limitations of some MCUs. So in order to run
the example you will need to adjust the baud rate using Quectel QGNSS evaluation software.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RTKRover

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
