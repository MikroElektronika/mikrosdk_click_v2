
---
# M-BUS RF 5 Click

> [M-BUS RF 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6763) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6763&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2025.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of the M-BUS RF 5 Click board in both
transmitter and receiver modes. The transmitter sends a predefined text 
message, while the receiver listens and parses incoming data packets.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MBUSRF5

### Example Key Functions

- `mbusrf5_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void mbusrf5_cfg_setup ( mbusrf5_cfg_t *cfg );
```

- `mbusrf5_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t mbusrf5_init ( mbusrf5_t *ctx, mbusrf5_cfg_t *cfg );
```

- `mbusrf5_send_cmd` This function sends a desired command packet from the Click context object.
```c
err_t mbusrf5_send_cmd ( mbusrf5_t *ctx );
```

- `mbusrf5_read_event` This function reads an event packet from the ring buffer and stores it in the Click context object.
```c
err_t mbusrf5_read_event ( mbusrf5_t *ctx );
```

- `mbusrf5_set_user_setting_ram` This function writes data to a desired user settings option in RAM.
```c
err_t mbusrf5_set_user_setting_ram ( mbusrf5_t *ctx, uint8_t option, uint8_t data_in );
```

### Application Init

> Initializes the logger, the M-BUS RF 5 Click driver, resets the device, 
retrieves the firmware version, and configures the device role and settings 
depending on the selected mode (transmitter or receiver).

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mbusrf5_cfg_t mbusrf5_cfg;  /**< Click config object. */

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
    mbusrf5_cfg_setup( &mbusrf5_cfg );
    MBUSRF5_MAP_MIKROBUS( mbusrf5_cfg, MIKROBUS_1 );
    if ( UART_ERROR == mbusrf5_init( &mbusrf5, &mbusrf5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, ">> Reset device.\r\n" );
    if ( MBUSRF5_ERROR == mbusrf5_reset_device ( &mbusrf5 ) )
    {
        log_error( &logger, " Reset device." );
        for ( ; ; );
    }
    mbusrf5_parse_event ( &mbusrf5 );

    log_printf( &logger, ">> Get FW version.\r\n" );
    if ( MBUSRF5_OK == mbusrf5_get_user_setting_flash ( &mbusrf5, MBUSRF5_OPT_FW_VERSION ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }

#ifdef DEMO_TRANSMITTER
    log_printf( &logger, ">> Set device role.\r\n" );
    if ( MBUSRF5_OK == mbusrf5_set_user_setting_ram ( &mbusrf5, MBUSRF5_OPT_WMBUS_ROLE, MBUSRF5_WMBUS_ROLE_METER ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }
    log_printf( &logger, ">> Get device role.\r\n" );
    if ( MBUSRF5_OK == mbusrf5_get_user_setting_ram ( &mbusrf5, MBUSRF5_OPT_WMBUS_ROLE ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }

    log_info( &logger, " Application Task " );

    log_printf( &logger, ">> Send message to receiver device.\r\n" );
    mbusrf5.cmd_pkt.cmd = MBUSRF5_CMD_REQ_DATAEX;
    mbusrf5.cmd_pkt.payload_len = strlen ( DEMO_TEXT_MESSAGE ) + 8;
    mbusrf5.cmd_pkt.payload[ 0 ] = MBUSRF5_OPT_WMBUS_TX_MODE;
    mbusrf5.cmd_pkt.payload[ 1 ] = 1;
    mbusrf5.cmd_pkt.payload[ 2 ] = MBUSRF5_WMBUS_TX_MODE_S;
    mbusrf5.cmd_pkt.payload[ 3 ] = MBUSRF5_OPT_WMBUS_FRAME_FORMAT;
    mbusrf5.cmd_pkt.payload[ 4 ] = 1;
    mbusrf5.cmd_pkt.payload[ 5 ] = MBUSRF5_WMBUS_FRAME_FORMAT_A;
    mbusrf5.cmd_pkt.payload[ 6 ] = MBUSRF5_OPT_WMBUS_DATA;
    mbusrf5.cmd_pkt.payload[ 7 ] = strlen ( DEMO_TEXT_MESSAGE );
    memcpy ( &mbusrf5.cmd_pkt.payload[ 8 ], DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) );
    if ( MBUSRF5_OK == mbusrf5_send_cmd ( &mbusrf5 ) )
    {
        if ( MBUSRF5_OK == mbusrf5_wait_for_event ( &mbusrf5, MBUSRF5_CMD_CNF_DATAEX, MBUSRF5_WAIT_TIME_1S ) ) 
        {
            mbusrf5_parse_event ( &mbusrf5 );
        }
    }
#else
    log_printf( &logger, ">> Set device role.\r\n" );
    if ( MBUSRF5_OK == mbusrf5_set_user_setting_ram ( &mbusrf5, MBUSRF5_OPT_WMBUS_ROLE, MBUSRF5_WMBUS_ROLE_GATEWAY ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }
    log_printf( &logger, ">> Get device role.\r\n" );
    if ( MBUSRF5_OK == mbusrf5_get_user_setting_ram ( &mbusrf5, MBUSRF5_OPT_WMBUS_ROLE ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }
    log_printf( &logger, ">> Set RX mode.\r\n" );
    if ( MBUSRF5_OK == mbusrf5_set_user_setting_ram ( &mbusrf5, MBUSRF5_OPT_WMBUS_RX_MODE, MBUSRF5_WMBUS_RX_MODE_S ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }
    log_printf( &logger, ">> Get RX mode.\r\n" );
    if ( MBUSRF5_OK == mbusrf5_get_user_setting_ram ( &mbusrf5, MBUSRF5_OPT_WMBUS_RX_MODE ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }
    log_printf( &logger, ">> Set CFG flags.\r\n" );
    if ( MBUSRF5_OK == mbusrf5_set_user_setting_ram ( &mbusrf5, MBUSRF5_OPT_CFG_FLAGS, MBUSRF5_CFG_FLAGS_RSSI_AND_TIMESTAMP_ENABLED ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }
    log_printf( &logger, ">> Get CFG flags.\r\n" );
    if ( MBUSRF5_OK == mbusrf5_get_user_setting_ram ( &mbusrf5, MBUSRF5_OPT_CFG_FLAGS ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }
    log_printf( &logger, ">> Enter RX mode.\r\n" );
    mbusrf5.cmd_pkt.cmd = MBUSRF5_CMD_REQ_DATARX_START;
    mbusrf5.cmd_pkt.payload_len = 0;
    if ( MBUSRF5_OK == mbusrf5_send_cmd ( &mbusrf5 ) )
    {
        if ( MBUSRF5_OK == mbusrf5_wait_for_event ( &mbusrf5, MBUSRF5_CMD_CNF_DATARX_START, MBUSRF5_WAIT_TIME_1S ) ) 
        {
            mbusrf5_parse_event ( &mbusrf5 );
        }
    }

    log_info( &logger, " Application Task " );
#endif
}
```

### Application Task

> In transmitter mode, sends a demo message repeatedly and waits for confirmation events.  
In receiver mode, continuously listens for incoming messages, parses, and logs the received data.

```c
void application_task ( void )
{
    if ( MBUSRF5_OK == mbusrf5_read_event ( &mbusrf5 ) ) 
    {
        mbusrf5_parse_event ( &mbusrf5 );
    }
}
```

### Note

> Ensure that two M-BUS RF 5 Click boards are available for proper demo 
operation: one configured as a transmitter and the other as a receiver.

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
