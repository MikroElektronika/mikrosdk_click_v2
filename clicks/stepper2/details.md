
---
# Stepper 2 click

> Stepper 2 click is a complete solution for driving bipolar stepper motors with full/half and micro-steps. It features the A4988 IC from Allegro Microsystems with DMOS low RDSON drivers on its outputs, which ensure high efficiency and reliable operation of the internal H-Bridges. This IC has the integrated translator section, used to simplify the control: using simple step control inputs from the host MCU, the stepper motor can be driven in both directions, with the predetermined step sizes. In addition, the output current is regulated allowing for noiseless operation of the stepper motor, with no resonance and ringing typically observed at unregulated stepper driver designs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/stepper-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : GPIO type


# Software Support

We provide a library for the Stepper 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper 2 Click driver.

#### Standard key functions :

- `stepper2_cfg_setup` Config Object Initialization function.
```c
void stepper2_cfg_setup ( stepper2_cfg_t *cfg );
```

- `stepper2_init` Initialization function.
```c
err_t stepper2_init ( stepper2_t *ctx, stepper2_cfg_t *cfg );
```

- `stepper2_default_cfg` Click Default Configuration function.
```c
void stepper2_default_cfg ( stepper2_t *ctx );
```

#### Example key functions :

- `stepper2_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void stepper2_drive_motor ( stepper2_t *ctx, uint32_t steps, uint8_t speed );
```

- `stepper2_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
void stepper2_set_direction ( stepper2_t *ctx, uint8_t dir );
```

- `stepper2_enable_device` This function enables the device by setting the ENABLE pin to low logic state.
```c
void stepper2_enable_device ( stepper2_t *ctx );
```

## Example Description

> This example demonstrates the use of the Stepper 2 click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper2_cfg_t stepper2_cfg;  /**< Click config object. */

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
    stepper2_cfg_setup( &stepper2_cfg );
    STEPPER2_MAP_MIKROBUS( stepper2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == stepper2_init( &stepper2, &stepper2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    stepper2_default_cfg ( &stepper2 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor clockwise for 64 steps and then counter-clockiwse for 32 steps
with 2 seconds delay before changing the direction. All data is being logged on
the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf ( &logger, " Move 64 steps clockwise\r\n\n" );
    stepper2_set_direction ( &stepper2, STEPPER2_DIR_CW );
    stepper2_drive_motor ( &stepper2, 64, STEPPER2_SPEED_VERY_FAST );
    Delay_ms ( 2000 );

    log_printf ( &logger, " Move 32 steps counter-clockwise\r\n\n" );
    stepper2_set_direction ( &stepper2, STEPPER2_DIR_CCW );
    stepper2_drive_motor ( &stepper2, 32, STEPPER2_SPEED_FAST );
    Delay_ms ( 2000 );
}
```

## Note

> Step Motor 5v [MIKROE-1530] is a compatible stepper motor for this click board: https://www.mikroe.com/step-motor-5v

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
