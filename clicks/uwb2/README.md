
---
# UWB 2 Click

> [UWB 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5410) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5410&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of an UWB 2 Click board by showing the communication between the two Click boards.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UWB2

### Example Key Functions

- `uwb2_cfg_setup` Config Object Initialization function.
```c
void uwb2_cfg_setup ( uwb2_cfg_t *cfg );
```

- `uwb2_init` Initialization function.
```c
err_t uwb2_init ( uwb2_t *ctx, uwb2_cfg_t *cfg );
```

- `uwb2_default_cfg` Click Default Configuration function.
```c
err_t uwb2_default_cfg ( uwb2_t *ctx );
```

- `uwb2_read_reg_32bit` This function reads 32-bit data from the selected register by using SPI serial interface.
```c
err_t uwb2_read_reg_32bit ( uwb2_t *ctx, uint16_t reg, uint32_t *data_out );
```

- `uwb2_send_message` This function write a desired number of data bytes to the TX buffer, sets the TX message size, starts transmission and waits for a TX frame sent event.
```c
err_t uwb2_send_message ( uwb2_t *ctx, uint8_t *data_in, uint16_t len );
```

- `uwb2_read_message` This function activates the reception and then waits for a frame with a good FCS/CRC then reads up to len number of data bytes from the RX buffer and adjust the len parameter with the number of data bytes actually read.
```c
err_t uwb2_read_message ( uwb2_t *ctx, uint8_t *data_out, uint16_t *len );
```

### Application Init

> Initializes the driver, performs the Click default configuration, then reads and displays the device ID number.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uwb2_cfg_t uwb2_cfg;  /**< Click config object. */

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
    uwb2_cfg_setup( &uwb2_cfg );
    UWB2_MAP_MIKROBUS( uwb2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == uwb2_init( &uwb2, &uwb2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UWB2_ERROR == uwb2_default_cfg ( &uwb2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint32_t dev_id = 0;
    if ( UWB2_OK == uwb2_read_reg_32bit ( &uwb2, UWB2_REG_DEV_ID, &dev_id ) )
    {
        log_printf ( &logger, " Device ID: 0x%.8LX\r\n", dev_id );
    }
    
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Depending on the selected application mode, it reads all the received data or sends the desired text message with the message counter once per second.

```c
void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    static uint8_t tx_msg_cnt = 0;
    uint8_t tx_buffer[ 128 ] = { 0 };
    uint16_t tx_msg_size = 0;
    tx_buffer[ 0 ] = tx_msg_cnt; // Message number.
    strcpy ( &tx_buffer[ 1 ], DEMO_TEXT_MESSAGE );
    tx_msg_size = strlen ( DEMO_TEXT_MESSAGE ) + 2; // Message size + null-terminated + tx_msg_cnt
    if ( UWB2_OK == uwb2_send_message ( &uwb2, tx_buffer, tx_msg_size ) )
    {
        log_printf ( &logger, " Message sent #%u\r\n\n", tx_buffer[ 0 ] );
        tx_msg_cnt++; // Increment message number (modulo 256).
    }
    Delay_ms ( 1000 );
#else
    uint8_t rx_buffer[ 128 ] = { 0 };
    uint16_t rx_msg_size = sizeof ( rx_buffer );
    if ( UWB2_OK == uwb2_read_message ( &uwb2, rx_buffer, &rx_msg_size ) )
    {
        log_printf ( &logger, " Message received #%u: %s\r\n\n", 
                     ( uint16_t ) rx_buffer[ 0 ], &rx_buffer[ 1 ] );
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
