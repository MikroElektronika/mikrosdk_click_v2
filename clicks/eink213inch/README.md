\mainpage Main Page
 
---
# eINK 2.13 inch display

eINK click is an adapter Click board™, used to interface a compatible eINK display with the host MCU. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eink_click_bundle213inch.png">
</p>

[click Product page](https://www.mikroe.com/e-paper-bundle-2)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the eInk213Inch Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for eInk213Inch Click driver.

#### Standard key functions :

- `eink213inch_cfg_setup` Config Object Initialization function.
```c
void eink213inch_cfg_setup ( eink213inch_cfg_t *cfg ); 
```

- `eink213inch_init` Initialization function.
```c
err_t eink213inch_init ( eink213inch_t *ctx, eink213inch_cfg_t *cfg );
```

#### Example key functions :

- `eink213inch_set_lut` Set LUT table
```c
void eink213inch_set_lut ( eink213inch_t *ctx, const uint8_t *lut, uint8_t n_bytes );
```

- `eink213inch_text` Function for draw text on the screen
```c
void eink213inch_text ( eink213inch_t *ctx, char *text, eink213inch_set_text_t *text_set );
```

- `eink213inch_display_image` Display image function
```c
void eink213inch_display_image ( eink213inch_t *ctx, const uint8_t* image_buffer );
```

## Examples Description

> This application demonstrates the use of eINK click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and configures the click board for 2.13 inch eINK display.
> After that, if the TEXT mode is supported, shows a desired text messages on the display.

```c

void application_init ( void )
{
    eink213inch_cfg_t cfg;
    eink213inch_font_t cfg_font;
    eink213inch_set_text_t set_text;

    //  Click initialization.
    eink213inch_cfg_setup( &cfg );
    EINK213INCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eink213inch_init( &eink213inch, &cfg );

    eink213inch_start_config( &eink213inch );
    eink213inch_set_lut( &eink213inch, &eink213inch_lut_table[ 0 ], 70 );
    Delay_ms ( 1000 );

#ifndef IMAGE_MODE_ONLY
    cfg_font.p_font = &guiFont_Tahoma_18_Regular[ 0 ]; 
    cfg_font.color = EINK213INCH_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK213INCH_FO_HORIZONTAL;  
    eink213inch_set_font( &eink213inch, &cfg_font );

    set_text.n_char = 4;
    set_text.text_x = 5;
    set_text.text_y = 50;
    eink213inch_text( &eink213inch, &demo_text[ 0 ], &set_text );
    
    cfg_font.p_font = &guiFont_Tahoma_10_Regular[ 0 ]; 
    cfg_font.color = EINK213INCH_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK213INCH_FO_HORIZONTAL; 
    eink213inch_set_font( &eink213inch, &cfg_font );

    set_text.n_char = 7;
    set_text.text_x = 5;
    set_text.text_y = 90;
    eink213inch_text( &eink213inch, &demo_text1[ 0 ], &set_text );
    
    cfg_font.p_font = &guiFont_Tahoma_8_Regular[ 0 ]; 
    cfg_font.color = EINK213INCH_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK213INCH_FO_HORIZONTAL; 
    eink213inch_set_font( &eink213inch, &cfg_font );

    set_text.n_char = 9;
    set_text.text_x = 5;
    set_text.text_y = 120;
    eink213inch_text( &eink213inch, &demo_text2[ 0 ], &set_text );
#endif
    Delay_ms ( 1000 );
}
  
```

### Application Task

> Draws four demo images to the display with a one-second delay between each drawing.

```c

void application_task ( void )
{
    eink213inch_display_image( &eink213inch, &demoImage_light[ 0 ] );
    Delay_1sec( );
    eink213inch_display_image( &eink213inch, &demoImage_dark[ 0 ] );
    Delay_1sec( );
    eink213inch_display_image( &eink213inch, &demoImage_light_180[ 0 ] );
    Delay_1sec( );
    eink213inch_display_image( &eink213inch, &demoImage_dark_180[ 0 ] );
    Delay_1sec( );
} 

```

## Note

> Due to insuficient RAM memory, only the IMAGE mode is supported with 8-bit PIC and AVR microcontrollers.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.eInk213Inch

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
