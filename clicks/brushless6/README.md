\mainpage Main Page
 

---
# Brushless 6 Click

Brushless 6 Click is designed to drive a three-phase sensorless, brushless motor, also known as the BLDC motor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless6_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/brushless-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the Brushless6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Brushless6 Click driver.

#### Standard key functions :

- `brushless6_cfg_setup` Config Object Initialization function.
```c
void brushless6_cfg_setup ( brushless6_cfg_t *cfg ); 
```

- `brushless6_init` Initialization function.
```c
BRUSHLESS6_RETVAL brushless6_init ( brushless6_t *ctx, brushless6_cfg_t *cfg );
```

#### Example key functions :

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

## Examples Description

> Brushless 6 Click is designed to drive a three-phase sensorless.

**The demo application is composed of two sections :**

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

### NOTE

> The maximal PWM Clock frequency for this Click board is 500 Hz. 
> So, the user will need to decrease the MCU's main clock frequency in MCU Settings in order to get up-to 500 Hz PWM clock frequency.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless6

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
