
---
# Charger 27 click

> Charger 27 Click is a compact add-on board that provides a single-cell charging solution. This board features the MP2639B, a Li-Ion or Li-Polymer switching charger from MPS. It is a highly integrated, flexible switch-mode battery charging management device for a single-cell battery for various portable applications. It uses a 4.5V up to 16V external input voltage to provide up to 2A of programmable charging current.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/charger27_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/charger-27-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the Charger 27 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Charger 27 Click driver.

#### Standard key functions :

- `charger27_cfg_setup` Config Object Initialization function.
```c
void charger27_cfg_setup ( charger27_cfg_t *cfg );
```

- `charger27_init` Initialization function.
```c
err_t charger27_init ( charger27_t *ctx, charger27_cfg_t *cfg );
```

#### Example key functions :

- `charger27_set_mode` This function is used for the charge or discharge mode selection.
```c
err_t charger27_set_mode ( charger27_t *ctx, uint8_t mode );
```

- `charger27_check_chg_completion` This function checks the charging completion indicator state.
```c
uint8_t charger27_check_chg_completion ( charger27_t *ctx );
```

- `charger27_check_input_supply` This function checks valid input supply indicator state.
```c
uint8_t charger27_check_input_supply ( charger27_t *ctx );
```

## Example Description

> This example demonstrates the use of the Charger 27 click board 
> by enabling charge or discharge mode and 
> indicating valid input supply and charging completion.

**The demo application is composed of two sections :**

### Application Init

> Initialization of GPIO module and log UART.
> After driver initialization, the app sets charge mode.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger27_cfg_t charger27_cfg;  /**< Click config object. */

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
    charger27_cfg_setup( &charger27_cfg );
    CHARGER27_MAP_MIKROBUS( charger27_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == charger27_init( &charger27, &charger27_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( CHARGER27_OK == charger27_set_mode( &charger27, CHARGER27_MODE_CHARGE ) )
    {
        log_printf( &logger, " > Charge mode <\r\n" );
        Delay_ms ( 100 );
    }
}
```

### Application Task

> The demo application operates as a switching charger to charge a 1S battery 
> from a wide input power range of 5V to 16V, which can cover a USB PD voltage level.
> The app also checks if the charging has been completed or is suspended.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( CHARGER27_CHG_CHARGE == charger27_check_chg_completion( &charger27 ) )
    {
        log_printf( &logger, " Charging.\r\n" );
        Delay_ms ( 1000 );
    }
    else
    {
        log_printf( &logger, " Charging has completed or is suspended.\r\n" );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger27

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
