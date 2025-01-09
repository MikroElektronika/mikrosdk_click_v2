
---
# GNSS 13 Click

> [GNSS 13 Click](https://www.mikroe.com/?pid_product=MIKROE-5580) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5580&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2023.
- **Type**          : UART/I2C type

# Software Support

## Example Description

> This example demonstrates the use of GNSS 13 Click by reading and displaying the GPS coordinates.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS13

### Example Key Functions

- `gnss13_cfg_setup` Config Object Initialization function.
```c
void gnss13_cfg_setup ( gnss13_cfg_t *cfg );
```

- `gnss13_init` Initialization function.
```c
err_t gnss13_init ( gnss13_t *ctx, gnss13_cfg_t *cfg );
```

- `gnss13_generic_read` This function reads a desired number of data bytes from the module.
```c
err_t gnss13_generic_read ( gnss13_t *ctx, uint8_t *data_out, uint8_t len );
```

- `gnss13_parse_gngga` This function parses the GNGGA data from the read response buffer.
```c
err_t gnss13_parse_gngga ( uint8_t *rsp_buf, uint8_t gngga_element, uint8_t *element_data );
```

- `gnss13_clear_ring_buffers` This function clears UART tx and rx ring buffers.
```c
void gnss13_clear_ring_buffers ( gnss13_t *ctx );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss13_cfg_t gnss13_cfg;  /**< Click config object. */

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
    gnss13_cfg_setup( &gnss13_cfg );
    GNSS13_MAP_MIKROBUS( gnss13_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gnss13_init( &gnss13, &gnss13_cfg ) ) 
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
    if ( GNSS13_OK == gnss13_process( &gnss13 ) )
    {
        if ( PROCESS_BUFFER_SIZE == app_buf_len )
        {
            gnss13_parser_application( &gnss13, app_buf );
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
