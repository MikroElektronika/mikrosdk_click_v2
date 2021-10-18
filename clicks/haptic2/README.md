\mainpage Main Page

---
# HAPTIC 2 click

HAPTIC 2 Click is a compact add-on board that contains a linear vibration driver. This board features the LC898302AXA, a motor driver dedicated to LRA and ERM applications from ON Semiconductor. Controlled by only one pin, it allows crisp vibration thanks to automatic braking and over-driving feature and ignores the deviation of resonance frequency thanks to auto-tuning function. The original driving waveform will enable you to reduce power consumption, and it is helpful to maintain battery lifetime. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/haptic2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/haptic-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the Haptic2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
This library contains API for Haptic2 Click driver.
```

#### Standard key functions :

- `haptic2_cfg_setup` Config Object Initialization function.
```
void haptic2_cfg_setup ( haptic2_cfg_t *cfg );
```

- `haptic2_init` Initialization function.
```
HAPTIC2_RETVAL haptic2_init ( haptic2_t *ctx, haptic2_cfg_t *cfg );
```

- `haptic2_default_cfg` Click Default Configuration function.
```
void haptic2_default_cfg ( haptic2_t *ctx );
```

#### Example key functions :

- `haptic2_set_duty_cycle` Sets PWM duty cycle.
```
err_t haptic2_set_duty_cycle ( haptic2_t *ctx, float duty_cycle );
```

- `haptic2_pwm_stop` Stop PWM module.
```
err_t haptic2_pwm_stop ( haptic2_t *ctx );
```

- `haptic2_pwm_start` Start PWM module.
```
err_t haptic2_pwm_start ( haptic2_t *ctx );
```

## Examples Description

This app shows some of the functions that Haptic 2 click has.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables - PWM, 
> PWM signal is set to 8000 HZ and to give a 0% duty cycle 
> and start PWM module.

```
void application_init ( void ) {
    log_cfg_t log_cfg;          /**< Logger config object. */
    haptic2_cfg_t haptic2_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    haptic2_cfg_setup( &haptic2_cfg );
    HAPTIC2_MAP_MIKROBUS( haptic2_cfg, MIKROBUS_1 );
    err_t init_flag  = haptic2_init( &haptic2, &haptic2_cfg );
    if ( init_flag == PWM_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    haptic2_default_cfg ( &haptic2 );

    haptic2_set_duty_cycle ( &haptic2, 0.0 );
    haptic2_pwm_start( &haptic2 );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> This is an example that demonstrates the use of the Haptic 2 Click board.
> In this example, we switched PWM signal back and forth 
> from 10% ( 0.1 ) duty cycle to 90% ( 0.9 ) duty cycle every 500 milliseconds.
> Results are being sent to the Usart Terminal where you can track their changes.

```
void application_task ( void ) {
    //  Task implementation.
    log_printf( &logger, "--------------------------\r\n" );
    
    for ( float duty = 0.1; duty < 0.9; duty += 0.1 ) {
        Delay_ms( 500 );
        haptic2_set_duty_cycle ( &haptic2, duty );
        log_printf( &logger, "   PWM duty cycle : %.1f \r\n", duty );
    }

    Delay_ms( 1000 );

    for ( float duty = 0.8; duty >= 0; duty -= 0.1 ) {
        Delay_ms( 500 );
        haptic2_set_duty_cycle ( &haptic2, duty );
        log_printf( &logger, "   PWM duty cycle : %.1f \r\n", duty );
    }

    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Haptic2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
