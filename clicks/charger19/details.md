
---
# Charger 19 Click

> Charger 19 Click is a compact add-on board that contains a battery charger. This board features the nPM1100, an integrated power management IC from Nordic Semiconductor. It has a highly efficient DC/DC buck regulator with automatic selection between hysteretic and PWM modes.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/charger19_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/charger-19-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : ADC type


# Software Support

We provide a library for the Charger 19 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Charger 19 Click driver.

#### Standard key functions :

- `charger19_cfg_setup` Config Object Initialization function.
```c
void charger19_cfg_setup ( charger19_cfg_t *cfg );
```

- `charger19_init` Initialization function.
```c
err_t charger19_init ( charger19_t *ctx, charger19_cfg_t *cfg );
```

- `charger19_default_cfg` Click Default Configuration function.
```c
err_t charger19_default_cfg ( charger19_t *ctx );
```

#### Example key functions :

- `charger19_set_vout` Charger 19 set output voltage function.
```c
err_t charger19_set_vout ( charger19_t *ctx, uint8_t vout_sel );
```

- `charger19_set_ship_mode` Charger 19 set Ship mode function.
```c
void charger19_set_ship_mode ( charger19_t *ctx, uint8_t ship_sel );
```

- `charger19_get_vbat` Charger 19 get battery voltage function.
```c
err_t charger19_get_vbat ( charger19_t *ctx, float *vbat );
```

## Example Description

> This example demonstrates the use of Charger 19 Click board by enabling the device
  and then reading and displaying the battery voltage.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables the device, sets the output 
  voltage to 3 V.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    charger19_cfg_t charger19_cfg;  /**< Click config object. */

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
    charger19_cfg_setup( &charger19_cfg );
    CHARGER19_MAP_MIKROBUS( charger19_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == charger19_init( &charger19, &charger19_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER19_ERROR == charger19_default_cfg ( &charger19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Tracking charging status, reading battery voltage.

```c

void application_task ( void ) 
{
    float voltage = 0;
    if ( CHARGER19_OK == charger19_get_vbat ( &charger19, &voltage ) ) 
    {
        log_printf( &logger, " Battery Voltage : %.3f[V]\r\n\n", voltage );
        Delay_ms ( 1000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger19

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
