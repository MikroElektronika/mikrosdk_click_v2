
---
# ISM 9 Click

> [ISM 9 Click](https://www.mikroe.com/?pid_product=MIKROE-6911) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6911&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2026.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of ISM 9 Click board by showing the communication between two Click boards.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ISM9

### Example Key Functions

- `ism9_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void ism9_cfg_setup ( ism9_cfg_t *cfg );
```

- `ism9_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t ism9_init ( ism9_t *ctx, ism9_cfg_t *cfg );
```

- `ism9_send_cmd` This function sends a desired command packet from the Click context object.
```c
err_t ism9_send_cmd ( ism9_t *ctx );
```

- `ism9_read_event` This function reads an event packet from the ring buffer and stores it in the Click context object.
```c
err_t ism9_read_event ( ism9_t *ctx );
```

- `ism9_get_user_setting` This function reads data from the desired user settings index and stores it in the Click context event packet object.
```c
err_t ism9_get_user_setting ( ism9_t *ctx, uint8_t set_idx );
```

### Application Init

> Initializes the driver, resets the Click board, reads the device info, and sends a message to initiate the communication with other Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ism9_cfg_t ism9_cfg;  /**< Click config object. */

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
    ism9_cfg_setup( &ism9_cfg );
    ISM9_MAP_MIKROBUS( ism9_cfg, MIKROBUS_POSITION_ISM9 );
    if ( UART_ERROR == ism9_init( &ism9, &ism9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, ">> Reset device.\r\n" );
    if ( ISM9_ERROR == ism9_reset_device ( &ism9 ) )
    {
        log_error( &logger, " Reset device." );
        for ( ; ; );
    }
    ism9_parse_event ( &ism9 );
    
    log_printf( &logger, ">> Get device info.\r\n" );
    if ( ISM9_OK == ism9_get_user_setting ( &ism9, ISM9_SET_IDX_FACTORY_SETTINGS ) ) 
    {
        log_printf( &logger, " < Serial number: 0x%.2X%.2X%.2X%.2X\r\n", 
                    ( uint16_t ) ism9.evt_pkt.payload[ 4 ], 
                    ( uint16_t ) ism9.evt_pkt.payload[ 3 ], 
                    ( uint16_t ) ism9.evt_pkt.payload[ 2 ], 
                    ( uint16_t ) ism9.evt_pkt.payload[ 1 ] );
        log_printf( &logger, "   Hardware version: %u.%u.%u\r\n", 
                    ( uint16_t ) ism9.evt_pkt.payload[ 5 ], 
                    ( uint16_t ) ism9.evt_pkt.payload[ 6 ], 
                    ( uint16_t ) ism9.evt_pkt.payload[ 7 ] );
        log_printf( &logger, "   Frequency correction factor: %u\r\n",  
                    ( uint16_t ) ism9.evt_pkt.payload[ 8 ] );
    }

    log_printf( &logger, ">> Get FW version.\r\n" );
    if ( ISM9_OK == ism9_get_user_setting ( &ism9, ISM9_SET_IDX_FIRMWARE_VERSION ) ) 
    {
        log_printf( &logger, " < FW version: %u.%u.%u\r\n\n", 
                    ( uint16_t ) ism9.evt_pkt.payload[ 3 ], 
                    ( uint16_t ) ism9.evt_pkt.payload[ 2 ], 
                    ( uint16_t ) ism9.evt_pkt.payload[ 1 ] );
    }

    log_printf( &logger, ">> Send message to initiate communication.\r\n" );
    ism9.cmd_pkt.cmd = ISM9_CMD_REQ_DATA;
    ism9.cmd_pkt.payload_len = strlen ( DEMO_TEXT_MESSAGE );
    strcpy ( ism9.cmd_pkt.payload, DEMO_TEXT_MESSAGE );
    if ( ISM9_OK == ism9_send_cmd ( &ism9 ) )
    {
        if ( ISM9_OK == ism9_wait_for_event ( &ism9, ISM9_CMD_CNF_DATA, ISM9_WAIT_TIME_1S ) ) 
        {
            ism9_parse_event ( &ism9 );
        }
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and parses all the received event packets and displays them the USB UART.
All incoming data messages received from the connected device will be echoed back.

```c
void application_task ( void )
{
    if ( ISM9_OK == ism9_read_event ( &ism9 ) ) 
    {
        ism9_parse_event ( &ism9 );
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
