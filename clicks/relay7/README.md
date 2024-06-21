\mainpage Main Page

---
# Relay 7 click

> Relay 7 Click is a compact add-on board for precise load control and monitoring applications. This board features four CRR05-1As, a CRR series reed relay from Standex Electronics, well-known for its ultra-miniature SMD design and high insulation resistance. These four relays each have four load connection terminals and orange LED indicators that signal the operational status, ensuring clear and immediate feedback. These relays are highly reliable and come in a rugged thermoset over-molded package with ceramic substrate and a typical 1013Ω insulation resistance. They support a coil voltage of 5VDC and switching capabilities up to 170VDC/0.5A/10W. It is ideally suited for test and measurement (ATE) equipment, instrumentation, and telecommunications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/relay7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/relay-7-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Relay 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Relay 7 Click driver.

#### Standard key functions :

- `relay7_cfg_setup` Config Object Initialization function.
```c
void relay7_cfg_setup ( relay7_cfg_t *cfg );
```

- `relay7_init` Initialization function.
```c
err_t relay7_init ( relay7_t *ctx, relay7_cfg_t *cfg );
```

- `relay7_default_cfg` Click Default Configuration function.
```c
err_t relay7_default_cfg ( relay7_t *ctx );
```

#### Example key functions :

- `relay7_set_relay` This function sets the desired state of the selected relay.
```c
err_t relay7_set_relay ( relay7_t *ctx, uint8_t relay_sel, relay7_relay_state_t state );
```

- `relay7_reset_device` This function performs a hardware reset of the device.
```c
void relay7_reset_device ( relay7_t *ctx );
```

- `relay7_get_interrupt` This function returns the interrupt pin logic state.
```c
uint8_t relay7_get_interrupt ( relay7_t *ctx );
```

## Example Description

> This example demonstrates the use of the Relay 7 click board by toggling the relay state.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    relay7_cfg_t relay7_cfg;  /**< Click config object. */

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
    relay7_cfg_setup( &relay7_cfg );
    RELAY7_MAP_MIKROBUS( relay7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == relay7_init( &relay7, &relay7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RELAY7_ERROR == relay7_default_cfg ( &relay7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application toggles the state of all relays every 5 seconds. 
> The results are sent to the UART terminal, where you can monitor their changes.

```c
void application_task ( void ) 
{
    for ( uint8_t relay_sel = RELAY7_SEL_REL1; relay_sel <= RELAY7_SEL_REL4; relay_sel++ )
    {
        if ( RELAY7_OK == relay7_set_relay( &relay7, relay_sel, relay_state ) )
        {
            log_printf( &logger, " Relay %d ", ( uint16_t ) relay_sel );
            if ( RELAY7_STATE_OPEN == relay_state )
            {
                log_printf( &logger, " normally open state\r\n" );
            }
            else
            {
                log_printf( &logger, " normally close state\r\n" );
            }
        }
        Delay_ms ( 1000 );
    }
    relay_state = ~relay_state;
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Relay7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
