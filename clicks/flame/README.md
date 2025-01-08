
---
# FLAME Click

> [FLAME Click](https://www.mikroe.com/?pid_product=MIKROE-1820) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1820&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application detects fire.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Flame

### Example Key Functions

- `flame_cfg_setup` Config Object Initialization function. 
```c
void flame_cfg_setup ( flame_cfg_t *cfg );
``` 
 
- `flame_init` Initialization function. 
```c
err_t flame_init ( flame_t *ctx, flame_cfg_t *cfg );
```

- `flame_check_status` Check the flame status function. 
```c
uint8_t flame_check_status ( flame_t *ctx );
```
 
- `flame_get_interrupt` Get interrupt status. 
```c
uint8_t flame_get_interrupt ( flame_t *ctx );
```

### Application Init

> Initialization driver enable's - GPIO and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    flame_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    flame_cfg_setup( &cfg );
    FLAME_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flame_init( &flame, &cfg );
}
```

### Application Task


> This is a example which demonstrates the use of Flame Click board. 

```c
void application_task ( void )
{
    //  Task implementation.

    flame_state = flame_check_status ( &flame );

    if ( ( flame_state == 1 ) && ( flame_state_old == 0) )
    {
        log_printf( &logger, "  ~  FLAME   ~ \r\n " );
       
        flame_state_old = 1;
    }

    if ( ( flame_state == 0 ) && ( flame_state_old == 1 ) )
    {
        log_printf( &logger, "   NO FLAME  \r\n " );
        flame_state_old = 0;
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
