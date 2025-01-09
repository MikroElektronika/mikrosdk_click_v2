
---
# Proteus-e Click

> [Proteus-e Click](https://www.mikroe.com/?pid_product=MIKROE-6429) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6429&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of Proteus-e Click board by processing data from a connected BT device.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proteuse

### Example Key Functions

- `proteuse_cfg_setup` Config Object Initialization function.
```c
void proteuse_cfg_setup ( proteuse_cfg_t *cfg );
```

- `proteuse_init` Initialization function.
```c
err_t proteuse_init ( proteuse_t *ctx, proteuse_cfg_t *cfg );
```

- `proteuse_default_cfg` Click Default Configuration function.
```c
err_t proteuse_default_cfg ( proteuse_t *ctx );
```

- `proteuse_send_cmd` This function sends a desired command packet from the Click context object.
```c
void proteuse_send_cmd ( proteuse_t *ctx );
```

- `proteuse_read_event` This function reads an event packet from the ring buffer and stores it in the Click context object.
```c
err_t proteuse_read_event ( proteuse_t *ctx );
```

- `proteuse_get_user_setting` This function reads data from the desired user settings index and stores it in the Click context event packet object.
```c
err_t proteuse_get_user_setting ( proteuse_t *ctx, uint8_t set_idx );
```

### Application Init

> Initializes the driver, resets and configures the Click board, and reads the device info.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proteuse_cfg_t proteuse_cfg;  /**< Click config object. */

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
    proteuse_cfg_setup( &proteuse_cfg );
    PROTEUSE_MAP_MIKROBUS( proteuse_cfg, MIKROBUS_1 );
    if ( UART_ERROR == proteuse_init( &proteuse, &proteuse_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROTEUSE_ERROR == proteuse_default_cfg ( &proteuse ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, ">> Get device info.\r\n" );
    if ( PROTEUSE_OK == proteuse_get_user_setting ( &proteuse, PROTEUSE_SET_IDX_FS_DEVICE_INFO ) ) 
    {
        log_printf( &logger, " < OS version: 0x%.2X%.2X\r\n", 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 2 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 1 ] );
        log_printf( &logger, "   Build code: 0x%.2X%.2X%.2X%.2X\r\n", 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 6 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 5 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 4 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 3 ] );
        log_printf( &logger, "   Package variant: 0x%.2X%.2X\r\n", 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 8 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 7 ] );
        log_printf( &logger, "   Chip ID: 0x%.2X%.2X%.2X%.2X\r\n\n", 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 12 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 11 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 10 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 9 ] );
    }

    log_printf( &logger, ">> Get FW version.\r\n" );
    if ( PROTEUSE_OK == proteuse_get_user_setting ( &proteuse, PROTEUSE_SET_IDX_FS_FW_VERSION ) ) 
    {
        log_printf( &logger, " < FW version: %u.%u.%u\r\n\n", 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 3 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 2 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 1 ] );
    }

    log_printf( &logger, ">> Get BT MAC.\r\n" );
    if ( PROTEUSE_OK == proteuse_get_user_setting ( &proteuse, PROTEUSE_SET_IDX_FS_BTMAC ) ) 
    {
        log_printf( &logger, " < BT MAC: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n\n", 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 6 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 5 ],
                    ( uint16_t ) proteuse.evt_pkt.payload[ 4 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 3 ],
                    ( uint16_t ) proteuse.evt_pkt.payload[ 2 ], 
                    ( uint16_t ) proteuse.evt_pkt.payload[ 1 ] );
    }

    log_printf( &logger, ">> Set device name to \"%s\".\r\n", ( char * ) DEVICE_NAME );
    if ( PROTEUSE_OK == proteuse_set_user_setting ( &proteuse, PROTEUSE_SET_IDX_RF_DEVICE_NAME, 
                                                    DEVICE_NAME, strlen ( DEVICE_NAME ) ) )
    {
        log_printf( &logger, " < Request received, settings set successfully\r\n\n" );
    }

    log_printf( &logger, ">> Get device name.\r\n" );
    if ( PROTEUSE_OK == proteuse_get_user_setting ( &proteuse, PROTEUSE_SET_IDX_RF_DEVICE_NAME ) ) 
    {
        log_printf( &logger, " < Device name: \"%s\"\r\n\n", &proteuse.evt_pkt.payload[ 1 ] );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and parses all the received event packets and displays them the USB UART. All incoming data messages received from the connected device will be echoed back.

```c
void application_task ( void )
{
    if ( PROTEUSE_OK == proteuse_read_event ( &proteuse ) ) 
    {
        proteuse_parse_event ( &proteuse );
    }
}
```

### Note

> We recommend using the WE Bluetooth LE Terminal smartphone application for the test.

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
