
---
# DC Motor 22 click

> DC Motor 22 Click is a compact add-on board that contains a brushed DC motor driver. This board features the TMC7300, a low voltage driver for one or two DC motors from TRINAMIC Motion Control. The TMC7300 is rated for an operating voltage range from 2V to 11V and operates up to two DC motors via simple UART control for direction, velocity, and torque. It also has a complete set of diagnostic and protection capabilities that supports robust and reliable operation, like short to ground protection, short to power supply protection and undervoltage detection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor22_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dc-motor-22-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : UART type


# Software Support

We provide a library for the DC Motor 22 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DC Motor 22 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of DC Motor 22 click board by controlling the speed of both motors over PWM duty cycle as well as displaying the motors current consumption.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor22

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
