\mainpage Main Page

---
# Charger 16 click

Charger 16 Click is a compact add-on board that represents a single-cell battery charger. This board features the LT1571, a constant-current/constant-voltage battery charger with preset voltage and termination flag from Analog Devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/charger16_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/charger-16-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the Charger16 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Charger16 Click driver.

#### Standard key functions :

- `charger16_cfg_setup` Config Object Initialization function.
```c
void charger16_cfg_setup ( charger16_cfg_t *cfg );
```

- `charger16_init` Initialization function.
```c
err_t charger16_init ( charger16_t *ctx, charger16_cfg_t *cfg );
```

- `charger16_default_cfg` Click Default Configuration function.
```c
err_t charger16_default_cfg ( charger16_t *ctx );
```

#### Example key functions :

- `charger16_enable_charging` Charger 16 enable charging function.
```c
err_t charger16_enable_charging ( charger16_t *ctx );
```

- `charger16_disable_charging` Charger 16 disable charging function.
```c
err_t charger16_disable_charging ( charger16_t *ctx );
```

## Example Description

> This library contains API for the Charger 16 Click driver.
> This demo application shows use of a Charger 16 Click board™.

**The demo application is composed of two sections :**

### Application Init

> Initialization of GPIO module and log UART.
> After driver initialization the app set default settings.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    charger16_cfg_t charger16_cfg;  /**< Click config object.  */

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

    charger16_cfg_setup( &charger16_cfg );
    CHARGER16_MAP_MIKROBUS( charger16_cfg, MIKROBUS_1 );
    if ( charger16_init( &charger16, &charger16_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    charger16_default_cfg ( &charger16 );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

```

### Application Task

> This is an example that shows the use of an Charger 16 Click board™.
> The app turns the battery charge on and off every 10 seconds.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{
    log_printf( &logger, "-----------------\r\n" );
    log_printf( &logger, " Enable charging \r\n" );
    charger16_enable_charging( &charger16 );
    Delay_ms( 10000 );

    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, " Disable charging \r\n" );
    charger16_disable_charging( &charger16 );
    Delay_ms( 10000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger16

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
