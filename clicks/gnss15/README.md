
---
# GNSS 15 Click

> [GNSS 15 Click](https://www.mikroe.com/?pid_product=MIKROE-5987) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5987&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of GNSS 15 Click board by processing
> the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS15

### Example Key Functions

- `gnss15_cfg_setup` Config Object Initialization function.
```c
void gnss15_cfg_setup ( gnss15_cfg_t *cfg );
```

- `gnss15_init` Initialization function.
```c
err_t gnss15_init ( gnss15_t *ctx, gnss15_cfg_t *cfg );
```

- `gnss15_parse_gpgga` This function parses the GPGGA data from the read response buffer.
```c
err_t gnss15_parse_gpgga ( uint8_t *rsp_buf, uint8_t gpgga_element, uint8_t *element_data )
```

- `gnss15_reset_device` This function resets the device by toggling the RST pin.
```c
void gnss15_reset_device ( gnss15_t *ctx );
```

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
