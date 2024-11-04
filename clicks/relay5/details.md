
---
# Relay 5 Click

> Relay 5 Click is a compact add-on board with general-purpose relays that any host MCU can control. This board features three J1031C3VDC.15S, a high-current single-pole double-throw (SPDT) signal relays controlled by the PCA9538A, a low-voltage 8-bit I/O port expander from NXP Semiconductors. Highly sensitive, the J1031C3VDC.15S offers a low coil power consumption in a small, lightweight package with PC pin mounting. It comes with a dimension of 12.5x7.5x10 millimeters (LxWxH) and a 1C contact arrangement with a coil voltage of 3VDC, providing a maximum switching voltage of 125VAC/60VDC.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/relay5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/relay-5-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Relay 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Relay 5 Click driver.

#### Standard key functions :

- `relay5_cfg_setup` Config Object Initialization function.
```c
void relay5_cfg_setup ( relay5_cfg_t *cfg );
```

- `relay5_init` Initialization function.
```c
err_t relay5_init ( relay5_t *ctx, relay5_cfg_t *cfg );
```

- `relay5_default_cfg` Click Default Configuration function.
```c
err_t relay5_default_cfg ( relay5_t *ctx );
```

#### Example key functions :

- `relay5_set_relay1_open` This function sets the relay 1 to normally open state by setting the RL1 pin to low logic level.
```c
err_t relay5_set_relay1_open ( relay5_t *ctx );
```

- `relay5_set_relay1_close` This function sets the relay 1 to normally close state by setting the RL1 pin to high logic level.
```c
err_t relay5_set_relay1_close ( relay5_t *ctx );
```

- `relay5_switch_relay1` This function switches the relay 1 state by toggling the RL1 pin logic level.
```c
err_t relay5_switch_relay1 ( relay5_t *ctx );
```

## Example Description

> This example demonstrates the use of Relay 5 Click board by toggling the relays state.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    relay5_cfg_t relay5_cfg;  /**< Click config object. */

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
    relay5_cfg_setup( &relay5_cfg );
    RELAY5_MAP_MIKROBUS( relay5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == relay5_init( &relay5, &relay5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RELAY5_ERROR == relay5_default_cfg ( &relay5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Switches all relays state every 5 seconds and displays the state on the USB UART.

```c
void application_task ( void )
{
    relay5_set_relay1_open ( &relay5 );
    log_printf( &logger, " Relay 1 set to normally open state\r\n" );
    relay5_set_relay2_close ( &relay5 );
    log_printf( &logger, " Relay 2 set to normally close state\r\n" );
    relay5_set_relay3_open ( &relay5 );
    log_printf( &logger, " Relay 3 set to normally open state\r\n\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    relay5_set_relay1_close ( &relay5 );
    log_printf( &logger, " Relay 1 set to normally close state\r\n" );
    relay5_set_relay2_open ( &relay5 );
    log_printf( &logger, " Relay 2 set to normally open state\r\n" );
    relay5_set_relay3_close ( &relay5 );
    log_printf( &logger, " Relay 3 set to normally close state\r\n\n" );
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
- Click.Relay5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
