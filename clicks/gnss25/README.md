
---
# GNSS 25 Click

> [GNSS 25 Click](https://www.mikroe.com/?pid_product=MIKROE-6535) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6535&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2025.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of GNSS 25 Click by reading and displaying the GNSS coordinates.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS25

### Example Key Functions

- `gnss25_cfg_setup` Config Object Initialization function.
```c
void gnss25_cfg_setup ( gnss25_cfg_t *cfg );
```

- `gnss25_init` Initialization function.
```c
err_t gnss25_init ( gnss25_t *ctx, gnss25_cfg_t *cfg );
```

- `gnss25_reset_device` This function resets the device by toggling the RST pin.
```c
void gnss25_reset_device ( gnss25_t *ctx );
```

- `gnss25_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t gnss25_generic_read ( gnss25_t *ctx, uint8_t *data_out, uint16_t len );
```

- `gnss25_parse_gga` This function parses the GGA data from the read response buffer.
```c
err_t gnss25_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );
```

### Application Init

> Initializes the driver and resets the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss25_cfg_t gnss25_cfg;  /**< Click config object. */

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
    gnss25_cfg_setup( &gnss25_cfg );
    GNSS25_MAP_MIKROBUS( gnss25_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gnss25_init( &gnss25, &gnss25_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    gnss25_reset_device ( &gnss25 );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the received data, parses the NMEA GGA info from it, and once it receives the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    if ( GNSS25_OK == gnss25_process( &gnss25 ) ) 
    {
        if ( app_buf_len > ( sizeof ( GNSS25_RSP_GGA ) + GNSS25_GGA_ELEMENT_SIZE ) ) 
        {
            gnss25_parser_application( app_buf );
        }
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
