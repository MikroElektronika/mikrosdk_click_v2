
---
# LR 6 Click

> [LR 6 Click](https://www.mikroe.com/?pid_product=MIKROE-6112) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6112&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2024.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the LR 6 Click board by showing
the communication between two Click boards. The app transmits a predefined
message and waits for a response. On successful reception, the payload and
packet status (RSSI, SNR) are logged on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LR6

### Example Key Functions

- `lr6_cfg_setup` Config Object Initialization function.
```c
void lr6_cfg_setup ( lr6_cfg_t *cfg );
```

- `lr6_init` Initialization function.
```c
err_t lr6_init ( lr6_t *ctx, lr6_cfg_t *cfg );
```

- `lr6_default_cfg` Click Default Configuration function.
```c
err_t lr6_default_cfg ( lr6_t *ctx );
```

- `lr6_send_data` This function sends a desired number of data bytes to the buffer by using the selected mode using the SPI serial interface.
```c
err_t lr6_send_data ( lr6_t *ctx, uint8_t *send_data, uint8_t len, uint8_t mode );
```

- `lr6_receive_data` This function receives a desired number of data bytes to the buffer by using the SPI serial interface.
```c
err_t lr6_receive_data ( lr6_t *ctx, uint8_t *receive_data, uint16_t buff_len, uint8_t *rx_len );
```

- `lr6_set_lr_config` This function performs the desired LoRa configuration by using the SPI serial interface.
```c
err_t lr6_set_lr_config ( lr6_t *ctx, lr6_lora_cfg_t lora_cfg );
```

### Application Init

> Initializes the logger and LR 6 Click and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr6_cfg_t lr6_cfg;  /**< Click config object. */

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
    lr6_cfg_setup( &lr6_cfg );
    LR6_MAP_MIKROBUS( lr6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == lr6_init( &lr6, &lr6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LR6_ERROR == lr6_default_cfg ( &lr6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " --------------------\r\n" );
}
```

### Application Task

> Sends the demo message, polls for incoming data for up to 5 seconds, logs the received content and the link quality (RSSI/SNR), and repeats.

```c
void application_task ( void )
{
    uint8_t rx_data[ 255 ] = { 0 };
    uint8_t rx_len = 0;
    uint16_t timeout_cnt = 0;
    if ( LR6_OK == lr6_send_data( &lr6, LR6_DEMO_TEXT, strlen( LR6_DEMO_TEXT ), LR6_TX_MODE_SYNC ) ) 
    {
        log_info( &logger, " Send - success" );
        for ( ; ; )
        {
            if ( LR6_OK == lr6_receive_data( &lr6, rx_data, strlen( LR6_DEMO_TEXT ), &rx_len ) )
            {
                if ( rx_len > 0 )
                { 
                    log_info( &logger, " Receive - success" );
                    log_printf( &logger, " > Receive: " );
                    for ( uint8_t cnt = 0; cnt < strlen( LR6_DEMO_TEXT ); cnt++ )
                    {
                        log_printf( &logger, "%c", rx_data[ cnt ] );
                    }
                    log_printf( &logger, "\r\n" );

                    int8_t rssi, snr;
                    if ( LR6_OK == lr6_get_packet_status( &lr6, &rssi, &snr ) )
                    {
                        log_printf( &logger, " Rssi Pkt: %d dBm\r\n", ( int16_t ) rssi );
                        log_printf( &logger, " Snr Pkt : %d dB\r\n", ( int16_t ) snr );
                        log_printf( &logger, " --------------------\r\n" );
                    }
                    break;
                }
            }
            timeout_cnt++;
            if ( timeout_cnt > 5000 )
            {
                log_info( &logger, " No response within 5 seconds" );
                break;
            }
            Delay_ms ( 1 );
        } 
    }
    else
    {
        log_info( &logger, "Send - fail" );
    }
    Delay_ms ( 500 );
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
