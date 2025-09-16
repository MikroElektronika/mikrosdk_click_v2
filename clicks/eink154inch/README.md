
---
# eINK 1.54 inch display

> [eINK 1.54 inch display](https://www.mikroe.com/?pid_product=MIKROE-3809) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3809&image=1" height=300px>
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
- Click.Eink154Inch

### Example Key Functions

- `eink154inch_cfg_setup` Config Object Initialization function.
```c
void eink154inch_cfg_setup ( eink154inch_cfg_t *cfg ); 
```

- `eink154inch_init` Initialization function.
```c
err_t eink154inch_init ( eink154inch_t *ctx, eink154inch_cfg_t *cfg );
```

- `eink154inch_set_lut` Set LUT table
```c
void eink154inch_set_lut ( eink154inch_t *ctx, const uint8_t *lut, uint8_t n_bytes );
```

- `eink154inch_image` Displays image
```c
void eink154inch_image ( eink154inch_t *ctx, const uint8_t* image_buffer );
```

- `eink154inch_set_font` Set text font
```c
void eink154inch_set_font ( eink154inch_t *ctx, eink154inch_font_t *cfg_font );
```

### Application Init

> Initializes the driver and configures the Click board for 1.54 inch eINK display.
After that, if the TEXT mode is supported, shows a desired text messages on the display.

```c
void application_init ( void )
{
    eink154inch_cfg_t cfg;   
    eink154inch_font_t cfg_font;
    eink154inch_text_set_t text_set;

    //  Click initialization.
    eink154inch_cfg_setup( &cfg );
    EINK154INCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eink154inch_init( &eink154inch, &cfg );

    eink154inch_start_config( &eink154inch );
    eink154inch_set_lut( &eink154inch, eink154inch_lut_table, 30 );
    Delay_ms ( 1000 );
    
#ifndef IMAGE_MODE_ONLY
    cfg_font.p_font = &guiFont_Tahoma_18_Regular[ 0 ];
    cfg_font.color = EINK154INCH_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK154INCH_FO_HORIZONTAL;  
    
    eink154inch_set_font( &eink154inch, &cfg_font );
    text_set.n_char = 4;
    text_set.text_x = 10;
    text_set.text_y = 50;
    eink154inch_text( &eink154inch, &demo_text[ 0 ], &text_set );
    text_set.n_char = 7;
    text_set.text_x = 10;
    text_set.text_y = 90;
    eink154inch_text( &eink154inch, &demo_text1[ 0 ], &text_set );
    text_set.n_char = 8;
    text_set.text_x = 10;
    text_set.text_y = 130;
    eink154inch_text( &eink154inch, &demo_text2[ 0 ], &text_set ); 
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
}
```

### Application Task

> Draws two demo images to the display with a one-second delay between each drawing.

```c
void application_task ( void )
{
    eink154inch_image( &eink154inch, &demoImage_light[ 0 ] );
    Delay_1sec( );
    eink154inch_image( &eink154inch, &demoImage_dark[ 0 ] );
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
