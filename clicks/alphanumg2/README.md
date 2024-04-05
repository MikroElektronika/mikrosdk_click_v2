\mainpage Main Page

---
# AlphaNum G 2 click

> AlphaNum G 2 Click is a compact add-on board that represents an easy solution for adding numeric or hexadecimal displays to your application. This board features the LTP-3862, a dual-digit 16-segment alphanumeric green display from Lite-ON. It is a 0.3” (7.62mm) display with black face and white segments. The LED segments use common anodes, and besides segments, the decimal point (DP) dot is also available.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/alphanumg2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/alphanum-g-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the AlphaNum G 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for AlphaNum G 2 Click driver.

#### Standard key functions :

- `alphanumg2_cfg_setup` Config Object Initialization function.
```c
void alphanumg2_cfg_setup ( alphanumg2_cfg_t *cfg );
```

- `alphanumg2_init` Initialization function.
```c
err_t alphanumg2_init ( alphanumg2_t *ctx, alphanumg2_cfg_t *cfg );
```

- `alphanumg2_default_cfg` Click Default Configuration function.
```c
err_t alphanumg2_default_cfg ( alphanumg2_t *ctx );
```

#### Example key functions :

- `alphanumg2_display_character` AlphaNum G 2 display character function.
```c
err_t alphanumg2_display_character ( alphanumg2_t *ctx, uint8_t left_char, uint16_t left_brightness, uint8_t right_char, uint16_t right_brightness );
```

- `alphanumg2_set_led_output` AlphaNum G 2 set LED output function.
```c
err_t alphanumg2_set_led_output ( alphanumg2_t *ctx, uint16_t seg_bit_mask, alphanumg2_dot_t seg_dot, uint16_t brightness );
```

## Example Description

> This example demonstrates the use of the AlphaNum G 2 Click board™ 
> by writing and displaying the desired alphanumeric characters.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    alphanumg2_cfg_t alphanumg2_cfg;  /**< Click config object. */

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
    alphanumg2_cfg_setup( &alphanumg2_cfg );
    ALPHANUMG2_MAP_MIKROBUS( alphanumg2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == alphanumg2_init( &alphanumg2, &alphanumg2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ALPHANUMG2_ERROR == alphanumg2_default_cfg ( &alphanumg2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application displays digits from '0' to '9', 
> symbols: colon, semicolon, less-than, equals-to, greater-than, question mark, at sign 
> and capital alphabet letters, on both alphanumeric segments of the click. 
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    log_printf( &logger, " %c %c\r\n", character, character + 1 );
    if ( ALPHANUMG2_OK == alphanumg2_display_character( &alphanumg2, 
                                                        character, ALPHANUMG2_BRIGHTNESS_MAX, 
                                                        character + 1, ALPHANUMG2_BRIGHTNESS_MAX ) )
    {
        character++;
        if ( ASCII_CHARACTER_UPPERCASE_Z <= character )
        {
            character = ASCII_CHARACTER_DIGIT_0;
            log_printf( &logger, "------------------------\r\n" );
            Delay_ms ( 1000 );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AlphaNumG2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
