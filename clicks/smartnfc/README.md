
---
# Smart NFC Click

> [Smart NFC Click](https://www.mikroe.com/?pid_product=MIKROE-6617) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6617&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2025.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of the Smart NFC Click board for detecting and 
reading NFC tags. The application resets the NFC module, retrieves the firmware 
version, and continuously scans for nearby NFC tags, displaying their UID and type.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartNFC

### Example Key Functions

- `smartnfc_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void smartnfc_cfg_setup ( smartnfc_cfg_t *cfg );
```

- `smartnfc_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t smartnfc_init ( smartnfc_t *ctx, smartnfc_cfg_t *cfg );
```

- `smartnfc_send_frame` This function sends a desired command frame from the Click context object.
```c
err_t smartnfc_send_frame ( smartnfc_t *ctx );
```

- `smartnfc_read_frame` This function reads response frame from the ring buffer and stores it in the Click context object.
```c
err_t smartnfc_read_frame ( smartnfc_t *ctx );
```

- `smartnfc_read_ack_frame` This function waits for the desired acknowledge frame to arrive and stores it in the Click context object.
```c
err_t smartnfc_read_ack_frame ( smartnfc_t *ctx, uint8_t cmd );
```

### Application Init

> Initializes the logger and configures the Smart NFC Click board. It establishes 
UART communication, resets the NFC module, and retrieves the firmware version 
to verify proper operation.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartnfc_cfg_t smartnfc_cfg;  /**< Click config object. */

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
    smartnfc_cfg_setup( &smartnfc_cfg );
    SMARTNFC_MAP_MIKROBUS( smartnfc_cfg, MIKROBUS_1 );
    if ( UART_ERROR == smartnfc_init( &smartnfc, &smartnfc_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, ">> Reset Device\r\n" );
    if ( SMARTNFC_OK == smartnfc_reset_device ( &smartnfc ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
    }
    
    log_printf( &logger, ">> Get Version\r\n" );
    smartnfc.cmd_frame.cmd = SMARTNFC_CMD_GET_VERSION;
    smartnfc.cmd_frame.payload_len = 0;
    smartnfc_send_frame ( &smartnfc );
    if ( SMARTNFC_OK == smartnfc_read_ack_frame ( &smartnfc, SMARTNFC_CMD_GET_VERSION ) )
    {
        log_printf ( &logger, "%s\r\n", &smartnfc.rsp_frame.payload[ 1 ] );
        log_printf( &logger, "--------------------------------\r\n" );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously scans for NFC tags and retrieves their unique identifiers (UID). 
If tags are detected, it logs their type, parameters, and UID values. The process 
repeats at 1-second intervals.

```c
void application_task ( void )
{
    uint8_t num_tags_found = 0;
    log_printf( &logger, ">> Get Tag Count\r\n" );
    smartnfc.cmd_frame.cmd = SMARTNFC_CMD_GET_TAG_COUNT;
    smartnfc.cmd_frame.payload_len = 0;
    smartnfc_send_frame ( &smartnfc );
    if ( SMARTNFC_OK == smartnfc_read_ack_frame ( &smartnfc, SMARTNFC_CMD_GET_TAG_COUNT ) )
    {
        log_printf ( &logger, "Number of tags found: %u\r\n", ( uint16_t ) smartnfc.rsp_frame.payload[ 1 ] );
        log_printf( &logger, "--------------------------------\r\n" );
        num_tags_found = smartnfc.rsp_frame.payload[ 1 ];
        for ( uint8_t tag_idx = 0; tag_idx < num_tags_found; tag_idx++ )
        {
            log_printf( &logger, ">> Get Tag UID\r\n" );
            smartnfc.cmd_frame.cmd = SMARTNFC_CMD_GET_TAG_UID;
            smartnfc.cmd_frame.payload[ 0 ] = tag_idx;
            smartnfc.cmd_frame.payload_len = 1;
            smartnfc_send_frame ( &smartnfc );
            if ( SMARTNFC_OK == smartnfc_read_ack_frame ( &smartnfc, SMARTNFC_CMD_GET_TAG_UID ) )
            {
                log_printf ( &logger, "Tag Type: 0x%.2X\r\n", ( uint16_t ) smartnfc.rsp_frame.payload[ 1 ] );
                log_printf ( &logger, "Tag Parameter: 0x%.2X\r\n", ( uint16_t ) smartnfc.rsp_frame.payload[ 2 ] );
                log_printf ( &logger, "UID:" );
                for ( uint8_t cnt_uid = 0; cnt_uid < ( smartnfc.rsp_frame.payload_len - 3 ); cnt_uid++ )
                {
                    log_printf ( &logger, " %.2X", ( uint16_t ) smartnfc.rsp_frame.payload[ 3 + cnt_uid ] );
                }
                log_printf( &logger, "\r\n--------------------------------\r\n" );
            }
        }
    }
    Delay_ms ( 1000 );
}
```

### Note

> A proper 13.56 MHz PCB NFC antenna must be attached to the Click board module for optimal tag detection.

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
