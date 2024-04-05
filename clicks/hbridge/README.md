\mainpage Main Page

---
# H-Bridge click

> H-Bridge click is a high-efficiency dual H-bridge driver Click board™, capable of providing reasonably high current while driving the connected load with up to 7V. Since the used driver IC has two full H-bridge channels, this Click board™ is an ideal solution for driving smaller bipolar stepper motors. H-Bridge click provides driving in both directions, with an addition of the brake mode, and the high impedance mode (Hi-Z). Overshoot current suppression algorithm protects the output stages from being damaged if both high-side and low-side MOSFETs on a single H-bridge channel become conductive.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hbridge_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/h-bridge-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : GPIO type


# Software Support

We provide a library for the H-Bridge Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for H-Bridge Click driver.

#### Standard key functions :

- `hbridge_cfg_setup` Config Object Initialization function.
```c
void hbridge_cfg_setup ( hbridge_cfg_t *cfg );
```

- `hbridge_init` Initialization function.
```c
err_t hbridge_init ( hbridge_t *ctx, hbridge_cfg_t *cfg );
```

#### Example key functions :

- `hbridge_set_step_mode` This function sets the step mode resolution settings in @b ctx->step_mode.
```c
void hbridge_set_step_mode ( hbridge_t *ctx, uint8_t mode );
```

- `hbridge_set_direction` This function sets the motor direction to clockwise or counter-clockwise in @b ctx->direction.
```c
void hbridge_set_direction ( hbridge_t *ctx, uint8_t dir );
```

- `hbridge_drive_motor` This function drives the motor for the specific number of steps at the selected speed.
```c
void hbridge_drive_motor ( hbridge_t *ctx, uint32_t steps, uint8_t speed );
```

## Example Description

> This example demonstrates the use of the H-Bridge click board by driving the motor in both directions for a desired number of steps.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge_cfg_t hbridge_cfg;  /**< Click config object. */

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
    hbridge_cfg_setup( &hbridge_cfg );
    HBRIDGE_MAP_MIKROBUS( hbridge_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == hbridge_init( &hbridge, &hbridge_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor clockwise for 200 full steps and then counter-clockiwse for 400 half
steps with a 2 seconds delay before changing the direction. All data is being logged on
the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    hbridge_set_step_mode ( &hbridge, HBRIDGE_MODE_FULL_STEP );
    hbridge_set_direction ( &hbridge, HBRIDGE_DIR_CW );
    hbridge_drive_motor ( &hbridge, 200, HBRIDGE_SPEED_MEDIUM );
    log_printf ( &logger, " Move 200 full steps clockwise\r\n\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    hbridge_set_step_mode ( &hbridge, HBRIDGE_MODE_HALF_STEP );
    hbridge_set_direction ( &hbridge, HBRIDGE_DIR_CCW );
    hbridge_drive_motor ( &hbridge, 400, HBRIDGE_SPEED_FAST );
    log_printf ( &logger, " Move 400 half steps counter-clockwise\r\n\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
