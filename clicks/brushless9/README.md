
---
# Brushless 9 Click

> [Brushless 9 Click](https://www.mikroe.com/?pid_product=MIKROE-4387) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4387&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Dec 2020.
- **Type**          : PWM type

# Software Support

## Example Description

> This application is a showcase of controlling speed and direction of brushless motor with hall sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless9

### Example Key Functions

- `brushless9_cfg_setup` Config Object Initialization function.
```c
void brushless9_cfg_setup ( brushless9_cfg_t *cfg );
```

- `brushless9_init` Initialization function.
```c
err_t brushless9_init ( brushless9_t *ctx, brushless9_cfg_t *cfg );
```

- `brushless9_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t brushless9_set_duty_cycle ( brushless9_t *ctx, float duty_cycle );
```

- `brushless9_set_dir` This function sets dir pin output to status setting.
```c
void brushless9_set_dir ( brushless9_t *ctx, uint8_t state );
```

- `brushless9_set_brk` This function sets brk pin output to status setting.
```c
void brushless9_set_brk ( brushless9_t *ctx, uint8_t state );
```

### Application Init

> Initialization of LOG, PWM module and additional pins for controlling motor.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless9_cfg_t brushless9_cfg;  /**< Click config object. */

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
    brushless9_cfg_setup( &brushless9_cfg );
    BRUSHLESS9_MAP_MIKROBUS( brushless9_cfg, MIKROBUS_1 );
    err_t init_flag  = brushless9_init( &brushless9, &brushless9_cfg );
    if ( init_flag == PWM_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    brushless9_set_dir( &brushless9, direction );
    brushless9_set_brk( &brushless9, 1 );

    brushless9_set_duty_cycle ( &brushless9, 0 );
    brushless9_pwm_start( &brushless9 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> In span of 2 seconds changes duty cycle from 0 to 100% and then back to 0, at the end changes direction of motor.

```c
void application_task ( void )
{
    log_info( &logger, " Starting... " );
    brushless9_set_brk( &brushless9, 0 );
    for ( uint8_t duty_cnt = 1; duty_cnt < 10; duty_cnt++ )
    {
        Delay_ms ( DUTY_CHANGE_DELAY );
        brushless9_set_duty_cycle ( &brushless9, ( float ) duty_cnt / 10.0 );
        log_printf( &logger, "Duty cycle: %u%%\r\n", ( uint16_t ) ( duty_cnt * 10 ) );
    }

    for ( uint8_t duty_cnt = 10; duty_cnt > 0; duty_cnt-- )
    {
        Delay_ms ( DUTY_CHANGE_DELAY );
        brushless9_set_duty_cycle ( &brushless9, ( float ) duty_cnt / 10.0 );
        log_printf( &logger, "Duty cycle: %u%%\r\n", ( uint16_t ) ( duty_cnt * 10 ) );
    }

    Delay_ms ( DUTY_CHANGE_DELAY );
    log_info( &logger, " Stopping... " );
    brushless9_set_duty_cycle ( &brushless9, 0 );
    brushless9_set_brk( &brushless9, 1 );
    Delay_ms ( BREAK_DELAY );
    log_info( &logger, " Changing direction... " );
    direction = !direction;
    brushless9_set_dir( &brushless9, direction );
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
