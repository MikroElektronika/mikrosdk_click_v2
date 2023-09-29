
---
# Step Down 9 click

> Step Down 9 Click is a compact add-on board that converts higher voltages into a lower voltage level. This board features the MAX20406, an automotive fully integrated synchronous silent switcher buck converter from Analog Devices. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepdown9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/step-down-9-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the Step Down 9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Step Down 9 Click driver.

#### Standard key functions :

- `stepdown9_cfg_setup` Config Object Initialization function.
```c
void stepdown9_cfg_setup ( stepdown9_cfg_t *cfg );
```

- `stepdown9_init` Initialization function.
```c
err_t stepdown9_init ( stepdown9_t *ctx, stepdown9_cfg_t *cfg );
```

- `stepdown9_default_cfg` Click Default Configuration function.
```c
err_t stepdown9_default_cfg ( stepdown9_t *ctx );
```

#### Example key functions :

- `stepdown9_set_en_pin` Step Down 9 set EN pin state function.
```c
void stepdown9_set_en_pin ( stepdown9_t *ctx, uint8_t pin_state );
```

- `stepdown9_set_wiper_pos` Step Down 9 set wiper position.
```c
err_t stepdown9_set_wiper_pos ( stepdown9_t *ctx, uint8_t wiper_pos );
```

- `stepdown9_set_output` Step Down 9 set output voltage.
```c
err_t stepdown9_set_output ( stepdown9_t *ctx, uint8_t voltage );
```

## Example Description

> This library contains API for the Step Down 9 Click driver.
  This driver provides the functions to set the output voltage treshold.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
  After driver initialization, default settings sets output voltage to 1.6 V.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown9_cfg_t stepdown9_cfg;  /**< Click config object. */

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
    stepdown9_cfg_setup( &stepdown9_cfg );
    STEPDOWN9_MAP_MIKROBUS( stepdown9_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == stepdown9_init( &stepdown9, &stepdown9_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPDOWN9_ERROR == stepdown9_default_cfg ( &stepdown9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example demonstrates the use of the Step Down 9 Click board™ by changing 
  output voltage every 5 seconds starting from 1.6 V up to 10 V.

```c
void application_task ( void )
{
    for ( uint8_t n_cnt = STEPDOWN9_VOUT_1V6; n_cnt <= STEPDOWN9_VOUT_10V; n_cnt++ )
    {
        stepdown9_set_output( &stepdown9, n_cnt );
        log_printf( &logger, " Selected output is:" );
        print_selected_output_level ( n_cnt );
        Delay_ms( 5000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.StepDown9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
