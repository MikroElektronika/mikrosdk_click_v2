
---
# Pedometer Click

> [Pedometer Click](https://www.mikroe.com/?pid_product=MIKROE-3567) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3567&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application detected steps. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pedometer

### Example Key Functions

- `pedometer_cfg_setup` Config Object Initialization function. 
```c
void pedometer_cfg_setup ( pedometer_cfg_t *cfg );
``` 
 
- `pedometer_init` Initialization function. 
```c
err_t pedometer_init ( pedometer_t *ctx, pedometer_cfg_t *cfg );
```

- `pedometer_default_cfg` Click Default Configuration function. 
```c
void pedometer_default_cfg ( pedometer_t *ctx );
```

- `pedometer_get_interrupt_state` Functions for get Interrupt state on the INT pin. 
```c
uint8_t pedometer_get_interrupt_state ( pedometer_t *ctx );
```
 
- `pedometer_get_step_counter` Functions for get step counter. 
```c
uint32_t pedometer_get_step_counter ( pedometer_t *ctx );
```

- `pedometer_generic_read` Generic read function. 
```c
void pedometer_generic_read ( pedometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

### Application Init

> Initializes driver init and sets step counter on 0.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pedometer_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ---- \r\n " );
}
```

### Application Task

> It checks if a new step is detected, if detected new step - reads the current number of steps made and logs data to the USBUART. 

```c
void application_task ( void )
{
    //  Task implementation.

    uint8_t new_step;
    uint32_t s_counter;
    char demoText[ 50 ];
    
    new_step = pedometer_process( &pedometer );

    if ( new_step == PEDOMETER_NEW_STEP_DETECTED )
    {
        s_counter = pedometer_get_step_counter( &pedometer );
        log_printf( &logger, " Step Counter : %d \r\n ", s_counter );
       
        Delay_ms ( 50 );
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
