
---
# UART MUX 2 Click

> [UART MUX 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4494) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4494&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This library contains API for UART MUX 2 Click driver.
> This example transmits/receives and processes data from UART MUX 2 Clicks.
> The library initializes and defines the UART bus drivers 
> to transmit or receive data. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UartMux2

### Example Key Functions

- `uartmux2_cfg_setup` Config Object Initialization function.
```c
void uartmux2_cfg_setup ( uartmux2_cfg_t *cfg );
```

- `uartmux2_init` Initialization function.
```c
err_t uartmux2_init ( uartmux2_t *ctx, uartmux2_cfg_t *cfg );
```

- `uartmux2_default_cfg` Click Default Configuration function.
```c
void uartmux2_default_cfg ( uartmux2_t *ctx );
```

- `uartmux2_set_operation_mode` UART MUX 2 set operation mode function.
```c
err_t uartmux2_set_operation_mode ( uartmux2_t *ctx, uint8_t op_mode );
```

- `uartmux2_set_channel` UART MUX 2 set channel function.
```c
err_t uartmux2_set_channel ( uartmux2_t *ctx, uint8_t mux_ch );
```

- `uartmux2_send_data` UART MUX 2 data writing function.
```c
err_t uartmux2_send_data ( uartmux2_t *ctx, char *tx_data );
```

### Application Init

> Initializes driver and set UART channel module.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uartmux2_cfg_t uartmux2_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n Application Init \r\n" );

    // Click initialization.

    uartmux2_cfg_setup( &uartmux2_cfg );
    UARTMUX2_MAP_MIKROBUS( uartmux2_cfg, MIKROBUS_1 );
    err_t init_flag  = uartmux2_init( &uartmux2, &uartmux2_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    uartmux2_default_cfg ( &uartmux2 );
    app_buf_len = 0;
    app_buf_cnt = 0;
    log_printf( &logger, "\r\n Application Task \r\n" );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms ( 500 );
    
    #ifdef TRANSMITTER
    
        log_printf( &logger, "    Send data:    \r\n" );
        log_printf( &logger, "      mikroE      \r\n" );
        log_printf( &logger, "------------------\r\n" );
        log_printf( &logger, "  Transmit data   \r\n" );
        Delay_ms ( 1000 );

    #endif

    #ifdef RECIEVER

        uart_ch = UARTMUX2_CHANNEL_0;
        log_printf( &logger, "   Receive data  \r\n" );
        log_printf( &logger, "      UART%u \r\n", ( uint16_t ) uart_ch );
        uartmux2_set_channel( &uartmux2, uart_ch );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    
    #endif
        
    log_printf( &logger, "------------------\r\n" );
}
```

### Application Task

> Transmitter/Receiver task depend on uncommented code.
> Receiver logging each received byte to the UART for data logging,
> while transmitted send messages every 2 seconds.

```c
void application_task ( void ) 
{
    #ifdef TRANSMITTER
    
    for ( uart_ch = UARTMUX2_CHANNEL_0; uart_ch <= UARTMUX2_CHANNEL_3; uart_ch++ ) {
        uartmux2_set_channel( &uartmux2, uart_ch );
        Delay_ms ( 100 );
        uartmux2_send_data( &uartmux2, demo_message );
        log_printf( &logger, "  UART%u : ", ( uint16_t ) uart_ch ); 
    
        for ( uint8_t cnt = 0; cnt < 9; cnt ++ ) {
            log_printf( &logger, "%c", demo_message[ cnt ] );
            Delay_ms ( 100 );
        }
        
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, "------------------\r\n" );
    Delay_ms ( 100 );
    
    #endif
    
    #ifdef RECIEVER
    
    uartmux2_process( );

    if ( app_buf_len > 0 ) {
        log_printf( &logger, "%s", app_buf );
        uartmux2_clear_app_buf(  );
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
