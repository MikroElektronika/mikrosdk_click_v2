
---
# USB UART 3 Click

> [USB UART 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3063) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3063&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type

# Software Support

## Example Description

> This example reads and processes data from USB UART 3 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UsbUart3

### Example Key Functions

- `usbuart3_cfg_setup` Config Object Initialization function. 
```c
void usbuart3_cfg_setup ( usbuart3_cfg_t *cfg );
``` 
 
- `usbuart3_init` Initialization function. 
```c
err_t usbuart3_init ( usbuart3_t *ctx, usbuart3_cfg_t *cfg );
```

- `usbuart3_reset` Function for reset. 
```c
void usbuart3_reset ( usbuart3_t *ctx );
```
 
- `usbuart3_get_susp` Set device mode. 
```c
uint8_t usbuart3_get_susp ( usbuart3_t *ctx );
```

- `usbuart3_send_command` Function for send command. 
```c
void usbuart3_send_command ( usbuart3_t *ctx, char *command );
```

### Application Init

> Initializes driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    usbuart3_cfg_t cfg;

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

    usbuart3_cfg_setup( &cfg );
    USBUART3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    usbuart3_init( &usbuart3, &cfg );
    
    usbuart3_reset( &usbuart3 );
}
```

### Application Task

> Reads the received data.

```c
void application_task ( void )
{
    rsp_size = usbuart3_generic_read( &usbuart3, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size > 0 )
    {  
        usbuart3_generic_write( &usbuart3, uart_rx_buffer, rsp_size );
        log_printf( &logger, "%s", uart_rx_buffer );
        memset( uart_rx_buffer, 0, rsp_size );
    }
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
