
---
# IrDA 4 Click

> [IrDA 4 Click](https://www.mikroe.com/?pid_product=MIKROE-5686) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5686&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Apr 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of IrDA 4 Click board by processing
 the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IrDA4

### Example Key Functions

- `irda4_cfg_setup` Config Object Initialization function.
```c
void irda4_cfg_setup ( irda4_cfg_t *cfg );
```

- `irda4_init` Initialization function.
```c
err_t irda4_init ( irda4_t *ctx, irda4_cfg_t *cfg );
```

- `irda4_generic_write` IrDA 4 data writing function.
```c
err_t irda4_generic_write ( irda4_t *ctx, uint8_t *data_in, uint16_t len );
```

- `irda4_generic_read` IrDA 4 data reading function.
```c
err_t irda4_generic_read ( irda4_t *ctx, uint8_t *data_out, uint16_t len );
```

- `irda_hw_reset` IrDA 4 hardware reset function.
```c
void irda_hw_reset ( irda4_t *ctx );
```

### Application Init

> Initializes the driver and disables the transmitter shutdown.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irda4_cfg_t irda4_cfg;  /**< Click config object. */

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
    irda4_cfg_setup( &irda4_cfg );
    IRDA4_MAP_MIKROBUS( irda4_cfg, MIKROBUS_1 );
    if ( UART_ERROR == irda4_init( &irda4, &irda4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    irda4_set_tx_shutdown( &irda4, IRDA4_SHUTDOWN_DISABLED );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Demonstrates the use of IrDA 4 Clicks which can be used as transmitter or receiver. 
  - TRANSMITTER : Device is sending tx_message data. 
  - RECEIVER    : Device is reading a message that is being transmitted and 
                  logs it on the UART terminal. 

```c
void application_task ( void ) 
{
#if defined( DEMO_APP_TRANSMITTER )
    for ( uint8_t n_cnt = 0; n_cnt < 8; n_cnt++ )
    {
        irda4_generic_write( &irda4, &tx_message[ n_cnt ], 1 );
        Delay_ms ( 500 );
    }
    log_printf( &logger, "Message sent \r\n" );
#else
    if ( 1 == irda4_generic_read( &irda4, &rx_message, 1 ) )
    {
        log_printf( &logger, "%c", rx_message );
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
