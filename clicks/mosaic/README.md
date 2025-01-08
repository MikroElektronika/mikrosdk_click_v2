
---
# Mosaic Click

> [Mosaic Click](https://www.mikroe.com/?pid_product=MIKROE-6087) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6087&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of Mosaic Click by reading and displaying the GNSS coordinates.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mosaic

### Example Key Functions

- `mosaic_cfg_setup` Config Object Initialization function.
```c
void mosaic_cfg_setup ( mosaic_cfg_t *cfg );
```

- `mosaic_init` Initialization function.
```c
err_t mosaic_init ( mosaic_t *ctx, mosaic_cfg_t *cfg );
```

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
