\mainpage Main Page

---
# Stepper 20 Click

> Stepper 20 Click is a compact add-on board that contains a bipolar stepper motor driver. This board features the TB67S580FNG, a two-phase bipolar stepping motor driver from Toshiba Semiconductor. Fabricated with the BiCD process, it supports a PWM constant-current control drive and steps resolution from full to 1/32 for less motor noise and smoother control. It has a wide operating voltage range of 8.2V to 44V with a maximum output current capacity of 1.28A, decay modes selection function, protection, and several anomaly detection indicators.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper20_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/stepper-20-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Stepper 20 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper 20 Click driver.

#### Standard key functions :

- `stepper20_cfg_setup` Config Object Initialization function.
```c
void stepper20_cfg_setup ( stepper20_cfg_t *cfg );
```

- `stepper20_init` Initialization function.
```c
err_t stepper20_init ( stepper20_t *ctx, stepper20_cfg_t *cfg );
```

- `stepper20_default_cfg` Click Default Configuration function.
```c
err_t stepper20_default_cfg ( stepper20_t *ctx );
```

#### Example key functions :

- `stepper20_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
void stepper20_set_direction ( stepper20_t *ctx, uint8_t dir );
```

- `stepper20_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void stepper20_drive_motor ( stepper20_t *ctx, uint32_t steps, uint8_t speed );
```

- `stepper20_set_step_mode` This function sets the step mode resolution settings.
```c
err_t stepper20_set_step_mode ( stepper20_t *ctx, uint8_t mode );
```

## Example Description

> This example demonstrates the use of the Stepper 20 Click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper20_cfg_t stepper20_cfg;  /**< Click config object. */

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
    stepper20_cfg_setup( &stepper20_cfg );
    STEPPER20_MAP_MIKROBUS( stepper20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper20_init( &stepper20, &stepper20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER20_ERROR == stepper20_default_cfg ( &stepper20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor clockwise for 200 full steps and then counter-clockiwse for 400 quarter
steps with 2 seconds delay before changing the direction. All data is being logged on
the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf ( &logger, " Move 200 full steps clockwise \r\n\n" );
    stepper20_set_step_mode ( &stepper20, STEPPER20_MODE_FULL_STEP );
    stepper20_set_direction ( &stepper20, STEPPER20_DIR_CW );
    stepper20_drive_motor ( &stepper20, 200, STEPPER20_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf ( &logger, " Move 400 quarter steps counter-clockwise \r\n\n" );
    stepper20_set_step_mode ( &stepper20, STEPPER20_MODE_QUARTER_STEP );
    stepper20_set_direction ( &stepper20, STEPPER20_DIR_CCW );
    stepper20_drive_motor ( &stepper20, 400, STEPPER20_SPEED_VERY_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper20

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
