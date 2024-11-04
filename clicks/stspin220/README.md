\mainpage Main Page

---
# STSPIN220 Click

> STSPIN220 Click is a stepper motor driver with the PWM current control and selectable microstepping up to 256 microsteps. It is based on the STSPIN220, a low voltage stepper motor driver from STSPIN2 series. It is optimized for battery-powered, low voltage motor driving applications, featuring the lowest standby current available on the market (max 80 nA). The STSPIN220 is a high-efficiency motor driver, featuring low ON resistance MOSFETs as the output stage, in a small 3x3mm QFN package. Its output stage implements the PWM current control with fixed OFF time, along with a full set of protection features. The device can be used with the step motor voltage ranging from 1.8V to 10V, and current up to 1.3A per bridge.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stspin220_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/stspin220-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2024.
- **Type**          : GPIO type


# Software Support

We provide a library for the STSPIN220 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for STSPIN220 Click driver.

#### Standard key functions :

- `stspin220_cfg_setup` Config Object Initialization function.
```c
void stspin220_cfg_setup ( stspin220_cfg_t *cfg );
```

- `stspin220_init` Initialization function.
```c
err_t stspin220_init ( stspin220_t *ctx, stspin220_cfg_t *cfg );
```

- `stspin220_default_cfg` Click Default Configuration function.
```c
void stspin220_default_cfg ( stspin220_t *ctx );
```

#### Example key functions :

- `stspin220_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
void stspin220_set_direction ( stspin220_t *ctx, uint8_t dir );
```

- `stspin220_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void stspin220_drive_motor ( stspin220_t *ctx, uint32_t steps, uint8_t speed );
```

- `stspin220_reset_device` This function resets the device by toggling the RST pin.
```c
void stspin220_reset_device ( stspin220_t *ctx );
```

## Example Description

> This example demonstrates the use of the STSPIN220 Click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stspin220_cfg_t stspin220_cfg;  /**< Click config object. */

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
    stspin220_cfg_setup( &stspin220_cfg );
    STSPIN220_MAP_MIKROBUS( stspin220_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == stspin220_init( &stspin220, &stspin220_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    stspin220_default_cfg ( &stspin220 );
    
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
    stspin220_set_direction ( &stspin220, STSPIN220_DIR_CW );
    stspin220_drive_motor ( &stspin220, 200, STSPIN220_SPEED_SLOW );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf ( &logger, " Move 200 steps counter-clockwise, speed: fast\r\n\n" );
    stspin220_set_direction ( &stspin220, STSPIN220_DIR_CCW );
    stspin220_drive_motor ( &stspin220, 200, STSPIN220_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.STSPIN220

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
