
---
# LCD Mono Click

> [LCD Mono Click](https://www.mikroe.com/?pid_product=MIKROE-3789) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3789&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This application sets text on lcd displey.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LcdMono

### Example Key Functions

- `lcdmono_cfg_setup` Config Object Initialization function.
```c
void lcdmono_cfg_setup ( lcdmono_cfg_t *cfg ); 
```

- `lcdmono_init` Initialization function.
```c
err_t lcdmono_init ( lcdmono_t *ctx, lcdmono_cfg_t *cfg );
```

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

### Note

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
