
---
# Charger 25 Click

> Charger 25 Click is a compact add-on board that contains a battery charger. This board features the BQ25792, a buck-boost battery charger with a dual-input selector, and a USB PD3.0 OTG output from Texas Instruments. It is fully integrated for 1-4 cell Li-Ion and Li-Polymer batteries. Designed specifically for USB applications, it also includes a Narrow voltage DC (NVDC) power path management in which the system is regulated at a voltage slightly higher than the battery voltage without being allowed to drop below the minimum system voltage.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/charger25_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/charger-25-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Charger 25 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Charger 25 Click driver.

#### Standard key functions :

- `charger25_cfg_setup` Config Object Initialization function.
```c
void charger25_cfg_setup ( charger25_cfg_t *cfg );
```

- `charger25_init` Initialization function.
```c
err_t charger25_init ( charger25_t *ctx, charger25_cfg_t *cfg );
```

- `charger25_default_cfg` Click Default Configuration function.
```c
err_t charger25_default_cfg ( charger25_t *ctx );
```

#### Example key functions :

- `charger25_get_vbat` Charger 25 get VBAT function.
```c
err_t charger25_get_vbat ( charger25_t *ctx, uint16_t *vbat );
```

- `charger25_get_status` Charger 25 get charging status function.
```c
err_t charger25_get_status ( charger25_t *ctx, charger25_status_t *status );
```

- `charger25_get_vbat_lim` Charger 25 get battery voltage limit function.
```c
err_t charger25_get_vbat_lim ( charger25_t *ctx, uint16_t *vtg_lim );
```

## Example Description

> This example demonstrates the use of Charger 25 Click board™ 
> by enabling battery charging and displaying battery voltage and charging status.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger25_cfg_t charger25_cfg;  /**< Click config object. */

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
    charger25_cfg_setup( &charger25_cfg );
    CHARGER25_MAP_MIKROBUS( charger25_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == charger25_init( &charger25, &charger25_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER25_ERROR == charger25_default_cfg ( &charger25 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads and displays the results of the battery voltage, 
> minimal system voltage, battery voltage limit and charging status.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static uint16_t vtg_data = 0;
    if ( CHARGER25_OK == charger25_get_status ( &charger25, &status ) )
    {
        charger25_display_status( );
    }
    Delay_ms ( 100 );
    
    if ( CHARGER25_OK == charger25_get_vbat( &charger25, &vtg_data ) )
    {
        log_printf( &logger, " VBAT: %u [mV]\r\n", vtg_data );
    }
    Delay_ms ( 100 );
    
    if ( CHARGER25_OK == charger25_get_vsys_min( &charger25, &vtg_data ) )
    {
        log_printf( &logger, " VMIN: %u [mV]\r\n", vtg_data );
    }
    Delay_ms ( 100 );
    
    if ( CHARGER25_OK == charger25_get_vbat_lim( &charger25, &vtg_data ) )
    {
        log_printf( &logger, " VLIM: %u [mV]\r\n", vtg_data );
    }
    log_printf( &logger, " ----------------\r\n" );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger25

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
