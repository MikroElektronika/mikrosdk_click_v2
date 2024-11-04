\mainpage Main Page

---
# STSPIN820 Click

> STSPIN820 Click is a stepper motor driver with the PWM current control, selectable microstepping up to 256 microsteps, and a wide voltage range. It is based on the STSPIN820, a stepper motor driver from STSPIN8 series. Designed to be a bullet-proof solution for the new wave of demanding industrial applications, it integrates two full-bridges with low ON resistance, the control logic, and a full set of protection features, in a small 4x4mm QFN package. Its output stage implements the PWM current control with the fixed OFF time. The device can be used with the step motor voltage ranging from 7V up to 45V, and current up to 1.5A per bridge.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stspin820_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/stspin820-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2024.
- **Type**          : GPIO type


# Software Support

We provide a library for the STSPIN820 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for STSPIN820 Click driver.

#### Standard key functions :

- `stspin820_cfg_setup` Config Object Initialization function.
```c
void stspin820_cfg_setup ( stspin820_cfg_t *cfg );
```

- `stspin820_init` Initialization function.
```c
err_t stspin820_init ( stspin820_t *ctx, stspin820_cfg_t *cfg );
```

- `stspin820_default_cfg` Click Default Configuration function.
```c
void stspin820_default_cfg ( stspin820_t *ctx );
```

#### Example key functions :

- `stspin820_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
void stspin820_set_direction ( stspin820_t *ctx, uint8_t dir );
```

- `stspin820_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void stspin820_drive_motor ( stspin820_t *ctx, uint32_t steps, uint8_t speed );
```

- `stspin820_reset_device` This function resets the device by toggling the RST pin.
```c
void stspin820_reset_device ( stspin820_t *ctx );
```

## Example Description

> This example demonstrates the use of the STSPIN820 Click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stspin820_cfg_t stspin820_cfg;  /**< Click config object. */

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
    stspin820_cfg_setup( &stspin820_cfg );
    STSPIN820_MAP_MIKROBUS( stspin820_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == stspin820_init( &stspin820, &stspin820_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    stspin820_default_cfg ( &stspin820 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor clockwise for 200 steps and then counter-clockwise with a 2 seconds
delay delay on driving mode change. All data is being logged on the USB UART where
you can track the program flow.

```c
void application_task ( void )
{
    log_printf ( &logger, " Move 200 steps clockwise, speed: slow\r\n\n" );
    stspin820_set_direction ( &stspin820, STSPIN820_DIR_CW );
    stspin820_drive_motor ( &stspin820, 200, STSPIN820_SPEED_SLOW );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf ( &logger, " Move 200 steps counter-clockwise, speed: fast\r\n\n" );
    stspin820_set_direction ( &stspin820, STSPIN820_DIR_CCW );
    stspin820_drive_motor ( &stspin820, 200, STSPIN820_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.STSPIN820

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
