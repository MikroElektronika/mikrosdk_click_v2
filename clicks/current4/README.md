\mainpage Main Page

---
# Current 4 Click

Current 4 Click is a compact add-on board that provides a precise and accurate current sensing solution. This board features the INA250, a bidirectional, zero-drift current-shunt monitor from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/current4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/current-4-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the Current4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Current4 Click driver.

#### Standard key functions :

- `current4_cfg_setup` Config Object Initialization function.
```c
void current4_cfg_setup ( current4_cfg_t *cfg );
```

- `current4_init` Initialization function.
```c
err_t current4_init ( current4_t *ctx, current4_cfg_t *cfg );
```

#### Example key functions :

- `current4_read_load_current` Read load current.
```c
err_t current4_read_load_current ( current4_t *ctx, float *load_current );
```

- `current4_read_an_pin_voltage` Read AN pin voltage level function.
```c
err_t current4_read_an_pin_voltage ( current4_t *ctx, float *data_out );
```

- `current4_read_an_pin_value` Read AN pin value function.
```c
err_t current4_read_an_pin_value ( current4_t *ctx, uint16_t *data_out );
```

## Example Description

> This example showcases the ability of the Current 4 Click board.
It configures Host MCU for communication and reads the voltage 
of AN pin and calculates current on load output.

**The demo application is composed of two sections :**

### Application Init

> Initialization of the communication modules(ADC and UART).

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current4_cfg_t current4_cfg;  /**< Click config object. */

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
    current4_cfg_setup( &current4_cfg );
    CURRENT4_MAP_MIKROBUS( current4_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == current4_init( &current4, &current4_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> In span on 500ms reads voltage and calculates the current on load.

```c

void application_task ( void ) 
{
    float current4_load_current = 0;

    if ( ADC_ERROR != current4_read_load_current ( &current4, &current4_load_current ) ) 
    {
        log_printf( &logger, " > Load current : %.2f[A]\r\n", current4_load_current );
        log_printf( &logger, "**********************\r\n" );
    }

    Delay_ms ( 500 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Current4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
