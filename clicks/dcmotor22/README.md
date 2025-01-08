
---
# DC Motor 22 Click

> [DC Motor 22 Click](https://www.mikroe.com/?pid_product=MIKROE-5189) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5189&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of DC Motor 22 Click board by controlling the speed of both motors over PWM duty cycle as well as displaying the motors current consumption.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor22

### Example Key Functions

- `dcmotor22_cfg_setup` Config Object Initialization function.
```c
void dcmotor22_cfg_setup ( dcmotor22_cfg_t *cfg );
```

- `dcmotor22_init` Initialization function.
```c
err_t dcmotor22_init ( dcmotor22_t *ctx, dcmotor22_cfg_t *cfg );
```

- `dcmotor22_default_cfg` Click Default Configuration function.
```c
err_t dcmotor22_default_cfg ( dcmotor22_t *ctx );
```

- `dcmotor22_set_motor_pwm` This function sets the PWM duty cycle of the selected motor.
```c
err_t dcmotor22_set_motor_pwm ( dcmotor22_t *ctx, uint8_t motor_sel, int16_t pwm_duty );
```

- `dcmotor22_get_motor_current` This function reads the current consumption of the selected motor.
```c
err_t dcmotor22_get_motor_current ( dcmotor22_t *ctx, uint8_t motor_sel, float *current );
```

- `dcmotor22_reset_device` This function resets the device by toggling the EN pin state.
```c
void dcmotor22_reset_device ( dcmotor22_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor22_cfg_t dcmotor22_cfg;  /**< Click config object. */

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
    dcmotor22_cfg_setup( &dcmotor22_cfg );
    DCMOTOR22_MAP_MIKROBUS( dcmotor22_cfg, MIKROBUS_1 );
    if ( UART_ERROR == dcmotor22_init( &dcmotor22, &dcmotor22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR22_ERROR == dcmotor22_default_cfg ( &dcmotor22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Controls the motor speed by changing the PWM duty cycle every 5 seconds, and displays
the motors current consumption. The duty cycle ranges from -100% to +100%. 
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static int16_t pwm_duty = 0;
    static int8_t pwm_duty_step = 50;
    float current;
    log_printf ( &logger, " Motor A\r\n" );
    if ( DCMOTOR22_OK == dcmotor22_set_motor_pwm ( &dcmotor22, DCMOTOR22_MOTOR_A, pwm_duty ) )
    {
        log_printf ( &logger, " PWM duty: %d\r\n", pwm_duty );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( DCMOTOR22_OK == dcmotor22_get_motor_current ( &dcmotor22, DCMOTOR22_MOTOR_A, &current ) )
    {
        log_printf ( &logger, " Current: %.3f A\r\n\n", current );
    }
    Delay_ms ( 500 );
    log_printf ( &logger, " Motor B\r\n" );
    if ( DCMOTOR22_OK == dcmotor22_set_motor_pwm ( &dcmotor22, DCMOTOR22_MOTOR_B, pwm_duty ) )
    {
        log_printf ( &logger, " PWM duty: %d\r\n", pwm_duty );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( DCMOTOR22_OK == dcmotor22_get_motor_current ( &dcmotor22, DCMOTOR22_MOTOR_B, &current ) )
    {
        log_printf ( &logger, " Current: %.3f A\r\n\n", current );
    }
    Delay_ms ( 500 );
    
    if ( ( ( pwm_duty + pwm_duty_step ) > DCMOTOR22_MAX_PWM ) || ( ( pwm_duty + pwm_duty_step ) < DCMOTOR22_MIN_PWM ) ) 
    {
        pwm_duty_step = -pwm_duty_step;
    }
    pwm_duty += pwm_duty_step;
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
