\mainpage Main Page

---
# Terminal 2 click

> Terminal 2 Click is an adapter Click board™ used as a mikroBUS™ socket expansion board. It provides an easy and elegant solution for adding the external connection capability to the Click board™, plugged on a mikroBUS™ socket. Featuring two 9-position 2.54mm pitch terminal blocks makes it an easy way to expand the development system's connectivity with the mikroBUS™ socket while keeping the bus free to use with any Click board™.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/terminal2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/terminal-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the Terminal 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Terminal 2 Click driver.

#### Standard key functions :

- `terminal2_cfg_setup` Config Object Initialization function.
```c
void terminal2_cfg_setup ( terminal2_cfg_t *cfg );
```

- `terminal2_init` Initialization function.
```c
err_t terminal2_init ( terminal2_t *ctx, terminal2_cfg_t *cfg );
```

#### Example key functions :

- `terminal2_set_all_pins_high` This function sets all terminal pins to high logic level.
```c
void terminal2_set_all_pins_high ( terminal2_t *ctx );
```

- `terminal2_set_all_pins_low` This function sets all terminal pins to low logic level.
```c
void terminal2_set_all_pins_low ( terminal2_t *ctx );
```

- `terminal2_toggle_pin` This function toggles the specified pin logic level.
```c
void terminal2_toggle_pin ( digital_out_t *pin );
```

## Example Description

> This example demonstates the use of Terminal 2 click board by toggling all its pins.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and sets all pins to low logic state.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    terminal2_cfg_t terminal2_cfg;  /**< Click config object. */

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
    terminal2_cfg_setup( &terminal2_cfg );
    TERMINAL2_MAP_MIKROBUS( terminal2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == terminal2_init( &terminal2, &terminal2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    terminal2_set_all_pins_low ( &terminal2 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Toggles all pins from mikroBUS one by one in the span of 1 second between each pin toggle.

```c
void application_task ( void )
{
    /**< Array of pins object addresses. */
    static digital_out_t *pin_addr[ 12 ] =
    {
        &terminal2.mosi,    // 0 MOSI
        &terminal2.miso,    // 1 MISO
        &terminal2.sck,     // 2 SCK
        &terminal2.cs,      // 3 CS
        &terminal2.rst,     // 4 RST
        &terminal2.an,      // 5 AN
        &terminal2.pwm,     // 6 PWM
        &terminal2.int_pin, // 7 INT
        &terminal2.tx_pin,  // 8 TX
        &terminal2.rx_pin,  // 9 RX
        &terminal2.scl,     // 10 SCL
        &terminal2.sda      // 11 SDA
    };
    static uint8_t pin_num = 0;
    log_printf( &logger, " Toggling pin: %u\r\n", ( uint16_t ) pin_num );
    terminal2_toggle_pin ( pin_addr[ pin_num ] );
    Delay_ms ( 1000 );
    terminal2_toggle_pin ( pin_addr[ pin_num ] );
    
    pin_num++;
    if ( 12 == pin_num )
    {
        pin_num = 0;
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Terminal2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
