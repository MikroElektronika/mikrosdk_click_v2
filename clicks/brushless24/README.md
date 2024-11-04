\mainpage Main Page

---
# Brushless 24 Click

> Brushless 24 Click is a compact add-on board that controls brushless DC (BLDC) motors with any MCU. 
> This board features the DRV10866, a 3- phase sensorless motor driver from Texas Instruments 
> with integrated power MOSFETs with current drive capability up to 800mA peak. 
> The DRV10866 implements a 150° commutation (sensorless BEMF control scheme) 
> for a 3-phase motor alongside a synchronous rectification mode of operation 
> that achieves increased efficiency for motor driver applications. 
> Besides choosing the motor speed and a wide operating voltage range of up to 5V, 
> it also has several built-in protection circuits, such as undervoltage, 
> lock detection, voltage surge protection, and overtemperature.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless24_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/brushless-24-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the Brushless 24 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless 24 Click driver.

#### Standard key functions :

- `brushless24_cfg_setup` Config Object Initialization function.
```c
void brushless24_cfg_setup ( brushless24_cfg_t *cfg );
```

- `brushless24_init` Initialization function.
```c
err_t brushless24_init ( brushless24_t *ctx, brushless24_cfg_t *cfg );
```

- `brushless24_default_cfg` Click Default Configuration function.
```c
err_t brushless24_default_cfg ( brushless24_t *ctx );
```

#### Example key functions :

- `brushless24_set_duty_cycle` Brushless 24 sets PWM duty cycle.
```c
err_t brushless24_set_duty_cycle ( brushless24_t *ctx, float duty_cycle );
```

- `brushless24_pwm_start` Brushless 24 start PWM module.
```c
err_t brushless24_pwm_start ( brushless24_t *ctx );
```

- `brushless24_get_int_state` Brushless 24 get INT pin state.
```c
uint8_t brushless24_get_int_state ( brushless24_t *ctx );
```

## Example Description

> This application is a schowcase of controlling speed of brushless motor using Brushless 24 Click.

**The demo application is composed of two sections :**

### Application Init

> Initialization of LOG, PWM module and additional pins.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless24_cfg_t brushless24_cfg;  /**< Click config object. */

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
    brushless24_cfg_setup( &brushless24_cfg );
    BRUSHLESS24_MAP_MIKROBUS( brushless24_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless24_init( &brushless24, &brushless24_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS24_ERROR == brushless24_default_cfg ( &brushless24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> In a span of second changes duty cycle from 0 to 100% which is changing speed of the motor.

```c
void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    brushless24_set_duty_cycle ( &brushless24, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 1000 );
    
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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless24

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
