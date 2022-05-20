
---
# Multi Stepper TB67S109 click

> Multi Stepper Click is a compact add-on board that contains a bipolar stepper motor driver. This board features the TB67S109AFTG, CLOCK-in controlled bipolar stepping motor driver from Toshiba Semiconductor. It supports a PWM constant-current control drive and allows from full-step up to 1/32 steps resolution for less motor noise and smoother control. It has a wide operating voltage range of 10V to 47V with an output current capacity of 2.8A in addition to several built-in error detection circuits.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/multisteppertb67s109_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/multi-stepper-click-tb67s109)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Multi Stepper TB67S109 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Multi Stepper TB67S109 Click driver.

#### Standard key functions :

- `multisteppertb67s109_cfg_setup` Config Object Initialization function.
```c
void multisteppertb67s109_cfg_setup ( multisteppertb67s109_cfg_t *cfg );
```

- `multisteppertb67s109_init` Initialization function.
```c
err_t multisteppertb67s109_init ( multisteppertb67s109_t *ctx, multisteppertb67s109_cfg_t *cfg );
```

- `multisteppertb67s109_default_cfg` Click Default Configuration function.
```c
err_t multisteppertb67s109_default_cfg ( multisteppertb67s109_t *ctx );
```

#### Example key functions :

- `multisteppertb67s109_set_step_mode` This function sets the step mode resolution settings.
```c
err_t multisteppertb67s109_set_step_mode ( multisteppertb67s109_t *ctx, uint8_t mode );
```

- `multisteppertb67s109_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void multisteppertb67s109_drive_motor ( multisteppertb67s109_t *ctx, uint32_t steps, uint8_t speed );
```

- `multisteppertb67s109_set_direction` This function sets the motor direction by setting the AN pin logic state.
```c
void multisteppertb67s109_set_direction ( multisteppertb67s109_t *ctx, uint8_t dir );
```

## Example Description

> This example demonstrates the use of the Multi Stepper TB67S109 click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    multisteppertb67s109_cfg_t multisteppertb67s109_cfg;  /**< Click config object. */

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
    multisteppertb67s109_cfg_setup( &multisteppertb67s109_cfg );
    MULTISTEPPERTB67S109_MAP_MIKROBUS( multisteppertb67s109_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == multisteppertb67s109_init( &multisteppertb67s109, &multisteppertb67s109_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MULTISTEPPERTB67S109_ERROR == multisteppertb67s109_default_cfg ( &multisteppertb67s109 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor clockwise for 200 steps and then counter-clockiwse for 100 steps with 2 seconds delay before changing the direction.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf ( &logger, " Move 200 steps clockwise \r\n\n" );
    multisteppertb67s109_set_direction ( &multisteppertb67s109, MULTISTEPPERTB67S109_DIR_CW );
    multisteppertb67s109_drive_motor ( &multisteppertb67s109, 200, MULTISTEPPERTB67S109_SPEED_FAST );
    Delay_ms ( 2000 );
    
    log_printf ( &logger, " Move 100 steps counter-clockwise \r\n\n" );
    multisteppertb67s109_set_direction ( &multisteppertb67s109, MULTISTEPPERTB67S109_DIR_CCW );
    multisteppertb67s109_drive_motor ( &multisteppertb67s109, 100, MULTISTEPPERTB67S109_SPEED_FAST );
    Delay_ms ( 2000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MultiStepperTB67S109

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
