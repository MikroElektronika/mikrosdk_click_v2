
---
# Vibro Motor Click

Vibro Motor Click features a compact size Eccentric Rotating Mass (ERM) motor, labeled as C1026B002F. This type of motor is often used for haptic feedback on many small handheld devices, such as the cellphones, pagers, RFID scanners and similar devices. This motor contains a small eccentric weight on its rotor, so while rotating it also produces vibration effect. This kind of motors is sometimes referred to as coin motors, due to its shape.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vibromotor_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/vibro-motor-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : PWM type


# Software Support

We provide a library for the VibroMotor Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for VibroMotor Click driver.

#### Standard key functions :

- `vibromotor_cfg_setup` Config Object Initialization function.
```c
void vibromotor_cfg_setup ( vibromotor_cfg_t *cfg );
```

- `vibromotor_init` Initialization function.
```c
err_t vibromotor_init ( vibromotor_t *ctx, vibromotor_cfg_t *cfg );
```

#### Example key functions :

- `vibromotor_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t vibromotor_set_duty_cycle ( vibromotor_t *ctx, float duty_cycle );
```

- `vibromotor_pwm_stop` This function stops the PWM moudle output.
```c
err_t vibromotor_pwm_stop ( vibromotor_t *ctx );
```

- `vibromotor_pwm_start` This function starts the PWM moudle output.
```c
err_t vibromotor_pwm_start ( vibromotor_t *ctx );
```

## Example Description

> This application contorl the speed of vibro motor.

**The demo application is composed of two sections :**

### Application Init

> Configures PWM to 5kHz frequency, calculates maximum duty ratio and starts PWM with duty ratio value 0.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    vibromotor_cfg_t vibromotor_cfg;  /**< Click config object. */

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

    vibromotor_cfg_setup( &vibromotor_cfg );
    VIBROMOTOR_MAP_MIKROBUS( vibromotor_cfg, MIKROBUS_1 );
    err_t init_flag  = vibromotor_init( &vibromotor, &vibromotor_cfg );
    if ( PWM_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    vibromotor_set_duty_cycle ( &vibromotor, 0.0 );
    vibromotor_pwm_start( &vibromotor );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Allows user to enter desired command to control Vibro Motor Click board.

```c

void application_task ( void ) {
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    vibromotor_set_duty_cycle ( &vibromotor, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );
    
    if ( 10 == duty_cnt ) {
        duty_inc = -1;
    } else if ( 0 == duty_cnt ) {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.VibroMotor

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
