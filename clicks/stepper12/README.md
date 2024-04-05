\mainpage Main Page

---
# Stepper 12 click

> Stepper 12 Click is a compact add-on board that contains a bipolar stepper motor driver. This board features the TB67S549FTG, a two-phase bipolar stepping motor driver from Toshiba Semiconductor. It supports a PWM constant-current control drive without a current sense resistor for motor-current detection and allows full-step to 1/32 steps resolution for less motor noise and smoother control. It has a wide operating voltage range of 4.5V to 34V with an output current capacity of 1.2A maximum and several anomaly detection indicators.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/stepper-12-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Stepper 12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper 12 Click driver.

#### Standard key functions :

- `stepper12_cfg_setup` Config Object Initialization function.
```c
void stepper12_cfg_setup ( stepper12_cfg_t *cfg );
```

- `stepper12_init` Initialization function.
```c
err_t stepper12_init ( stepper12_t *ctx, stepper12_cfg_t *cfg );
```

- `stepper12_default_cfg` Click Default Configuration function.
```c
err_t stepper12_default_cfg ( stepper12_t *ctx );
```

#### Example key functions :

- `stepper12_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
void stepper12_set_direction ( stepper12_t *ctx, uint8_t dir );
```

- `stepper12_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void stepper12_drive_motor ( stepper12_t *ctx, uint32_t steps, uint8_t speed );
```

- `stepper12_set_step_mode` This function sets the step mode resolution settings.
```c
err_t stepper12_set_step_mode ( stepper12_t *ctx, uint8_t mode );
```

## Example Description

> This example demonstrates the use of the Stepper 12 click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper12_cfg_t stepper12_cfg;  /**< Click config object. */

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
    stepper12_cfg_setup( &stepper12_cfg );
    STEPPER12_MAP_MIKROBUS( stepper12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper12_init( &stepper12, &stepper12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER12_ERROR == stepper12_default_cfg ( &stepper12 ) )
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
    stepper12_set_step_mode ( &stepper12, STEPPER12_MODE_FULL_STEP );
    stepper12_set_direction ( &stepper12, STEPPER12_DIR_CW );
    stepper12_drive_motor ( &stepper12, 200, STEPPER12_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf ( &logger, " Move 400 quarter steps counter-clockwise \r\n\n" );
    stepper12_set_step_mode ( &stepper12, STEPPER12_MODE_QUARTER_STEP );
    stepper12_set_direction ( &stepper12, STEPPER12_DIR_CCW );
    stepper12_drive_motor ( &stepper12, 400, STEPPER12_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
