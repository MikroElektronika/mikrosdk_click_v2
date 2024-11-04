\mainpage Main Page

---
# Stepper 4 Click

> Stepper 4 Click is a very versatile bipolar stepping motor driver. It features TB67S269FTG IC, fabricated with the BiCD process, allowing the Click board™ to handle significant voltage and current levels up to 35V and 1.2A. This IC has the integrated translator section, used to simplify the control: using simple step control inputs from the host MCU, the stepper motor can be driven in both directions, with the predetermined step sizes from the full step, up to 1/32 step.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepper4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/stepper-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : GPIO type


# Software Support

We provide a library for the Stepper 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Stepper 4 Click driver.

#### Standard key functions :

- `stepper4_cfg_setup` Config Object Initialization function.
```c
void stepper4_cfg_setup ( stepper4_cfg_t *cfg );
```

- `stepper4_init` Initialization function.
```c
err_t stepper4_init ( stepper4_t *ctx, stepper4_cfg_t *cfg );
```

- `stepper4_default_cfg` Click Default Configuration function.
```c
void stepper4_default_cfg ( stepper4_t *ctx );
```

#### Example key functions :

- `stepper4_set_direction` This function sets the motor direction by setting the DIR pin logic state.
```c
void stepper4_set_direction ( stepper4_t *ctx, uint8_t dir );
```

- `stepper4_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void stepper4_drive_motor ( stepper4_t *ctx, uint32_t steps, uint8_t speed );
```

- `stepper4_reset_device` This function resets the device by toggling the RST pin.
```c
void stepper4_reset_device ( stepper4_t *ctx );
```

## Example Description

> This example demonstrates the use of the Stepper 4 Click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper4_cfg_t stepper4_cfg;  /**< Click config object. */

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
    stepper4_cfg_setup( &stepper4_cfg );
    STEPPER4_MAP_MIKROBUS( stepper4_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == stepper4_init( &stepper4, &stepper4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    stepper4_default_cfg ( &stepper4 );
    
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
    stepper4_set_direction ( &stepper4, STEPPER4_DIR_CW );
    stepper4_drive_motor ( &stepper4, 200, STEPPER4_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf ( &logger, " Move 100 steps counter-clockwise \r\n\n" );
    stepper4_set_direction ( &stepper4, STEPPER4_DIR_CCW );
    stepper4_drive_motor ( &stepper4, 100, STEPPER4_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Stepper4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
