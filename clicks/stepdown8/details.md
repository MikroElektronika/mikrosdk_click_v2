
---
# Step Down 8 click

> Step Down 8 Click is a compact add-on board that converts higher voltages into a lower voltage level. This board features the MAX25232, a mini buck converter from Analog Devices. It is designed to deliver up to 3A with 3.5V to 36V input voltages while using only 3.5μA quiescent current at no load.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepdown8_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/step-down-8-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Step Down 8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Step Down 8 Click driver.

#### Standard key functions :

- `stepdown8_cfg_setup` Config Object Initialization function.
```c
void stepdown8_cfg_setup ( stepdown8_cfg_t *cfg );
```

- `stepdown8_init` Initialization function.
```c
err_t stepdown8_init ( stepdown8_t *ctx, stepdown8_cfg_t *cfg );
```

- `stepdown8_default_cfg` Click Default Configuration function.
```c
err_t stepdown8_default_cfg ( stepdown8_t *ctx );
```

#### Example key functions :

- `stepdown8_set_en_pin` Step Down 8 set EN pin state function.
```c
void stepdown8_set_en_pin ( stepdown8_t *ctx, uint8_t pin_state );
```

- `stepdown8_set_wiper_pos` Step Down 8 set wiper position.
```c
err_t stepdown8_set_wiper_pos ( stepdown8_t *ctx, uint16_t wiper_pos );
```

- `stepdown8_set_output` Step Down 8 set output voltage.
```c
err_t stepdown8_set_output ( stepdown8_t *ctx, float voltage );
```

## Example Description

> This library contains API for the Step Down 8 Click driver.
  This driver provides the functions to set the output voltage treshold.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
  After driver initialization, default settings sets output voltage to 3 V.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown8_cfg_t stepdown8_cfg;  /**< Click config object. */

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
    stepdown8_cfg_setup( &stepdown8_cfg );
    STEPDOWN8_MAP_MIKROBUS( stepdown8_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown8_init( &stepdown8, &stepdown8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPDOWN8_ERROR == stepdown8_default_cfg ( &stepdown8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example demonstrates the use of the Step Down 8 Click board™ by changing 
  output voltage every 2 seconds starting from 3 V up to 18 V.

```c
void application_task ( void ) 
{
    for ( uint8_t n_cnt = STEPDOWN8_MIN_OUTPUT; n_cnt <= STEPDOWN8_MAX_OUTPUT; n_cnt++ )
    {
        stepdown8_set_output( &stepdown8, ( float ) n_cnt );
        log_printf( &logger, " Output voltage %d V\r\n", ( uint16_t ) n_cnt );
        Delay_ms( 2000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.StepDown8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---