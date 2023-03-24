\mainpage Main Page

---
# 7x10 B click

7x10 B click is a LED dot matrix display click, which can be used to display graphics or letters in a very simple and easy way. The click board has two LED dot matrix modules with 7x5 stylish, round, dot-like LED elements. These displays produce clean and uniform patterns since the elements are optically isolated from each other and there is no light bleeding between the adjacent LED cells. Additionally, turn-on and turn-off times of the matrix cells are optimized for a clean and fluid display performance, with no flickering or lag.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/7x10b_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/7x10-b-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the c7x10B Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for c7x10B Click driver.

#### Standard key functions :

- `c7x10b_cfg_setup` Config Object Initialization function.
```c
void c7x10b_cfg_setup ( c7x10b_cfg_t *cfg );
```

- `c7x10b_init` Initialization function.
```c
C7X10B_RETVAL c7x10b_init ( c7x10b_t *ctx, c7x10b_cfg_t *cfg );
```

#### Example key functions :

- `c7x10b_draw_pixel`  Drawing the pixel on the display.
```c
void c7x10b_draw_pixel ( c7x10b_t *ctx, c7x10b_pixel_t *pixel, uint8_t mode, uint8_t px_delay );
```

- `c7x10b_draw_char` Drawing the character on the display.
```c
void c7x10b_draw_char ( c7x10b_t *ctx, char ch, uint8_t pos, uint8_t ch_delay );
```

- `c7x10b_draw_number` Drawing the number on the display.
```c
void c7x10b_draw_number ( c7x10b_t *ctx, uint8_t num, uint16_t num_delay );
```

## Example Description

> This demo example shows a drawing of pixels, characters and a number on the screen.

**The demo application is composed of two sections :**

### Application Init

> Configuring the click board.

```c

void application_init ( void ) {
    
    c7x10b_cfg_t c7x10b_cfg;  /**< Click config object. */

    //  Click initialization.

    c7x10b_cfg_setup( &c7x10b_cfg );
    C7X10B_MAP_MIKROBUS( c7x10b_cfg, MIKROBUS_1 );
    c7x10b_init( &c7x10b, &c7x10b_cfg );
}

```

### Application Task

> Draws characters, numbers, and pixels to the display.

```c

void application_task ( void ) {
    
    c7x10b_pixel_t pixel;
    uint8_t cnt;
    uint8_t cnt_x;
    uint8_t cnt_y;
    
    // CHAR PROCEDURE
    
    for ( cnt = 'A'; cnt < 'Z'; cnt+=2 ) {
        
        c7x10b_draw_char( &c7x10b, cnt, C7X10B_DISPLAY_LEFT, C7X10B_DISPLAY_DELAY_50MS );
        c7x10b_draw_char( &c7x10b, cnt + 1, C7X10B_DISPLAY_RIGHT | C7X10B_DISPLAY_REFRESH, C7X10B_DISPLAY_DELAY_50MS );
        
        Delay_ms( 1000 );
    }

    // COUNTER PROCEDURE
    
    for ( cnt = 0; cnt < 15; cnt++ ) {
        
        c7x10b_draw_number( &c7x10b, cnt, C7X10B_DISPLAY_DELAY_50MS );
        
        Delay_ms( 500 );
    }
    
    // PIXELS PROCEDURE
    
    for ( cnt_x = 0; cnt_x <= 7; cnt_x++ ) {
        
        for ( cnt_y = 0; cnt_y <= 10; cnt_y++ ) {
            
            pixel.cord_x = cnt_x;
            pixel.cord_y = cnt_y;
            c7x10b_draw_pixel( &c7x10b, &pixel, C7X10B_DISPLAY_PIXEL_STORAGE, C7X10B_DISPLAY_DELAY_20MS );

            pixel.cord_x = cnt_x;
            pixel.cord_y = cnt_y + 1;
            c7x10b_draw_pixel( &c7x10b, &pixel, C7X10B_DISPLAY_PIXEL_REFRESH, C7X10B_DISPLAY_DELAY_20MS );
        }
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.7x10B

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
