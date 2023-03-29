\mainpage Main Page

---
# Brushless 23 click

> Brushless 23 Click is a compact add-on board suitable for controlling BLDC motors with any MCU. This board features the TC78B011FTG, a three-phase sine-wave PWM pre-driver realized with six external MOSFETs to drive sensorless brushless motors from Toshiba Semiconductor. Some of the main features are a built-in closed-loop speed control function with internal non-volatile memory (NVM) for speed profile setting and the ability to set other features such as rotation direction selection, brake, Standby mode, and others. It also has a wide operating voltage range of 11V to 27V with an output current capacity of 5A and several built-in error detection circuits.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless23_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/brushless-23-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Brushless 23 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless 23 Click driver.

#### Standard key functions :

- `brushless23_cfg_setup` Config Object Initialization function.
```c
void brushless23_cfg_setup ( brushless23_cfg_t *cfg );
```

- `brushless23_init` Initialization function.
```c
err_t brushless23_init ( brushless23_t *ctx, brushless23_cfg_t *cfg );
```

- `brushless23_default_cfg` Click Default Configuration function.
```c
err_t brushless23_default_cfg ( brushless23_t *ctx );
```

#### Example key functions :

- `brushless23_pwm_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t brushless23_pwm_set_duty_cycle ( brushless23_t *ctx, float duty_cycle );
```

- `brushless23_switch_direction` This function switches the direction by toggling the DIR pin state.
```c
void brushless23_switch_direction ( brushless23_t *ctx );
```

- `brushless23_get_motor_speed` This function reads the motor speed in Hz.
```c
err_t brushless23_get_motor_speed ( brushless23_t *ctx, float *motor_speed_hz );
```

## Example Description

> This example demonstrates the use of the Brushless 23 click board by driving the motor in both directions at different speeds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless23_cfg_t brushless23_cfg;  /**< Click config object. */

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
    brushless23_cfg_setup( &brushless23_cfg );
    BRUSHLESS23_MAP_MIKROBUS( brushless23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == brushless23_init( &brushless23, &brushless23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS23_ERROR == brushless23_default_cfg ( &brushless23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Controls the motor speed by changing the PWM duty cycle every 2 seconds.
The duty cycle ranges from 20% to 80%. At the minimal speed, the motor switches direction.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 2;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    brushless23_pwm_set_duty_cycle ( &brushless23, duty );
    log_printf( &logger, "\r\n Duty cycle: %u%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 1500 );
    float motor_speed_hz = 0;
    if ( BRUSHLESS23_OK == brushless23_get_motor_speed ( &brushless23, &motor_speed_hz ) )
    {
        log_printf( &logger, " Speed: %.1f Hz\r\n", motor_speed_hz );
    }
    duty_cnt += duty_inc;
    if ( duty_cnt > 8 ) 
    {
        duty_cnt = 7;
        duty_inc = -1;
    }
    else if ( duty_cnt < 2 ) 
    {
        duty_cnt = 2;
        duty_inc = 1;
        log_printf( &logger, "\r\n Switch direction\r\n" );
        brushless23_pwm_set_duty_cycle ( &brushless23, BRUSHLESS23_DUTY_CYCLE_MIN_PCT );
        Delay_ms ( 500 );
        brushless23_switch_direction ( &brushless23 );
    }
    Delay_ms ( 500 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless23

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
