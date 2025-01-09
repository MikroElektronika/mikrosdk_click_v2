
---
# CAN Isolator 2 Click

> [CAN Isolator 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4809) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4809&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : May 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from CAN Isolator 2 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CanIsolator2

### Example Key Functions

- `canisolator2_cfg_setup` Config Object Initialization function.
```c
void canisolator2_cfg_setup ( canisolator2_cfg_t *cfg );
```

- `canisolator2_init` Initialization function.
```c
err_t canisolator2_init ( canisolator2_t *ctx, canisolator2_cfg_t *cfg );
```

- `canisolator2_default_cfg` Click Default Configuration function.
```c
void canisolator2_default_cfg ( canisolator2_t *ctx );
```

- `canisolator2_generic_write` CAN Isolator 2 data writing function.
```c
err_t canisolator2_generic_write ( canisolator2_t *ctx, char *data_buf, uint16_t len );
```

- `canisolator2_generic_read` CAN Isolator 2 data reading function.
```c
err_t canisolator2_generic_read ( canisolator2_t *ctx, char *data_buf, uint16_t max_len );
```

- `canisolator2_send_data` CAN Isolator 2 send data function.
```c
err_t canisolator2_send_data ( canisolator2_t *ctx, char *tx_data );
```

### Application Init

> Initializes driver and wake-up module.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                    /**< Logger config object. */
    canisolator2_cfg_t canisolator2_cfg;  /**< Click config object. */

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

    canisolator2_cfg_setup( &canisolator2_cfg );
    CANISOLATOR2_MAP_MIKROBUS( canisolator2_cfg, MIKROBUS_1 );
    err_t init_flag  = canisolator2_init( &canisolator2, &canisolator2_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    canisolator2_default_cfg ( &canisolator2 );
    app_buf_len = 0;
    app_buf_cnt = 0;
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    #ifdef TRANSMIT
    
        log_printf( &logger, "    Send data:    \r\n" );
        log_printf( &logger, "      MikroE      \r\n" );
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

> Transmitter/Receiver task depends on uncommented code.
> Receiver logging each received byte to the UART for data logging,
> while transmitted send messages every 2 seconds.

```c
void application_task ( void ) 
{
   #ifdef TRANSMIT
    
        canisolator2_send_data( &canisolator2, demo_message );
        log_printf( &logger, "\t%s", demo_message );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        log_printf( &logger, "------------------\r\n" );    
    
    #endif
    
    #ifdef RECIEVER
    
        canisolator2_process( );

        if ( app_buf_len > 0 ) {
            log_printf( &logger, "%s", app_buf );
            canisolator2_clear_app_buf(  );
        }
    
    #endif
}
```

## Additional Function

- `canisolator2_clear_app_buf` CAN Isolator 2 clear app buffer function.
```c
static void canisolator2_clear_app_buf ( void );
```

- `canisolator2_process` CAN Isolator 2 process function.
```c
 static err_t canisolator2_process ( void );
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
