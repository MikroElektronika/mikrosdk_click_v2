\mainpage Main Page

---
# Expand 10 click

> Expand 10 Click is a compact add-on board that contains a multi-port I/O expander. This board features the PCAL6524, a 24-bit general-purpose I/O expander providing remote I/O expansion for most MCU’s families via the Fast-mode Plus I2C-serial interface from NXP Semiconductors.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/expand-10-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Expand10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Expand10 Click driver.

#### Standard key functions :

- `expand10_cfg_setup` Config Object Initialization function.
```c
void expand10_cfg_setup ( expand10_cfg_t *cfg );
```

- `expand10_init` Initialization function.
```c
err_t expand10_init ( expand10_t *ctx, expand10_cfg_t *cfg );
```

- `expand10_default_cfg` Click Default Configuration function.
```c
err_t expand10_default_cfg ( expand10_t *ctx );
```

#### Example key functions :

- `expand10_set_pin_direction` This function sets the direction of the selected pins.
```c
err_t expand10_set_pin_direction ( expand10_t *ctx, uint8_t direction, uint8_t port, uint8_t pin_mask );
```

- `expand10_set_pin_value` This function sets the value of the selected pins.
```c
err_t expand10_set_pin_value ( expand10_t *ctx, uint8_t port, uint8_t clr_mask, uint8_t set_mask );
```

- `expand10_read_port_value` This function reads the value of the selected port input pins.
```c
err_t expand10_read_port_value ( expand10_t *ctx, uint8_t port, uint8_t *data_out );
```

## Example Description

> This example demonstrates the use of Expand 10 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which sets the first two ports as output and the third port as input with pull-down enabled.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    expand10_cfg_t expand10_cfg;  /**< Click config object. */

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
    expand10_cfg_setup( &expand10_cfg );
    EXPAND10_MAP_MIKROBUS( expand10_cfg, MIKROBUS_1 );
    err_t init_flag = expand10_init( &expand10, &expand10_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    init_flag = expand10_default_cfg ( &expand10 );
    if ( EXPAND10_ERROR == init_flag ) 
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Sets the pins of the first two ports and then reads and displays the status of all ports on the USB UART approximately once per second.

```c

void application_task ( void )
{
    uint8_t port_value = 0;
  
    for ( uint16_t pin_num = EXPAND10_PIN_0_MASK; pin_num <= EXPAND10_PIN_7_MASK; pin_num <<= 1 )
    {
        expand10_set_all_pins_value( &expand10, pin_num );
        
        expand10_read_port_value( &expand10, EXPAND10_PORT_0, &port_value );
        log_printf( &logger, " Status P0 (output): 0x%.2X\r\n", ( uint16_t ) port_value );
        
        expand10_read_port_value( &expand10, EXPAND10_PORT_1, &port_value );
        log_printf( &logger, " Status P1 (output): 0x%.2X\r\n", ( uint16_t ) port_value );
        
        expand10_read_port_value( &expand10, EXPAND10_PORT_2, &port_value );
        log_printf( &logger, " Status P2 (input) : 0x%.2X\r\n\r\n", ( uint16_t ) port_value );
        Delay_ms( 1000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
