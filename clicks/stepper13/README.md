\mainpage Main Page

---
# Stepper 13 click

> Stepper 13 Click is a bipolar step motor driver. It features an H-bridge bipolar step motor driver, which supports full-, half-, quarter-, or eighth-step modes. Stepper 13 click also carries a port expander so that the communication can be done with a minimal number of pins, through the mikroBUS™ I2C bus.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper13_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/stepper-13-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Stepper 13 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper 13 Click driver.

#### Standard key functions :

- `stepper13_cfg_setup` Config Object Initialization function.
```c
void stepper13_cfg_setup ( stepper13_cfg_t *cfg );
```

- `stepper13_init` Initialization function.
```c
err_t stepper13_init ( stepper13_t *ctx, stepper13_cfg_t *cfg );
```

- `stepper13_default_cfg` Click Default Configuration function.
```c
err_t stepper13_default_cfg ( stepper13_t *ctx );
```

#### Example key functions :

- `stepper13_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
err_t stepper13_set_direction ( stepper13_t *ctx, uint8_t dir );
```

- `stepper13_set_step_mode` This function sets the step mode resolution settings.
```c
err_t stepper13_set_step_mode ( stepper13_t *ctx, uint8_t mode );
```

- `stepper13_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
err_t stepper13_drive_motor ( stepper13_t *ctx, uint32_t steps, uint8_t speed );
```

## Example Description

> This example demonstrates the use of the Stepper 13 click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper13_cfg_t stepper13_cfg;  /**< Click config object. */

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
    stepper13_cfg_setup( &stepper13_cfg );
    STEPPER13_MAP_MIKROBUS( stepper13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper13_init( &stepper13, &stepper13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER13_ERROR == stepper13_default_cfg ( &stepper13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor clockwise for 200 full steps and then counter-clockwise for 200 half
steps and 400 quarter steps with 2 seconds delay on driving mode change. All data is
being logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    stepper13_set_direction ( &stepper13, STEPPER13_DIR_CW );
    stepper13_set_step_mode ( &stepper13, STEPPER13_MODE_FULL_STEP );
    stepper13_drive_motor ( &stepper13, 200, STEPPER13_SPEED_SLOW );
    Delay_ms ( 2000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper13_set_direction ( &stepper13, STEPPER13_DIR_CCW );
    stepper13_set_step_mode ( &stepper13, STEPPER13_MODE_HALF_STEP );
    stepper13_drive_motor ( &stepper13, 200, STEPPER13_SPEED_MEDIUM );
    Delay_ms ( 2000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    stepper13_set_direction ( &stepper13, STEPPER13_DIR_CCW );
    stepper13_set_step_mode ( &stepper13, STEPPER13_MODE_QUARTER_STEP );
    stepper13_drive_motor ( &stepper13, 400, STEPPER13_SPEED_FAST );
    Delay_ms ( 2000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper13

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
