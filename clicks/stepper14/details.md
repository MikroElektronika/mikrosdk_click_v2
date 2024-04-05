
---
# Stepper 14 click

> The Stepper 14 Click is a Click board™ that features the DRV8847PWPR, a step motor driver, from Texas Instruments. This Click board™ provides a bipolar step motor controle, It features an H-bridge bipolar step motor driver, which supports full-, half-, quarter-, or eighth-step modes. This click board™ also carries a port expander so that the communication can be done with a minimal number of pins, through the mikroBUS™ I2C bus.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper14_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/stepper-14-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Stepper 14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper 14 Click driver.

#### Standard key functions :

- `stepper14_cfg_setup` Config Object Initialization function.
```c
void stepper14_cfg_setup ( stepper14_cfg_t *cfg );
```

- `stepper14_init` Initialization function.
```c
err_t stepper14_init ( stepper14_t *ctx, stepper14_cfg_t *cfg );
```

- `stepper14_default_cfg` Click Default Configuration function.
```c
err_t stepper14_default_cfg ( stepper14_t *ctx );
```

#### Example key functions :

- `stepper14_set_direction` This function sets the motor direction to clockwise or counter-clockwise in ctx->direction.
```c
void stepper14_set_direction ( stepper14_t *ctx, uint8_t dir );
```

- `stepper14_set_step_mode` This function sets the step mode resolution settings in ctx->step_mode.
```c
void stepper14_set_step_mode ( stepper14_t *ctx, uint8_t mode );
```

- `stepper14_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
err_t stepper14_drive_motor ( stepper14_t *ctx, uint32_t steps, uint8_t speed );
```

## Example Description

> This example demonstrates the use of the Stepper 14 click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper14_cfg_t stepper14_cfg;  /**< Click config object. */

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
    stepper14_cfg_setup( &stepper14_cfg );
    STEPPER14_MAP_MIKROBUS( stepper14_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper14_init( &stepper14, &stepper14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER14_ERROR == stepper14_default_cfg ( &stepper14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor clockwise for 200 full steps and then counter-clockwise for 400 half
steps with a 2 seconds delay on driving mode change. All data is being logged on the
USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: medium\r\n\n" );
    stepper14_set_direction ( &stepper14, STEPPER14_DIR_CW );
    stepper14_set_step_mode ( &stepper14, STEPPER14_MODE_FULL_STEP );
    stepper14_drive_motor ( &stepper14, 200, STEPPER14_SPEED_MEDIUM );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 half steps counter-clockwise, speed: fast\r\n\n" );
    stepper14_set_direction ( &stepper14, STEPPER14_DIR_CCW );
    stepper14_set_step_mode ( &stepper14, STEPPER14_MODE_HALF_STEP );
    stepper14_drive_motor ( &stepper14, 400, STEPPER14_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
