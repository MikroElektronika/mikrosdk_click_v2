\mainpage Main Page

---
# 4x4 RGB Click

4x4 RGB Click is a matrix of 16 intelligent RGB elements, forming a 4x4 display screen.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/4x4rgb_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/4x4-rgb-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the 4x4Rgb Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 4x4Rgb Click driver.

#### Standard key functions :

- `c4x4rgb_cfg_setup` This function initializes Click configuration structure to init state.
```c
void c4x4rgb_cfg_setup ( c4x4rgb_cfg_t *cfg, drv_logic_t logic_zero, drv_logic_t logic_one, uint8_t select_ctrl_pin );
```

- `c4x4rgb_init` This function initializes all necessary pins and peripherals used for this Click.
```c
err_t c4x4rgb_init ( c4x4rgb_t *ctx, c4x4rgb_cfg_t *cfg );
```

#### Example key functions :

- `c4x4rgb_set_diode` This function allows to set color of one diode.
```c
err_t c4x4rgb_set_diode ( c4x4rgb_t *ctx, uint32_t diode_num, uint32_t diode_color );
```
 
- `c4x4rgb_fill_screen` This function sets every diode on selected color.
```c
void c4x4rgb_fill_screen ( c4x4rgb_t *ctx, uint32_t fill_color );
```

## Examples Description

> This application is used for powering 4x4 RGB LED matrix.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - GPIO. 

```c

void application_init ( void )
{
    c4x4rgb_cfg_t cfg;

    //  Click initialization.
    c4x4rgb_cfg_setup( &cfg, &c4x4rgb_logic_zero, &c4x4rgb_logic_one, C4X4RGB_CTRL_PIN_IN1 );
    C4X4RGB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c4x4rgb_init( &c4x4rgb, &cfg );
    
    c4x4rgb_fill_screen( &c4x4rgb, C4X4RGB_COLOR_WHITE );
    Delay_ms ( 100 ); 
    
    c4x4rgb_color_mash();
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
  
```

### Application Task

> This is an example which demonstrates the use of 4x4 RGB Click board.
> This simple example shows all ten numbers in different colors on 4x4 RGB Click.
> The 4x4 RGB Click carries a matrix of 16 RGB LEDs and an MCP1826 low dropout regulator.
> These LEDs actually consist of three single colored LEDs ( Red, Green and Blue ) in a single package.
> Various colors can be reproduced by mixing the intensity of each LED.

```c

void application_task ( void )
{
    c4x4rgb_snake( C4X4RGB_COLOR_BLUE );
    Delay_ms ( 500 ); 
    
    c4x4rgb_snake_return( C4X4RGB_COLOR_LIGHT_BLUE );
    Delay_ms ( 1000 ); 
    
    c4x4rgb_snake(  C4X4RGB_COLOR_GREEN );
    Delay_ms ( 500 ); 
    
    c4x4rgb_snake_return( C4X4RGB_COLOR_YELLOW );
    Delay_ms ( 1000 ); 
    
    c4x4rgb_snake( C4X4RGB_COLOR_RED );
    Delay_ms ( 500 ); 
    
    c4x4rgb_snake_return( C4X4RGB_COLOR_PURPLE );
    Delay_ms ( 1000 ); 
    
    c4x4rgb_fill_screen( &c4x4rgb, C4X4RGB_COLOR_WHITE );
    Delay_ms ( 100 ); 
}

```

## Note

> Make sure the logic delays are defined for your system in the c4x4rgb_delays.h file.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.4x4Rgb

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
