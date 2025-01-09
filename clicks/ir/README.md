
---
# IR Click

> [IR Click](https://www.mikroe.com/?pid_product=MIKROE-1377) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1377&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This is an example that demonstrates the use of the IR Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IR

### Example Key Functions

- `ir_cfg_setup` Config Object Initialization function.
```c
void ir_cfg_setup ( ir_cfg_t *cfg );
```

- `ir_init` Initialization function.
```c
err_t ir_init ( ir_t *ctx, ir_cfg_t *cfg );
```

- `ir_get_an_state` IR get AN pin state function.
```c
uint8_t ir_get_an_state ( ir_t *ctx );
```

- `ir_nec_send_command` IR NEC send data function.
```c
void ir_nec_send_command ( ir_t *ctx, uint8_t address, uint8_t command );
```

- `ir_nec_read_command` IR NEC data reading function.
```c
err_t ir_nec_read_command ( ir_t *ctx, uint8_t *address, uint8_t *command );
```

### Application Init

> Initialization driver enables - GPIO and Log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ir_cfg_t ir_cfg;    /**< Click config object. */

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
    ir_cfg_setup( &ir_cfg );
    IR_MAP_MIKROBUS( ir_cfg, MIKROBUS_1 );
    err_t error_flag = ir_init( &ir, &ir_cfg );
    if ( ( UART_ERROR == error_flag ) || ( PWM_ERROR == error_flag ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    
    #ifdef IR_TRANSMITTER_MODE
        log_printf( &logger, "-  Transmitter mode   - \r\n" );
    #else
        log_printf( &logger, "-    Receiver mode    - \r\n" );
    #endif
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
}
```

### Application Task

> This example contains two parts :
> - Transmitter mode - Sends data using NEC protocol.
> - Receiver mode - Reads data that is been sent using NEC protocol and 
>                   displaying it on the UART terminal.

```c
void application_task ( void ) 
{
    #ifdef IR_TRANSMITTER_MODE
        log_printf( &logger, " Sending message." );
        
        for ( uint8_t cnt = 0; cnt < 8; cnt++ )
        {
            ir_nec_send_command( &ir, 0x00, tx_data[ cnt ] );
            log_printf( &logger, "." );
            Delay_ms ( 50 );
        }
        
        log_printf( &logger, "\r\n Message sent! \r\n" );
        log_printf( &logger, "- - - - - - - - - - - - \r\n" );
        Delay_ms ( 500 );
    #else
        uint8_t arr;
        char rx_data;
        
        err_t err_flag = ir_nec_read_command ( &ir, &arr, &rx_data );
        
        if ( IR_OK == err_flag )
        {
            log_printf( &logger, "%c", rx_data );
        }
        else
        {
            log_printf( &logger, "Read ERROR! \r\n" );
        }
        Delay_ms ( 50 );
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
