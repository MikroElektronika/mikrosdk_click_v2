\mainpage Main Page

---
# LED Ring 2 click

> LED Ring 2 Click is a compact add-on board that provides 
> a circular-shaped electronic lighting solution. 
> This board features three I2C-configurable high-performance LED matrix drivers, 
> the LP5862 from Texas Instruments. 
> The LP5862 integrates 18 constant current sinks for driving 18 yellow LEDs. 
> With the help of two additional LP5862 drivers, it is possible to realize, 
> as shown on this board, a solution of 54 yellow LEDs arranged in a circular pattern. 
> In addition, it also provides excellent PWM dimming effects.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ledring2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/led-ring-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the LED Ring 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LED Ring 2 Click driver.

#### Standard key functions :

- `ledring2_cfg_setup` Config Object Initialization function.
```c
void ledring2_cfg_setup ( ledring2_cfg_t *cfg );
```

- `ledring2_init` Initialization function.
```c
err_t ledring2_init ( ledring2_t *ctx, ledring2_cfg_t *cfg );
```

- `ledring2_default_cfg` Click Default Configuration function.
```c
err_t ledring2_default_cfg ( ledring2_t *ctx );
```

#### Example key functions :

- `ledring2_set_led_brightness` LED Ring 2 set LED brightness function.
```c
err_t ledring2_set_led_brightness ( ledring2_t *ctx, uint8_t led_pos, uint16_t led_brightness );
```

- `ledring2_set_led_pos_state` LED Ring 2 set LED state function.
```c
err_t ledring2_set_led_pos_state ( ledring2_t *ctx, uint8_t led_pos, ledring2_led_state_t led_state );
```

- `ledring2_enable` LED Ring 2 enable function.
```c
err_t ledring2_enable ( ledring2_t *ctx );
```

## Example Description

> This library contains API for LED Ring 2 Click driver.
> The library initializes and defines the I2C bus drivers 
> to write and read data from registers. 
> The library also includes a function for controlling LEDs.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ledring2_cfg_t ledring2_cfg;  /**< Click config object. */

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
    ledring2_cfg_setup( &ledring2_cfg );
    LEDRING2_MAP_MIKROBUS( ledring2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ledring2_init( &ledring2, &ledring2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( LEDRING2_ERROR == ledring2_default_cfg ( &ledring2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, " LED Ring 2 Click\r\n" );
}
```

### Application Task

> This example demonstrates the use of the LED Ring 2 Click board™.
> The demo example controls every LED and changes the LED brightness by PWM,
> increasing its brightness from LED1 to LED54.

```c
void application_task ( void ) 
{
    for ( uint8_t led_pos = 1; led_pos < 55; led_pos++ )
    {
        if ( LEDRING2_OK == ledring2_set_led_brightness( &ledring2, led_pos, ( led_pos * 100 ) + 255 ) )
        {
            ledring2_set_vsync( &ledring2 );
            Delay_ms ( 10 );
        }
    }
    Delay_ms ( 1000 );
    
    for ( uint8_t led_pos = 54; led_pos > 0; led_pos-- )
    {
        if ( LEDRING2_OK == ledring2_set_led_brightness( &ledring2, led_pos, 0 ) )
        {
            ledring2_set_vsync( &ledring2 );
            Delay_ms ( 10 );
        }
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDRing2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
