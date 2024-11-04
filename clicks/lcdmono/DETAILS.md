
---
# LCD Mono Click

LCD Mono Click is a Click board™ that uses the LS013B7DH03 LCD display from Sharp which combined with the EFM32, from Silicon Labs, and its energy saving capabilities creates a powerful display application.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lcdmono_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lcd-mono-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the LcdMono Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LcdMono Click driver.

#### Standard key functions :

- `lcdmono_cfg_setup` Config Object Initialization function.
```c
void lcdmono_cfg_setup ( lcdmono_cfg_t *cfg ); 
```

- `lcdmono_init` Initialization function.
```c
err_t lcdmono_init ( lcdmono_t *ctx, lcdmono_cfg_t *cfg );
```

#### Example key functions :

- `lcdmono_draw_text` Draw text on the screen
```c
void lcdmono_draw_text ( lcdmono_t *ctx, uint8_t * __generic_ptr text_buf, lcdmono_text_settings_t *tx_set, uint8_t end_mode );
```

- `lcdmono_display_power` Display Power State
```c
void lcdmono_display_power ( lcdmono_t *ctx, uint8_t ctrl );
```

- `lcdmono_display_reset` Reset procedure
```c
void lcdmono_display_reset ( lcdmono_t *ctx );
```

## Examples Description

> This application sets text on lcd displey.

**The demo application is composed of two sections :**

### Application Init 

> Driver initialization - Starting LCD Mono display. Print text to the display by changing font size ...

```c

void application_init ( void )
{
    lcdmono_cfg_t cfg;
    lcdmono_text_settings_t tx_set;
    lcdmono_font_t font_cfg;

    //  Click initialization.
    lcdmono_cfg_setup( &cfg );
    LCDMONO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lcdmono_init( &lcdmono, &cfg );

    lcdmono_display_reset( &lcdmono );
    lcdmono_clear( &lcdmono );

    // Background color for all text
    tx_set.bg_color = LCDMONO_COLOR_WHITE;
    // Display text
    font_cfg.this_font = lcdmono_font_tahoma_16;
    lcdmono_set_font( &lcdmono, &font_cfg );

    tx_set.len = 3;
    tx_set.start_cord_x = 25;
    tx_set.start_cord_y = 15;
    lcdmono_draw_text( &lcdmono, demo_text_lcd, &tx_set, LCDMONO_REFRESH_TEXT_BUFFER | 
                                                         LCDMONO_CHECK_NEW_TEXT );

    font_cfg.this_font = lcdmono_font_tahoma_8;
    lcdmono_set_font( &lcdmono, &font_cfg );

    tx_set.len = 4;
    tx_set.start_cord_x = 60;
    tx_set.start_cord_y = 50;
    lcdmono_draw_text( &lcdmono, demo_text_mono, &tx_set, LCDMONO_CHECK_NEW_TEXT );

    tx_set.len = 9;
    tx_set.start_cord_x = 10;
    tx_set.start_cord_y = 80;
    lcdmono_draw_text( &lcdmono, demo_text_128x128px, &tx_set, LCDMONO_REFRESH_DISPLAY_END );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    lcdmono_clear( &lcdmono );
}
  
```

### Application Task

> Drawing an image to the display every 3 second.

```c

void application_task ( void )
{
    lcdmono_draw_frame( &lcdmono, demo_img_mikroe_light );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    lcdmono_draw_frame( &lcdmono, demo_img_mikroe );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    lcdmono_draw_frame( &lcdmono, demo_img_logo_light );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    lcdmono_draw_frame( &lcdmono, demo_img_logo );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

## Note

>  - Create Image:
>      Save the image in resolution of 128x128 px with the extension (monochrome bmp) ...
>      Upload the image to Image2Lcd program
>      Set parameters to:
>             1. Output file type : C array
>             2. Scan Mode : Horisontal scan
>             3. Bits Pixel : monochrome
>             4. Max width and height : 128x128
>             5. Check only MSB first
>             6. Check Reverse color and adjust Normal type
>  The image to be generated should contain about 2048 bytes ...
>  Insert the image into the file lcdmono_image.h
> 
>  - Create Font:
>      Close existing project, open a new VTFT project
>      Add label and adjust text font
>      Generate source code
>      Copy the font from resource.c file to this project in file lcdmono_font.h

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LcdMono

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
