
---
# Expand 19 click

> Expand 19 Click is an add-on board that provides additional input/output capabilities for various applications. This board features the TCAL9538, an 8-bit I2C-bus I/O expander from Texas Instruments. The board features eight configurable I/O pins that can be set as inputs or outputs, with polarity inversion, programmable output drive strength, and interrupt functionality for real-time event handling. It operates using a standard 2-wire I2C communication interface, supporting clock frequencies up to 1MHz, and includes an onboard interrupt pin for efficient system integration.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand19_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/expand-19-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Expand 19 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Expand 19 Click driver.

#### Standard key functions :

- `expand19_cfg_setup` Config Object Initialization function.
```c
void expand19_cfg_setup ( expand19_cfg_t *cfg );
```

- `expand19_init` Initialization function.
```c
err_t expand19_init ( expand19_t *ctx, expand19_cfg_t *cfg );
```

- `expand19_default_cfg` Click Default Configuration function.
```c
err_t expand19_default_cfg ( expand19_t *ctx );
```

#### Example key functions :

- `expand19_set_pin_direction` This function sets the direction of the selected pins.
```c
err_t expand19_set_pin_direction ( expand19_t *ctx, uint8_t direction, uint8_t pin_mask );
```

- `expand19_set_all_pins_value` This function sets the value of all output pins.
```c
err_t expand19_set_all_pins_value ( expand19_t *ctx, uint8_t set_mask );
```

- `expand19_read_port_value` This function reads the value of all input pins.
```c
err_t expand19_read_port_value ( expand19_t *ctx, uint8_t *data_out );
```

## Example Description

> This example demonstrates the use of Expand 19 click board by setting and reading the port state.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which sets the pins 0-3 as output and others as input with pull-up enabled.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand19_cfg_t expand19_cfg;  /**< Click config object. */

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
    expand19_cfg_setup( &expand19_cfg );
    EXPAND19_MAP_MIKROBUS( expand19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand19_init( &expand19, &expand19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND19_ERROR == expand19_default_cfg ( &expand19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Sets the output pins and then reads the status of all pins and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    uint8_t port_value = 0;
    for ( uint16_t pin_num = EXPAND19_PIN_0_MASK; pin_num <= EXPAND19_PIN_3_MASK; pin_num <<= 1 )
    {
        expand19_set_all_pins_value( &expand19, pin_num );
        
        expand19_read_port_value( &expand19, &port_value );
        log_printf( &logger, " Port status: 0x%.2X\r\n", ( uint16_t ) port_value );
        
        Delay_ms( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand19

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
