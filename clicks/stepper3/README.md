\mainpage Main Page

---
# Stepper 3 Click

> Stepper 3 Click is designed to drive unipolar stepper motors, with a supply voltage applied to the common wire. The current flows through the common wire and the motor coil, via the activated current sink driver, to the ground. This Click board™ uses the ULN2003A, a high voltage and current Darlington transistors array IC, as the sink driver. This IC is an ideal solution for this purpose, as it has seven high power Darlington output stages, activated by TTL/CMOS logic level signals, applied to the control pins. This allows driving unipolar stepper motors with up to 30V and 500mA per coil.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/stepper-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : GPIO type


# Software Support

We provide a library for the Stepper 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper 3 Click driver.

#### Standard key functions :

- `stepper3_cfg_setup` Config Object Initialization function.
```c
void stepper3_cfg_setup ( stepper3_cfg_t *cfg );
```

- `stepper3_init` Initialization function.
```c
err_t stepper3_init ( stepper3_t *ctx, stepper3_cfg_t *cfg );
```

#### Example key functions :

- `stepper3_set_step_mode` This function sets the step mode resolution settings in ctx->step_mode.
```c
void stepper3_set_step_mode ( stepper3_t *ctx, uint8_t mode );
```

- `stepper3_set_direction` This function sets the motor direction to clockwise or counter-clockwise in ctx->direction.
```c
void stepper3_set_direction ( stepper3_t *ctx, uint8_t dir );
```

- `stepper3_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void stepper3_drive_motor ( stepper3_t *ctx, uint32_t steps, uint8_t speed );
```

## Example Description

> This example demonstrates the use of the Stepper 3 Click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper3_cfg_t stepper3_cfg;  /**< Click config object. */

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
    stepper3_cfg_setup( &stepper3_cfg );
    STEPPER3_MAP_MIKROBUS( stepper3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == stepper3_init( &stepper3, &stepper3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
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
    stepper3_set_step_mode ( &stepper3, STEPPER3_MODE_FULL_STEP );
    stepper3_set_direction ( &stepper3, STEPPER3_DIR_CW );
    stepper3_drive_motor ( &stepper3, 64, STEPPER3_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 128 half steps counter-clockwise \r\n\n" );
    stepper3_set_step_mode ( &stepper3, STEPPER3_MODE_HALF_STEP );
    stepper3_set_direction ( &stepper3, STEPPER3_DIR_CCW );
    stepper3_drive_motor ( &stepper3, 128, STEPPER3_SPEED_VERY_FAST );
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
- Click.Stepper3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
