
---
# GNSS 21 Click

> [GNSS 21 Click](https://www.mikroe.com/?pid_product=MIKROE-6409) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6409&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2024.
- **Type**          : UART/I2C type

# Software Support

## Example Description

> This example demonstrates the use of GNSS 21 Click by reading and displaying the GNSS coordinates.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS21

### Example Key Functions

- `gnss21_cfg_setup` Config Object Initialization function.
```c
void gnss21_cfg_setup ( gnss21_cfg_t *cfg );
```

- `gnss21_init` Initialization function.
```c
err_t gnss21_init ( gnss21_t *ctx, gnss21_cfg_t *cfg );
```

- `gnss21_generic_read` This function reads a desired number of data bytes by using UART or I2C serial interface.
```c
err_t gnss21_generic_read ( gnss21_t *ctx, uint8_t *data_out, uint16_t len );
```

- `gnss21_parse_gga` This function parses the GGA data from the read response buffer.
```c
err_t gnss21_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );
```

- `gnss21_reset_device` This function resets the device by toggling the RST pin.
```c
void gnss21_reset_device ( gnss21_t *ctx );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss21_cfg_t gnss21_cfg;  /**< Click config object. */

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
    gnss21_cfg_setup( &gnss21_cfg );
    GNSS21_MAP_MIKROBUS( gnss21_cfg, MIKROBUS_1 );
    if ( GNSS21_OK != gnss21_init( &gnss21, &gnss21_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the received data, parses the NMEA GGA info from it, and once it receives 
the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    if ( GNSS21_OK == gnss21_process( &gnss21 ) ) 
    {
        gnss21_parser_application( app_buf );
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
