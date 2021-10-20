
---
# Hydrogen  click

Hydrogen click carries an MQ-8 sensor for hydrogen (H2). The gas sensing layer on the sensor unit is made of tin dioxide (SnO2), which has lower conductivity in clean air.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hydrogen_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hydrogen-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the Hydrogen Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Hydrogen Click driver.

#### Standard key functions :

- `hydrogen_cfg_setup` Config Object Initialization function.
```c
void hydrogen_cfg_setup ( hydrogen_cfg_t *cfg );
```

- `hydrogen_init` Initialization function.
```c
HYDROGEN_RETVAL hydrogen_init ( hydrogen_t *ctx, hydrogen_cfg_t *cfg );
```

#### Example key functions :

- `hydrogen_read_an_pin_value` This function reads results of AD conversion of the AN pin.
```c
err_t hydrogen_read_an_pin_value ( hydrogen_t *ctx, uint16_t *data_out );
```

- `hydrogen_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t hydrogen_read_an_pin_voltage ( hydrogen_t *ctx, float *data_out );
```

## Example Description

> The demo application shows the reading of the adc values given by the sensors.

**The demo application is composed of two sections :**

### Application Init

> Configuring clicks and log objects.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    hydrogen_cfg_t hydrogen_cfg;  /**< Click config object. */

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

    hydrogen_cfg_setup( &hydrogen_cfg );
    HYDROGEN_MAP_MIKROBUS( hydrogen_cfg, MIKROBUS_1 );
    if ( hydrogen_init( &hydrogen, &hydrogen_cfg ) == ADC_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the adc value and prints in two forms (DEC and HEX).

```c

void application_task ( void ) {
    uint16_t hydrogen_an_value = 0;

    if ( hydrogen_read_an_pin_value ( &hydrogen, &hydrogen_an_value ) != ADC_ERROR ) {
        log_printf( &logger, " ADC Value : %u\r\n", hydrogen_an_value );
    }

    float hydrogen_an_voltage = 0;

    if ( hydrogen_read_an_pin_voltage ( &hydrogen, &hydrogen_an_voltage ) != ADC_ERROR ) {
        log_printf( &logger, " AN Voltage : %.3f[V]\r\n\n", hydrogen_an_voltage );
    }

    Delay_ms( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Hydrogen

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
