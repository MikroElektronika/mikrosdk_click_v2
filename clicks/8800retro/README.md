\mainpage Main Page

---
# 8800 Retro click

8800 Retro Click is a compact add-on board that simplifies the control of multiple LEDs. This board features the AS1115, compact LED driver for 8x8 display screen programmed via a compatible 2-wire I2C interface from ASM-AG.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/8800retro_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/8800-retro-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the 8800Retro Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 8800Retro Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of 8800 Retro click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and issues the click default configuration, then asks the user to select the demo example using the on-board KeyPad.

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


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.8800Retro

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
