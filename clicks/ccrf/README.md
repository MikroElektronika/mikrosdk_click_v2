
---
# ccRF Click

> [ccRF Click](https://www.mikroe.com/?pid_product=MIKROE-1435) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1435&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of an ccRF Click board by showing the communication between the two Click boards configured as a receiver and transmitter.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ccRf

### Example Key Functions

- `ccrf_cfg_setup` Config Object Initialization function.
```c
void ccrf_cfg_setup ( ccrf_cfg_t *cfg ); 
```

- `ccrf_init` Initialization function.
```c
err_t ccrf_init ( ccrf_t *ctx, ccrf_cfg_t *cfg );
```

- `ccrf_default_cfg` Click Default Configuration function.
```c
void ccrf_default_cfg ( ccrf_t *ctx );
```

- `ccrf_transmit_packet` Function transmit a packet with packet length up to 63 bytes to the targeted 8-bit register address.
```c
void ccrf_transmit_packet ( ccrf_t *ctx, uint8_t *tx_buffer, uint8_t n_bytes );
```

- `ccrf_receive_packet` Function receive a packet of variable packet length.
```c
uint8_t ccrf_receive_packet ( ccrf_t *ctx, uint8_t *rx_buffer, uint8_t *length_buff );
```

- `ccrf_get_start` Function for getting state of GD0 pin function.
```c
uint8_t ccrf_get_start( ctx );
```

### Application Init

> Initializes the driver and logger, performs the Click default configuration and displays the selected application mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ccrf_cfg_t cfg;

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
    ccrf_cfg_setup( &cfg );
    CCRF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ccrf_init( &ccrf, &cfg );

    ccrf_default_cfg( &ccrf );
    
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c
void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    ccrf_transmit_packet( &ccrf, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, " The message \"%s\" has been sent!\r\n", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    uint8_t data_buf[ 64 ] = { 0 };
    uint8_t data_len = sizeof( data_buf );
    if ( CCRF_CRC_OK == ccrf_receive_packet( &ccrf, data_buf, &data_len ) )
    {
        log_printf( &logger, " A new message has received: \"" );
        for ( uint16_t cnt = 0; cnt < data_len; cnt++ )
        {
            log_printf( &logger, "%c", data_buf[ cnt ] );
        }
        log_printf( &logger, "\"\r\n" );
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
