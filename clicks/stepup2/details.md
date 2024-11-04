
---
# Step Up 2 Click

> Step Up 2 Click is a compact add-on board designed to boost the power capabilities of devices. This board features the TPS61299, a synchronous boost converter from Texas Instruments. This component is renowned for its low quiescent current and high efficiency under light-load conditions. The board distinguishes itself with the ability to adjust output voltage via the integrated MAX5419 digital potentiometer, offering precise control through an I2C interface. It supports external voltages from 0.2V to 5.5V, delivering a regulated output range of 1.8V to 5.5V.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepup2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/step-up-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Step Up 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Step Up 2 Click driver.

#### Standard key functions :

- `stepup2_cfg_setup` Config Object Initialization function.
```c
void stepup2_cfg_setup ( stepup2_cfg_t *cfg );
```

- `stepup2_init` Initialization function.
```c
err_t stepup2_init ( stepup2_t *ctx, stepup2_cfg_t *cfg );
```

- `stepup2_default_cfg` Click Default Configuration function.
```c
err_t stepup2_default_cfg ( stepup2_t *ctx );
```

#### Example key functions :

- `stepup2_set_vout` This function sets the voltage output level.
```c
err_t stepup2_set_vout ( stepup2_t *ctx, stepup2_vout_t vout );
```

- `stepup2_set_resistance` This function sets a desired resistance by writing to the volatile memory register and the wiper position.
```c
err_t stepup2_set_resistance ( stepup2_t *ctx, float res_kohm );
```

- `stepup2_enable` This function turns on the power switch and enables the boost mode.
```c
void stepup2_enable ( stepup2_t *ctx );
```

## Example Description

> This example demonstrates the use of the Step Up 2 Click board by changing the output voltage.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepup2_cfg_t stepup2_cfg;  /**< Click config object. */

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
    stepup2_cfg_setup( &stepup2_cfg );
    STEPUP2_MAP_MIKROBUS( stepup2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepup2_init( &stepup2, &stepup2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPUP2_ERROR == stepup2_default_cfg ( &stepup2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application changes the output voltage and displays the current voltage output value.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float vout_table[ 15 ] = { STEPUP2_VOUT_LIST };
    for ( stepup2_vout_t vout = STEPUP2_VOUT_5V5; vout <= STEPUP2_VOUT_3V3; vout++ )
    {
        if ( STEPUP2_OK == stepup2_set_vout( &stepup2, vout ) )
        {
            log_printf( &logger, " Voltage: %.2f[V]\r\n\n", vout_table[ vout ] );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.StepUp2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
