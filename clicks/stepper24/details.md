
---
# Stepper 24 Click

> Stepper 24 Click is a compact add-on board designed to drive small stepping motors in consumer electronics and industrial equipment applications. This board features the TB67S589FTG, a BiCD constant-current 2-phase bipolar stepping motor driver IC from Toshiba Semiconductor. Key features include a PWM chopper-type 2-phase bipolar drive system, high withstand voltage of up to 34V operating, and a maximum operating current of 2.7A per phase. The board also integrates safety mechanisms such as over-temperature, over-current, and low-supply voltage detection. Additional control is provided by the PCA9555A port expander via I2C, enabling functions like decay and torque modes, step resolution settings, and many more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper24_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/stepper-24-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Stepper 24 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper 24 Click driver.

#### Standard key functions :

- `stepper24_cfg_setup` Config Object Initialization function.
```c
void stepper24_cfg_setup ( stepper24_cfg_t *cfg );
```

- `stepper24_init` Initialization function.
```c
err_t stepper24_init ( stepper24_t *ctx, stepper24_cfg_t *cfg );
```

- `stepper24_default_cfg` Click Default Configuration function.
```c
err_t stepper24_default_cfg ( stepper24_t *ctx );
```

#### Example key functions :

- `stepper24_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
void stepper24_set_direction ( stepper24_t *ctx, uint8_t dir );
```

- `stepper24_set_step_mode` This function sets the step mode resolution settings.
```c
err_t stepper24_set_step_mode ( stepper24_t *ctx, uint8_t mode );
```

- `stepper24_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void stepper24_drive_motor ( stepper24_t *ctx, uint32_t steps, uint8_t speed );
```

## Example Description

> This example demonstrates the use of the Stepper 24 Click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper24_cfg_t stepper24_cfg;  /**< Click config object. */

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
    stepper24_cfg_setup( &stepper24_cfg );
    STEPPER24_MAP_MIKROBUS( stepper24_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper24_init( &stepper24, &stepper24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER24_ERROR == stepper24_default_cfg ( &stepper24 ) )
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
    stepper24_set_direction ( &stepper24, STEPPER24_DIR_CW );
    stepper24_set_step_mode ( &stepper24, STEPPER24_MODE_FULL_STEP );
    stepper24_drive_motor ( &stepper24, 200, STEPPER24_SPEED_SLOW );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper24_set_direction ( &stepper24, STEPPER24_DIR_CCW );
    stepper24_set_step_mode ( &stepper24, STEPPER24_MODE_HALF_STEP_TYPE_A );
    stepper24_drive_motor ( &stepper24, 200, STEPPER24_SPEED_MEDIUM );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    stepper24_set_direction ( &stepper24, STEPPER24_DIR_CCW );
    stepper24_set_step_mode ( &stepper24, STEPPER24_MODE_QUARTER_STEP );
    stepper24_drive_motor ( &stepper24, 400, STEPPER24_SPEED_FAST );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper24

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
