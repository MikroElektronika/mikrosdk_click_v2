
---
# LPG click

LPG click carries an MQ-5 sensor for detecting liquefied petroleum gas leakage. The gas sensing layer on the sensor unit is made of Tin dioxide (SnO2), which has lower conductivity in clean air.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lpg_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lpg-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the LPG Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LPG Click driver.

#### Standard key functions :

- `lpg_cfg_setup` Config Object Initialization function.
```c
void lpg_cfg_setup ( lpg_cfg_t *cfg );
```

- `lpg_init` Initialization function.
```c
LPG_RETVAL lpg_init ( lpg_t *ctx, lpg_cfg_t *cfg );
```

#### Example key functions :

- `lpg_read_an_pin_value` This function reads results of AD conversion of the AN pin.
```c
err_t lpg_read_an_pin_value ( lpg_t *ctx, uint16_t *data_out );
```

- `lpg_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t lpg_read_an_pin_voltage ( lpg_t *ctx, float *data_out );
```

## Example Description

> The demo application shows the reading of the adc values given by the sensors.

**The demo application is composed of two sections :**

### Application Init

> Configuring clicks and log objects.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    lpg_cfg_t lpg_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    lpg_cfg_setup( &lpg_cfg );
    LPG_MAP_MIKROBUS( lpg_cfg, MIKROBUS_1 );
    if ( lpg_init( &lpg, &lpg_cfg ) == ADC_ERROR ) {
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
    uint16_t lpg_an_value = 0;

    if ( lpg_read_an_pin_value ( &lpg, &lpg_an_value ) != ADC_ERROR ) {
        log_printf( &logger, " ADC Value : %u\r\n", lpg_an_value );
    }

    float lpg_an_voltage = 0;

    if ( lpg_read_an_pin_voltage ( &lpg, &lpg_an_voltage ) != ADC_ERROR ) {
        log_printf( &logger, " AN Voltage : %.3f[V]\r\n\n", lpg_an_voltage );
    }

    Delay_ms( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LPG

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
