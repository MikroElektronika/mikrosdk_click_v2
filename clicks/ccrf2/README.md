
---
# ccRF 2 Click

> [ccRF 2 Click](https://www.mikroe.com/?pid_product=MIKROE-1716) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1716&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of ccRF 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ccRf2

### Example Key Functions

- `ccrf2_cfg_setup` Config Object Initialization function. 
```c
void ccrf2_cfg_setup ( ccrf2_cfg_t *cfg );
``` 
 
- `ccrf2_init` Initialization function. 
```c
err_t ccrf2_init ( ccrf2_t *ctx, ccrf2_cfg_t *cfg );
```

- `ccrf2_default_cfg` Click Default Configuration function. 
```c
void ccrf2_default_cfg ( ccrf2_t *ctx );
```

- `ccrf2_receive_rx_data` Function receives RX data from the transmit module of the CC1120 single-chip radio transceiver. 
```c
uint8_t ccrf2_receive_rx_data ( ccrf2_t *ctx, uint8_t *rx_data );
```
 
- `ccrf2_send_tx_data` Function sends TX data to the receive module of the CC1120 single-chip radio transceiver. 
```c
void ccrf2_send_tx_data ( ccrf2_t *ctx, uint8_t *tx_data, uint8_t n_bytes );
```

- `ccrf2_set_rx_mode` Function sets RX mode of the CC1120 single-chip radio transceiver on the ccRF 2 Click board. 
```c
void ccrf2_set_rx_mode ( ccrf2_t *ctx );
```

### Application Init

> Initializes the driver, performs the default configuration and enables the selected mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ccrf2_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ccrf2_cfg_setup( &cfg );
    CCRF2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ccrf2_init( &ccrf2, &cfg );
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " Hardware reset\r\n" );
    ccrf2_hw_reset( &ccrf2 );
    Delay_ms ( 1000 );

    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " Default config\r\n" );
    ccrf2_default_cfg( &ccrf2 );
    Delay_ms ( 1000 );

    log_printf( &logger, "----------------------\r\n" );

#ifdef DEMO_APP_RECEIVER
    ccrf2_set_rx_mode( &ccrf2 );
    
    log_printf( &logger, " Receiver mode\r\n" );
#endif
#ifdef DEMO_APP_TRANSMITTER
    ccrf2_set_tx_mode( &ccrf2 );
    
    log_printf( &logger, " Transmitter mode\r\n" );
#endif

    log_printf( &logger, "----------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> Depending on the selected mode, it reads the received data or sends the desired message
> every 2 seconds. All data is being logged on the USB UART where you can track their changes.

```c
void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    uint8_t num_bytes = ccrf2_receive_rx_data( &ccrf2, &rx_buffer[ 0 ] );
    if ( num_bytes )
    {
        log_printf( &logger, " Received message: " );
        for ( uint8_t cnt = 3; cnt < rx_buffer[ 0 ]; cnt++ )
        {
            log_printf( &logger, "%c", rx_buffer[ cnt ] );
        }
        log_printf( &logger, " Packet number: %u", ccrf2.packet_counter );
        log_printf( &logger, "\r\n----------------------\r\n" );
    }
#endif
#ifdef DEMO_APP_TRANSMITTER
    ccrf2_send_tx_data( &ccrf2, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_printf( &logger, " Sent message: MikroE\r\n" );
    log_printf( &logger, " Packet number: %u\r\n", ccrf2.packet_counter );
    log_printf( &logger, "----------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
