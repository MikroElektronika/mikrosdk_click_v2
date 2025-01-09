
---
# GNSS 9 Click

> [GNSS 9 Click](https://www.mikroe.com/?pid_product=MIKROE-6073) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6073&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic 
- **Date**          : Jan 2024.
- **Type**          : UART/I2C type

# Software Support

## Example Description

> This example demonstrates the use of GNSS 9 Click by reading and displaying the GNSS coordinates.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS9

### Example Key Functions

- `gnss9_cfg_setup` Config Object Initialization function.
```c
void gnss9_cfg_setup ( gnss9_cfg_t *cfg );
```

- `gnss9_init` Initialization function.
```c
err_t gnss9_init ( gnss9_t *ctx, gnss9_cfg_t *cfg );
```

- `gnss9_get_pps_pin` This function returns the PPS pin logic state.
```c
uint8_t gnss9_get_pps_pin ( gnss9_t *ctx );
```

- `gnss9_reset_device` This function resets the device by toggling the RST pin.
```c
void gnss9_reset_device ( gnss9_t *ctx );
```

- `gnss9_parse_gpgga` This function parses the GPGGA data from the read response buffer.
```c
err_t gnss9_parse_gpgga ( uint8_t *rsp_buf, uint8_t gpgga_element, uint8_t *element_data );
```

### Application Init

> Initializes the driver and resets the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss9_cfg_t gnss9_cfg;  /**< Click config object. */

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
    gnss9_cfg_setup( &gnss9_cfg );
    GNSS9_MAP_MIKROBUS( gnss9_cfg, MIKROBUS_1 );
    err_t init_flag = gnss9_init( &gnss9, &gnss9_cfg );
    if ( ( UART_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the received data, parses the GPGGA info from it, and once it receives the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    if ( GNSS9_OK == gnss9_process( &gnss9 ) )
    {
        if ( PROCESS_BUFFER_SIZE == app_buf_len )
        {
            gnss9_parser_application( app_buf );
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
