
---
# 7-SEG RGB Click

> [7-SEG RGB Click](https://www.mikroe.com/?pid_product=MIKROE-2734) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2734&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> This Click shows all ten digits on a full-color single 7 segment digit display. 
> Each segment has R, G, B LEDs that can be adjusted in 255 steps and the ability to control the brightness of all the LED.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.7SegRgb

### Example Key Functions

- `c7segrgb_cfg_setup` This function initializes Click configuration structure to init state.
```c
void c7segrgb_cfg_setup ( c7segrgb_cfg_t *cfg );
```

- `c7segrgb_init` This function initializes all necessary pins and peripherals used for this Click.
```c
err_t c7segrgb_init ( c7segrgb_t *ctx, c7segrgb_cfg_t *cfg );
```

- `c7segrgb_set_num` The function sets character and its color.
```c
void c7segrgb_set_num ( c7segrgb_t *ctx, uint8_t character, uint8_t green_brightness, uint8_t red_brightness, uint8_t blue_brightness );
```
 
- `c7segrgb_set_seven_seg` The function sets the state and color of every segment from Click board object segment array data.
```c
void c7segrgb_set_seven_seg ( c7segrgb_t *ctx );
```

### Application Init

> Initialization driver enables - GPIO.

```c
void application_init ( void )
{
    c7segrgb_cfg_t cfg;

    //  Click initialization.
    c7segrgb_cfg_setup( &cfg );
    cfg.logic_one = &logic_one;
    cfg.logic_zero = &logic_zero;
    C7SEGRGB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c7segrgb_init( &c7segrgb, &cfg );
    
    for ( uint8_t cnt = 0; cnt < 8; cnt++ )
    {
        c7segrgb.segments[ cnt ] = segments_data[ cnt ];
    }
    c7segrgb_set_seven_seg( &c7segrgb );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Application Task

> This is an example which demonstrates the use of 7-SEG RGB Click board.
> This simple example shows all ten digits in different colors on 7-SEG RGB Click.

```c
void application_task ( void )
{
    for ( uint8_t cnt_i = 0; cnt_i < 10; cnt_i++ )
    {
        for ( uint8_t cnt_j = 10; cnt_j > 0; cnt_j-- )
        {
            c7segrgb_set_num( &c7segrgb, CHARACTER_TABLE[ cnt_i ], 4 * cnt_i, 4 * cnt_j, cnt_i * cnt_j );
            Delay_ms ( 100 );
        }
    }
    
    c7segrgb_set_num( &c7segrgb, C7SEGRGB_POINT, 10, 10, 10 );
    Delay_ms ( 1000 );
    
    c7segrgb_set_num( &c7segrgb, C7SEGRGB_ZERO, 40, 40, 40 );
    Delay_ms ( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_ONE, 40, 0, 0 );
    Delay_ms ( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_TWO, 0, 40, 0 );
    Delay_ms ( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_THREE, 0, 0, 40 );
    Delay_ms ( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_FOUR, 40, 0, 40 );
    Delay_ms ( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_FIVE, 0, 40, 40 );
    Delay_ms ( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_SIX, 40, 40, 0 );
    Delay_ms ( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_SEVEN, 20, 30, 40 );
    Delay_ms ( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_EIGHT, 40, 15, 31 );
    Delay_ms ( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_NINE, 20, 10, 30 );
    Delay_ms ( 1000 );
}
```

### Note

> Make sure the logic delays are defined for your system in the c7segrgb_delays.h file.
>
> <pre>
> Additional Functions :
> void logic_one ( )  - Generic logic one function.
> void logic_zero ( ) - Generic logic zero function.
> </pre>

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
