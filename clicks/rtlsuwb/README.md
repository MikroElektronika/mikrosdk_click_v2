
---
# RTLS UWB Click

> [RTLS UWB Click](https://www.mikroe.com/?pid_product=MIKROE-6863) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6863&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2026.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of an RTLS UWB Click board by showing
the two-way ranging (TWR) communication between two or three Click boards.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RTLSUWB

### Example Key Functions

- `rtlsuwb_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void rtlsuwb_cfg_setup ( rtlsuwb_cfg_t *cfg );
```

- `rtlsuwb_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t rtlsuwb_init ( rtlsuwb_t *ctx, rtlsuwb_cfg_t *cfg );
```

- `rtlsuwb_cmd_run` This function sends a specified command to the Click module.
```c
void rtlsuwb_cmd_run ( rtlsuwb_t *ctx, uint8_t *cmd );
```

- `rtlsuwb_cmd_set` This function sets a value to a specified command of the Click module.
```c
void rtlsuwb_cmd_set ( rtlsuwb_t *ctx, uint8_t *cmd, uint8_t *value );
```

- `rtlsuwb_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t rtlsuwb_generic_read ( rtlsuwb_t *ctx, uint8_t *data_out, uint16_t len );
```

### Application Init

> Initializes the logger and RTLS UWB Click driver, resets the device,
switches it to stop mode, and configures the selected application mode
as initiator or responder.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtlsuwb_cfg_t rtlsuwb_cfg;  /**< Click config object. */

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
    rtlsuwb_cfg_setup( &rtlsuwb_cfg );
    RTLSUWB_MAP_MIKROBUS( rtlsuwb_cfg, MIKROBUS_POSITION_RTLSUWB );
    if ( UART_ERROR == rtlsuwb_init( &rtlsuwb, &rtlsuwb_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    rtlsuwb_reset_device ( &rtlsuwb );
    
    log_printf( &logger, ">>> Switch to stop mode.\r\n" );
    rtlsuwb_cmd_run( &rtlsuwb, RTLSUWB_CMD_STOP );
    rtlsuwb_read_response( &rtlsuwb, RTLSUWB_RSP_OK, RTLSUWB_MAX_RSP_TIME_DEFAULT );
    Delay_ms ( 1000 );
    
#if ( DEMO_APP == APP_RESPONDER_1 )
    rtlsuwb_cmd_set ( &rtlsuwb, RTLSUWB_CMD_RESPF, RESPONDER_1_CONFIG );
    rtlsuwb_read_response( &rtlsuwb, RTLSUWB_RSP_OK, RTLSUWB_MAX_RSP_TIME_DEFAULT );
    log_printf( &logger, "Application Mode: Responder 1\r\n" );
#elif ( DEMO_APP == APP_RESPONDER_2 )
    rtlsuwb_cmd_set ( &rtlsuwb, RTLSUWB_CMD_RESPF, RESPONDER_2_CONFIG );
    rtlsuwb_read_response( &rtlsuwb, RTLSUWB_RSP_OK, RTLSUWB_MAX_RSP_TIME_DEFAULT );
    log_printf( &logger, "Application Mode: Responder 2\r\n" );
#else
    rtlsuwb_cmd_set ( &rtlsuwb, RTLSUWB_CMD_INITF, INITIATOR_CONFIG );
    rtlsuwb_read_response( &rtlsuwb, RTLSUWB_RSP_OK, RTLSUWB_MAX_RSP_TIME_DEFAULT );
    log_printf( &logger, "Application Mode: Initiator\r\n" );
#endif
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays all incoming messages on the USB UART. One Click board
should be configured to APP_INITIATOR and the others to APP_RESPONDER_1 and APP_RESPONDER_2.
The initiator Click displays the address and distance of each responder nodes, while
the responder Click boards displays the address and distance of the initiator Click board.

```c
void application_task ( void )
{
    rtlsuwb_read_response( &rtlsuwb, RTLSUWB_RSP_BLOCK_END, RTLSUWB_MAX_RSP_TIME_DEFAULT );
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
