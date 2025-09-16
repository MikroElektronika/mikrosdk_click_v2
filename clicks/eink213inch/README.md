
---
# eINK 2.13 inch display

> [eINK 2.13 inch display](https://www.mikroe.com/?pid_product=MIKROE-3810) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3810&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application demonstrates the use of eINK Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.eInk213Inch

### Example Key Functions

- `eink213inch_cfg_setup` Config Object Initialization function.
```c
void eink213inch_cfg_setup ( eink213inch_cfg_t *cfg ); 
```

- `eink213inch_init` Initialization function.
```c
err_t eink213inch_init ( eink213inch_t *ctx, eink213inch_cfg_t *cfg );
```

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

### Application Init

> Initializes the driver and configures the Click board for 2.13 inch eINK display.
After that, if the TEXT mode is supported, shows a desired text messages on the display.

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

### Note

> Due to insuficient RAM memory, only the IMAGE mode is supported with 8-bit PIC and AVR microcontrollers.

## Application Output

This application can be interfaced and monitored in two ways:
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
