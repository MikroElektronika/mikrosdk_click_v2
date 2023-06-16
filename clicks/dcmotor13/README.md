\mainpage Main Page

---
# DC Motor 13 click

> DC Motor 13 Click is a compact add-on board with a brushed DC motor driver. This board features the TB67H481FNG, a dual-channel, H-bridge, brushed DC motor driver from Toshiba Semiconductor that uses the PWM IN interface to control the DC motor outputs. Fabricated with the BiCD process (DMOSFET is used for output power transistor), it covers a wide operating voltage range of 8.2V to 44V with a maximum output current capacity of 2A. It also offers helpful features like a robust and reliable operation, like the decay modes selection function, PWM constant-current drive, torque settings, protection features, and one anomaly detection indicator.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor13_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dc-motor-13-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the DC Motor 13 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DC Motor 13 Click driver.

#### Standard key functions :

- `dcmotor13_cfg_setup` Config Object Initialization function.
```c
void dcmotor13_cfg_setup ( dcmotor13_cfg_t *cfg );
```

- `dcmotor13_init` Initialization function.
```c
err_t dcmotor13_init ( dcmotor13_t *ctx, dcmotor13_cfg_t *cfg );
```

- `dcmotor13_default_cfg` Click Default Configuration function.
```c
err_t dcmotor13_default_cfg ( dcmotor13_t *ctx );
```

#### Example key functions :

- `dcmotor13_set_outa_mode` This function sets the OUTA mode.
```c
err_t dcmotor13_set_outa_mode ( dcmotor13_t *ctx, uint8_t mode );
```

- `dcmotor13_set_outb_mode` This function sets the OUTB mode.
```c
err_t dcmotor13_set_outb_mode ( dcmotor13_t *ctx, uint8_t mode );
```

- `dcmotor13_set_outa_torque` This function sets the OUTA torque.
```c
err_t dcmotor13_set_outa_torque ( dcmotor13_t *ctx, uint8_t torque );
```

## Example Description

> This example demonstrates the use of DC Motor 13 click board by driving the motors in both direction in the span of 9 seconds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which sets the output torque to 100%.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor13_cfg_t dcmotor13_cfg;  /**< Click config object. */

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
    dcmotor13_cfg_setup( &dcmotor13_cfg );
    DCMOTOR13_MAP_MIKROBUS( dcmotor13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dcmotor13_init( &dcmotor13, &dcmotor13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR13_ERROR == dcmotor13_default_cfg ( &dcmotor13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motors in the clockwise direction, then switches to the counter-clockwise direction, and after that pulls the motors brake with a 3 seconds delay after each change.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    if ( DCMOTOR13_OK == dcmotor13_set_outa_mode ( &dcmotor13, DCMOTOR13_MODE_CW ) )
    {
        log_printf ( &logger, " OUTA: Clockwise\r\n" );
    }
    if ( DCMOTOR13_OK == dcmotor13_set_outb_mode ( &dcmotor13, DCMOTOR13_MODE_CW ) )
    {
        log_printf ( &logger, " OUTB: Clockwise\r\n\n" );
    }
    Delay_ms ( 3000 );
    if ( DCMOTOR13_OK == dcmotor13_set_outa_mode ( &dcmotor13, DCMOTOR13_MODE_CCW ) )
    {
        log_printf ( &logger, " OUTA: Counter-Clockwise\r\n" );
    }
    if ( DCMOTOR13_OK == dcmotor13_set_outb_mode ( &dcmotor13, DCMOTOR13_MODE_CCW ) )
    {
        log_printf ( &logger, " OUTB: Counter-Clockwise\r\n\n" );
    }
    Delay_ms ( 3000 );
    if ( DCMOTOR13_OK == dcmotor13_set_outa_mode ( &dcmotor13, DCMOTOR13_MODE_SHORT_BRAKE ) )
    {
        log_printf ( &logger, " OUTA: Short brake\r\n" );
    }
    if ( DCMOTOR13_OK == dcmotor13_set_outb_mode ( &dcmotor13, DCMOTOR13_MODE_SHORT_BRAKE ) )
    {
        log_printf ( &logger, " OUTB: Short brake\r\n\n" );
    }
    Delay_ms ( 3000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor13

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
