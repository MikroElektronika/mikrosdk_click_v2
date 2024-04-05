
---
# Stepper 5 click

> Stepper 5 Click is the complete integrated bipolar step motor driver solution, rich with many features that allow silent operation and optimal working conditions for the connected motor. The specialized TMC2208 IC driver from Trinamic company far exceeds the capabilities of similar step motor drivers that are commonly used. In order to achieve such outstanding performances with a wide range of various step motors, this device features several technologies: stealth Chop2™ - for silent motor operation; spreadCycle™ - highly dynamic, motor current control; microPlayer™ interpolation with 256 microsteps.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/stepper-5-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : UART type


# Software Support

We provide a library for the Stepper 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper 5 Click driver.

#### Standard key functions :

- `stepper5_cfg_setup` Config Object Initialization function.
```c
void stepper5_cfg_setup ( stepper5_cfg_t *cfg );
```

- `stepper5_init` Initialization function.
```c
err_t stepper5_init ( stepper5_t *ctx, stepper5_cfg_t *cfg );
```

- `stepper5_default_cfg` Click Default Configuration function.
```c
err_t stepper5_default_cfg ( stepper5_t *ctx );
```

#### Example key functions :

- `stepper5_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
void stepper5_set_direction ( stepper5_t *ctx, uint8_t dir );
```

- `stepper5_set_step_res` This function sets the microstep resolution bits in CHOPCONF register.
```c
err_t stepper5_set_step_res ( stepper5_t *ctx, uint8_t mres );
```

- `stepper5_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void stepper5_drive_motor ( stepper5_t *ctx, uint32_t steps, uint8_t speed );
```

## Example Description

> This example demonstrates the use of the Stepper 5 click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper5_cfg_t stepper5_cfg;  /**< Click config object. */

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
    stepper5_cfg_setup( &stepper5_cfg );
    STEPPER5_MAP_MIKROBUS( stepper5_cfg, MIKROBUS_1 );
    if ( UART_ERROR == stepper5_init( &stepper5, &stepper5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER5_ERROR == stepper5_default_cfg ( &stepper5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor clockwise for 200 full steps and then counter-clockiwse for 200 half
steps and 400 quarter steps with 2 seconds delay on driving mode change. All data is
being logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    stepper5_set_direction ( &stepper5, STEPPER5_DIR_CW );
    stepper5_set_step_res ( &stepper5, STEPPER5_MRES_FULLSTEP );
    stepper5_drive_motor ( &stepper5, 200, STEPPER5_SPEED_SLOW );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper5_set_direction ( &stepper5, STEPPER5_DIR_CCW );
    stepper5_set_step_res ( &stepper5, STEPPER5_MRES_2 );
    stepper5_drive_motor ( &stepper5, 200, STEPPER5_SPEED_MEDIUM );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    stepper5_set_direction ( &stepper5, STEPPER5_DIR_CCW );
    stepper5_set_step_res ( &stepper5, STEPPER5_MRES_4 );
    stepper5_drive_motor ( &stepper5, 400, STEPPER5_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
