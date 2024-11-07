
---
# Expand 18 Click

> Expand 18 Click is a compact add-on board used for expanding the I/O capabilities of various microcontroller (MCU) systems. This board features the PCAL9714, an ultra-low-voltage 14-bit SPI I/O expander from NXP. This board supports both 3.3V and 5V logic levels, features integrated level shifting for mixed-voltage systems, and operates via a high-speed 5MHz SPI interface. Additionally, it offers Agile I/O capabilities such as programmable output drive strength, latchable inputs, and interrupt management. Expand 18 Click is ideal for interfacing MCUs with sensors, keypads, and push buttons in power-sensitive applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand18_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/expand-18-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : SPI type


# Software Support

We provide a library for the Expand 18 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Expand 18 Click driver.

#### Standard key functions :

- `expand18_cfg_setup` Config Object Initialization function.
```c
void expand18_cfg_setup ( expand18_cfg_t *cfg );
```

- `expand18_init` Initialization function.
```c
err_t expand18_init ( expand18_t *ctx, expand18_cfg_t *cfg );
```

- `expand18_default_cfg` Click Default Configuration function.
```c
err_t expand18_default_cfg ( expand18_t *ctx );
```

#### Example key functions :

- `expand18_set_pin_direction` This function sets the direction of the selected pins.
```c
err_t expand18_set_pin_direction ( expand18_t *ctx, uint8_t direction, uint8_t port, uint8_t pin_mask );
```

- `expand18_set_all_pins_value` This function sets the value of all output pins.
```c
err_t expand18_set_all_pins_value ( expand18_t *ctx, uint8_t set_mask );
```

- `expand18_read_port_value` This function reads the value of the selected port input pins.
```c
err_t expand18_read_port_value ( expand18_t *ctx, uint8_t port, uint8_t *data_out );
```

## Example Description

> This example demonstrates the use of Expand 18 Click board by setting and reading the ports state.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which sets the port 0 as output and the port 1 as input with pull-down enabled.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand18_cfg_t expand18_cfg;  /**< Click config object. */

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
    expand18_cfg_setup( &expand18_cfg );
    EXPAND18_MAP_MIKROBUS( expand18_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == expand18_init( &expand18, &expand18_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND18_ERROR == expand18_default_cfg ( &expand18 ) )
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
    for ( uint16_t pin_num = EXPAND18_PIN_0_MASK; pin_num <= EXPAND18_PIN_7_MASK; pin_num <<= 1 )
    {
        expand18_set_all_pins_value( &expand18, pin_num );
        
        expand18_read_port_value( &expand18, EXPAND18_PORT_0, &port_value );
        log_printf( &logger, " Status port 0 (output): 0x%.2X\r\n", ( uint16_t ) port_value );
        
        expand18_read_port_value( &expand18, EXPAND18_PORT_1, &port_value );
        log_printf( &logger, " Status port 1 (input) : 0x%.2X\r\n\n", ( uint16_t ) port_value );
        Delay_ms( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand18

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
