\mainpage Main Page

---
# Stepper 10 click

> Stepper 10 Click is a two-phase bipolar stepping motor driver capable of controlling one stepper motor with PWM constant current drive. Click's featured chip TB67S128FTG, from Toshiba Semiconductor, fabricated with BiCD process with an output rating of 50V/5A and a built-in decoder can supply the motor with voltage of up to 44V. Toshiba's innovative technology process results in low-power consumption with low on-resistance (0.25Ω) on the integrated MOSFET output stage. The stepper motor can be driven in both directions from full step to 1/128 micro-steps.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/stepper-10-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2024.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Stepper 10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper 10 Click driver.

#### Standard key functions :

- `stepper10_cfg_setup` Config Object Initialization function.
```c
void stepper10_cfg_setup ( stepper10_cfg_t *cfg );
```

- `stepper10_init` Initialization function.
```c
err_t stepper10_init ( stepper10_t *ctx, stepper10_cfg_t *cfg );
```

- `stepper10_default_cfg` Click Default Configuration function.
```c
err_t stepper10_default_cfg ( stepper10_t *ctx );
```

#### Example key functions :

- `stepper10_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
void stepper10_set_direction ( stepper10_t *ctx, uint8_t dir );
```

- `stepper10_set_step_mode` This function sets the step mode resolution settings.
```c
err_t stepper10_set_step_mode ( stepper10_t *ctx, uint8_t mode );
```

- `stepper10_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
err_t stepper10_drive_motor ( stepper10_t *ctx, uint32_t steps, uint8_t speed );
```

## Example Description

> This example demonstrates the use of the Stepper 10 click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper10_cfg_t stepper10_cfg;  /**< Click config object. */

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
    stepper10_cfg_setup( &stepper10_cfg );
    STEPPER10_MAP_MIKROBUS( stepper10_cfg, MIKROBUS_1 );
    err_t init_flag = stepper10_init( &stepper10, &stepper10_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER10_ERROR == stepper10_default_cfg ( &stepper10 ) )
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
    stepper10_set_direction ( &stepper10, STEPPER10_DIR_CW );
    stepper10_set_step_mode ( &stepper10, STEPPER10_MODE_FULL_STEP );
    stepper10_drive_motor ( &stepper10, 200, STEPPER10_SPEED_SLOW );
    Delay_ms ( 2000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper10_set_direction ( &stepper10, STEPPER10_DIR_CCW );
    stepper10_set_step_mode ( &stepper10, STEPPER10_MODE_HALF_STEP );
    stepper10_drive_motor ( &stepper10, 200, STEPPER10_SPEED_MEDIUM );
    Delay_ms ( 2000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    stepper10_set_direction ( &stepper10, STEPPER10_DIR_CCW );
    stepper10_set_step_mode ( &stepper10, STEPPER10_MODE_QUARTER_STEP );
    stepper10_drive_motor ( &stepper10, 400, STEPPER10_SPEED_FAST );
    Delay_ms ( 2000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
