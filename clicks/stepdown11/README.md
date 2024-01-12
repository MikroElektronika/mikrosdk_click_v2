\mainpage Main Page

---
# Step Down 11 click

> Step Down 11 Click is a compact add-on board that converts higher voltages into lower voltage levels. This board features the TPSM82913, a low-noise and low-ripple buck power module from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepdown11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/step-down-11-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Step Down 11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Step Down 11 Click driver.

#### Standard key functions :

- `stepdown11_cfg_setup` Config Object Initialization function.
```c
void stepdown11_cfg_setup ( stepdown11_cfg_t *cfg );
```

- `stepdown11_init` Initialization function.
```c
err_t stepdown11_init ( stepdown11_t *ctx, stepdown11_cfg_t *cfg );
```

- `stepdown11_default_cfg` Click Default Configuration function.
```c
err_t stepdown11_default_cfg ( stepdown11_t *ctx );
```

#### Example key functions :

- `stepdown11_get_resistance` Step Down 11 get the resistance function.
```c
err_t stepdown11_get_resistance ( stepdown11_t *ctx, uint8_t wiper_sel, float *res_kohm );
```

- `stepdown11_set_voltage` Step Down 11 set voltage output function.
```c
err_t stepdown11_set_voltage ( stepdown11_t *ctx, float v_out );
```

- `stepdown11_set_mode` Step Down 11 set S-CONF device configuration mode function.
```c
err_t stepdown11_set_mode ( stepdown11_t *ctx, float sconf_mode );
```

## Example Description

> This library contains API for the Step Down 11 Click driver.
  This driver provides the functions to set the output voltage treshold.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
  After driver initialization, default settings sets output voltage to 1 V.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown11_cfg_t stepdown11_cfg;  /**< Click config object. */

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
    stepdown11_cfg_setup( &stepdown11_cfg );
    STEPDOWN11_MAP_MIKROBUS( stepdown11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown11_init( &stepdown11, &stepdown11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPDOWN11_ERROR == stepdown11_default_cfg ( &stepdown11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example demonstrates the use of the Step Down 11 Click board™ by changing 
  output voltage every 5 seconds starting from 1 V up to 5 V.

```c
void application_task ( void ) 
{
    for ( uint8_t vout = 1; vout <= 5; vout++ )
    {
        log_printf( &logger, " Set output voltage %dV \r\n", ( uint16_t ) vout );
        stepdown11_set_voltage ( &stepdown11, vout );
        Delay_ms( 5000 );
    }
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.StepDown11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
