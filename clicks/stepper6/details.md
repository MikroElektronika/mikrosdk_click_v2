
---
# Stepper 6 Click

> Stepper 6 Click is the complete integrated bipolar step motor driver solution. It comes with the abundance of features that allow silent operation and optimal working conditions for the connected motor. A specialized integrated driver chip on this Click board™ far exceeds the capabilities of similar, commonly used step motor drivers. It comes in the package which also includes the mikroSDK™ software, and a library with all the functions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper6_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/stepper-6-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Stepper 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper 6 Click driver.

#### Standard key functions :

- `stepper6_cfg_setup` Config Object Initialization function.
```c
void stepper6_cfg_setup ( stepper6_cfg_t *cfg );
```

- `stepper6_init` Initialization function.
```c
err_t stepper6_init ( stepper6_t *ctx, stepper6_cfg_t *cfg );
```

- `stepper6_default_cfg` Click Default Configuration function.
```c
err_t stepper6_default_cfg ( stepper6_t *ctx );
```

#### Example key functions :

- `stepper6_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
void stepper6_set_direction ( stepper6_t *ctx, uint8_t dir );
```

- `stepper6_set_step_mode` This function sets the step mode resolution settings.
```c
err_t stepper6_set_step_mode ( stepper6_t *ctx, uint8_t mode );
```

- `stepper6_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void stepper6_drive_motor ( stepper6_t *ctx, uint32_t steps, uint8_t speed );
```

## Example Description

> This example demonstrates the use of the Stepper 6 Click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper6_cfg_t stepper6_cfg;  /**< Click config object. */

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
    stepper6_cfg_setup( &stepper6_cfg );
    STEPPER6_MAP_MIKROBUS( stepper6_cfg, MIKROBUS_1 );
    err_t init_flag = stepper6_init( &stepper6, &stepper6_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER6_ERROR == stepper6_default_cfg ( &stepper6 ) )
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
    stepper6_set_direction ( &stepper6, STEPPER6_DIR_CW );
    stepper6_set_step_mode ( &stepper6, STEPPER6_MODE_FULL_STEP );
    stepper6_drive_motor ( &stepper6, 200, STEPPER6_SPEED_SLOW );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper6_set_direction ( &stepper6, STEPPER6_DIR_CCW );
    stepper6_set_step_mode ( &stepper6, STEPPER6_MODE_HALF_STEP );
    stepper6_drive_motor ( &stepper6, 200, STEPPER6_SPEED_MEDIUM );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    stepper6_set_direction ( &stepper6, STEPPER6_DIR_CCW );
    stepper6_set_step_mode ( &stepper6, STEPPER6_MODE_QUARTER_STEP );
    stepper6_drive_motor ( &stepper6, 400, STEPPER6_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
