
---
# EnOcean Click

> [EnOcean Click](https://www.mikroe.com/?pid_product=MIKROE-1908) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1908&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from EnOcean Clicks. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EnOcean

### Example Key Functions

- `enocean_cfg_setup` Config Object Initialization function. 
```c
void enocean_cfg_setup ( enocean_cfg_t *cfg );
``` 
 
- `enocean_init` Initialization function. 
```c
err_t enocean_init ( enocean_t *ctx, enocean_cfg_t *cfg );
```

- `enocean_response_ready` Response Ready function. 
```c
uint8_t enocean_response_ready ( enocean_t *ctx );
```
 
- `enocean_uart_isr` UART Interrupt Routine function. 
```c
void enocean_uart_isr ( enocean_t *ctx );
```

- `enocean_send_packet` Packet Send function. 
```c
uint8_t enocean_send_packet ( enocean_t *ctx, enocean_packet_t *packet );
```

### Application Init

> Initializes the driver and sets the driver handler.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    enocean_cfg_t cfg;

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

    enocean_cfg_setup( &cfg );
    ENOCEAN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    enocean_init( &enocean, &cfg );

    Delay_ms ( 500 );
    
    enocean_response_handler_set( &enocean, &make_response );
}
```

### Application Task

> Reads the received data and parses it on the USB UART if the response buffer is ready.

```c
void application_task ( void )
{
    enocean_uart_isr ( &enocean );
    check_response ( );
    Delay_1ms( );
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
