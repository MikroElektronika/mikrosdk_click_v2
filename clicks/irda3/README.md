
---
# IrDA 3 Click

> [IrDA 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2871) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2871&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of IrDA 3 Click boards. The example can perform both roles, transmitter and receiver.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IrDA3

### Example Key Functions

- `irda3_cfg_setup` Config Object Initialization function.
```c
void irda3_cfg_setup ( irda3_cfg_t *cfg );
```

- `irda3_init` Initialization function.
```c
err_t irda3_init ( irda3_t *ctx, irda3_cfg_t *cfg );
```

- `irda3_default_cfg` Click Default Configuration function.
```c
void irda3_default_cfg ( irda3_t *ctx );
```

- `irda3_mode_setup` This function allows IrDA 3 Click mode to be set.
```c
void irda3_mode_setup( irda3_t *ctx, irda3_mode_t state );
```

- `irda3_pwr_setup` This function allows IrDA 3 Click power mode to be set.
```c
void irda3_pwr_setup( irda3_t *ctx, irda3_pwr_t state );
```

- `irda3_reset` This function executes a device reset operation.
```c
void irda3_reset( irda3_t *ctx );
```

### Application Init

> Initializes UART driver and all used control pins. Also clears the response buffer.
```c
void application_init( void ) 
{
    irda3_cfg_t irda3_cfg;
    log_cfg_t logger_cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( logger_cfg );
    log_init( &logger, &logger_cfg );
    log_printf( &logger, "***  IrDA initialization done  ***\r\n" );
    log_printf( &logger, "**********************************\r\n" );
    
    //  Click initialization.
    
    irda3_cfg_setup( &irda3_cfg );
    IRDA3_MAP_MIKROBUS( irda3_cfg, MIKROBUS_1 );
    irda3_init( &irda3, &irda3_cfg );
    irda3_default_cfg( &irda3 );
    irda3_reset( &irda3 );

    //  Clear response.
    
    memset( rx_message, 0, sizeof( rx_message ) );
}
```

### Application Task

> Demonstrates the use of IrDA 3 Clicks which can be used as transmitter or receiver. There are four different examples in this project. 
Uncomment one of the below macros to select which example will be executed. By default the DEMO_APP_TRANSMITTER_1 example is selected.

```c
void application_task( void ) 
{

#ifdef DEMO_APP_RECEIVER_1
    rx_message[ 0 ] = irda3_generic_single_receive( &irda3 );

    if ( rx_message[ 0 ] != 0 ) {
        log_printf( &logger, "%c", ( char ) rx_message[ 0 ] );
    }
    Delay_ms ( 100 );

#endif

#ifdef DEMO_APP_RECEIVER_2

    irda3_generic_multiple_receive( &irda3, rx_message, '\n' );

    log_printf( &logger, "RECEIVED MESSAGE : " );
    log_printf( &logger, "%s\r\n", rx_message );
    Delay_ms ( 100 );

#endif
    
#ifdef DEMO_APP_TRANSMITTER_1

    irda3_generic_multiple_send( &irda3, tx_message );

    log_printf( &logger, "MESSAGE SENT\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

#endif
    
#ifdef DEMO_APP_TRANSMITTER_2

    idx = 0;

    while ( tx_message[ idx ] != '\0' ) {
        irda3_generic_single_send( &irda3, tx_message[ idx++ ] );
    }

    log_printf( &logger, "MESSAGE SENT\r\n" );
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
