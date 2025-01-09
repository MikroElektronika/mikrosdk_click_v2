
---
# MCP1664 Click

> [MCP1664 Click](https://www.mikroe.com/?pid_product=MIKROE-2548) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2548&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type

# Software Support

## Example Description

> This application turn on and turn off white LEDs.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mcp1664

### Example Key Functions

- `mcp1664_cfg_setup` Config Object Initialization function. 
```c
void mcp1664_cfg_setup ( mcp1664_cfg_t *cfg );
``` 
 
- `mcp1664_init` Initialization function. 
```c
err_t mcp1664_init ( mcp1664_t *ctx, mcp1664_cfg_t *cfg );
```

- `mcp1664_pwm_start` Start PWM module. 
```c
void mcp1664_pwm_start ( mcp1664_t *ctx );
```
 
- `mcp1664_pwm_stop` Stop PWM module. 
```c
void mcp1664_pwm_stop ( mcp1664_t *ctx );
```

### Application Init

> Enables GPIO and PWM, sets the frequency and duty cycle and enables PWM.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp1664_cfg_t cfg;

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

    mcp1664_cfg_setup( &cfg );
    MCP1664_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp1664_init( &mcp1664, &cfg );

    mcp1664_set_duty_cycle( &mcp1664, duty_cycle );
    mcp1664_pwm_start( &mcp1664 );
    Delay_ms ( 1000 );
    log_printf( &logger, "------------------ \r\n" );
    log_printf( &logger, "  MCP1664  Click   \r\n" );
    log_printf( &logger, "------------------ \r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This is a example which demonstrates the use of MCP1664 Click board.
> It shows how to enable the device and gradualy increase the duty cycle.

```c
void application_task ( void )
{
    //  Task implementation.
    
    if ( duty_cycle > mcp1664.pwm_period )
    {
        duty_cycle = 5000;
    }
    
    mcp1664_set_duty_cycle ( &mcp1664, duty_cycle );
    duty_cycle += 50;
    Delay_100ms();

    log_printf( &logger,  "  Duty cycle is : %d  \r\n", duty_cycle );
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
