\mainpage Main Page

---
# Power MUX 2 Click

Power MUX 2 Click is a compact add-on board that contains a highly configurable power mux. This board features the TPS2120, a dual-input single-output power multiplexer with an automatic switchover feature from Texas Instruments. This Click board™ prioritizes the main supply when present and quickly switches to auxiliary supply when the main supply drops. During switchover, the voltage drop is controlled to block reverse current before it happens and provide uninterrupted power to the load with minimal hold-up capacitance. This Click board™ is suitable for applications as a backup and standby power, input source selection, and various systems having multiple power sources.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/power_mux_2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/power-mux-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the PowerMux2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for PowerMux2 Click driver.

#### Standard key functions :

- `powermux2_cfg_setup` Config Object Initialization function.
```c
void powermux2_cfg_setup ( powermux2_cfg_t *cfg );
```

- `powermux2_init` Initialization function.
```c
POWERMUX2_RETVAL powermux2_init ( powermux2_t *ctx, powermux2_cfg_t *cfg );
```

- `powermux2_default_cfg` Click Default Configuration function.
```c
void powermux2_default_cfg ( powermux2_t *ctx );
```

#### Example key functions :

- `powermux2_generic_write` Power MUX 2 data writing function.
```c
err_t powermux2_generic_write ( powermux2_t *ctx, uint8_t data_in );
```

- `powermux2_set_resistance` Power MUX 2 set resistance function.
```c
err_t powermux2_set_resistance ( powermux2_t *ctx, float resistance );
```

## Example Description

> This library contains API for the Power MUX 2 Click driver. 
> The Power MUX 2 operates in automatic switchover mode with a priority prioritizing supply 1 
> when present and quickly switches to supply 2 when supply 1 drops below approximately 6V.

**The demo application is composed of two sections :**

### Application Init

> The application init consist of initialization of SPI driver and logger.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;              /**< Logger config object. */
    powermux2_cfg_t powermux2_cfg;  /**< Click config object.  */

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

    powermux2_cfg_setup( &powermux2_cfg );
    POWERMUX2_MAP_MIKROBUS( powermux2_cfg, MIKROBUS_1 );
    err_t init_flag  = powermux2_init( &powermux2, &powermux2_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> This is an example that demonstrates the use of the Power MUX 2 Click board™. 
> In this example, we set the resistance of the 100kΩ 
> for the output current limit of approximately 1.23A 
> and lower the resistance to 50kΩ, which fits the current limit of 2.25 A. 
> Results are sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) {
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " Resistance    ~ 100 kOhm \r\n" );
    log_printf( &logger, " Current Limit ~   1.23 A \r\n" );
    powermux2_set_resistance( &powermux2, 100 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " Resistance    ~  50 kOhm \r\n" );
    log_printf( &logger, " Current Limit ~   2.25 A \r\n" );
    powermux2_set_resistance( &powermux2, 50 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PowerMux2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all Mikroelektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
