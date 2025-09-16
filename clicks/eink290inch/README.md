
---
# eINK 2.90 inch display

> [eINK 2.90 inch display](https://www.mikroe.com/?pid_product=MIKROE-3811) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3811&image=1" height=300px>
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
- Click.Eink290Inch

### Example Key Functions

- `eink290inch_cfg_setup` Config Object Initialization function.
```c
void eink290inch_cfg_setup ( eink290inch_cfg_t *cfg ); 
```

- `eink290inch_init` Initialization function.
```c
err_t eink290inch_init ( eink290inch_t *ctx, eink290inch_cfg_t *cfg );
```

- `eink290inch_fill_screen` Function that fills the screen
```c
void eink290inch_fill_screen ( eink290inch_t *ctx, uint8_t color );
```

- `eink290inch_display_image` Display image function
```c
void eink290inch_display_image ( eink290inch_t *ctx, const uint8_t* image_buffer );
```

- `eink290inch_set_font` Set font function
```c
void eink290inch_set_font ( eink290inch_t *ctx, eink290inch_font_t *cfg_font );
```

### Application Init

> Initializes the driver and configures the Click board for 2.90 inch eINK display.
After that, if the TEXT mode is supported, shows a desired text messages on the display.

```c
void application_init ( void )
{
    eink290inch_cfg_t cfg;
    eink290inch_font_t cfg_font;
    eink290inch_set_text_t text_set;

    //  Click initialization.
    eink290inch_cfg_setup( &cfg );
    EINK290INCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eink290inch_init( &eink290inch, &cfg );

    eink290inch_start_config( &eink290inch );
    eink290inch_set_lut( &eink290inch, eink290inch_lut_table, 70 );
    Delay_ms ( 1000 );
    
#ifndef IMAGE_MODE_ONLY
    cfg_font.p_font = &guiFont_Tahoma_18_Regular[ 0 ];
    cfg_font.color = EINK290INCH_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK290INCH_FO_HORIZONTAL;  
    eink290inch_set_font( &eink290inch, &cfg_font );
    text_set.n_char = 4;
    text_set.text_x = 5;
    text_set.text_y = 50;
    eink290inch_text( &eink290inch, &demo_text[ 0 ], &text_set );
    Delay_ms ( 1000 );
    
    cfg_font.p_font = &guiFont_Tahoma_10_Regular[ 0 ];
    cfg_font.color = EINK290INCH_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK290INCH_FO_HORIZONTAL; 
    eink290inch_set_font( &eink290inch, &cfg_font );
    text_set.n_char = 7;
    text_set.text_x = 5;
    text_set.text_y = 90;
    eink290inch_text( &eink290inch, &demo_text1[ 0 ], &text_set );
    Delay_ms ( 1000 );
    
    cfg_font.p_font = &guiFont_Tahoma_8_Regular[ 0 ];
    cfg_font.color = EINK290INCH_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK290INCH_FO_HORIZONTAL; 
    eink290inch_set_font( &eink290inch, &cfg_font );
    text_set.n_char = 9;
    text_set.text_x = 5;
    text_set.text_y = 120;
    eink290inch_text( &eink290inch, &demo_text2[ 0 ], &text_set ); 
    Delay_ms ( 1000 );
#endif
}
```

### Application Task

> Draws four demo images to the display with a one-second delay between each drawing.

```c
void application_task ( void )
{
    eink290inch_display_image( &eink290inch, &demoImage_light[ 0 ] );
    Delay_1sec( );
    eink290inch_display_image( &eink290inch, &demoImage_dark[ 0 ] );
    Delay_1sec( );
    eink290inch_display_image( &eink290inch, &demoImage_light_180[ 0 ] );
    Delay_1sec( );
    eink290inch_display_image( &eink290inch, &demoImage_dark_180[ 0 ] );
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
