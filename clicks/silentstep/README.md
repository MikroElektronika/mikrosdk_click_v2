\mainpage Main Page

---
# Silent Step Click

> Silent Step Click is the complete integrated bipolar step motor driver solution, rich with many features that allow extremely smooth and silent operation of the connected motor while being able to provide up to 2.5A peak motor current and withstand up to 46V supply voltage. The specialized TMC5130 IC driver from Trinamic Company far exceeds the capabilities of similar step motor drivers that are commonly used.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/silentstep_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/silent-step-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : SPI type


# Software Support

We provide a library for the Silent Step Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Silent Step Click driver.

#### Standard key functions :

- `silentstep_cfg_setup` Config Object Initialization function.
```c
void silentstep_cfg_setup ( silentstep_cfg_t *cfg );
```

- `silentstep_init` Initialization function.
```c
err_t silentstep_init ( silentstep_t *ctx, silentstep_cfg_t *cfg );
```

- `silentstep_default_cfg` Click Default Configuration function.
```c
err_t silentstep_default_cfg ( silentstep_t *ctx );
```

#### Example key functions :

- `silentstep_set_step_res` This function sets the microstep resolution bits in CHOPCONF register.
```c
err_t silentstep_set_step_res ( silentstep_t *ctx, uint8_t mres );
```

- `silentstep_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
void silentstep_set_direction ( silentstep_t *ctx, uint8_t dir );
```

- `silentstep_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void silentstep_drive_motor ( silentstep_t *ctx, uint32_t steps, uint8_t speed );
```

## Example Description

> This example demonstrates the use of the Silent Step Click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    silentstep_cfg_t silentstep_cfg;  /**< Click config object. */

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
    silentstep_cfg_setup( &silentstep_cfg );
    SILENTSTEP_MAP_MIKROBUS( silentstep_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == silentstep_init( &silentstep, &silentstep_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SILENTSTEP_ERROR == silentstep_default_cfg ( &silentstep ) )
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
    silentstep_set_direction ( &silentstep, SILENTSTEP_DIR_CW );
    silentstep_set_step_res ( &silentstep, SILENTSTEP_MRES_FULLSTEP );
    silentstep_drive_motor ( &silentstep, 200, SILENTSTEP_SPEED_SLOW );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    silentstep_set_direction ( &silentstep, SILENTSTEP_DIR_CCW );
    silentstep_set_step_res ( &silentstep, SILENTSTEP_MRES_2 );
    silentstep_drive_motor ( &silentstep, 200, SILENTSTEP_SPEED_MEDIUM );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    silentstep_set_direction ( &silentstep, SILENTSTEP_DIR_CCW );
    silentstep_set_step_res ( &silentstep, SILENTSTEP_MRES_4 );
    silentstep_drive_motor ( &silentstep, 400, SILENTSTEP_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SilentStep

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
