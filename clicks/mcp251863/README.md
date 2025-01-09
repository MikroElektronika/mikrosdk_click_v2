
---
# MCP251863 Click

> [MCP251863 Click](https://www.mikroe.com/?pid_product=MIKROE-4955) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4955&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of an MCP251863 Click board by showing
the communication between the two Click boards configured as a receiver and transmitter.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MCP251863

### Example Key Functions

- `mcp251863_cfg_setup` Config Object Initialization function.
```c
void mcp251863_cfg_setup ( mcp251863_cfg_t *cfg );
```

- `mcp251863_init` Initialization function.
```c
err_t mcp251863_init ( mcp251863_t *ctx, mcp251863_cfg_t *cfg );
```

- `mcp251863_default_cfg` Click Default Configuration function.
```c
err_t mcp251863_default_cfg ( mcp251863_t *ctx );
```

- `mcp251863_transmit_message` Transmits the desired message and checks is message successfully sent.
```c
err_t mcp251863_transmit_message ( mcp251863_t *ctx, uint8_t *data_in, uint16_t data_len );
```

- `mcp251863_receive_message` Receives the message and checks is message successfully received.
```c
err_t mcp251863_receive_message ( mcp251863_t *ctx, uint8_t *data_out, uint16_t *data_len );
```

- `mcp251863_operation_mode_select` Function for select operation mode.
```c
err_t mcp251863_operation_mode_select ( mcp251863_t *ctx, uint8_t op_mode );
```

### Application Init

> Initializes the driver and logger, performs the Click default configuration and displays the selected application mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mcp251863_cfg_t mcp251863_cfg;  /**< Click config object. */

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
    mcp251863_cfg_setup( &mcp251863_cfg );
    MCP251863_MAP_MIKROBUS( mcp251863_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == mcp251863_init( &mcp251863, &mcp251863_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MCP251863_ERROR == mcp251863_default_cfg ( &mcp251863 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
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

> Depending on the selected mode, it sends a desired message using CAN protocol or reads all the received data and displays them on the USB UART.

```c
void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    if ( MCP251863_OK == mcp251863_transmit_message( &mcp251863, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf( &logger, " The message \"%s\" has been sent!\r\n", ( char * ) DEMO_TEXT_MESSAGE );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    uint8_t data_buf[ 256 ] = { 0 };
    uint16_t data_len = 0;
    if ( MCP251863_OK == mcp251863_receive_message( &mcp251863, data_buf, &data_len ) )
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
