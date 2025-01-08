
---
# 16x9 Click

> [16x9 G Click](https://www.mikroe.com/?pid_product=MIKROE-2520) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2520&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> Demo application is used to shows basic controls 16x9 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.16x9

### Example Key Functions

- `c16x9_cfg_setup` Config Object Initialization function. 
```c
void c16x9_cfg_setup ( c16x9_cfg_t *cfg );
``` 
 
- `c16x9_init` Initialization function. 
```c
err_t c16x9_init ( c16x9_t *ctx, c16x9_cfg_t *cfg );
```

- `c16x9_draw_rectangle` Draw rectangle. 
```c
void c16x9_draw_rectangle ( c16x9_t *ctx,  c16x9_rectangle_t *rectangle );
```
 
- `c16x9_display_image` Image display function. 
```c
void c16x9_display_image ( c16x9_t *ctx, c16x9_image_t *image );
```

- `c16x9_draw_point` Functions for draw point. 
```c
void c16x9_draw_point ( c16x9_t *ctx, c16x9_point_t *point );
```

### Application Init

> Configuring Clicks and log objects.
> Set basic images and characters to be drawn on the screen.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c16x9_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c16x9_cfg_setup( &cfg );
    C16X9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c16x9_init( &c16x9, &cfg );

    // Image ON

    image_on.buf[ 0 ] = 0x0000;
    image_on.buf[ 1 ] = 0xC630;
    image_on.buf[ 2 ] = 0x6318;
    image_on.buf[ 3 ] = 0x318C;
    image_on.buf[ 4 ] = 0x18C6;
    image_on.buf[ 5 ] = 0x318C;
    image_on.buf[ 6 ] = 0x6318;
    image_on.buf[ 7 ] = 0xC630;
    image_on.buf[ 8 ] = 0x0000;

    image_on.frame = C16X9_FRAME_1;
    image_on.pwm = 250;

    // Image OFF

    image_off.buf[ 0 ] = 0xFFFF;
    image_off.buf[ 1 ] = 0x39CF;
    image_off.buf[ 2 ] = 0x9CE7;
    image_off.buf[ 3 ] = 0xCE73;
    image_off.buf[ 4 ] = 0xE739;
    image_off.buf[ 5 ] = 0xCE73;
    image_off.buf[ 6 ] = 0x9CE7;
    image_off.buf[ 7 ] = 0x39CF;
    image_off.buf[ 8 ] = 0xFFFF;

    image_off.frame = C16X9_FRAME_1;
    image_off.pwm = 250;

    // Char

    data_char.character = 'G';
    data_char.frame = C16X9_FRAME_1;
    data_char.pwm = 250;

    // Rectangle

    rectangle.x = 1;
    rectangle.y = 4;
    rectangle.width = 6;
    rectangle.height = 4;
    rectangle.frame = C16X9_FRAME_1;
    rectangle.pwm = 250;
}
```

### Application Task

> Display character, image and rectangle every 1 second.

```c
void application_task ( void )
{
    //  Task implementation.

    c16x9_display_refresh( &c16x9 );
    c16x9_display_byte( &c16x9, &data_char );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    c16x9_display_refresh( &c16x9 );
    c16x9_display_image( &c16x9, &image_on );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    c16x9_display_refresh( &c16x9 );
    c16x9_display_image( &c16x9, &image_off );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    c16x9_display_refresh( &c16x9 );
    c16x9_draw_rectangle( &c16x9, &rectangle );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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


