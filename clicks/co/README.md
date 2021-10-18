\mainpage Main Page

---
# CO click

CO clickis designed to run on a 5V power supply only. It communicates with the target microcontroller over the AN pin on the mikroBUS™ line.The board also features a calibration potentiometer, a mikroBUS™ host socket, two jumpers and a power indicator LED.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/co_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/co-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the CO Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for CO Click driver.

#### Standard key functions :

- `co_cfg_setup` Config Object Initialization function.
```c
void co_cfg_setup ( co_cfg_t *cfg );
```

- `co_init` Initialization function.
```c
CO_RETVAL co_init ( co_t *ctx, co_cfg_t *cfg );
```

#### Example key functions :

- `co_read_an_pin_value` This function reads results of AD conversion of the AN pin.
```c
err_t co_read_an_pin_value ( co_t *ctx, uint16_t *data_out );
```

- `co_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t co_read_an_pin_voltage ( co_t *ctx, float *data_out );
```

## Example Description

> The demo application shows the reading of the adc 
values given by the sensors.

**The demo application is composed of two sections :**

### Application Init

> Configuring clicks and log objects.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    co_cfg_t co_cfg;  /**< Click config object. */

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

    co_cfg_setup( &co_cfg );
    CO_MAP_MIKROBUS( co_cfg, MIKROBUS_1 );
    if ( co_init( &co, &co_cfg ) == ADC_ERROR ) {
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
    uint16_t co_an_value = 0;

    if ( co_read_an_pin_value ( &co, &co_an_value ) != ADC_ERROR ) {
        log_printf( &logger, " ADC Value : %u\r\n", co_an_value );
    }

    float co_an_voltage = 0;

    if ( co_read_an_pin_voltage ( &co, &co_an_voltage ) != ADC_ERROR ) {
        log_printf( &logger, " AN Voltage : %.3f[V]\r\n\n", co_an_voltage );
    }

    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.CO

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
