
---
# Mosaic 2 Click

> [Mosaic 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6931) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6931&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2026.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of Mosaic 2 Click by reading and displaying the GNSS coordinates.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mosaic2

### Example Key Functions

- `mosaic2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void mosaic2_cfg_setup ( mosaic2_cfg_t *cfg );
```

- `mosaic2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t mosaic2_init ( mosaic2_t *ctx, mosaic2_cfg_t *cfg );
```

- `mosaic2_enable_nmea_output` This function enables the NMEA output with the selected message parameters and an output interval.
```c
void mosaic2_enable_nmea_output ( mosaic2_t *ctx, uint8_t *msg_param, uint8_t *interval );
```

- `mosaic2_parse_gga` This function parses the GGA data from the read response buffer.
```c
err_t mosaic2_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );
```

- `mosaic2_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t mosaic2_generic_read ( mosaic2_t *ctx, uint8_t *data_out, uint16_t len );
```

### Application Init

> Initializes the driver, reads the NMEA version, and enables the NMEA output.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mosaic2_cfg_t mosaic2_cfg;  /**< Click config object. */

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
    mosaic2_cfg_setup( &mosaic2_cfg );
    MOSAIC2_MAP_MIKROBUS( mosaic2_cfg, MIKROBUS_POSITION_MOSAIC2 );
    if ( UART_ERROR == mosaic2_init( &mosaic2, &mosaic2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MOSAIC2_OK != mosaic2_wait_prompt( &mosaic2 ) )
    {
        log_error( &logger, " No connection prompt detected." );
        for ( ; ; );
    }
    mosaic2_log_app_buf( );
    mosaic2_clear_app_buf( );
    Delay_ms ( 100 );

    mosaic2_cmd_run( &mosaic2, MOSAIC2_CMD_GET_NMEA_VERSION );
    mosaic2_wait_prompt( &mosaic2 );
    mosaic2_log_app_buf( );
    mosaic2_clear_app_buf( );
    Delay_ms ( 100 );

    mosaic2_enable_nmea_output( &mosaic2, MOSAIC2_SNO_MESSAGES_GGA, MOSAIC2_SNO_INTERVAL_SEC1 );
    mosaic2_wait_prompt( &mosaic2 );
    mosaic2_log_app_buf( );
    mosaic2_clear_app_buf( );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the received data, parses the NMEA GGA info from it, and once it receives 
the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    mosaic2_process( &mosaic2 );
    if ( app_buf_len > ( sizeof ( MOSAIC2_NMEA_GGA ) + MOSAIC2_GGA_ELEMENT_SIZE ) ) 
    {
        mosaic2_parser_application( app_buf );
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
