
---
# PWM 2 Click

> [PWM 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3148) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3148&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : PWM type

# Software Support

## Example Description

> This application send the PWM signal in one or more outputs.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pwm2

### Example Key Functions

- `pwm2_cfg_setup` Config Object Initialization function. 
```c
void pwm2_cfg_setup ( pwm2_cfg_t *cfg );
``` 
 
- `pwm2_init` Initialization function. 
```c
err_t pwm2_init ( pwm2_t *ctx, pwm2_cfg_t *cfg );
```

- `pwm2_set_channel` Set channel function. 
```c
uint8_t pwm2_set_channel ( pwm2_t *ctx, uint8_t n_channel, uint16_t width, uint8_t correction );
```
 
- `pwm2_pwm_start` Start PWM module. 
```c
void pwm2_pwm_start ( pwm2_t *ctx );
```

- `void send_output_enable_frame` Enable frame. 
```c
static void send_output_enable_frame ( pwm2_t *ctx );
```

### Application Init

> Configures the Click board and sets all PWM channels on the Click board to
> 50% duty cycle with the phase shift enabled.

```c
void application_init ( void )
{
    pwm2_cfg_t cfg;

    //  Click initialization.

    pwm2_cfg_setup( &cfg );
    PWM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pwm2_init( &pwm2, &cfg );
    
    pwm2_set_duty_cycle( &pwm2, 0.5 );
    pwm2_pwm_start( &pwm2 );

    pwm2_default_cfg( &pwm2 );
    pwm2_toggle_phase_shift( &pwm2 );

    //setting all 48 PWM channels of the PWM2 Click to 50% duty
    for( uint8_t cnt = 1; cnt < 49; cnt++ ) 
    {
        pwm2_set_channel( &pwm2, cnt, PWM2_50_PERCENT_DUTY, PWM2_NO_CORRECTION );
    }
}
```

### Application Task

> The first 10 PWM channels of PWM2 Click board are switched back and forth 
> from 25% duty cycle to 75% duty cycle every 10 seconds.

```c
void application_task ( void )
{
    for ( uint8_t cnt = 1; cnt < 10; cnt++ )
    { 
        pwm2_set_channel( &pwm2, cnt, PWM2_25_PERCENT_DUTY, PWM2_NO_CORRECTION );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    for ( uint8_t cnt = 1; cnt < 10; cnt++ )
    { 
        pwm2_set_channel( &pwm2, cnt, PWM2_75_PERCENT_DUTY, PWM2_NO_CORRECTION );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
