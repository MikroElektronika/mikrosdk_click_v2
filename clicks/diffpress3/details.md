
---
# Diff Press 3 Click

> Diff Press 3 Click is a compact add-on board that can measure differential pressure. 
> It features the 2513130810401, a WSEN-PDUS differential pressure sensor from Würth Elektronik. 
> The sensor is MEMS based and uses a piezo-resistive sensing principle. 
> It is a fully calibrated pressure sensor with 15-bit digital and 11-bit analog outputs. 
> In addition to pressure measurement, the 2513130810401 WSEN-PDUS sensor also has an embedded temperature sensor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/diffpress3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/diff-press-3-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the Diff Press 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Diff Press 3 Click driver.

#### Standard key functions :

- `diffpress3_cfg_setup` Config Object Initialization function.
```c
void diffpress3_cfg_setup ( diffpress3_cfg_t *cfg );
```

- `diffpress3_init` Initialization function.
```c
err_t diffpress3_init ( diffpress3_t *ctx, diffpress3_cfg_t *cfg );
```

#### Example key functions :

- `diffpress3_get_pressure` Diff Press 3 get pressure function.
```c
err_t diffpress3_get_pressure ( diffpress3_t *ctx, float *pressure );
```

- `diffpress3_get_temperature` Diff Press 3 get temperature function.
```c
err_t diffpress3_get_temperature ( diffpress3_t *ctx, float *temperature );
```

- `diffpress3_read_raw_adc` Diff Press 3 read raw ADC value function.
```c
err_t diffpress3_read_raw_adc ( diffpress3_t *ctx, uint16_t *raw_adc, diffpress3_d_sel_t data_sel );
```

## Example Description

> This library contains API for the Diff Press 3 Click driver.
> This demo application shows an example of 
> differential pressure and temperature measurement.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C and ADC module and log UART.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    diffpress3_cfg_t diffpress3_cfg;  /**< Click config object. */

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
    diffpress3_cfg_setup( &diffpress3_cfg );
    DIFFPRESS3_MAP_MIKROBUS( diffpress3_cfg, MIKROBUS_1 );
    err_t init_flag = diffpress3_init( &diffpress3, &diffpress3_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Diff Press 3 Click board™.
> The demo application measures and display the Differential Pressure [kPa]
> and Temperature [degree Celsius] data.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float pressure, temperature;
    if ( DIFFPRESS3_OK == diffpress3_get_pressure( &diffpress3, &pressure ) )
    {
        log_printf( &logger, " Diff Pressure: %.3f [kPa]\r\n", pressure );
        Delay_ms ( 100 );
    }
    if ( DIFFPRESS3_OK == diffpress3_get_temperature( &diffpress3, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f [C]\r\n", temperature );
        Delay_ms ( 100 );
    }
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DiffPress3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
