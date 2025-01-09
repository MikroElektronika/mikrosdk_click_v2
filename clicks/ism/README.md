
---
# ISM Click

> [ISM Click](https://www.mikroe.com/?pid_product=MIKROE-4625) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4625&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for the ISM Click driver.
> This example transmits/receives and processes data from ISM Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ism

### Example Key Functions

- `ism_cfg_setup` Config Object Initialization function.
```c
void ism_cfg_setup ( ism_cfg_t *cfg );
```

- `ism_init` Initialization function.
```c
err_t ism_init ( ism_t *ctx, ism_cfg_t *cfg );
```

- `ism_default_cfg` Click Default Configuration function.
```c
void ism_default_cfg ( ism_t *ctx );
```

- `ism_device_config` ISM device configuration function.
```c
err_t ism_device_config ( ism_t *ctx );
```

- `ism_receive_packet` ISM receive packet function.
```c
err_t ism_receive_packet ( ism_t *ctx, uint8_t *rx_data );
```

- `ism_transmit_packet` ISM transmit package function.
```c
err_t ism_transmit_packet ( ism_t *ctx, uint8_t type, uint8_t *tx_data, uint8_t len );
```

### Application Init

> Initializes driver and performs the default configuration. 

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ism_cfg_t ism_cfg;  /**< Click config object. */

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
    ism_cfg_setup( &ism_cfg );
    ISM_MAP_MIKROBUS( ism_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ism_init( &ism, &ism_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    ism_default_cfg ( &ism );
    Delay_ms ( 100 );
    
#ifdef DEMO_APP_TRANSMITTER
    ism_switch_tx_mode( &ism );
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    ism_switch_rx_mode( &ism );
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Transmitter/Receiver task depends on uncommented code.
> Receiver logging each received byte to the UART for data logging,
> while transmitter send messages every 1 second.

```c
void application_task ( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    ism_transmit_packet( &ism, ISM_CMD_W_TX_PAYLOAD_NOACK, demo_message_1, 9 );
    log_printf( &logger, "  Tx : %s", demo_message_1 );
    Delay_ms ( 1000 );

    ism_transmit_packet( &ism, ISM_CMD_W_TX_PAYLOAD_NOACK, demo_message_2, 12 );
    log_printf( &logger, "  Tx : %s", demo_message_2 );
    Delay_ms ( 1000 );
#else
    uint8_t rx_buf[ ISM_MAX_PACKET_LEN ] = { 0 };

    ism_receive_packet( &ism, &rx_buf[ 0 ] );

    if ( rx_buf[ 0 ] ) 
    {
        log_printf( &logger, "  Rx : %s", rx_buf );
    }
#endif
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
