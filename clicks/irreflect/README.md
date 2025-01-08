
---
# IR reflect Click

> [IR reflect Click](https://www.mikroe.com/?pid_product=MIKROE-1882) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1882&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> Example demonstrates the use of IR Reflect Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IrReflect

### Example Key Functions

- `irreflect_cfg_setup` Config Object Initialization function. 
```c
void irreflect_cfg_setup ( irreflect_cfg_t *cfg );
``` 
 
- `irreflect_init` Initialization function. 
```c
err_t irreflect_init ( irreflect_t *ctx, irreflect_cfg_t *cfg );
```

- `irreflect_default_cfg` Click Default Configuration function. 
```c
void irreflect_default_cfg ( irreflect_t *ctx );
```

- `irreflect_reflect_status` Function detecting interrupt states of IR reflection. 
```c
uint8_t irreflect_reflect_status ( irreflect_t *ctx );
```
 
- `irreflect_analog_status` Function detecting states of analog pin of IR reflection. 
```c
uint8_t irreflect_analog_status ( irreflect_t *ctx );
```

### Application Init

> Initialization driver enables - Start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    irreflect_cfg_t cfg;

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
    log_info(&logger, "---- Application ----\n");

    //  Click initialization.
    irreflect_cfg_setup( &cfg );
    IRREFLECT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irreflect_init( &irreflect, &cfg );
    
    ir_state = 0;
    ir_state_old = 0;
    counter = 1;
}
```

### Application Task

> This is a example which demonstrates the use of IR Reflect Click board.
> On this type of photointerrupter the infrared emitter and receiver are facing the same direction,
> the infrared beam from the emitter gets bounced back to the receiver when an object 
> is placed within the detecting range of the sensor ( optimal range is 3mm ).
> These sensors are used to detect an object's presence or motion, such as a piece of paper passing through a printer
> and counting when sensor is triggered.
> Results are being sent to the Usart Terminal where you can track their changes.
> Data logs on usb uart when the sensor is triggered.

```c
void application_task ( void )
{
    //  Task implementation.
    
    ir_state = irreflect_reflect_status( &irreflect );

    if ( ir_state_old != ir_state )
    {
        if ( ir_state )
        {
            log_printf( &logger, "  Counter = %u\n", counter);
            counter++;
        }
        ir_state_old = ir_state;
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
