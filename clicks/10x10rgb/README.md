
---
# 10x10 RGB Click

> [10x10 RGB Click](https://www.mikroe.com/?pid_product=MIKROE-4115) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4115&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example showcases how to initialize, configure and use the 10x10 RGB Click module. The
Click has a 10 by 10 RGB LED matrix which can be programmed to show different colors or even
images. LED elements that form the matrix communicate by a single line with the host MCU. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.10x10RGB

### Example Key Functions

- `c10x10rgb_cfg_setup` Config Object Initialization function.
```c
void c10x10rgb_cfg_setup ( c10x10rgb_cfg_t *cfg ); 
```

- `c10x10rgb_init` Initialization function.
```c
err_t c10x10rgb_init ( c10x10rgb_t *ctx, c10x10rgb_cfg_t *cfg );
```

- `c10x10rgb_default_cfg` Click Default Configuration function.
```c
void c10x10rgb_default_cfg ( c10x10rgb_t *ctx );
```

- `c10x10rgb_display_image` This function displays an image from the specified demo_image address.
```c
void c10x10rgb_display_image ( c10x10rgb_t *ctx, const uint32_t *demo_image );
```
 
- `c10x10rgb_display_byte` This function displays the specified byte.
```c
void c10x10rgb_display_byte ( c10x10rgb_t *ctx, c10x10rgb_byte_t *data_obj );
```

- `c10x10rgb_display_string` This function displays the specified string.
```c
void c10x10rgb_display_string ( c10x10rgb_t *ctx, c10x10rgb_byte_t *data_obj, uint8_t len, uint16_t speed_ms );
```

### Application Init

> This function initializes and configures the Click board.

```c
void application_init ( void )
{
    c10x10rgb_cfg_t cfg;

    //  Click initialization.
    c10x10rgb_cfg_setup( &cfg, &logic_zero, &logic_one );
    C10X10RGB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c10x10rgb_init( &c10x10rgb, &cfg );

    c10x10rgb_fill_screen( &c10x10rgb, C10X10RGB_COLOR_OFF );
    Delay_ms ( 1000 );
}
```

### Application Task

> This function first displays 3 chars { R, G, B }, the string "MIKROE", the company logo and a rainbow in the end. 

```c
void application_task ( void )
{
    c10x10rgb_display_byte ( &c10x10rgb, &rgb_data_byte[ 0 ] );
    Delay_ms ( 1000 );
    c10x10rgb_display_byte ( &c10x10rgb, &rgb_data_byte[ 1 ] );
    Delay_ms ( 1000 );
    c10x10rgb_display_byte ( &c10x10rgb, &rgb_data_byte[ 2 ] );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    c10x10rgb_display_string( &c10x10rgb, &scroll_data_obj, scroll_data_len, scroll_speed_ms );
    Delay_ms ( 1000 );
    c10x10rgb_display_image( &c10x10rgb, &MIKROE_IMAGE[ 0 ] );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    c10x10rgb_demo_rainbow( &c10x10rgb, rainbow_brightness, rainbow_speed_ms );
    Delay_ms ( 1000 );
} 

``` 

### Note

> Make sure the logic delays are defined for your system in the c10x10rgb_delays.h file.

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
