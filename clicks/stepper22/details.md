
---
# Stepper 22 click

> Stepper 22 Click is a compact add-on board designed for precise motion control of bipolar stepper motors and brushed DC motors. This board features the DRV8711, a bipolar stepper motor gate driver from Texas Instruments, which uses external N-channel MOSFETs to drive motors with up to 5A of output current. The board features a wide range of microstepping options from full-step to 1/256-step, adaptive blanking time, and various current decay modes, ensuring smooth and accurate motor operation. Control is achieved via a standard SPI interface and STEP/DIR inputs, with additional management through an onboard I2C-configurable GPIO expander.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper22_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/stepper-22-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2024.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Stepper 22 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper 22 Click driver.

#### Standard key functions :

- `stepper22_cfg_setup` Config Object Initialization function.
```c
void stepper22_cfg_setup ( stepper22_cfg_t *cfg );
```

- `stepper22_init` Initialization function.
```c
err_t stepper22_init ( stepper22_t *ctx, stepper22_cfg_t *cfg );
```

- `stepper22_default_cfg` Click Default Configuration function.
```c
err_t stepper22_default_cfg ( stepper22_t *ctx );
```

#### Example key functions :

- `stepper22_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
err_t stepper22_set_direction ( stepper22_t *ctx, uint8_t dir );
```

- `stepper22_set_step_mode` This function sets the step mode resolution settings.
```c
err_t stepper22_set_step_mode ( stepper22_t *ctx, uint8_t mode );
```

- `stepper22_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
err_t stepper22_drive_motor ( stepper22_t *ctx, uint32_t steps, uint8_t speed );
```

## Example Description

> This example demonstrates the use of the Stepper 22 click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper22_cfg_t stepper22_cfg;  /**< Click config object. */

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
    stepper22_cfg_setup( &stepper22_cfg );
    STEPPER22_MAP_MIKROBUS( stepper22_cfg, MIKROBUS_1 );
    err_t init_flag = stepper22_init( &stepper22, &stepper22_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER22_ERROR == stepper22_default_cfg ( &stepper22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor clockwise for 200 full steps and then counter-clockiwse for 200 half
steps and 400 quarter steps with a 1 second delay on driving mode change. All data is
being logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    stepper22_set_direction ( &stepper22, STEPPER22_DIR_CW );
    stepper22_set_step_mode ( &stepper22, STEPPER22_MODE_FULL_STEP );
    stepper22_drive_motor ( &stepper22, 200, STEPPER22_SPEED_SLOW );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper22_set_direction ( &stepper22, STEPPER22_DIR_CCW );
    stepper22_set_step_mode ( &stepper22, STEPPER22_MODE_HALF_STEP );
    stepper22_drive_motor ( &stepper22, 200, STEPPER22_SPEED_MEDIUM );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    stepper22_set_direction ( &stepper22, STEPPER22_DIR_CCW );
    stepper22_set_step_mode ( &stepper22, STEPPER22_MODE_QUARTER_STEP );
    stepper22_drive_motor ( &stepper22, 400, STEPPER22_SPEED_FAST );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper22

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
