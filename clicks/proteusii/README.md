
---
# Proteus-II Click

> [Proteus-II Click](https://www.mikroe.com/?pid_product=MIKROE-7157) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7157&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2026.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of Proteus-II Click board by processing data from a connected BT device.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ProteusII

### Example Key Functions

- `proteusii_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void proteusii_cfg_setup ( proteusii_cfg_t *cfg );
```

- `proteusii_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t proteusii_init ( proteusii_t *ctx, proteusii_cfg_t *cfg );
```

- `proteusii_reset_device` This function resets the device by toggling the reset pin logic state.
```c
err_t proteusii_reset_device ( proteusii_t *ctx )
```

- `proteusii_send_cmd` This function sends a desired command packet from the Click context object.
```c
void proteusii_send_cmd ( proteusii_t *ctx );
```

- `proteusii_read_event` This function reads an event packet from the ring buffer and stores it in the Click context object.
```c
err_t proteusii_read_event ( proteusii_t *ctx );
```

- `proteusii_get_user_setting` This function reads data from the desired user settings index and stores it in the Click context event packet object.
```c
err_t proteusii_get_user_setting ( proteusii_t *ctx, uint8_t set_idx );
```

### Application Init

> Initializes the driver, resets and configures the Click board, and reads the device info.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proteusii_cfg_t proteusii_cfg;  /**< Click config object. */

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
    proteusii_cfg_setup( &proteusii_cfg );
    PROTEUSII_MAP_MIKROBUS( proteusii_cfg, MIKROBUS_POSITION_PROTEUSII );
    if ( UART_ERROR == proteusii_init( &proteusii, &proteusii_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, ">> Reset device.\r\n" );
    if ( PROTEUSII_OK == proteusii_reset_device ( &proteusii ) )
    {
        log_printf( &logger, " < OK.\r\n" );
    }
    else
    {
        log_error( &logger, " Reset device." );
        for ( ; ; );
    }

    log_printf( &logger, ">> Get device info.\r\n" );
    if ( PROTEUSII_OK == proteusii_get_user_setting ( &proteusii, PROTEUSII_SET_IDX_FS_DEVICE_INFO ) )
    {
        log_printf( &logger, " < OS version: 0x%.2X%.2X\r\n",
                    ( uint16_t ) proteusii.evt_pkt.payload[ 2 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 1 ] );
        log_printf( &logger, "   Build code: 0x%.2X%.2X%.2X%.2X\r\n",
                    ( uint16_t ) proteusii.evt_pkt.payload[ 6 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 5 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 4 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 3 ] );
        log_printf( &logger, "   Package variant: 0x%.2X%.2X\r\n",
                    ( uint16_t ) proteusii.evt_pkt.payload[ 8 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 7 ] );
        log_printf( &logger, "   Chip ID: 0x%.2X%.2X%.2X%.2X\r\n\n",
                    ( uint16_t ) proteusii.evt_pkt.payload[ 12 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 11 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 10 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 9 ] );
    }

    log_printf( &logger, ">> Get FW version.\r\n" );
    if ( PROTEUSII_OK == proteusii_get_user_setting ( &proteusii, PROTEUSII_SET_IDX_FS_FW_VERSION ) )
    {
        log_printf( &logger, " < FW version: %u.%u.%u\r\n\n",
                    ( uint16_t ) proteusii.evt_pkt.payload[ 3 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 2 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 1 ] );
    }

    log_printf( &logger, ">> Get BT MAC.\r\n" );
    if ( PROTEUSII_OK == proteusii_get_user_setting ( &proteusii, PROTEUSII_SET_IDX_FS_BTMAC ) )
    {
        log_printf( &logger, " < BT MAC: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n\n",
                    ( uint16_t ) proteusii.evt_pkt.payload[ 6 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 5 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 4 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 3 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 2 ],
                    ( uint16_t ) proteusii.evt_pkt.payload[ 1 ] );
    }

    log_printf( &logger, ">> Get device name.\r\n" );
    if ( PROTEUSII_OK == proteusii_get_user_setting ( &proteusii, PROTEUSII_SET_IDX_RF_DEVICE_NAME ) )
    {
        log_printf( &logger, " < Device name: \"%s\"\r\n\n", &proteusii.evt_pkt.payload[ 1 ] );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and parses all the received event packets and displays them on the USB UART.
All incoming data messages received from the connected device will be echoed back.

```c
void application_task ( void )
{
    if ( PROTEUSII_OK == proteusii_read_event ( &proteusii ) )
    {
        proteusii_parse_event ( &proteusii );
    }
}
```

### Note

> Set MODE to C for normal command mode. Use the WE Bluetooth LE Terminal smartphone application and enable notifications before sending data.

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
