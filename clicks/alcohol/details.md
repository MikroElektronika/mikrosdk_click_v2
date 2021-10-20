
---
# Alcohol click

Alcohol click has a high sensitivity to alcohol and it can be used to detect alcohol in concentrations from 0.04 to 4mg/l.

Alcohol click carries an MQ-3 Semiconductor sensor for alcohol. The click is designed to run on a 5V power supply only. It communicates with the target microcontroller through the AN pin on the mikroBUS™ line. 


<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/alcohol_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/alcohol-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the Alcohol Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Alcohol Click driver.

#### Standard key functions :

- `alcohol_cfg_setup` Config Object Initialization function.
```c
void alcohol_cfg_setup ( alcohol_cfg_t *cfg );
```

- `alcohol_init` Initialization function.
```c
ALCOHOL_RETVAL alcohol_init ( alcohol_t *ctx, alcohol_cfg_t *cfg );
```

#### Example key functions :

- `alcohol_read_an_pin_value` This function reads results of AD conversion of the AN pin.
```c
err_t alcohol_read_an_pin_value ( alcohol_t *ctx, uint16_t *data_out );
```

- `alcohol_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t alcohol_read_an_pin_voltage ( alcohol_t *ctx, float *data_out );
```

## Example Description

> The demo application shows the reading of the adc values given by the sensors.

**The demo application is composed of two sections :**

### Application Init

> Configuring clicks and log objects.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    alcohol_cfg_t alcohol_cfg;  /**< Click config object. */

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

    alcohol_cfg_setup( &alcohol_cfg );
    ALCOHOL_MAP_MIKROBUS( alcohol_cfg, MIKROBUS_1 );
    if ( alcohol_init( &alcohol, &alcohol_cfg ) == ADC_ERROR ) {
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
    uint16_t alcohol_an_value = 0;

    if ( alcohol_read_an_pin_value ( &alcohol, &alcohol_an_value ) != ADC_ERROR ) {
        log_printf( &logger, " ADC Value : %u\r\n", alcohol_an_value );
    }

    float alcohol_an_voltage = 0;

    if ( alcohol_read_an_pin_voltage ( &alcohol, &alcohol_an_voltage ) != ADC_ERROR ) {
        log_printf( &logger, " AN Voltage : %.3f[V]\r\n\n", alcohol_an_voltage );
    }

    Delay_ms( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Alcohol

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
