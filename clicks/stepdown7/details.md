
---
# Step Down 7 Click

> Step Down 7 Click is a compact add-on board that converts higher voltages into a lower voltages level. This board features the MAX17624, a synchronous step-down converter with integrated MOSFETs from Analog Devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepdown7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/step-down-7-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Step Down 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Step Down 7 Click driver.

#### Standard key functions :

- `stepdown7_cfg_setup` Config Object Initialization function.
```c
void stepdown7_cfg_setup ( stepdown7_cfg_t *cfg );
```

- `stepdown7_init` Initialization function.
```c
err_t stepdown7_init ( stepdown7_t *ctx, stepdown7_cfg_t *cfg );
```

- `stepdown7_default_cfg` Click Default Configuration function.
```c
err_t stepdown7_default_cfg ( stepdown7_t *ctx );
```

#### Example key functions :

- `stepdown7_set_mode` Step Down 5 mode selection function.
```c
void stepdown7_set_mode ( stepdown7_t *ctx, uint8_t mode );
```

- `stepdown7_get_pg_state` Step Down 5 get PG pin state function.
```c
uint8_t stepdown7_get_pg_state ( stepdown7_t *ctx );
```

- `stepdown7_set_output` Step Down 7 set output voltage.
```c
err_t stepdown7_set_output ( stepdown7_t *ctx, uint8_t voltage );
```

## Example Description

> This library contains API for the Step Down 7 Click driver.
  This driver provides the functions to set the output voltage treshold.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
 After driver initialization, default settings sets output voltage to 1.5 V.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown7_cfg_t stepdown7_cfg;  /**< Click config object. */

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
    stepdown7_cfg_setup( &stepdown7_cfg );
    STEPDOWN7_MAP_MIKROBUS( stepdown7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown7_init( &stepdown7, &stepdown7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPDOWN7_ERROR == stepdown7_default_cfg ( &stepdown7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example demonstrates the use of the Step Down 7 Click board™ by changing 
  output voltage every 5 seconds starting from 1.5 V up to 3.3 V.

```c
void application_task ( void ) 
{
    for ( uint8_t n_cnt = STEPDOWN7_OUTPUT_1V5; n_cnt <= STEPDOWN7_OUTPUT_3V3; n_cnt++ )
    {
        stepdown7_set_output( &stepdown7, n_cnt );
        log_printf( &logger, " Selected output is:" );
        print_selected_output_level ( n_cnt );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.StepDown7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
