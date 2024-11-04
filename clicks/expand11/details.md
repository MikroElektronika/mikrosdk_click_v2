
---
# Expand 11 Click

> Expand 11 Click is a compact add-on board that contains a multi-port I/O expander. This board features the TCA9536, a general-purpose remote I/O expansion for most microcontroller families from Texas Instruments. The TCA9536 comes in a 4-port configuration and allows easy addition of I/O through a standard I2C serial interface. Each port is user-configurable to either a logic input or logic output by writing to the I/O configuration register bits. The data for each input or output is kept in the corresponding input or output register. There is an additional special function register that port P3, in addition to its standard I/O function, can also configure as an interrupt feature.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand11_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/expand-11-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Expand 11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Expand 11 Click driver.

#### Standard key functions :

- `expand11_cfg_setup` Config Object Initialization function.
```c
void expand11_cfg_setup ( expand11_cfg_t *cfg );
```

- `expand11_init` Initialization function.
```c
err_t expand11_init ( expand11_t *ctx, expand11_cfg_t *cfg );
```

- `expand11_default_cfg` Click Default Configuration function.
```c
err_t expand11_default_cfg ( expand11_t *ctx );
```

#### Example key functions :

- `expand11_set_pin_direction` This function sets the direction of the selected pins.
```c
err_t expand11_set_pin_direction ( expand11_t *ctx, uint8_t direction, uint8_t pin_mask );
```

- `expand11_set_all_pins_value` This function sets the value of all output pins.
```c
err_t expand11_set_all_pins_value ( expand11_t *ctx, uint8_t set_mask );
```

- `expand11_read_port_value` This function reads the value of the port input pins.
```c
err_t expand11_read_port_value ( expand11_t *ctx, uint8_t *data_out );
```

## Example Description

> This example demonstrates the use of Expand 11 Click board by setting and reading the port state.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which sets the pins P0-P1 as output and P2-P3 as input.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand11_cfg_t expand11_cfg;  /**< Click config object. */

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
    expand11_cfg_setup( &expand11_cfg );
    EXPAND11_MAP_MIKROBUS( expand11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand11_init( &expand11, &expand11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND11_ERROR == expand11_default_cfg ( &expand11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Toggles all output pins and then reads the status of the whole port and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    static uint16_t pin_num = EXPAND11_PIN_0_MASK;
    uint8_t port_value = 0;
    if ( EXPAND11_OK == expand11_set_all_pins_value( &expand11, pin_num ) )
    {
        if ( EXPAND11_OK == expand11_read_port_value( &expand11, &port_value ) )
        {
            log_printf( &logger, " PORT STATUS \r\n" );
            log_printf( &logger, "  P0: %u\r\n", ( uint16_t ) ( port_value & EXPAND11_PIN_0_MASK ) );
            log_printf( &logger, "  P1: %u\r\n", ( uint16_t ) ( ( port_value & EXPAND11_PIN_1_MASK ) >> 1 ) );
            log_printf( &logger, "  P2: %u\r\n", ( uint16_t ) ( ( port_value & EXPAND11_PIN_2_MASK ) >> 2 ) );
            log_printf( &logger, "  P3: %u\r\n\n", ( uint16_t ) ( ( port_value & EXPAND11_PIN_3_MASK ) >> 3 ) );
            pin_num = ( ~pin_num ) & EXPAND11_ALL_PINS_MASK;
        }
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
