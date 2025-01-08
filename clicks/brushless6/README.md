
---
# Brushless 6 Click

> [Brushless 6 Click](https://www.mikroe.com/?pid_product=MIKROE-2847) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2847&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type

# Software Support

## Example Description

> Brushless 6 Click is designed to drive a three-phase sensorless.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless6

### Example Key Functions

- `brushless6_cfg_setup` Config Object Initialization function.
```c
void brushless6_cfg_setup ( brushless6_cfg_t *cfg ); 
```

- `brushless6_init` Initialization function.
```c
err_t brushless6_init ( brushless6_t *ctx, brushless6_cfg_t *cfg );
```

- `brushless6_pwm_start` Start PWM module.
```c
void brushless6_pwm_start ( brushless6_t *ctx );
```

- `brushless6_pwm_stop` Stop PWM module.
```c
void brushless6_pwm_stop ( brushless6_t *ctx );
```

- `brushless6_set_duty_cycle` Generic sets PWM duty cycle.
```c
void brushless6_set_duty_cycle ( brushless6_t *ctx, float duty_cycle );
```

### Application Init

> This function initializes and configures the logger and the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless6_cfg_t cfg;

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

    brushless6_cfg_setup( &cfg );
    BRUSHLESS6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless6_init( &brushless6, &cfg );
    brushless6_calibration( );
    brushless6_setings( );
}
```

### Application Task

> This function drives the motor in both directions increasing and decreasing the speed of the motor.

```c
void application_task ( void )
{
    clockwise( );
    counter_clockwise( );
}
```

### Note

> The maximal PWM Clock frequency for this Click board is 500 Hz. 
> So, the user will need to decrease the MCU's main clock frequency in MCU Settings in order to get up-to 500 Hz PWM clock frequency.

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
