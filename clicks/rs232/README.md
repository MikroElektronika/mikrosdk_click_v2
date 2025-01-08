
---
# RS232 Click

> [RS232 Click](https://www.mikroe.com/?pid_product=MIKROE-2897) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2897&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type

# Software Support

## Example Description

> This example reads and processes data from RS232 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs232

### Example Key Functions

- `rs232_cfg_setup` Config Object Initialization function. 
```c
void rs232_cfg_setup ( rs232_cfg_t *cfg );
``` 
 
- `rs232_init` Initialization function. 
```c
err_t rs232_init ( rs232_t *ctx, rs232_cfg_t *cfg );
```

- `rs232_generic_write` Generic write function. 
```c
void rs232_generic_write ( rs232_t *ctx, char *data_buf, uint16_t len );
```
 
- `rs232_generic_read` Generic read function. 
```c
int32_t rs232_generic_read ( rs232_t *ctx, char *data_buf, uint16_t max_len );
```

### Application Init

> Initializes driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rs232_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rs232_cfg_setup( &cfg );
    RS232_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs232_init( &rs232, &cfg );
    
    Delay_ms ( 100 );
#ifdef RS232_RECEIVER
    log_printf( &logger, " ** RS232 Receiver **\r\n" );
#endif
    
#ifdef RS232_TRANSMITTER
    log_printf( &logger, " ** RS232 Transmitter **\r\n" );
#endif
}
```

### Application Task

> Depending on the selected mode (receiver/transmitter) this function reads/sends an appropriate message.
> All data is displayed on USB UART.

```c
void application_task ( void )
{
#ifdef RS232_RECEIVER
    rsp_size = rs232_generic_read( &rs232, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size == strlen( message ) )
    {  
        log_printf( &logger, "Message received: %s", uart_rx_buffer );
        log_printf( &logger, "\r\n-------------------------\r\n" );
        memset( uart_rx_buffer, 0, rsp_size );
    }  
    Delay_ms ( 100 );
#endif
    
#ifdef RS232_TRANSMITTER
    rs232_generic_write( &rs232, message, strlen( message ) );
    log_printf( &logger, "Message sent: %s", message );
    log_printf( &logger, "\r\n-------------------------\r\n" );
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
