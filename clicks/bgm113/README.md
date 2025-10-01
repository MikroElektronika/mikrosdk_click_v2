
---
# BGM113 Click

> [BGM113 Click](https://www.mikroe.com/?pid_product=MIKROE-6584) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6584&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2025.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the usage of the BGM113 Click board. The application initializes
the module, resets the device, checks communication, retrieves the BT address, 
and manages bondings. It also configures the device to be discoverable and bondable 
and handles various BT-related events such as connection state changes, 
security mode, and GATT operations.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BGM113

### Example Key Functions

- `bgm113_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void bgm113_cfg_setup ( bgm113_cfg_t *cfg );
```

- `bgm113_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t bgm113_init ( bgm113_t *ctx, bgm113_cfg_t *cfg );
```

- `bgm113_send_packet` This function sends a desired command packet from the Click context object.
```c
void bgm113_send_packet ( bgm113_t *ctx );
```

- `bgm113_read_packet` This function reads an event or response packet from the ring buffer and stores it in the Click context object.
```c
err_t bgm113_read_packet ( bgm113_t *ctx );
```

- `bgm113_set_gap_mode` This function configures the current BT LE GAP Connectable and Discoverable modes.
```c
err_t bgm113_set_gap_mode ( bgm113_t *ctx, uint8_t connectable, uint8_t discoverable );
```

### Application Init

> Initializes the logger and sets up the BGM113 Click configuration. Resets the device, 
checks communication, retrieves the BT address, and deletes existing bondings. 
Configures the device to be bondable and sets LE GAP modes.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bgm113_cfg_t bgm113_cfg;  /**< Click config object. */

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
    bgm113_cfg_setup( &bgm113_cfg );
    BGM113_MAP_MIKROBUS( bgm113_cfg, MIKROBUS_1 );
    if ( UART_ERROR == bgm113_init( &bgm113, &bgm113_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, ">> Reset Device\r\n" );
    if ( BGM113_OK == bgm113_reset_device ( &bgm113 ) )
    {   
        bgm113_parse_packet ( &bgm113 );
    }

    log_printf( &logger, ">> Check Communication\r\n" );
    if ( BGM113_OK == bgm113_check_communication ( &bgm113 ) )
    {   
        bgm113_parse_packet ( &bgm113 );
    }

    log_printf( &logger, ">> Get BT Address\r\n" );
    if ( BGM113_OK == bgm113_get_bt_address ( &bgm113 ) )
    {
        bgm113_parse_packet ( &bgm113 );
    }

    log_printf( &logger, ">> Delete Bondings\r\n" );
    if ( BGM113_OK == bgm113_delete_bondings ( &bgm113 ) )
    {
        bgm113_parse_packet ( &bgm113 );
    }
    
    log_printf( &logger, ">> Set Bondable Mode\r\n" );
    if ( BGM113_OK == bgm113_set_bondable_mode ( &bgm113, BGM113_SM_SET_BONDABLE_ALLOWED ) )
    {
        bgm113_parse_packet ( &bgm113 );
    }
    
    log_printf( &logger, ">> Set LE GAP Mode\r\n" );
    if ( BGM113_OK == bgm113_set_gap_mode ( &bgm113, BGM113_LE_GAP_UNDIRECTED_CONNECTABLE, 
                                                     BGM113_LE_GAP_GENERAL_DISCOVERABLE ) )
    {
        bgm113_parse_packet ( &bgm113 );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads packets from the BGM113, parses the contents, and logs relevant information 
regarding system events, BT connections, and bonding information.

```c
void application_task ( void )
{
    if ( BGM113_OK == bgm113_read_packet ( &bgm113 ) ) 
    {
        bgm113_parse_packet ( &bgm113 );
    }
}
```

### Note

> We recommend using the Simplicity Connect smartphone application for the test.

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
