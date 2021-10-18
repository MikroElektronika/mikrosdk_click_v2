
---
# Methane click

Methane click carries an MQ-4 sensor for methane (CH4). The gas sensing layer on the sensor unit is made of tin dioxide (SnO2), which has lower conductivity in clean air.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/methane_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/methane-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the Methane Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Methane Click driver.

#### Standard key functions :

- `methane_cfg_setup` Config Object Initialization function.
```c
void methane_cfg_setup ( methane_cfg_t *cfg );
```

- `methane_init` Initialization function.
```c
METHANE_RETVAL methane_init ( methane_t *ctx, methane_cfg_t *cfg );
```

- `methane_default_cfg` Click Default Configuration function.
```c
void methane_default_cfg ( methane_t *ctx );
```

#### Example key functions :

- `methane_read_an_pin_value` Methane read AN pin value function.
```c
err_t methane_read_an_pin_value ( methane_t *ctx, uint16_t *data_out );
```

- `methane_read_an_pin_voltage` Methane read AN pin voltage level function.
```c
err_t methane_read_an_pin_voltage ( methane_t *ctx, float *data_out );
```


## Example Description

> The demo application shows the reading of the adc values given by the sensors.

**The demo application is composed of two sections :**

### Application Init

> Configuring clicks and log objects.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    methane_cfg_t methane_cfg;  /**< Click config object. */

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

    methane_cfg_setup( &methane_cfg );
    METHANE_MAP_MIKROBUS( methane_cfg, MIKROBUS_1 );
    if ( methane_init( &methane, &methane_cfg ) == ADC_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the adc value and prints in two forms adc value and voltage.

```c

void application_task ( void ) {
    uint16_t methane_an_value = 0;

    if ( methane_read_an_pin_value ( &methane, &methane_an_value ) != ADC_ERROR ) {
        log_printf( &logger, " ADC Value : %u\r\n", methane_an_value );
    }

    float methane_an_voltage = 0;

    if ( methane_read_an_pin_voltage ( &methane, &methane_an_voltage ) != ADC_ERROR ) {
        log_printf( &logger, " AN Voltage : %.3f[V]\r\n\n", methane_an_voltage );
    }

    Delay_ms( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Methane

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
