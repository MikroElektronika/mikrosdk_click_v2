
---
# MiWi 2 Click

> [MiWi 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2925) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2925&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Mar 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates basic transmit and receive functionality of the
MiWi 2 Click board based on the MRF89XA sub-GHz transceiver. The application
configures the device to operate at 915 MHz using FSK modulation in packet
mode with a bit rate of 5 kbps and frequency deviation of 33 kHz.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MiWi2

### Example Key Functions

- `miwi2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void miwi2_cfg_setup ( miwi2_cfg_t *cfg );
```

- `miwi2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t miwi2_init ( miwi2_t *ctx, miwi2_cfg_t *cfg );
```

- `miwi2_default_cfg` This function executes a default configuration of MiWi 2 Click board.
```c
err_t miwi2_default_cfg ( miwi2_t *ctx );
```

- `miwi2_set_mode` This function sets RF operating mode by updating GCONREG.CMOD[7:5] field.
```c
err_t miwi2_set_mode ( miwi2_t *ctx, uint8_t mode );
```

- `miwi2_tx_packet` This function loads FIFO with payload bytes and switches to TX mode.
```c
err_t miwi2_tx_packet ( miwi2_t *ctx, uint8_t *payload );
```

- `miwi2_rx_packet` This function reads a fixed number of bytes from the device FIFO using SPI DATA interface.
```c
err_t miwi2_rx_packet ( miwi2_t *ctx, uint8_t *payload );
```

### Application Init

> Initializes the logger and driver, performs the default radio configuration,
and sets the device into transmitter or receiver mode depending on the
selected demo macro.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    miwi2_cfg_t miwi2_cfg;  /**< Click config object. */

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
    miwi2_cfg_setup( &miwi2_cfg );
    MIWI2_MAP_MIKROBUS( miwi2_cfg, MIKROBUS_POSITION_MIWI2 );
    if ( SPI_MASTER_ERROR == miwi2_init( &miwi2, &miwi2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MIWI2_ERROR == miwi2_default_cfg ( &miwi2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
#ifdef DEMO_APP_TRANSMITTER
    log_info( &logger, " *** TX MODE ***" );
    log_printf( &logger, "915 MHz | FSK | 5kbps | 33Khz frequency deviation | %u B payload\r\n", MIWI2_PAYLOAD_LEN );
    log_printf( &logger, "-----------------------------------\r\n" );
    Delay_ms( 200 );
#else
    /* Enter RX mode immediately */
    miwi2_set_mode( &miwi2, MIWI2_RF_RECEIVER );
    log_info( &logger, " *** RX MODE ***" );
    log_printf( &logger, "915 MHz | FSK | 5kbps | 33Khz frequency deviation | %u B payload\r\n", MIWI2_PAYLOAD_LEN );
    log_printf( &logger, "Waiting for packets...\r\n" );
    log_printf( &logger, "-----------------------------------\r\n" );
    Delay_ms( 200 ); 
#endif

    log_info( &logger, " Application Task " );
}
```

### Application Task

> In transmitter mode, the application periodically sends a fixed-length
payload and logs transmitted packet.
In receiver mode, the application polls the IRQ0 pin for packet reception,
reads the received payload from FIFO, and logs packet data.

```c
void application_task ( void )
{
    static uint16_t pkt_count = 0;
    uint8_t payload[ MIWI2_PAYLOAD_LEN ];

#ifdef DEMO_APP_TRANSMITTER
    memcpy( payload, DEMO_MESSAGE, MIWI2_PAYLOAD_LEN );

    log_printf( &logger, "[TX #%u] %.*s\r\n", pkt_count, MIWI2_PAYLOAD_LEN, ( char* ) payload );

    if ( MIWI2_OK == miwi2_tx_packet( &miwi2, payload ) )
    {
        log_printf( &logger, "  TXDONE OK\r\n" );
    }
    else
    {
        log_printf( &logger, "  TXDONE TIMEOUT\r\n" );
    }

    log_printf( &logger, "-----------------------------------\r\n" );
    pkt_count++;
    Delay_ms( MIWI2_TX_INTERVAL_MS );
#else
    if ( MIWI2_OK == miwi2_rx_packet( &miwi2, payload ) )
    {
        log_printf( &logger, "[RX #%u] %.*s\r\n", pkt_count, MIWI2_PAYLOAD_LEN, ( char* ) payload );
        log_printf( &logger, "-----------------------------------\r\n" );
        pkt_count++;
    }
    else
    {
        log_printf( &logger, "  RX TIMEOUT\r\n" );
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
