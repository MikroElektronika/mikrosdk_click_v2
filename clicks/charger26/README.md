\mainpage Main Page

---
# Charger 26 click

> Charger 26 Click is a compact add-on board that provides a single-cell charging solution. This board features the MAX1811, a USB-powered Li+ charger from Analog Devices. The charger uses an internal FET to deliver the battery up to 500mA charging current. It has pre-conditioning that soft-starts a near-dead battery cell before charging. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/charger26_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/charger-26-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the Charger 26 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Charger 26 Click driver.

#### Standard key functions :

- `charger26_cfg_setup` Config Object Initialization function.
```c
void charger26_cfg_setup ( charger26_cfg_t *cfg );
```

- `charger26_init` Initialization function.
```c
err_t charger26_init ( charger26_t *ctx, charger26_cfg_t *cfg );
```

- `charger26_default_cfg` Click Default Configuration function.
```c
void charger26_default_cfg ( charger26_t *ctx );
```

#### Example key functions :

- `charger26_set_vsel` Charger 26 select charger voltage function.
```c
void charger26_set_vsel ( charger26_t *ctx, uint8_t vout_sel );
```

- `charger26_set_isel` Charger 26 select charger current function.
```c
void charger26_set_isel ( charger26_t *ctx, uint8_t iout_sel );
```

- `charger26_get_chg_state` Charger 26 chg pin reading function.
```c
uint8_t charger26_get_chg_state ( charger26_t *ctx );
```

## Example Description

> This example demonstrates the use of Charger 26 click board by enabling the device
  and then reading and displaying the charger status.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables the device, sets the output 
  voltage to 4.2 V and charging current to 100 mA.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger26_cfg_t charger26_cfg;  /**< Click config object. */

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
    charger26_cfg_setup( &charger26_cfg );
    CHARGER26_MAP_MIKROBUS( charger26_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == charger26_init( &charger26, &charger26_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    charger26_default_cfg ( &charger26 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Connect input power and battery. \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Enableing output. \r\n" );
    charger26_enable_output ( &charger26, CHARGER26_ENABLE_OUTPUT );
    
    while ( CHARGER26_PIN_STATE_LOW != charger26_get_chg_state( &charger26 ) )
    {
        log_printf( &logger, " Check connection. \r\n" );
        Delay_ms ( 1000 );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Tracking charging status, as soon as charging stops, device output is disabled.

```c
void application_task ( void ) 
{
    if ( CHARGER26_PIN_STATE_LOW == charger26_get_chg_state( &charger26 ) )
    {
        log_printf( &logger, " Battery is charging. \r\n" );
    }
    else
    {
        log_printf( &logger, " Battery isn't charging, disabling output. \r\n" );
        charger26_enable_output ( &charger26, CHARGER26_DISABLE_OUTPUT );
        for ( ; ; );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger26

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
