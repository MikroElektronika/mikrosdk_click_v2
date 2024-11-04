
---
# Stepper Click

> Stepper Click is a complete solution for driving bipolar stepper motors with full/half and micro-steps. It features the A3967 IC from Allegro Microsystems with proprietary Satlington™ sink drivers on its outputs, which ensure high efficiency and reliable operation of the internal H-Bridges. This IC has the integrated translation section, used to simplify the control: using simple step control inputs from the host MCU, the stepper motor can be driven in both directions, with the predetermined step sizes. In addition, the output current is regulated allowing for noiseless operation of the stepper motor, with no resonance and ringing typically observed at unregulated stepper driver designs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/stepper-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : GPIO type


# Software Support

We provide a library for the Stepper Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper Click driver.

#### Standard key functions :

- `stepper_cfg_setup` Config Object Initialization function.
```c
void stepper_cfg_setup ( stepper_cfg_t *cfg );
```

- `stepper_init` Initialization function.
```c
err_t stepper_init ( stepper_t *ctx, stepper_cfg_t *cfg );
```

- `stepper_default_cfg` Click Default Configuration function.
```c
void stepper_default_cfg ( stepper_t *ctx );
```

#### Example key functions :

- `stepper_set_step_mode` This function sets the step mode resolution settings.
```c
void stepper_set_step_mode ( stepper_t *ctx, uint8_t mode );
```

- `stepper_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
void stepper_set_direction ( stepper_t *ctx, uint8_t dir );
```

- `stepper_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void stepper_drive_motor ( stepper_t *ctx, uint32_t steps, uint8_t speed );
```

## Example Description

> This example demonstrates the use of the Stepper Click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper_cfg_t stepper_cfg;  /**< Click config object. */

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
    stepper_cfg_setup( &stepper_cfg );
    STEPPER_MAP_MIKROBUS( stepper_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == stepper_init( &stepper, &stepper_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    stepper_default_cfg ( &stepper );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor clockwise for 64 full steps and then counter-clockiwse for 128 half
steps with 2 seconds delay before changing the direction. All data is being logged on
the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf ( &logger, " Move 64 full steps clockwise \r\n\n" );
    stepper_set_step_mode ( &stepper, STEPPER_MODE_FULL_STEP );
    stepper_set_direction ( &stepper, STEPPER_DIR_CW );
    stepper_drive_motor ( &stepper, 64, STEPPER_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 128 half steps counter-clockwise \r\n\n" );
    stepper_set_step_mode ( &stepper, STEPPER_MODE_HALF_STEP );
    stepper_set_direction ( &stepper, STEPPER_DIR_CCW );
    stepper_drive_motor ( &stepper, 128, STEPPER_SPEED_VERY_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Note

> Step Motor 5v [MIKROE-1530] is a fully compatible stepper motor for this Click board: https://www.mikroe.com/step-motor-5v

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
