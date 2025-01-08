
---
# Nano GPS 3 Click

> [Nano GPS 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5782) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5782&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2023.
- **Type**          : UART/I2C type

# Software Support

## Example Description

> This example demonstrates the use of Nano GPS 3 Click by reading and displaying
> the GPS coordinates.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NanoGPS3

### Example Key Functions

- `nanogps3_cfg_setup` Config Object Initialization function.
```c
void nanogps3_cfg_setup ( nanogps3_cfg_t *cfg );
```

- `nanogps3_init` Initialization function.
```c
err_t nanogps3_init ( nanogps3_t *ctx, nanogps3_cfg_t *cfg );
```

- `nanogps3_default_cfg` Click Default Configuration function.
```c
void nanogps3_default_cfg ( nanogps3_t *ctx );
```

- `nanogps3_parse_gngga` Nano GPS 3 parse GNGGA function.
```c
err_t nanogps3_parse_gngga ( char *rsp,  uint8_t cmd, uint8_t element, char *element_data );
```

- `nanogps3_generic_read` Nano GPS 3 data reading function.
```c
err_t nanogps3_generic_read ( nanogps3_t *ctx, uint8_t *data_out, uint8_t len );
```

- `nanogps3_generic_write` Nano GPS 3 data writing function.
```c
err_t nanogps3_generic_write ( nanogps3_t *ctx, uint8_t *data_in, uint8_t len );
```

### Application Init

> Initializes the driver and resets the Click board.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nanogps3_cfg_t nanogps3_cfg;  /**< Click config object. */

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
    nanogps3_cfg_setup( &nanogps3_cfg );
    NANOGPS3_MAP_MIKROBUS( nanogps3_cfg, MIKROBUS_1 );
    err_t init_flag = nanogps3_init( &nanogps3, &nanogps3_cfg ); 
    if ( ( UART_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    nanogps3_default_cfg( &nanogps3 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the received data, parses the GNGGA info from it, and once it receives the position fix
> it will start displaying the coordinates on the USB UART.

```c
void application_task ( void ) 
{
    nanogps3_process( &nanogps3 );
    if ( app_buf_len > ( sizeof( NANOGPS3_RSP_GNGGA ) + NANOGPS3_NMEA_GNGGA_NUM_ELEMENT ) ) 
    {
        nanogps3_parser_application( app_buf );
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
