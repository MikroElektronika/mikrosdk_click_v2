\mainpage Main Page

---
# Stepper 21 click

> Stepper 21 Click is a compact add-on board that contains a bipolar stepper motor driver. This board features the DRV8825, a stepper motor controller integral circuit from Texas Instruments. It is a PWM micro-stepping stepper motor driver with up to 1/32 micro-stepping resolution and a built-in micro-stepper indexer. The driver has two H-bridge drivers and is intended to drive a bipolar stepper motor in a voltage supply operating range of 8.2V up to 45V.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper21_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/stepper-21-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Stepper 21 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper 21 Click driver.

#### Standard key functions :

- `stepper21_cfg_setup` Config Object Initialization function.
```c
void stepper21_cfg_setup ( stepper21_cfg_t *cfg );
```

- `stepper21_init` Initialization function.
```c
err_t stepper21_init ( stepper21_t *ctx, stepper21_cfg_t *cfg );
```

- `stepper21_default_cfg` Click Default Configuration function.
```c
err_t stepper21_default_cfg ( stepper21_t *ctx );
```

#### Example key functions :

- `stepper21_set_step_mode` This function sets the step mode resolution settings.
```c
err_t stepper21_set_step_mode ( stepper21_t *ctx, uint8_t mode );
```

- `stepper21_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
void stepper21_set_direction ( stepper21_t *ctx, uint8_t dir );
```

- `stepper21_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void stepper21_drive_motor ( stepper21_t *ctx, uint32_t steps, uint8_t speed );
```

## Example Description

> This example demonstrates the use of the Stepper 21 click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper21_cfg_t stepper21_cfg;  /**< Click config object. */

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
    stepper21_cfg_setup( &stepper21_cfg );
    STEPPER21_MAP_MIKROBUS( stepper21_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper21_init( &stepper21, &stepper21_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER21_ERROR == stepper21_default_cfg ( &stepper21 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor clockwise for 200 full steps and then counter-clockiwse for 400 quarter
steps with 2 seconds delay before changing the direction. All data is being logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf ( &logger, " Move 200 full steps clockwise \r\n\n" );
    stepper21_set_step_mode ( &stepper21, STEPPER21_MODE_FULL_STEP );
    stepper21_set_direction ( &stepper21, STEPPER21_DIR_CW );
    stepper21_drive_motor ( &stepper21, 200, STEPPER21_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf ( &logger, " Move 400 quarter steps counter-clockwise \r\n\n" );
    stepper21_set_step_mode ( &stepper21, STEPPER21_MODE_QUARTER_STEP );
    stepper21_set_direction ( &stepper21, STEPPER21_DIR_CCW );
    stepper21_drive_motor ( &stepper21, 400, STEPPER21_SPEED_VERY_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper21

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
