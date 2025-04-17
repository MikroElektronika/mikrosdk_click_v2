
---
# GNSS 24 Click

> [GNSS 24 Click](https://www.mikroe.com/?pid_product=MIKROE-6551) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6551&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2025.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of GNSS 24 Click by reading and displaying the GNSS coordinates.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSS24

### Example Key Functions

- `gnss24_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void gnss24_cfg_setup ( gnss24_cfg_t *cfg );
```

- `gnss24_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t gnss24_init ( gnss24_t *ctx, gnss24_cfg_t *cfg );
```

- `gnss24_reset_device` This function resets the device by toggling the RST pin.
```c
void gnss24_reset_device ( gnss24_t *ctx );
```

- `gnss24_cmd_run` This function sends a specified command to the Click module.
```c
void gnss24_cmd_run ( gnss24_t *ctx, uint8_t *cmd );
```

- `gnss24_parse_gga` This function parses the GGA data from the read response buffer.
```c
err_t gnss24_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );
```

### Application Init

> Initializes the driver, resets the Click board, reads the module version, enables 1PPS output, and starts positioning.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss24_cfg_t gnss24_cfg;  /**< Click config object. */

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
    gnss24_cfg_setup( &gnss24_cfg );
    GNSS24_MAP_MIKROBUS( gnss24_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gnss24_init( &gnss24, &gnss24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, ">>> Reset device.\r\n" );
    gnss24_reset_device ( &gnss24 );
    
    log_printf( &logger, ">>> Get module version.\r\n" );
    gnss24_cmd_run ( &gnss24, GNSS24_CMD_FW_REV_NUM_ACQ );
    gnss24_read_response ( &gnss24, GNSS24_RSP_DONE );

    log_printf( &logger, ">>> Enable 1PPS output.\r\n" );
    gnss24_cmd_set ( &gnss24, GNSS24_CMD_1PPS_OUT_SET, "1" );
    gnss24_read_response ( &gnss24, GNSS24_RSP_DONE );

    log_printf( &logger, ">>> Start positioning.\r\n" );
    gnss24_cmd_run ( &gnss24, GNSS24_CMD_HOT_START_TTFF );
    gnss24_read_response ( &gnss24, GNSS24_RSP_DONE );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the received data, parses the NMEA GGA info from it, and once it receives the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    if ( GNSS24_OK == gnss24_process( &gnss24 ) ) 
    {
        if ( app_buf_len > ( sizeof ( GNSS24_RSP_GGA ) + GNSS24_GGA_ELEMENT_SIZE ) ) 
        {
            gnss24_parser_application( app_buf );
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
