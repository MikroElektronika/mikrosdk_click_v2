
---
# 8800 Retro Click

> [8800 Retro Click](https://www.mikroe.com/?pid_product=MIKROE-4771) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4771&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of 8800 Retro Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.8800Retro

### Example Key Functions

- `c8800retro_cfg_setup` Config Object Initialization function.
```c
void c8800retro_cfg_setup ( c8800retro_cfg_t *cfg );
```

- `c8800retro_init` Initialization function.
```c
err_t c8800retro_init ( c8800retro_t *ctx, c8800retro_cfg_t *cfg );
```

- `c8800retro_default_cfg` Click Default Configuration function.
```c
err_t c8800retro_default_cfg ( c8800retro_t *ctx );
```

- `c8800retro_display_char` This function displays a single character from the predefined charset (IBM BIOS 8x8 font array).
```c
err_t c8800retro_display_char ( c8800retro_t *ctx, uint8_t char_index );
```

- `c8800retro_get_keypad` This function reads KEYA and KEYB registers and stores the register's inverted value to the keypad variable.
```c
err_t c8800retro_get_keypad ( c8800retro_t *ctx, uint16_t *keypad );
```

- `c8800retro_display_string` This function scrolls a desired string on LEDs.
```c
err_t c8800retro_display_string ( c8800retro_t *ctx, uint8_t scroll_mode, uint16_t scroll_speed_ms, uint8_t *text );
```

### Application Init

> Initializes the driver and issues the Click default configuration, then asks the user to select the demo example using the on-board KeyPad.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;                /**< Logger config object. */
    c8800retro_cfg_t c8800retro_cfg;  /**< Click config object. */
    
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
    c8800retro_cfg_setup( &c8800retro_cfg );
    C8800RETRO_MAP_MIKROBUS( c8800retro_cfg, MIKROBUS_1 );
    err_t init_flag = c8800retro_init( &c8800retro, &c8800retro_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    c8800retro_default_cfg( &c8800retro );
    c8800retro_select_demo_example( &c8800retro );
}
```

### Application Task

> There are 4 different demo examples: KeyPad 4x4, Full charset, Text, and Image.
> This function will run the previously selected demo example in the loop. 
> The user can always switch the example by pressing the button D4 three times in a row. 
> In order to run the demo examples successfully, please follow the instructions logged on the USB UART.

```c
void application_task ( void )
{
    switch ( demo_example )
    {
        case DEMO_KEYPAD4x4:
        {
            c8800retro_demo_keypad4x4 ( &c8800retro );
            break;
        }
        case DEMO_FULL_CHARSET:
        {
            c8800retro_demo_full_charset ( &c8800retro );
            break;
        }
        case DEMO_TEXT:
        {
            c8800retro_demo_text ( &c8800retro, C8800RETRO_SCROLL_HORIZONTAL_LEFT, 
                                                C8800RETRO_SCROLL_SPEED_MEDIUM, 
                                                c8800retro_demo_string );
            break;
        }
        case DEMO_IMAGE:
        {
            c8800retro_demo_image ( &c8800retro, c8800retro_demo_logo_mikroe );
            break;
        }
        default:
        {
            break;
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
