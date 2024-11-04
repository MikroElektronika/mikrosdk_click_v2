
---
# Silent Step 4 Click

> Silent Step 4 Click is a compact add-on board representing a completely integrated step motor driver solution. This board features the TMC2240, a smart integrated stepper driver from Analog Devices. The driver is based on a 256 micro-steps built-in indexer, two fully integrated H-Bridges, and non-dissipative integrated current sensing (ICS). The two H-Bridges can drive motors of up to 36V and 3A at max.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/silentstep4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/silent-step-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Silent Step 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Silent Step 4 Click driver.

#### Standard key functions :

- `silentstep4_cfg_setup` Config Object Initialization function.
```c
void silentstep4_cfg_setup ( silentstep4_cfg_t *cfg );
```

- `silentstep4_init` Initialization function.
```c
err_t silentstep4_init ( silentstep4_t *ctx, silentstep4_cfg_t *cfg );
```

- `silentstep4_default_cfg` Click Default Configuration function.
```c
err_t silentstep4_default_cfg ( silentstep4_t *ctx );
```

#### Example key functions :

- `silentstep4_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
void silentstep4_set_direction ( silentstep4_t *ctx, uint8_t dir );
```

- `silentstep4_set_step_res` This function sets the microstep resolution bits in CHOPCONF register.
```c
err_t silentstep4_set_step_res ( silentstep4_t *ctx, uint8_t mres );
```

- `silentstep4_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void silentstep4_drive_motor ( silentstep4_t *ctx, uint32_t steps, uint8_t speed );
```

## Example Description

> This example demonstrates the use of the Silent Step 4 Click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    silentstep4_cfg_t silentstep4_cfg;  /**< Click config object. */

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
    silentstep4_cfg_setup( &silentstep4_cfg );
    SILENTSTEP4_MAP_MIKROBUS( silentstep4_cfg, MIKROBUS_1 );
    err_t init_flag = silentstep4_init( &silentstep4, &silentstep4_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SILENTSTEP4_ERROR == silentstep4_default_cfg ( &silentstep4 ) )
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
    silentstep4_set_direction ( &silentstep4, SILENTSTEP4_DIR_CW );
    silentstep4_set_step_res ( &silentstep4, SILENTSTEP4_MRES_FULLSTEP );
    silentstep4_drive_motor ( &silentstep4, 200, SILENTSTEP4_SPEED_SLOW );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    silentstep4_set_direction ( &silentstep4, SILENTSTEP4_DIR_CCW );
    silentstep4_set_step_res ( &silentstep4, SILENTSTEP4_MRES_2 );
    silentstep4_drive_motor ( &silentstep4, 200, SILENTSTEP4_SPEED_MEDIUM );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    silentstep4_set_direction ( &silentstep4, SILENTSTEP4_DIR_CCW );
    silentstep4_set_step_res ( &silentstep4, SILENTSTEP4_MRES_4 );
    silentstep4_drive_motor ( &silentstep4, 400, SILENTSTEP4_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SilentStep4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
