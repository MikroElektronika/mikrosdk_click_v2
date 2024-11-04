\mainpage Main Page

---
# LED Driver 9 Click

LED Driver 9 Click is a compact add-on board that simplifies the control of multiple LEDs. This board features the TLC59116, I2C bus-controlled 16-channel LED driver optimized for red/green/blue/amber (RGBA) color mixing and backlight application from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/led_driver_9_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/led-driver-9-click)

---


#### Click library

- **Author**        : Stefan Nikolic
- **Date**          : feb 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the LEDDriver9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LEDDriver9 Click driver.

#### Standard key functions :

- `leddriver9_cfg_setup` Config Object Initialization function.
```c
void leddriver9_cfg_setup ( leddriver9_cfg_t *cfg );
```

- `leddriver9_init` Initialization function.
```c
LEDDRIVER9_RETVAL leddriver9_init ( leddriver9_t *ctx, leddriver9_cfg_t *cfg );
```

- `leddriver9_default_cfg` Click Default Configuration function.
```c
void leddriver9_default_cfg ( leddriver9_t *ctx );
```

#### Example key functions :

- `leddriver9_ledout_state` This function configures the LEDOUTx registers from the defined config structure.
```c
err_t leddriver9_ledout_state ( leddriver9_t *ctx, leddriver9_output_state_t *output_state );
```

- `leddriver9_set_pwm` This function sets the PWM duty cycle on selected ledout channel.
```c
err_t leddriver9_set_pwm ( leddriver9_t *ctx, leddriver9_channel_sel_t ch_out, float duty_cycle );
```

- `leddriver9_set_dimmer_pwm` This function sets the group PWM duty cycle ( GRPPWM ) which can be used for dimming already set PWM channels.
```c
err_t leddriver9_set_dimmer_pwm ( leddriver9_t *ctx, float duty_cycle );
```

## Example Description

> This app demonstrates the configuration and control of the LED Driver 9 Click board resulting in a nice breathing effect.

**The demo application is composed of two sections :**

### Application Init

> The initialization configures the UART LOG and I2C drivers and adjusts the Led Driver 9 Click general register settings.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;                /**< Logger config object. */
    leddriver9_cfg_t leddriver9_cfg;  /**< Click config object. */

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

    leddriver9_cfg_setup( &leddriver9_cfg );
    LEDDRIVER9_MAP_MIKROBUS( leddriver9_cfg, MIKROBUS_1 );
    err_t init_flag = leddriver9_init( &leddriver9, &leddriver9_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    leddriver9_default_cfg( &leddriver9 );
    log_info( &logger, " Application Task " );
    
    mode1_register_settings( );
    mode2_register_settings( );
    Delay_ms ( 100 );
    
    led_output_state( );
    Delay_ms ( 100 );
}

```

### Application Task

> The application task is a simple breathing effect on all LED out channels.

```c

void application_task ( void ) {
    float duty_cnt = min_duty;
    
    while ( duty_cnt <= max_duty ) {
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL0, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL1, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL2, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL3, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL4, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL5, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL6, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL7, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL8, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL9, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL10, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL11, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL12, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL13, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL14, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL15, duty_cnt );
        duty_cnt += duty_gradient;
        Delay_ms ( breathing_speed );
    }
    while ( duty_cnt > min_duty ) {
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL0, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL1, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL2, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL3, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL4, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL5, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL6, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL7, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL8, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL9, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL10, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL11, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL12, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL13, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL14, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL15, duty_cnt );
        duty_cnt -= duty_gradient;
        Delay_ms ( breathing_speed );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
