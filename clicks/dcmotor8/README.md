
---
# DC Motor 8 Click

> [DC Motor 8 Click](https://www.mikroe.com/?pid_product=MIKROE-2893) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2893&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

> This Click can drive simple DC motors with brushes, providing them with a significant amount 
> of current and voltage up to 40V. The Click has one control input, that uses the PWM signal 
> from the host MCU. It uses the half-bridge topology to regulate the speed of the motor 
> rotation, employs advanced dead-time circuitry that monitors the output stage, providing 
> maximum switching efficiency and features an advanced technique to avoid shoot-through 
> currents.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor8

### Example Key Functions

- `dcmotor8_cfg_setup` Config Object Initialization function. 
```c
void dcmotor8_cfg_setup ( dcmotor8_cfg_t *cfg );
``` 
 
- `dcmotor8_init` Initialization function. 
```c
err_t dcmotor8_init ( dcmotor8_t *ctx, dcmotor8_cfg_t *cfg );
```

- `dcmotor8_set_duty_cycle` This function sets the PWM duty cycle. 
```c
void dcmotor8_set_duty_cycle ( dcmotor8_t *ctx, float duty_cycle );
```
 
- `dcmotor8_pwm_start` This function starts PWM module. 
```c
void dcmotor8_pwm_start ( dcmotor8_t *ctx );
```

- `dcmotor8_pwm_stop` This function stops PWM module. 
```c
void dcmotor8_pwm_stop ( dcmotor8_t *ctx );
```

### Application Init

> Initializes the driver and enables the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor8_cfg_t cfg;

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

    dcmotor8_cfg_setup( &cfg );
    DCMOTOR8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor8_init( &dcmotor8, &cfg );

    dcmotor8_set_duty_cycle ( &dcmotor8, 0.0 );
    dcmotor8_enable ( &dcmotor8, DCMOTOR8_ENABLE );
    dcmotor8_pwm_start( &dcmotor8 );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 500 );
}
```

### Application Task

>  This is an example that demonstrates the use of DC Motor 8 Click
>  board by increasing and decreasing the motor speed.
>  DC Motor 8 Click communicates with the register via the PWM interface.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    dcmotor8_set_duty_cycle ( &dcmotor8, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
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
