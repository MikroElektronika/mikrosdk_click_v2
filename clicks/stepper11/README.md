\mainpage Main Page

---
# Stepper 11 Click

> Stepper 11 Click is a compact add-on board that contains a bipolar stepper motor driver. This board features the TB9120AFTG, a two-phase bipolar stepping motor driver with a clock input interface and a PWM constant-current control system from Toshiba Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper_11_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/stepper-11-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Stepper11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper11 Click driver.

#### Standard key functions :

- `stepper11_cfg_setup` Config Object Initialization function.
```c
void stepper11_cfg_setup ( stepper11_cfg_t *cfg );
```

- `stepper11_init` Initialization function.
```c
err_t stepper11_init ( stepper11_t *ctx, stepper11_cfg_t *cfg );
```

- `stepper11_default_cfg` Click Default Configuration function.
```c
err_t stepper11_default_cfg ( stepper11_t *ctx );
```

#### Example key functions :

- `stepper11_set_step_resolution` Set step resolution.
```c
err_t stepper11_set_step_resolution ( stepper11_t *ctx, uint8_t step_res );
```

- `stepper11_move_motor_angle` Move motor in angle value.
```c
void stepper11_move_motor_angle ( stepper11_t *ctx, float degree, uint8_t speed );
```

- `stepper11_move_motor_step` Move motor in step value.
```c
void stepper11_move_motor_step ( stepper11_t *ctx, uint16_t steps, uint8_t speed );
```

## Example Description

> This example showcases the device's ability to control the motor.
It initializes the device for control and moves the motor in two 
directions in a variety of resolutions for 360 degrees.

**The demo application is composed of two sections :**

### Application Init

> Initialization of communication modules(I2C, UART) and additional pins
for control of device. Then sets default configuration that enables
device for motor control.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper11_cfg_t stepper11_cfg;  /**< Click config object. */

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
    stepper11_cfg_setup( &stepper11_cfg );
    STEPPER11_MAP_MIKROBUS( stepper11_cfg, MIKROBUS_1 );
    err_t init_flag = stepper11_init( &stepper11, &stepper11_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    stepper11_default_cfg ( &stepper11 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Firstly it rotates motor in CW direction for 360 degrees in FULL step 
resolution. Then changes direction in CCW and rotates backwards 360 degrees
in 2 different step resolutions (Quarter and 1/16) in 180 degrees each.

```c

void application_task ( void ) 
{
    stepper11_set_step_resolution( &stepper11, STEPPER11_RESOLUTION_FULL );
    stepper11_set_direction( &stepper11, 1 );
    log_info( &logger, " Rotate motor CW for 360 degrees in full step" );
    stepper11_move_motor_angle( &stepper11, 360, STEPPER11_SPEED_FAST );
    Delay_ms ( 1000 );
    stepper11_set_direction( &stepper11, 0 );
    stepper11_set_step_resolution( &stepper11, STEPPER11_RESOLUTION_QUARTER );
    log_info( &logger, " Rotate motor CCW for 180 degrees in half step" );
    stepper11_move_motor_angle( &stepper11, 180, STEPPER11_SPEED_FAST );
    Delay_ms ( 1000 );
    stepper11_set_step_resolution( &stepper11, STEPPER11_RESOLUTION_1div16 );
    log_info( &logger, " Rotate motor CCW for 180 degrees in 1/8 step" );
    stepper11_move_motor_angle( &stepper11, 180, STEPPER11_SPEED_FAST );
    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
