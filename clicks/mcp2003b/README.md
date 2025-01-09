
---
# MCP2003B Click

> [MCP2003B Click](https://www.mikroe.com/?pid_product=MIKROE-2227) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2227&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of an MCP2003B Click board by showing the communication between the two Click board configured as a receiver and transmitter.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MCP2003B

### Example Key Functions

- `mcp2003b_cfg_setup` Config Object Initialization function.
```c
void mcp2003b_cfg_setup ( mcp2003b_cfg_t *cfg );
```

- `mcp2003b_init` Initialization function.
```c
err_t mcp2003b_init ( mcp2003b_t *ctx, mcp2003b_cfg_t *cfg );
```

- `mcp2003b_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t mcp2003b_generic_write ( mcp2003b_t *ctx, uint8_t *data_in, uint16_t len );
```

- `mcp2003b_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t mcp2003b_generic_read ( mcp2003b_t *ctx, uint8_t *data_out, uint16_t len );
```

- `mcp2003b_set_cs_pin` This function sets the chip select (CS) pin logic state.
```c
void mcp2003b_set_cs_pin ( mcp2003b_t *ctx, uint8_t state );
```

### Application Init

> Initializes the driver and logger and displays the selected application mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mcp2003b_cfg_t mcp2003b_cfg;  /**< Click config object. */

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
    mcp2003b_cfg_setup( &mcp2003b_cfg );
    MCP2003B_MAP_MIKROBUS( mcp2003b_cfg, MIKROBUS_1 );
    if ( UART_ERROR == mcp2003b_init( &mcp2003b, &mcp2003b_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
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

> Depending on the selected mode, it reads all the received data or sends the desired message every 3 seconds.

```c
void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    mcp2003b_generic_write( &mcp2003b, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 ); 
#else
    uint8_t rx_data = 0;
    if ( mcp2003b_generic_read( &mcp2003b, &rx_data, 1 ) > 0 )
    {
        log_printf( &logger, "%c", rx_data );
    }
#endif
}
```

### Note

> The Click boards should be connected as follows: VBB->VBB, LBUS->LBUS, GND->GND.
The communication power supply voltage provided on VBB pin should be in range from 5.5V to 30V.

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
