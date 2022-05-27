\mainpage Main Page

---
# Step Down 3 click

> Step Down 3 Click is a compact add-on board that steps down the voltage from its input to its output. This board features the ST1PS03, a nano-quiescent miniaturized synchronous step-down converter with a load switch from STMicroelectronics. The ST1PS03 can provide up to 400mA output current with an input voltage ranging from 1.8V to 5.5V, specifically designed for applications where high efficiency is crucial. It also embeds a controlled switch accessible from auxiliary channel input to supply a subsystem, output voltage from 1.6V to 3.3V set using three digital control inputs, and a Power Good signal to indicate stabilized output voltages.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepdown3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/step-down-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : GPIO type


# Software Support

We provide a library for the Step Down 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Step Down 3 Click driver.

#### Standard key functions :

- `stepdown3_cfg_setup` Config Object Initialization function.
```c
void stepdown3_cfg_setup ( stepdown3_cfg_t *cfg );
```

- `stepdown3_init` Initialization function.
```c
err_t stepdown3_init ( stepdown3_t *ctx, stepdown3_cfg_t *cfg );
```

#### Example key functions :

- `stepdown3_enable_device` This function enables the auxiliary output (VOUT_AUX) by setting the AUX pin to HIGH logic state.
```c
void stepdown3_enable_device ( stepdown3_t *ctx );
```

- `stepdown3_enable_aux_output` This function disables the auxiliary output (VOUT_AUX) by setting the AUX pin to LOW logic state.
```c
void stepdown3_enable_aux_output ( stepdown3_t *ctx );
```

- `stepdown3_set_output_voltage` This function sets the output voltage by setting the D2, D1, and D0 pins to a desired state.
```c
void stepdown3_set_output_voltage ( stepdown3_t *ctx, uint8_t vout );
```

## Example Description

> This example demonstrates the use of Step Down 3 click board by iterating through the entire output voltage range.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger, then enables the click board and disables the auxiliary output.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepdown3_cfg_t stepdown3_cfg;  /**< Click config object. */

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
    stepdown3_cfg_setup( &stepdown3_cfg );
    STEPDOWN3_MAP_MIKROBUS( stepdown3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == stepdown3_init( &stepdown3, &stepdown3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    stepdown3_enable_device ( &stepdown3 );
    stepdown3_disable_aux_output ( &stepdown3 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the output voltage every 3 seconds and displays the set voltage output value on the USB UART.

```c
void application_task ( void )
{
    static uint8_t vout = STEPDOWN3_OUT_VOLTAGE_1V6;
    stepdown3_set_output_voltage ( &stepdown3, vout );
    switch ( vout )
    {
        case STEPDOWN3_OUT_VOLTAGE_1V6:
        {
            log_printf( &logger, " Output voltage: 1.6 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_1V8:
        {
            log_printf( &logger, " Output voltage: 1.8 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_2V1:
        {
            log_printf( &logger, " Output voltage: 2.1 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_2V5:
        {
            log_printf( &logger, " Output voltage: 2.5 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_2V7:
        {
            log_printf( &logger, " Output voltage: 2.7 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_2V8:
        {
            log_printf( &logger, " Output voltage: 2.8 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_3V0:
        {
            log_printf( &logger, " Output voltage: 3.0 V\r\n\n" );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_3V3:
        {
            log_printf( &logger, " Output voltage: 3.3 V\r\n\n" );
            break;
        }
    }
    if ( ++vout > STEPDOWN3_OUT_VOLTAGE_3V3 )
    {
        vout = STEPDOWN3_OUT_VOLTAGE_1V6;
    }
    Delay_ms ( 3000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.StepDown3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
