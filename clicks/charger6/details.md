
---
# Charger 6 click

Charger 6 Click is a compact add-on board that represents a single-cell battery charger. This board features the BQ25601, an I2C controlled battery charger for high input voltage and narrow voltage DC power path management from Texas Instruments. This buck charger supports USB, and it’s optimized for USB voltage input. The low impedance power path optimizes switch-mode operation efficiency, reduces battery charging time, and extends battery life during discharge. It also has a programmable current limiting, allowing it to use an external power supply rated up to 13.5V. This Click board™ is suitable as a Li-Ion and Li-polymer battery charger for portable devices and accessories, power tools, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/charger6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/charger-6-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Charger6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Charger6 Click driver.

#### Standard key functions :

- `charger6_cfg_setup` Config Object Initialization function.
```c
void charger6_cfg_setup ( charger6_cfg_t *cfg );
```

- `charger6_init` Initialization function.
```c
CHARGER6_RETVAL charger6_init ( charger6_t *ctx, charger6_cfg_t *cfg );
```

- `charger6_default_cfg` Click Default Configuration function.
```c
void charger6_default_cfg ( charger6_t *ctx );
```

#### Example key functions :

- `charger6_set_system_minimum_voltage` Charger 6 set system minimum voltage function.
```c
err_t charger6_set_system_minimum_voltage ( charger6_t *ctx, uint16_t sys_min_voltage );
```

- `charger6_set_fast_charge_current` Charger 6 set fast charge current function.
```c
err_t charger6_set_fast_charge_current ( charger6_t *ctx, uint16_t fast_chg_current );
```

- `charger6_get_status` Charger 6 get status function.
```c
err_t charger6_get_status ( charger6_t *ctx, charger6_status_t *chg_status );
```

## Example Description

> This library contains API for the Charger 6 Click driver.
> The library contains drivers to enable/disable battery charging, 
> set current limit, set system min voltage, set fast charge current,
> set charge voltage, etc.

**The demo application is composed of two sections :**

### Application Init

> Initializes I2C driver and set default configuration:
> input current limit set to 500 mA, system minimum voltage to 3500 mV,
> fast charge current set to 360 mA, charge voltage to 4112 mV and
> enable battery charging. 

```c

void application_init ( void ) {
    log_cfg_t log_cfg;            /**< Logger config object. */
    charger6_cfg_t charger6_cfg;  /**< Click config object. */

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

    charger6_cfg_setup( &charger6_cfg );
    CHARGER6_MAP_MIKROBUS( charger6_cfg, MIKROBUS_1 );
    err_t init_flag = charger6_init( &charger6, &charger6_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    charger6_default_cfg ( &charger6 );
    log_info( &logger, " Application Task " );
    Delay_ms( 1000 );

    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, " Set Current Limit   :  500 mA \r\n" );
    charger6_set_input_current_limit( &charger6, 500 );
    Delay_ms( 100 );
    
    log_printf( &logger, " Set Sys Min Voltage : 3500 mV \r\n" );
    charger6_set_system_minimum_voltage( &charger6, 3500 );
    Delay_ms( 100 );
    
    log_printf( &logger, " Set Fast Chg Current:  360 mA \r\n" );
    charger6_set_fast_charge_current( &charger6, 360 );
    Delay_ms( 100 );
    
    log_printf( &logger, " Set Charge Voltage  : 4112 mV \r\n" );
    charger6_set_charge_voltage( &charger6, 4112 );
    Delay_ms( 100 );
    
    log_printf( &logger, " >> Enable Battery Charging << \r\n" );
    charger6_enable_battery_charging( &charger6 );
    Delay_ms( 1000 );
    
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "       >>>   Status   <<<      \r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
}

```

### Application Task

This example monitors the operation of the Charger 6 Click and all its charging states. 
 * The user can observe information such as charging status, selected mode, 
 * charging current value, and the momentary value 
 * of the supply voltage relative to the battery voltage.
 * Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) {
    charger6_get_status( &charger6, &chg_status );
    Delay_ms( 100 );
    
    display_power_good_status( );
    Delay_ms( 100 );
    
    display_chrg_status( );
    Delay_ms( 100 );
    
    display_bat_status( );
    Delay_ms( 100 );
    
    display_chrg_fault_status( );
    Delay_ms( 100 );
    
    display_vsys_status( );
    log_printf( &logger, "-------------------------------\r\n" );
    Delay_ms( 2000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
