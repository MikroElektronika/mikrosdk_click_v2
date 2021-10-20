\mainpage Main Page

---
# Vibro Motor 4 click

> Vibro Motor 4 Click is a compact add-on board that makes an ideal solution for adding simple haptic feedback in any design. This board features the G1040003D, a coin-sized linear resonant actuator (LRA) that generates vibration/haptic feedback from Jinlong Machinery & Electronics, Inc. Driven by a flexible Haptic/Vibra driver, the DRV2605, G1040003D vibrates in the Z-axis, which is perpendicular to the face of the vibration motor. It draws a maximum of 170mA while producing the highest G force/vibration energy of 2 GRMS.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vibromotor4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/vibro-motor-4-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the VibroMotor4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for VibroMotor4 Click driver.

#### Standard key functions :

- `vibromotor4_cfg_setup` Config Object Initialization function.
```c
void vibromotor4_cfg_setup ( vibromotor4_cfg_t *cfg );
```

- `vibromotor4_init` Initialization function.
```c
err_t vibromotor4_init ( vibromotor4_t *ctx, vibromotor4_cfg_t *cfg );
```

- `vibromotor4_default_cfg` Click Default Configuration function.
```c
err_t vibromotor4_default_cfg ( vibromotor4_t *ctx );
```

#### Example key functions :

- `vibromotor4_set_mode` Vibro Motor 4 sets the desired mode function.
```c
err_t vibromotor4_set_mode ( vibromotor4_t *ctx, uint8_t mode_sel );
```

- `vibromotor4_set_duty_cycle` Vibro Motor 4 sets PWM duty cycle.
```c
err_t vibromotor4_set_duty_cycle ( vibromotor4_t *ctx, float duty_cycle );
```

- `vibromotor4_pwm_start` Vibro Motor 4 start PWM module.
```c
err_t vibromotor4_pwm_start ( vibromotor4_t *ctx );
```

## Example Description

> This library contains API for Vibro Motor 4 Click driver.
> The library initializes and defines the I2C bus drivers 
> to write and read data from registers and PWM module.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C and PWM module, log UART, and additional pins. 
> After successful driver init, executes a default configuration
> and configures Vibro Motor 4 Click board™.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    vibromotor4_cfg_t vibromotor4_cfg;  /**< Click config object. */

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
    vibromotor4_cfg_setup( &vibromotor4_cfg );
    VIBROMOTOR4_MAP_MIKROBUS( vibromotor4_cfg, MIKROBUS_1 );
    err_t init_flag = vibromotor4_init( &vibromotor4, &vibromotor4_cfg );
    if ( I2C_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    vibromotor4_enable( &vibromotor4, VIBROMOTOR4_PROPERTY_ENABLE );
    Delay_ms( 100 );

    vibromotor4_soft_rst( &vibromotor4 );
    Delay_ms( 100 );

    vibromotor4_default_cfg ( &vibromotor4 );
    Delay_ms( 100 );

    vibromotor4_set_duty_cycle( &vibromotor4, 0.0 );
    Delay_ms( 100 );

    vibromotor4_pwm_start( &vibromotor4 );
    Delay_ms( 100 );

    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

```

### Application Task

> This is an example that shows the use of Vibro Motor 4 Click board™.
> Changing duty cycle results in different vibrations.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    static int8_t duty_cnt = 0;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    vibromotor4_set_duty_cycle ( &vibromotor4, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );

    Delay_ms( 1000 );

    if ( 5 == duty_cnt ) {
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
- Click.VibroMotor4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
