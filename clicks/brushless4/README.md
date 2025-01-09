
---
# Brushless 4 Click

> [Brushless 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3019) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3019&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

> This Click has many features for driving a wide range of small to medium BLDC motors.
> It provides the rotor position digital output, via the FG pin, routed to the mikroBUS INT pin. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless4

### Example Key Functions

- `brushless4_cfg_setup` Config Object Initialization function. 
```c
void brushless4_cfg_setup ( brushless4_cfg_t *cfg );
``` 
 
- `brushless4_init` Initialization function. 
```c
err_t brushless4_init ( brushless4_t *ctx, brushless4_cfg_t *cfg );
```

- `brushless4_default_cfg` Click Default Configuration function. 
```c
void brushless4_default_cfg ( brushless4_t *ctx );
```

- `brushless4_set_duty_cycle` This function sets the PWM duty cycle. 
```c
void brushless4_set_duty_cycle ( brushless4_t *ctx, pwm_data_t duty_cycle );
```
 
- `brushless4_pwm_start` This function starts PWM module. 
```c
void brushless4_pwm_start ( brushless4_t *ctx );
```

- `brushless4_pwm_pin` This function sets the state of the PWM pin. 
```c
void brushless4_pwm_pin ( brushless4_t *ctx, uint8_t state );
```

### Application Init

> Initializes the GPIO driver and configures the PWM peripheral for controlling the speed of the motor.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless4_cfg_t cfg;

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

    brushless4_cfg_setup( &cfg );
    BRUSHLESS4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless4_init( &brushless4, &cfg );
    
    brushless4_set_duty_cycle ( &brushless4, 0.0 );
    brushless4_pwm_start( &brushless4 );  
      
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 1000 );
}
```

### Application Task

>  This is an example that demonstrates the use of a Brushless 4 Click board.
>  Brushless 4 Click communicates with the register via the PWM interface.  
>  Increases and decreasing the speed of the motor demonstrate speed control.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    brushless4_set_duty_cycle ( &brushless4, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
        log_printf( &logger, " Slowing down... \r\n" );
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
        log_printf( &logger, " Increasing the motor speed... \r\n" );
    }
    duty_cnt += duty_inc;
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
