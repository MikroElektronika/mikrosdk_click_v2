
---
# GNSS 27 Click

> [GNSS 27 Click](https://www.mikroe.com/?pid_product=MIKROE-6766) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6766&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2025.
- **Type**          : UART/I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of GNSS 27 Click by reading and displaying the GNSS coordinates.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS27

### Example Key Functions

- `gnss27_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void gnss27_cfg_setup ( gnss27_cfg_t *cfg );
```

- `gnss27_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t gnss27_init ( gnss27_t *ctx, gnss27_cfg_t *cfg );
```

- `gnss27_generic_read` This function reads a desired number of data bytes by using the selected serial interface.
```c
err_t gnss27_generic_read ( gnss27_t *ctx, uint8_t *data_out, uint16_t len );
```

- `gnss27_parse_gga` This function parses the GGA data from the read response buffer.
```c
err_t gnss27_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );
```

- `gnss27_get_pps_pin` This function returns the pulse per second (PPS) pin logic state.
```c
uint8_t gnss27_get_pps_pin ( gnss27_t *ctx );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss27_cfg_t gnss27_cfg;  /**< Click config object. */

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
    gnss27_cfg_setup( &gnss27_cfg );
    GNSS27_MAP_MIKROBUS( gnss27_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gnss27_init( &gnss27, &gnss27_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the received data, parses the NMEA GGA info from it, and once it receives the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    if ( GNSS27_OK == gnss27_process( &gnss27 ) ) 
    {
        gnss27_parser_application( app_buf );
    }
}
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
