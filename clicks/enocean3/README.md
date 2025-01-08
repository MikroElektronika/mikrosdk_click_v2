
---
# EnOcean 3 Click

> [EnOcean 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3653) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3653&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from EnOcean 3 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Enocean3

### Example Key Functions

- `enocan3_cfg_setup` Config Object Initialization function. 
```c
void enocan3_cfg_setup ( enocan3_cfg_t *cfg );
``` 
 
- `enocan3_init` Initialization function. 
```c
err_t enocan3_init ( enocan3_t *ctx, enocan3_cfg_t *cfg );
```

- `enocean3_uart_isr` UART Interrupt Routine function. 
```c
void enocean3_uart_isr ( enocean3_t *ctx );
```
 
- `enocean3_response_handler_set` Handler Set function. 
```c
void enocean3_response_handler_set ( enocan3_t *ctx, enocean3_hdl_t handler );
```

- `enocean3_send_packet` Packet Send function. 
```c
uint8_t enocean3_send_packet ( enocan3_t *ctx, enocean3_packet_t *packet );
```

### Application Init

> Initializes the driver and sets the driver handler.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    enocean3_cfg_t cfg;

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

    enocean3_cfg_setup( &cfg );
    ENOCEAN3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    enocean3_init( &enocean3, &cfg );

    Delay_ms ( 500 );

    enocean3_response_handler_set( &enocean3, &make_response );
    rsp_check = 1;
}
```

### Application Task

> Reads the received data and parses it on the USB UART if the response buffer is ready.

```c
void application_task ( void )
{
    enocean3_uart_isr ( &enocean3 );
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
