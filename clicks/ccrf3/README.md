
---
# ccRF 3 Click

> [ccRF 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2389) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2389&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of ccRF 3 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ccRF3

### Example Key Functions

- `ccrf3_cfg_setup` Config Object Initialization function.
```c
void ccrf3_cfg_setup ( ccrf3_cfg_t *cfg );
```

- `ccrf3_init` Initialization function.
```c
err_t ccrf3_init ( ccrf3_t *ctx, ccrf3_cfg_t *cfg );
```

- `ccrf3_default_cfg` Click Default Configuration function.
```c
err_t ccrf3_default_cfg ( ccrf3_t *ctx );
```

- `ccrf3_cmd_strobe` Set command strobe function.
```c
uint8_t ccrf3_cmd_strobe ( ccrf3_t *ctx, uint8_t cmd )
```

- `ccrf3_send_tx_data` Send TX data function.
```c
void ccrf3_send_tx_data ( ccrf3_t *ctx, uint8_t *tx_data, uint8_t n_bytes );
```

- `ccrf3_receive_rx_data` Receive RX data function.
```c
uint8_t ccrf3_receive_rx_data ( ccrf3_t *ctx, uint8_t *rx_data );
```

### Application Init

> Initializes the driver, performs the default configuration and enables the selected mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ccrf3_cfg_t ccrf3_cfg;  /**< Click config object. */

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
    log_printf( &logger, " Application Init \r\n" );

    // Click initialization.
    ccrf3_cfg_setup( &ccrf3_cfg );
    CCRF3_MAP_MIKROBUS( ccrf3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ccrf3_init( &ccrf3, &ccrf3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " Hardware reset\r\n" );
    ccrf3_hw_reset( &ccrf3 );
    Delay_ms ( 1000 );
    
    if ( CCRF3_ERROR == ccrf3_default_cfg ( &ccrf3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, "----------------------\r\n" );
#ifdef DEMO_APP_TRANSMITTER
    ccrf3_set_tx_mode( &ccrf3 );
    
    log_printf( &logger, " Transmitter mode\r\n" );
#else
    ccrf3_set_rx_mode( &ccrf3 );
    
    log_printf( &logger, " Receiver mode\r\n" );
#endif

    log_printf( &logger, "----------------------\r\n" );
    Delay_ms ( 100 );
    
    log_printf( &logger, " Application Task \r\n" );
    log_printf( &logger, "----------------------\r\n" );
}
```

### Application Task

> Depending on the selected mode, it reads the received data or sends the desired message
> every 2 seconds. All data is being logged on the USB UART where you can track their changes.

```c
void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    ccrf3_send_tx_data( &ccrf3, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_printf( &logger, " Sent message: MikroE\r\n" );
    log_printf( &logger, " Packet number: %u\r\n", ccrf3.packet_counter );
    log_printf( &logger, "----------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    uint8_t num_bytes = ccrf3_receive_rx_data( &ccrf3, &rx_buffer[ 0 ] );
    if ( num_bytes )
    {
        log_printf( &logger, " Received message: " );
        for ( uint8_t cnt = 3; cnt < rx_buffer[ 0 ]; cnt++ )
        {
            log_printf( &logger, "%c", rx_buffer[ cnt ] );
        }
        log_printf( &logger, " Packet number: %u", ccrf3.packet_counter );
        log_printf( &logger, "\r\n----------------------\r\n" );
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
