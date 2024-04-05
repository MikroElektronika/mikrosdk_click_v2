\mainpage Main Page

---
# Multi Stepper TB62262 click

> Multi Stepper Click is a compact add-on board that contains a bipolar stepper motor driver. This board features the TB62262FTG, CLOCK-in controlled bipolar stepping motor driver from Toshiba Semiconductor. It supports a PWM constant-current control drive and allows full-, half-, and quarter-step operation for less motor noise and smoother control. It has a wide operating voltage range of 10V to 38V with an output current capacity of 1.2A in addition to several built-in error detection circuits.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/multisteppertb62262_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/multi-stepper-click-tb62262)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Multi Stepper TB62262 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Multi Stepper TB62262 Click driver.

#### Standard key functions :

- `multisteppertb62262_cfg_setup` Config Object Initialization function.
```c
void multisteppertb62262_cfg_setup ( multisteppertb62262_cfg_t *cfg );
```

- `multisteppertb62262_init` Initialization function.
```c
err_t multisteppertb62262_init ( multisteppertb62262_t *ctx, multisteppertb62262_cfg_t *cfg );
```

- `multisteppertb62262_default_cfg` Click Default Configuration function.
```c
err_t multisteppertb62262_default_cfg ( multisteppertb62262_t *ctx );
```

#### Example key functions :

- `multisteppertb62262_set_step_mode` This function sets the step mode resolution settings.
```c
err_t multisteppertb62262_set_step_mode ( multisteppertb62262_t *ctx, uint8_t mode );
```

- `multisteppertb62262_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void multisteppertb62262_drive_motor ( multisteppertb62262_t *ctx, uint32_t steps, uint8_t speed );
```

- `multisteppertb62262_set_direction` This function sets the motor direction by setting the AN pin logic state.
```c
void multisteppertb62262_set_direction ( multisteppertb62262_t *ctx, uint8_t dir );
```

## Example Description

> This example demonstrates the use of the Multi Stepper TB62262 click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    multisteppertb62262_cfg_t multisteppertb62262_cfg;  /**< Click config object. */

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
    multisteppertb62262_cfg_setup( &multisteppertb62262_cfg );
    MULTISTEPPERTB62262_MAP_MIKROBUS( multisteppertb62262_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == multisteppertb62262_init( &multisteppertb62262, &multisteppertb62262_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MULTISTEPPERTB62262_ERROR == multisteppertb62262_default_cfg ( &multisteppertb62262 ) )
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
    multisteppertb62262_set_direction ( &multisteppertb62262, MULTISTEPPERTB62262_DIR_CW );
    multisteppertb62262_drive_motor ( &multisteppertb62262, 200, MULTISTEPPERTB62262_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf ( &logger, " Move 100 steps counter-clockwise \r\n\n" );
    multisteppertb62262_set_direction ( &multisteppertb62262, MULTISTEPPERTB62262_DIR_CCW );
    multisteppertb62262_drive_motor ( &multisteppertb62262, 100, MULTISTEPPERTB62262_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MultiStepperTB62262

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
