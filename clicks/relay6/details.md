
---
# Relay 6 Click

> Relay 6 Click is a compact add-on board for precise load control and monitoring applications. This board features four 9913-05-20TRs, a reed relay from Coto Technology, well-known for its ultra-miniature SMD design, which offers the smallest footprint in the market. These four relays each have four load connection terminals and blue LED indicators that signal the operational status, ensuring clear and immediate feedback.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/relay6_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/relay-6-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Relay 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Relay 6 Click driver.

#### Standard key functions :

- `relay6_cfg_setup` Config Object Initialization function.
```c
void relay6_cfg_setup ( relay6_cfg_t *cfg );
```

- `relay6_init` Initialization function.
```c
err_t relay6_init ( relay6_t *ctx, relay6_cfg_t *cfg );
```

- `relay6_default_cfg` Click Default Configuration function.
```c
err_t relay6_default_cfg ( relay6_t *ctx );
```

#### Example key functions :

- `relay6_reset_port_expander` Relay 6 reset port expander function.
```c
void relay6_reset_port_expander ( relay6_t *ctx );
```

- `relay6_port_expander_write` Relay 6 port expander write register function.
```c
err_t relay6_port_expander_write ( relay6_t *ctx, uint8_t reg, uint8_t data_in );
```

- `relay6_set_relay` Relay 6 set relay state function.
```c
err_t relay6_set_relay ( relay6_t *ctx, uint8_t on_relay, uint8_t off_relay );
```

## Example Description

> This example demonstrates the use of Relay 6 Click board by toggling the relays state.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    relay6_cfg_t relay6_cfg;  /**< Click config object. */

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
    relay6_cfg_setup( &relay6_cfg );
    RELAY6_MAP_MIKROBUS( relay6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == relay6_init( &relay6, &relay6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RELAY6_ERROR == relay6_default_cfg ( &relay6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Switches all relays state every second and displays the state on the USB UART.

```c
void application_task ( void ) 
{
    uint8_t relay_data;
    relay_data = RELAY6_RELAY1_PIN;

    log_printf( &logger, " Turning on only Relay 1 \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = \r\n" );
    relay6_set_relay( &relay6, relay_data, ~relay_data );
    relay_data <<= 1;
    Delay_ms ( 1000 );

    log_printf( &logger, " Turning on only Relay 2 \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = \r\n" );
    relay6_set_relay( &relay6, relay_data, ~relay_data );
    relay_data <<= 1;
    Delay_ms ( 1000 );

    log_printf( &logger, " Turning on only Relay 3 \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = \r\n" );
    relay6_set_relay( &relay6, relay_data, ~relay_data );
    relay_data <<= 1;
    Delay_ms ( 1000 );

    log_printf( &logger, " Turning on only Relay 4 \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = \r\n" );
    relay6_set_relay( &relay6, relay_data, ~relay_data );
    relay_data <<= 1;
    Delay_ms ( 1000 );

}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Relay6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
