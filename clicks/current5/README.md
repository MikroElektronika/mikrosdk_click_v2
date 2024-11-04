\mainpage Main Page

---
# Current 5 Click

> Current 5 Click is a compact add-on board that provides a precise and accurate current sensing solution. This board features the INA381, a high-speed current-sense amplifier with an integrated comparator from Texas Instruments. This device has selectable operating modes (transparent or latched) and detects overcurrent conditions by measuring the voltage developed across a current shunt resistor. Then it compares that voltage to a user-defined threshold limit set by the comparator reference potentiometer. The current-shunt monitor can measure differential voltage signals on common-mode voltages that vary from –0.2V to 26V, independent of the supply voltage. This Click board™ delivers higher performance to applications such as test and measurement, load and power supplies monitoring, low-side phase motor control, and many more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/current5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/current-5-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Sep 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Current5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Current5 Click driver.

#### Standard key functions :

- `current5_cfg_setup` Config Object Initialization function.
```c
void current5_cfg_setup ( current5_cfg_t *cfg );
```

- `current5_init` Initialization function.
```c
err_t current5_init ( current5_t *ctx, current5_cfg_t *cfg );
```

#### Example key functions :

- `current5_get_current` Get current.
```c
err_t current5_get_current ( current5_t *ctx, float *current )
```

- `current5_get_adc` Read raw adc value.
```c
err_t current5_get_adc ( current5_t *ctx, uint16_t *adc_data )
```

- `current5_get_alert` Get alert pin state.
```c
uint8_t current5_get_alert ( current5_t *ctx )
```

## Example Description

> This example application showcases ability of the device
to read raw adc data and calculate the current from it.

**The demo application is composed of two sections :**

### Application Init

> Initialization of communication modules(SPI, UART) and 
additional pins for controlling device(RST, ALERT->INT).

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current5_cfg_t current5_cfg;  /**< Click config object. */

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
    current5_cfg_setup( &current5_cfg );
    CURRENT5_MAP_MIKROBUS( current5_cfg, MIKROBUS_1 );
    err_t init_flag  = current5_init( &current5, &current5_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Read ADC data with SPI communication and calculate input current.

```c

void application_task ( void )
{
    float current = 0;
    current5_get_current( &current5, &current );
    log_printf( &logger, " > Current[ A ]: %.2f\r\n", current );
    log_printf( &logger, "*************************************************\r\n" );
    Delay_ms ( 300 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Current5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
