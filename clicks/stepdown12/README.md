\mainpage Main Page

---
# Step Down 12 Click

> Step Down 12 Click is a compact add-on board for reliable DC-DC step-down applications. Based on Texas Instruments' TPS62902 synchronous step-down converter, it features the DCS-Control topology, which combines hysteretic, voltage mode, and current mode control for precision and fast response to voltage changes. Supporting a wide input voltage range of 3V to 17V, it provides stable output voltages with accuracy within ±1% and can enter power save mode for high efficiency under light loads. With 16 configurable output voltages from 0.7V to 5.5V, this Click board™ is ideal for applications in factory automation, building systems, data centers, enterprise computing, and motor drives where efficient, stable power conversion is essential.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepdown12_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/step-down-12-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Step Down 12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Step Down 12 Click driver.

#### Standard key functions :

- `stepdown12_cfg_setup` Config Object Initialization function.
```c
void stepdown12_cfg_setup ( stepdown12_cfg_t *cfg );
```

- `stepdown12_init` Initialization function.
```c
err_t stepdown12_init ( stepdown12_t *ctx, stepdown12_cfg_t *cfg );
```

- `stepdown12_default_cfg` Click Default Configuration function.
```c
void stepdown12_default_cfg ( stepdown12_t *ctx );
```

#### Example key functions :

- `stepdown12_get_pg_pin` This function returns the power good (PG) pin logic state.
```c
uint8_t stepdown12_get_pg_pin ( stepdown12_t *ctx );
```

- `stepdown12_set_vout` This function sets the voltage output by setting the digipot wiper resistance.
```c
err_t stepdown12_set_vout ( stepdown12_t *ctx, float vout );
```

- `stepdown12_enable_device` This function enables the device by setting the EN pin to high logic state.
```c
void stepdown12_enable_device ( stepdown12_t *ctx );
```

## Example Description

> This example demonstrates the use of Step Down 12 Click board by changing the output voltage every 3 seconds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown12_cfg_t stepdown12_cfg;  /**< Click config object. */

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
    stepdown12_cfg_setup( &stepdown12_cfg );
    STEPDOWN12_MAP_MIKROBUS( stepdown12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown12_init( &stepdown12, &stepdown12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    stepdown12_default_cfg ( &stepdown12 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the output voltage every 3 seconds from MAX (5.5V) to MIN (1.05V) in steps of 0.5V
and displays the currently set voltage output value on the USB UART. It also monitors
the power good fault indication.

```c
void application_task ( void )
{
    static float vout = STEPDOWN12_VOUT_MAX;

    if ( !stepdown12_get_pg_pin ( &stepdown12 ) )
    {
        log_error( &logger, " Power Good Fault - Vout is below nominal regulation\r\n" );
    }

    if ( STEPDOWN12_OK == stepdown12_set_vout ( &stepdown12, vout ) )
    {
        log_printf( &logger, " Vout: %.3f V\r\n\n", vout );
        vout -= 0.5;
        if ( vout < STEPDOWN12_VOUT_MIN )
        {
            vout = STEPDOWN12_VOUT_MAX;
        }
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.StepDown12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
