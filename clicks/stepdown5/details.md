
---
# Step Down 5 click

> Step Down 5 Click is a compact add-on board that converts a higher voltage into a lower voltage level. This board features the TPS628510, a high-efficiency, easy-to-use, synchronous step-down DC/DC converter from Texas Instruments. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepdown5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/step-down-5-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Step Down 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Step Down 5 Click driver.

#### Standard key functions :

- `stepdown5_cfg_setup` Config Object Initialization function.
```c
void stepdown5_cfg_setup ( stepdown5_cfg_t *cfg );
```

- `stepdown5_init` Initialization function.
```c
err_t stepdown5_init ( stepdown5_t *ctx, stepdown5_cfg_t *cfg );
```

- `stepdown5_default_cfg` Click Default Configuration function.
```c
err_t stepdown5_default_cfg ( stepdown5_t *ctx );
```

#### Example key functions :

- `stepdown5_set_wiper_0_pos` Step Down 5 set wiper 0 position.
```c
err_t stepdown5_set_wiper_0_pos ( stepdown5_t *ctx, uint16_t wiper_0_pos );
```

- `stepdown5_set_r1_resistance` Step Down 5 set potentiometer 0 resistance.
```c
err_t stepdown5_set_r1_resistance ( stepdown5_t *ctx, uint32_t resistance );
```

- `stepdown5_set_output` Step Down 5 set output voltage.
```c
err_t stepdown5_set_output ( stepdown5_t *ctx, uint8_t voltage );
```

## Example Description

> This library contains API for the Step Down 5 Click driver.
 This driver provides the functions to set the output voltage treshold.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
 After driver initialization, default settings sets output voltage to 0.6 V.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown5_cfg_t stepdown5_cfg;  /**< Click config object. */

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
    stepdown5_cfg_setup( &stepdown5_cfg );
    STEPDOWN5_MAP_MIKROBUS( stepdown5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepdown5_init( &stepdown5, &stepdown5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPDOWN5_ERROR == stepdown5_default_cfg ( &stepdown5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example demonstrates the use of the Step Down 5 Click board™ by changing 
 output voltage every 5 seconds starting from 0.6 V up to 3.3 V.

```c
void application_task ( void ) 
{
    for ( uint8_t n_cnt = STEPDOWN5_OUTPUT_0V6; n_cnt <= STEPDOWN5_OUTPUT_3V3; n_cnt++ )
    {
        stepdown5_set_output( &stepdown5, n_cnt );
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
- Click.StepDown5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
