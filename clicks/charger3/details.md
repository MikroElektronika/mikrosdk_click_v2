
---
# Charger 3 Click

> Charger 3 Click is a compact add-on board that represents a standalone battery charger with thermal regulation. This board features the TP4056, a complete constant-current/constant-voltage linear charger for single-cell lithium-ion batteries from NanJing Top Power ASIC Corp.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/charger3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/charger-3-click)

---


#### Click library

- **Author**        : Stefan Nikolic
- **Date**          : nov 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Charger3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
This library contains API for Charger3 Click driver.
```

#### Standard key functions :

- Config Object Initialization function.
```
void charger3_cfg_setup ( charger3_cfg_t *cfg );
```

- Initialization function.
```
CHARGER3_RETVAL charger3_init ( charger3_t *ctx, charger3_cfg_t *cfg );
```

- Click Default Configuration function.
```
void charger3_default_cfg ( charger3_t *ctx );
```

#### Example key functions :

- Charger 3 enable write function.
```
void charger3_enable_write ( charger3_t *ctx );
```

- Charger 3 set current function.
```
uint8_t charger3_set_current ( charger3_t *ctx, float curr_value );
```

- Charger 3 calculate digipot resistance function.
```
float charger3_calc_digipot_res ( charger3_t *ctx );
```

## Examples Description

This example demonstrates the utilization of Charger 3 Click.

**The demo application is composed of two sections :**

### Application Init

The application init sets up the UART LOG and I2C communication
drivers. The default configuration disables write protection
and sets the operation mode to charging.

```
void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger3_cfg_t charger3_cfg;  /**< Click config object. */

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

    charger3_cfg_setup( &charger3_cfg );
    CHARGER3_MAP_MIKROBUS( charger3_cfg, MIKROBUS_1 );
    err_t init_flag = charger3_init( &charger3, &charger3_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    Delay_ms ( 100 );
    charger3_default_cfg ( &charger3 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ------------------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

Task consists of two operations. First, the desired battery
charging current is set by the user. Since setting the current
doesn't implicitly reveals the resistance, the value
of AD5175 digipot is directly read from the RDAC register,
calculated and displayed on the uart log.

```
void application_task ( void ) {
    float result;
    
    charger3_set_current( &charger3, 0.4 );
    Delay_ms ( 1000 );
    result = charger3_calc_digipot_res( &charger3 );
    log_printf( &logger, " Digipot res value: %.2f ohm\r\n", result );
    log_printf( &logger, " ------------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Note

While the resistance of the AD5175 can be directly set and read,
the total resistance value on the PROG pin should be accounted for
( this means an additional 1kohm in series ) setting of the
battery charging current.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
