
---
# GPS 6 Click

> [GPS 6 Click](https://www.mikroe.com/?pid_product=MIKROE-5115) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5115&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of GPS 6 Click by reading and displaying the GPS coordinates.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GPS6

### Example Key Functions

- `gps6_cfg_setup` Config Object Initialization function.
```c
void gps6_cfg_setup ( gps6_cfg_t *cfg );
```

- `gps6_init` Initialization function.
```c
err_t gps6_init ( gps6_t *ctx, gps6_cfg_t *cfg );
```

- `gps6_enable_device` This function enables device by setting the RST pin to LOW logic state.
```c
void gps6_enable_device ( gps6_t *ctx );
```

- `gps6_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t gps6_generic_read ( gps6_t *ctx, char *data_buf, uint16_t max_len );
```

- `gps6_parse_gpgga` This function parses the GPGGA data from the read response buffer.
```c
err_t gps6_parse_gpgga ( char *rsp_buf, uint8_t gpgga_element, char *element_data );
```

### Application Init

> Initializes the driver and logger and enables the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gps6_cfg_t gps6_cfg;  /**< Click config object. */

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
    gps6_cfg_setup( &gps6_cfg );
    GPS6_MAP_MIKROBUS( gps6_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gps6_init( &gps6, &gps6_cfg ) ) 
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
    gps6_process( &gps6 );
    if ( app_buf_len > ( sizeof ( ( char * ) GPS6_RSP_GPGGA ) + GPS6_GPGGA_ELEMENT_SIZE ) ) 
    {
        gps6_parser_application( app_buf );
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
