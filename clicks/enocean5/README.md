
---
# EnOcean 5 Click

> [EnOcean 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6796) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6796&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2025.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates radio communication betweeen two EnOcean 5 Click boards.
The application performs a module reset, retrieves and logs device information,
sends text-based radio telegrams, and waits for received ERP1 messages.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EnOcean5

### Example Key Functions

- `enocean5_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void enocean5_cfg_setup ( enocean5_cfg_t *cfg );
```

- `enocean5_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t enocean5_init ( enocean5_t *ctx, enocean5_cfg_t *cfg );
```

- `enocean5_send_packet` This function sends TX packet from the Click context object.
```c
err_t enocean5_send_packet ( enocean5_t *ctx );
```

- `enocean5_read_packet` This function reads RX packet from the ring buffer and stores it in the Click context object.
```c
err_t enocean5_read_packet ( enocean5_t *ctx );
```

- `enocean5_read_info` This function reads the device information and stores it in the Click context object.
```c
err_t enocean5_read_info ( enocean5_t *ctx );
```

- `enocean5_send_radio_message` This function forms and sends the radio message telegram.
```c
err_t enocean5_send_radio_message ( enocean5_t *ctx, uint8_t rorg, uint8_t *data_in, uint8_t data_len );
```

### Application Init

> Initializes the logger and EnOcean 5 Click driver. 
Performs a hardware reset and reads module information including APP version, 
API version, and device identifiers.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    enocean5_cfg_t enocean5_cfg;  /**< Click config object. */

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
    enocean5_cfg_setup( &enocean5_cfg );
    ENOCEAN5_MAP_MIKROBUS( enocean5_cfg, MIKROBUS_1 );
    if ( UART_ERROR == enocean5_init( &enocean5, &enocean5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf ( &logger, "\r\n>> Hardware reset.\r\n" );
    if ( ENOCEAN5_OK != enocean5_reset_device ( &enocean5 ) )
    {
        log_error( &logger, " Hardware reset." );
        for ( ; ; );
    }
    enocean5_parse_packet ( &enocean5 );

    log_printf ( &logger, "\r\n>> Get device info.\r\n" );
    if ( ENOCEAN5_OK == enocean5_read_info ( &enocean5 ) )
    {
        log_printf ( &logger, " < APP version: %u.%u.%u.%u\r\n", 
                     ( uint16_t ) enocean5.info.app_ver[ 0 ], 
                     ( uint16_t ) enocean5.info.app_ver[ 1 ], 
                     ( uint16_t ) enocean5.info.app_ver[ 2 ], 
                     ( uint16_t ) enocean5.info.app_ver[ 3 ] );
        log_printf ( &logger, "   APP description: %s\r\n", enocean5.info.app_desc );
        log_printf ( &logger, "   API version: %u.%u.%u.%u\r\n", 
                     ( uint16_t ) enocean5.info.api_ver[ 0 ], 
                     ( uint16_t ) enocean5.info.api_ver[ 1 ], 
                     ( uint16_t ) enocean5.info.api_ver[ 2 ], 
                     ( uint16_t ) enocean5.info.api_ver[ 3 ] );
        log_printf ( &logger, "   Device ID: 0x%.8LX\r\n", enocean5.info.device_id );
        log_printf ( &logger, "   Device version: 0x%.8LX\r\n", enocean5.info.device_ver );
    }
}
```

### Application Task

> Sends "MIKROE" and "EnOcean 5" telegrams, waits for TX_DONE events, 
and listens for incoming ERP1 VLD telegrams, logging their content.

```c
void application_task ( void )
{
    log_printf ( &logger, "\r\n>> Sending \"%s\" radio telegram.\r\n", ( char * ) DEMO_TEXT_MESSAGE_1 );
    enocean5_send_radio_message ( &enocean5, ENOCEAN5_RORG_VLD, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    enocean5_wait_packet_w_parse ( &enocean5, ENOCEAN5_PKT_TYPE_EVENT, ENOCEAN5_EVT_TX_DONE, ENOCEAN5_WAIT_TIME_5S );

    log_printf ( &logger, "\r\n>> Waiting for radio telegram.\r\n" );
    enocean5_wait_packet_w_parse ( &enocean5, ENOCEAN5_PKT_TYPE_RADIO_ERP1, ENOCEAN5_RORG_VLD, ENOCEAN5_WAIT_TIME_5S );
    Delay_ms ( 1000 );

    log_printf ( &logger, "\r\n>> Sending \"%s\" radio telegram.\r\n", ( char * ) DEMO_TEXT_MESSAGE_2 );
    enocean5_send_radio_message ( &enocean5, ENOCEAN5_RORG_VLD, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    enocean5_wait_packet_w_parse ( &enocean5, ENOCEAN5_PKT_TYPE_EVENT, ENOCEAN5_EVT_TX_DONE, ENOCEAN5_WAIT_TIME_5S );

    log_printf ( &logger, "\r\n>> Waiting for radio telegram.\r\n" );
    enocean5_wait_packet_w_parse ( &enocean5, ENOCEAN5_PKT_TYPE_RADIO_ERP1, ENOCEAN5_RORG_VLD, ENOCEAN5_WAIT_TIME_5S );
    Delay_ms ( 1000 );
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
