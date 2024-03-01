\mainpage Main Page

---
# Stepper 7 click

> Stepper 7 click is a bipolar step motor driver. It features an H-bridge bipolar step motor driver, which supports full and half step control modes. Stepper 7 click also carries a port expander so that the communication can be done with a minimal number of pins, through the mikroBUS™ SPI bus.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/stepper-7-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : SPI type


# Software Support

We provide a library for the Stepper 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper 7 Click driver.

#### Standard key functions :

- `stepper7_cfg_setup` Config Object Initialization function.
```c
void stepper7_cfg_setup ( stepper7_cfg_t *cfg );
```

- `stepper7_init` Initialization function.
```c
err_t stepper7_init ( stepper7_t *ctx, stepper7_cfg_t *cfg );
```

- `stepper7_default_cfg` Click Default Configuration function.
```c
err_t stepper7_default_cfg ( stepper7_t *ctx );
```

#### Example key functions :

- `stepper7_set_direction` This function sets the motor direction to clockwise or counter-clockwise in ctx->direction.
```c
void stepper7_set_direction ( stepper7_t *ctx, uint8_t dir );
```

- `stepper7_set_step_mode` This function sets the step mode resolution settings in ctx->step_mode.
```c
void stepper7_set_step_mode ( stepper7_t *ctx, uint8_t mode );
```

- `stepper7_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
err_t stepper7_drive_motor ( stepper7_t *ctx, uint32_t steps, uint8_t speed );
```

## Example Description

> This example demonstrates the use of the Stepper 7 click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper7_cfg_t stepper7_cfg;  /**< Click config object. */

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
    stepper7_cfg_setup( &stepper7_cfg );
    STEPPER7_MAP_MIKROBUS( stepper7_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == stepper7_init( &stepper7, &stepper7_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER7_ERROR == stepper7_default_cfg ( &stepper7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor clockwise for 200 full steps and then counter-clockiwse for 200 half
steps and 800 1/8th steps with 2 seconds delay on driving mode change. All data is
being logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    stepper7_set_direction ( &stepper7, STEPPER7_DIR_CW );
    stepper7_set_step_mode ( &stepper7, STEPPER7_MODE_FULL_STEP );
    stepper7_drive_motor ( &stepper7, 200, STEPPER7_SPEED_SLOW );
    Delay_ms ( 2000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper7_set_direction ( &stepper7, STEPPER7_DIR_CCW );
    stepper7_set_step_mode ( &stepper7, STEPPER7_MODE_HALF_STEP );
    stepper7_drive_motor ( &stepper7, 200, STEPPER7_SPEED_MEDIUM );
    Delay_ms ( 2000 );

    log_printf ( &logger, " Move 800 1/8th steps counter-clockwise, speed: fast\r\n\n" );
    stepper7_set_direction ( &stepper7, STEPPER7_DIR_CCW );
    stepper7_set_step_mode ( &stepper7, STEPPER7_MODE_1_OVER_8_STEP );
    stepper7_drive_motor ( &stepper7, 800, STEPPER7_SPEED_FAST );
    Delay_ms ( 2000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
