\mainpage Main Page

---
# Expand 3 Click

> Expand 3 Click is a compact add-on board providing general-purpose I/O expansion. This board features the DS2408, an 8-channel programmable I/O expander from Analog Devices. The DS2408 has a factory-lasered 64-bit registration number, enabling multiple Expand 3 Click boards™ to be connected on the same data line, communicating with the host MCU through a standard Dallas Semiconductor 1-Wire interface (15.3kbps or 100kbps). PIO outputs are configured as open-drain and provide a maximum on-resistance of 100Ω.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/expand-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : One Wire type


# Software Support

We provide a library for the Expand 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Expand 3 Click driver.

#### Standard key functions :

- `expand3_cfg_setup` Config Object Initialization function.
```c
void expand3_cfg_setup ( expand3_cfg_t *cfg );
```

- `expand3_init` Initialization function.
```c
err_t expand3_init ( expand3_t *ctx, expand3_cfg_t *cfg );
```

- `expand3_default_cfg` Click Default Configuration function.
```c
err_t expand3_default_cfg ( expand3_t *ctx );
```

#### Example key functions :

- `expand3_write_state` This function writes data to the PIO output-latch state register which controls the open-drain output transistors of the PIO channels.
```c
err_t expand3_write_state ( expand3_t *ctx, uint8_t state );
```

- `expand3_read_last_state` This function reads the latest data written to the PIO using
```c
err_t expand3_read_last_state ( expand3_t *ctx, uint8_t *last_state );
```

- `expand3_read_current_state` This function reads the current logic state of the PIO pins.
```c
err_t expand3_read_current_state ( expand3_t *ctx, uint8_t *curr_state );
```

## Example Description

> This example demonstrates the use of Expand 3 Click board by setting and reading the port state.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand3_cfg_t expand3_cfg;  /**< Click config object. */

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
    expand3_cfg_setup( &expand3_cfg );
    EXPAND3_MAP_MIKROBUS( expand3_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == expand3_init( &expand3, &expand3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND3_ERROR == expand3_default_cfg ( &expand3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Writes a counter data to the port output pins and reads the status of the same port input pins approximately every 500ms. All data are displayed on the USB UART.

```c
void application_task ( void )
{
    static uint8_t out_state = 0;
    static uint8_t in_state = 0;
    if ( ( EXPAND3_OK == expand3_write_state ( &expand3, out_state ) ) && 
         ( EXPAND3_OK == expand3_read_last_state ( &expand3, &out_state ) ) )
    {
        log_printf( &logger, " Output state: 0x%.2X\r\n\n", out_state++ );
    }
    if ( EXPAND3_OK == expand3_read_current_state ( &expand3, &in_state ) )
    {
        log_printf( &logger, " Input state: 0x%.2X\r\n\n", in_state );
    }
    Delay_ms ( 500 );
}
```

## Note

> The PIO pins are in the open-drain mode, therefore a pull-up resistor must be added to each pin.
This Click board can be used in a combination with an EasyLED [MIKROE-571] and EasyPULL [MIKROE-575] boards.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
