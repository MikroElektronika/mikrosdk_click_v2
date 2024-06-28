\mainpage Main Page

---
# Battery Source click

> Battery Source Click is a compact add-on board designed to boost power from a battery for portable applications. This board features the TPS81256, a high-efficiency step-up converter from Texas Instruments. The board boosts input voltage (2.5V to 5.5V) to 5V/1A on a USB Type-C connector. It operates at a 4MHz switching frequency, enters Power-Save mode at light loads, and reduces supply current to 43μA during light load operation. The board supports over 3W output power and has an input current of less than 1µA in shutdown mode, maximizing battery life.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/batterysource_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/battery-source-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2024.
- **Type**          : GPIO type


# Software Support

We provide a library for the Battery Source Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Battery Source Click driver.

#### Standard key functions :

- `batterysource_cfg_setup` Config Object Initialization function.
```c
void batterysource_cfg_setup ( batterysource_cfg_t *cfg );
```

- `batterysource_init` Initialization function.
```c
err_t batterysource_init ( batterysource_t *ctx, batterysource_cfg_t *cfg );
```

#### Example key functions :

- `batterysource_set_output` This function is used to set output state of Battery Source click board.
```c
void batterysource_set_output ( batterysource_t *ctx, uint8_t output_state );
```

## Example Description

> This example demonstrates the use of Battery Source Click board, 
 by changing state of the output.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and disables the output.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    batterysource_cfg_t batterysource_cfg;  /**< Click config object. */

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
    batterysource_cfg_setup( &batterysource_cfg );
    BATTERYSOURCE_MAP_MIKROBUS( batterysource_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == batterysource_init( &batterysource, &batterysource_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    batterysource_set_output( &batterysource, BATTERYSOURCE_DISABLE_OUTPUT );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Enabling output for 5 seconds, then disabling it for 5 seconds.

```c
void application_task ( void ) 
{
    log_printf( &logger, " Output is enabled \r\n" );
    batterysource_set_output( &batterysource, BATTERYSOURCE_ENABLE_OUTPUT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Output is disabled \r\n" );
    batterysource_set_output( &batterysource, BATTERYSOURCE_DISABLE_OUTPUT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BatterySource

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
