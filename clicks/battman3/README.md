\mainpage Main Page

---
# BATT-MAN 3 click

> BATT-MAN 3 Click is a compact add-on board representing an advanced battery management solution. This board features the ADP5350, a power management IC with inductive boost LED, and three LDO regulators from Analog Devices. This I2C programmable board supports USB optimized for USB voltage input. It combines one high-performance buck regulator for single Li-Ion/Li-Ion polymer battery charging, a fuel gauge, a highly programmable boost regulator for LED backlight illumination, and three 150mA LDO regulators.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/battman3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/batt-man-3-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Oct 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the BATT-MAN3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BATT-MAN3 Click driver.

#### Standard key functions :

- `battman3_cfg_setup` Config Object Initialization function.
```c
void battman3_cfg_setup ( battman3_cfg_t *cfg );
```

- `battman3_init` Initialization function.
```c
err_t battman3_init ( battman3_t *ctx, battman3_cfg_t *cfg );
```

- `battman3_default_cfg` Click Default Configuration function.
```c
err_t battman3_default_cfg ( battman3_t *ctx );
```

#### Example key functions :

- `battman3_get_battery_voltage` Read battery voltage level.
```c
err_t battman3_get_battery_voltage ( battman3_t *ctx, float *vout );
```

- `battman3_set_ldo_vout` Set voltage output on LDO.
```c
err_t battman3_set_ldo_vout ( battman3_t *ctx, battman3_ldo_t ldo, battman3_ldo_vout_t vout );
```

- `battman3_set_charge_termination_voltage` Set charge termination voltage.
```c
err_t battman3_set_charge_termination_voltage ( battman3_t *ctx, float voltage );
```

## Example Description

> This example showcases ability of device to charge battery,
and outputs and supply 4 different devices with 3 LDO's and
1 boost channel.

**The demo application is composed of two sections :**

### Application Init

> Initialization of the communication modules(UART, I2C) and 3 additional
input pins(power good, battery ok, and interrupt). Configures device
to enable charging, battery voltage monitoring, sets charging termination
to 3.7V, charging threshold to 3.1V and dead battery to 2.5V. Enables all
3 LDO's( channel 1 -> 3.3V, channel 2 -> 1.5V, and channel 3 -> 2.5V ). 

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battman3_cfg_t battman3_cfg;  /**< Click config object. */

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
    battman3_cfg_setup( &battman3_cfg );
    BATTMAN3_MAP_MIKROBUS( battman3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == battman3_init( &battman3, &battman3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BATTMAN3_ERROR == battman3_default_cfg ( &battman3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint8_t temp_data = 0;
    
    battman3_reg_read( &battman3, BATTMAN3_REG_MANUFACTURE_AND_MODEL_ID, &temp_data );
    log_printf( &logger, " > ID: 0x%.2X\r\n", ( uint16_t )temp_data );
    battman3_reg_read( &battman3, BATTMAN3_REG_SILICON_REVSION, &temp_data );
    log_printf( &logger, " > REV: 0x%.2X\r\n", ( uint16_t )temp_data );
    
    //Charging voltage termination
    battman3_set_charge_termination_voltage( &battman3, 3.7 );
    //Charging voltage threshold
    battman3_set_charge_voltage_threshold( &battman3, BATTMAN3_VTRK_DEAD_2p5V, 3.1 );
    //LDO 1
    battman3_set_ldo_state( &battman3, BATTMAN3_LDO1, BATTMAN3_ENABLE );
    battman3_set_ldo_vout( &battman3, BATTMAN3_LDO1, BATTMAN3_LDO_3p30V );
    //LDO 2
    battman3_set_ldo_state( &battman3, BATTMAN3_LDO2, BATTMAN3_ENABLE );
    battman3_set_ldo_vout( &battman3, BATTMAN3_LDO2, BATTMAN3_LDO_1p50V );
    //LDO 3
    battman3_set_ldo_state( &battman3, BATTMAN3_LDO3, BATTMAN3_ENABLE );
    battman3_set_ldo_vout( &battman3, BATTMAN3_LDO3, BATTMAN3_LDO_2p50V );
    
    log_info( &logger, " Application Task " );
    Delay_ms( 500 );
}

```

### Application Task

> Reads battery voltage level and logs it. Besides that reads status and logs
every change on charging and battery status. If power good flag occurs(PGD 
pin goes low) disables LDO's, and reenables them when battery is full(when 
battery reaches charging termination voltage).

```c

void application_task ( void ) 
{
    static uint8_t counter = 0;
    static uint8_t ldo_enable = 1;
    float vbat = 0; 
    
    if ( !battman3_get_power_good( &battman3 ) && ldo_enable )
    {
        battman3_ldo( BATTMAN3_DISABLE );
        log_printf( &logger, " > Power is not good - LDO disabled\r\n" );
        ldo_enable = 0;
    }
    else if ( battman3_get_power_good( &battman3 ) && !ldo_enable )
    {
        battman3_ldo( BATTMAN3_ENABLE );
        log_printf( &logger, " > Power is good - LDO enabled\r\n" );
        ldo_enable = 1;
    }
    
    battman3_charge_status( );
    
    if ( counter >= LOG_THRESHOLD_3SEC )
    {
        counter = 0;
        battman3_get_battery_voltage( &battman3, &vbat );
        log_printf( &logger, " > Battery voltage: %.2f\r\n", vbat );  
        log_printf( &logger, "****************************************************\r\n" );
    }
    counter++;
    Delay_ms( 100 );
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BATT-MAN3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
