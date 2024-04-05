
---
# Expand 12 click

> Expand 12 Click is a compact add-on board that contains a multi-port I/O expander. This board features the MAX7300, a general-purpose I/O expander providing remote I/O expansion for most MCU’s families from Maxim Integrated, now part of Analog Devices. The MAX7300 comes in a 28-port configuration and allows easy addition of I/O through a standard I2C serial interface. Each port is user-configurable to either a logic input or logic output, capable of sinking 10mA and sourcing 4.5mA.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/expand-12-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Expand12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Expand12 Click driver.

#### Standard key functions :

- `expand12_cfg_setup` Config Object Initialization function.
```c
void expand12_cfg_setup ( expand12_cfg_t *cfg );
```

- `expand12_init` Initialization function.
```c
err_t expand12_init ( expand12_t *ctx, expand12_cfg_t *cfg );
```

- `expand12_default_cfg` Click Default Configuration function.
```c
err_t expand12_default_cfg ( expand12_t *ctx );
```

#### Example key functions :

- `expand12_set_pin_direction` This function sets the direction of the selected pin.
```c
err_t expand12_set_pin_direction ( expand12_t *ctx, uint8_t pin, uint8_t direction );
```

- `expand12_set_pin_value` This function sets the logic level of the selected pin.
```c
err_t expand12_set_pin_value ( expand12_t *ctx, uint8_t pin, uint8_t pin_value );
```

- `expand12_read_all_pins_value` This function reads all pins logic levels.
```c
err_t expand12_read_all_pins_value ( expand12_t *ctx, uint32_t *pins_value );
```

## Example Description

> This example demonstrates the use of Expand 12 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which sets 
> the first three ports (pins 4-23) as output and the fourth port (pins 24-31) as input with pull-ups.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand12_cfg_t expand12_cfg;  /**< Click config object. */

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
    expand12_cfg_setup( &expand12_cfg );
    EXPAND12_MAP_MIKROBUS( expand12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand12_init( &expand12, &expand12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND12_ERROR == expand12_default_cfg ( &expand12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Sets the pins of the first three ports and then reads the status of all pins and 
> displays the result on the USB UART approximately every 100 miliseconds.

```c

void application_task ( void )
{
    static uint8_t port_value = 0;
    static uint32_t pins_status = 0;
    
    expand12_set_port_value( &expand12, EXPAND12_PORT_4_7, EXPAND12_ALL_PINS, port_value );
    expand12_set_port_value( &expand12, EXPAND12_PORT_8_15, EXPAND12_ALL_PINS, port_value );
    expand12_set_port_value( &expand12, EXPAND12_PORT_16_23, EXPAND12_ALL_PINS, port_value++ );
        
    expand12_read_all_pins_value( &expand12, &pins_status );
    log_printf( &logger, " Pins status (32-bit) : 0x%.8LX\r\n\n", pins_status );
    Delay_ms ( 100 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
