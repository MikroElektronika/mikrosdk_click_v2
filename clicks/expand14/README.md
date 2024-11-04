\mainpage Main Page

---
# Expand 14 Click

> Expand 14 Click is a compact add-on board that contains a multi-port I/O expander. This board features the CAT9555, a CMOS device that provides 16-bit parallel input/output port expansion from ON Semiconductor. The CAT9555 contains two 8-bit configuration ports (input or output), input, output, and polarity inversion registers, alongside an I2C-compatible serial interface. Any of the sixteen I/Os can be configured as an input or output by writing to the configuration register. It also features an active-low interrupt output, indicating to the host controller that an input state has been changed.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand14_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/expand-14-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Expand 14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Expand 14 Click driver.

#### Standard key functions :

- `expand14_cfg_setup` Config Object Initialization function.
```c
void expand14_cfg_setup ( expand14_cfg_t *cfg );
```

- `expand14_init` Initialization function.
```c
err_t expand14_init ( expand14_t *ctx, expand14_cfg_t *cfg );
```

- `expand14_default_cfg` Click Default Configuration function.
```c
err_t expand14_default_cfg ( expand14_t *ctx );
```

#### Example key functions :

- `expand14_set_pin_direction` This function sets the direction of the selected pins.
```c
err_t expand14_set_pin_direction ( expand14_t *ctx, uint8_t direction, uint8_t port, uint8_t pin_mask );
```

- `expand14_set_all_pins_value` This function sets the value of all output pins.
```c
err_t expand14_set_all_pins_value ( expand14_t *ctx, uint8_t set_mask );
```

- `expand14_read_port_value` This function reads the value of the selected port input pins.
```c
err_t expand14_read_port_value ( expand14_t *ctx, uint8_t port, uint8_t *data_out );
```

## Example Description

> This example demonstrates the use of Expand 14 Click board by setting and reading the ports state.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which sets the port 0 as output and the port 1 as input.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand14_cfg_t expand14_cfg;  /**< Click config object. */

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
    expand14_cfg_setup( &expand14_cfg );
    EXPAND14_MAP_MIKROBUS( expand14_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand14_init( &expand14, &expand14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND14_ERROR == expand14_default_cfg ( &expand14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Sets the pins of the port 0 and then reads the status of both ports and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    uint8_t port_value = 0;
    for ( uint16_t pin_num = EXPAND14_PIN_0_MASK; pin_num <= EXPAND14_PIN_7_MASK; pin_num <<= 1 )
    {
        expand14_set_all_pins_value( &expand14, pin_num );
        
        expand14_read_port_value( &expand14, EXPAND14_PORT_0, &port_value );
        log_printf( &logger, " Status port 0 (output): 0x%.2X\r\n", ( uint16_t ) port_value );
        
        expand14_read_port_value( &expand14, EXPAND14_PORT_1, &port_value );
        log_printf( &logger, " Status port 1 (input) : 0x%.2X\r\n\n", ( uint16_t ) port_value );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
