
---
# 4x4 RGB Click

> [4x4 RGB Click](https://www.mikroe.com/?pid_product=MIKROE-1881) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1881&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application is used for powering 4x4 RGB LED matrix.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.4x4Rgb

### Example Key Functions

- `c4x4rgb_cfg_setup` This function initializes Click configuration structure to init state.
```c
void c4x4rgb_cfg_setup ( c4x4rgb_cfg_t *cfg, drv_logic_t logic_zero, drv_logic_t logic_one, uint8_t select_ctrl_pin );
```

- `c4x4rgb_init` This function initializes all necessary pins and peripherals used for this Click.
```c
err_t c4x4rgb_init ( c4x4rgb_t *ctx, c4x4rgb_cfg_t *cfg );
```

- `c4x4rgb_set_diode` This function allows to set color of one diode.
```c
err_t c4x4rgb_set_diode ( c4x4rgb_t *ctx, uint32_t diode_num, uint32_t diode_color );
```
 
- `c4x4rgb_fill_screen` This function sets every diode on selected color.
```c
void c4x4rgb_fill_screen ( c4x4rgb_t *ctx, uint32_t fill_color );
```

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

### Note

> Make sure the logic delays are defined for your system in the c4x4rgb_delays.h file.

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
