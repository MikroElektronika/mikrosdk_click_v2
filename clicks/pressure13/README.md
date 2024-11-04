\mainpage Main Page

---
# Pressure 13 Click

> Pressure 13 Click is a compact add-on board that contains an integrated pressure sensor for manifold air pressure measurement applications. This board features the KP229E2701, a miniaturized analog manifold air pressure sensor based on a capacitive principle from Infineon.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure13_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/pressure-13-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the Pressure13 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Pressure13 Click driver.

#### Standard key functions :

- `pressure13_cfg_setup` Config Object Initialization function.
```c
void pressure13_cfg_setup ( pressure13_cfg_t *cfg );
```

- `pressure13_init` Initialization function.
```c
err_t pressure13_init ( pressure13_t *ctx, pressure13_cfg_t *cfg );
```

#### Example key functions :

- `pressure13_read_an_pin_value` Pressure 13 read AN pin value function.
```c
err_t pressure13_read_an_pin_value ( pressure13_t *ctx, uint16_t *data_out );
```

- `pressure13_read_an_pin_voltage` Pressure 13 read AN pin voltage level function.
```c
err_t pressure13_read_an_pin_voltage ( pressure13_t *ctx, float *data_out );
```

- `pressure13_get_pressure` Pressure 13 get pressure function.
```c
err_t pressure13_get_pressure ( pressure13_t *ctx, float *data_out );
```

## Example Description

> This is an example which demonstrates the use of Pressure 13 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables - GPIO, initializes ADC, also write log.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure13_cfg_t pressure13_cfg;  /**< Click config object. */

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
    pressure13_cfg_setup( &pressure13_cfg );
    PRESSURE13_MAP_MIKROBUS( pressure13_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == pressure13_init( &pressure13, &pressure13_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n", voltage_val );
}

```

### Application Task

> Measure and display pressure ( mBar ). Results are being sent to the Usart Terminal where you can track their changes. All data logs on usb uart approximately every sec.

```c

void application_task ( void ) {
    if ( pressure13_get_pressure( &pressure13, &pressure_val ) != ADC_ERROR ) {
        log_printf( &logger, " Pressure: %.3f [mBar]\r\n", pressure_val );
    }
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure13

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
