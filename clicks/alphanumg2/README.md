
---
# AlphaNum G 2 Click

> [AlphaNum G 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5903) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5903&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the AlphaNum G 2 Click board&trade; 
> by writing and displaying the desired alphanumeric characters.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AlphaNumG2

### Example Key Functions

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

- `alphanumg2_display_character` AlphaNum G 2 display character function.
```c
err_t alphanumg2_display_character ( alphanumg2_t *ctx, uint8_t left_char, uint16_t left_brightness, uint8_t right_char, uint16_t right_brightness );
```

- `alphanumg2_set_led_output` AlphaNum G 2 set LED output function.
```c
err_t alphanumg2_set_led_output ( alphanumg2_t *ctx, uint16_t seg_bit_mask, alphanumg2_dot_t seg_dot, uint16_t brightness );
```

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
> and capital alphabet letters, on both alphanumeric segments of the Click. 
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

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
