
---
# RS232 Isolator 2 Click

> [RS232 Isolator 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4536) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4536&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This library contains API for RS 232 Isolator 2 Click driver.
> This example transmits/receives and processes data from RS 232 Isolator 2 Clicks.
> The library initializes and defines the UART bus drivers 
> to transmit or receive data. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs232Isolator2

### Example Key Functions

- `rs232isolator2_cfg_setup` Config Object Initialization function.
```c
void rs232isolator2_cfg_setup ( rs232isolator2_cfg_t *cfg );
```

- `rs232isolator2_init` Initialization function.
```c
err_t rs232isolator2_init ( rs232isolator2_t *ctx, rs232isolator2_cfg_t *cfg );
```

- `rs232isolator2_default_cfg` Click Default Configuration function.
```c
void rs232isolator2_default_cfg ( rs232isolator2_t *ctx );
```

- `rs232isolator2_generic_write` RS 232 Isolator 2 data writing function.
```c
err_t rs232isolator2_generic_write ( rs232isolator2_t *ctx, char *data_buf, uint16_t len );
```

- `rs232isolator2_generic_read` RS 232 Isolator 2 data reading function.
```c
err_t rs232isolator2_generic_read ( rs232isolator2_t *ctx, char *data_buf, uint16_t max_len );
```

- `rs232isolator2_send_data` RS 232 Isolator 2 data writing function.
```c
err_t rs232isolator2_send_data ( rs232isolator2_t *ctx, char *tx_data );
```

### Application Init

> Initializes driver and wake-up module.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rs232isolator2_cfg_t rs232isolator2_cfg;  /**< Click config object. */

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

    rs232isolator2_cfg_setup( &rs232isolator2_cfg );
    RS232ISOLATOR2_MAP_MIKROBUS( rs232isolator2_cfg, MIKROBUS_1 );
    err_t init_flag  = rs232isolator2_init( &rs232isolator2, &rs232isolator2_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    app_buf_len = 0;
    app_buf_cnt = 0;
    log_info( &logger, " Application Task " );
    
    #ifdef TRANSMITTER
    
        log_printf( &logger, "    Send data:    \r\n" );
        log_printf( &logger, "      mikroE      \r\n" );
        log_printf( &logger, "------------------\r\n" );
        log_printf( &logger, "  Transmit data   \r\n" );
        Delay_ms ( 1000 );

    #endif
        
    #ifdef RECIEVER

        log_printf( &logger, "   Receive data  \r\n" );
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
    
    rs232isolator2_send_data( &rs232isolator2, demo_message );
    log_printf( &logger, "%s", demo_message );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "------------------\r\n" );    
    
    #endif
    
    #ifdef RECIEVER
    
    rs232isolator2_process( );

    if ( app_buf_len > 0 ) {
        log_printf( &logger, "%s", app_buf );
        rs232isolator2_clear_app_buf(  );
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
