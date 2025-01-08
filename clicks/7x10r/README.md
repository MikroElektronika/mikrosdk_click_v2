
---
# 7x10 R Click

> [7x10 R Click](https://www.mikroe.com/?pid_product=MIKROE-1993) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1993&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This demo example shows a drawing of pixels, characters and a number on the screen.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.7x10R

### Example Key Functions

- `c7x10r_cfg_setup` Config Object Initialization function.
```c
void c7x10r_cfg_setup ( c7x10r_cfg_t *cfg );
```

- `c7x10r_init` Initialization function.
```c
err_t c7x10r_init ( c7x10r_t *ctx, c7x10r_cfg_t *cfg );
```

- `c7x10r_draw_pixel` Drawing the pixel on the display.
```c
void c7x10r_draw_pixel ( c7x10r_t *ctx, c7x10r_pixel_t *pixel, uint8_t mode, uint8_t px_delay );
```

- `c7x10r_draw_char` Drawing the character on the display.
```c
void c7x10r_draw_char ( c7x10r_t *ctx, char ch, uint8_t pos, uint8_t ch_delay );
```

- `c7x10r_draw_number` Drawing the number on the display.
```c
void c7x10r_draw_number ( c7x10r_t *ctx, uint8_t num, uint16_t num_delay );
```

### Application Init

> Configuring the Click board.

```c
void application_init ( void ) 
{
    
    c7x10r_cfg_t c7x10r_cfg;  /**< Click config object. */

    //  Click initialization.

    c7x10r_cfg_setup( &c7x10r_cfg );
    C7X10R_MAP_MIKROBUS( c7x10r_cfg, MIKROBUS_1 );
    c7x10r_init( &c7x10r, &c7x10r_cfg );
}
```

### Application Task

> Draws characters, numbers, and pixels to the display.

```c
void application_task ( void ) 
{
    
    c7x10r_pixel_t pixel;
    uint8_t cnt;
    uint8_t cnt_x;
    uint8_t cnt_y;
    
    // CHAR PROCEDURE
    for ( cnt = 'A'; cnt < 'Z'; cnt+=2 ) {
        
        c7x10r_draw_char( &c7x10r, cnt, C7X10R_DISPLAY_LEFT, C7X10R_DISPLAY_DELAY_50MS );
        c7x10r_draw_char( &c7x10r, cnt + 1, C7X10R_DISPLAY_RIGHT | C7X10R_DISPLAY_REFRESH, C7X10R_DISPLAY_DELAY_50MS );
       
        Delay_ms ( 1000 );
    }

    // COUNTER PROCEDURE
    for ( cnt = 0; cnt < 15; cnt++ ) {
        
        c7x10r_draw_number( &c7x10r, cnt, C7X10R_DISPLAY_DELAY_50MS );
        
        Delay_ms ( 500 );
    }
    
    // PIXELS PROCEDURE
    for ( cnt_x = 0; cnt_x <= 7; cnt_x++ ) {
        
        for ( cnt_y = 0; cnt_y <= 10; cnt_y++ ) {
            
            pixel.cord_x = cnt_x;
            pixel.cord_y = cnt_y;
            c7x10r_draw_pixel( &c7x10r, &pixel, C7X10R_DISPLAY_PIXEL_STORAGE, C7X10R_DISPLAY_DELAY_20MS );

            pixel.cord_x = cnt_x;
            pixel.cord_y = cnt_y + 1;
            c7x10r_draw_pixel( &c7x10r, &pixel, C7X10R_DISPLAY_PIXEL_REFRESH, C7X10R_DISPLAY_DELAY_20MS );
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
