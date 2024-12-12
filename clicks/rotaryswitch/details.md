
---
# Rotary Switch Click

> Rotary Switch Click is a compact add-on board for applications requiring precise rotary input. This board is based on the RDS6-16S-1065-1-SMT, a 16-position notched cap surface-mount rotary DIP switch from Same Sky. This switch features continuous 360-degree actuator rotation, a 2.54mm pin pitch, and robust construction with a contact resistance of 80mΩ and a maximum operating torque of 700gf*cm, ensuring reliable operation for up to 10,000 steps. The board supports the innovative Click Snap feature, allowing the rotary switch to operate autonomously when detached, providing flexibility in various implementations.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rotaryswitch_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rotary-switch-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Rotary Switch Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Rotary Switch Click driver.

#### Standard key functions :

- `rotaryswitch_cfg_setup` Config Object Initialization function.
```c
void rotaryswitch_cfg_setup ( rotaryswitch_cfg_t *cfg );
```

- `rotaryswitch_init` Initialization function.
```c
err_t rotaryswitch_init ( rotaryswitch_t *ctx, rotaryswitch_cfg_t *cfg );
```

- `rotaryswitch_default_cfg` Click Default Configuration function.
```c
err_t rotaryswitch_default_cfg ( rotaryswitch_t *ctx );
```

#### Example key functions :

- `rotaryswitch_get_position` This function reads the rotary switch position.
```c
err_t rotaryswitch_get_position ( rotaryswitch_t *ctx, uint8_t *position );
```

- `rotaryswitch_write_reg` This function writes a desired data to the selected register by using I2C serial interface.
```c
err_t rotaryswitch_write_reg ( rotaryswitch_t *ctx, uint8_t reg, uint8_t data_in );
```

- `rotaryswitch_read_reg` This function reads data from the selected register by using I2C serial interface.
```c
err_t rotaryswitch_read_reg ( rotaryswitch_t *ctx, uint8_t reg, uint8_t *data_out );
```

## Example Description

> This example demonstrates the use of Rotary Switch Click board by reading and displaying the switch position on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rotaryswitch_cfg_t rotaryswitch_cfg;  /**< Click config object. */

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
    rotaryswitch_cfg_setup( &rotaryswitch_cfg );
    ROTARYSWITCH_MAP_MIKROBUS( rotaryswitch_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rotaryswitch_init( &rotaryswitch, &rotaryswitch_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ROTARYSWITCH_ERROR == rotaryswitch_default_cfg ( &rotaryswitch ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the switch position every 20ms and displays it on the USB UART on position change.

```c
void application_task ( void )
{
    static uint8_t old_position = 0xFF;
    uint8_t position = 0;
    if ( ( ROTARYSWITCH_OK == rotaryswitch_get_position ( &rotaryswitch, &position ) ) && 
         ( position != old_position ) )
    {
        Delay_ms ( 20 );
        // Double-check for debouncing
        if ( ( ROTARYSWITCH_OK == rotaryswitch_get_position ( &rotaryswitch, &position ) ) && 
             ( position != old_position ) )
        {
            old_position = position;
            log_printf ( &logger, " Switch position: %.1X\r\n", ( uint16_t ) position );
        }
    }
    Delay_ms ( 20 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RotarySwitch

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
