
---
# 7-SEG RGB click

7-SEG RGB click carries a full color single 7 segment digit display. The click is designed to run on either 3.3V or 5V power supply. It communicates with the target microcontroller over the CS, and PWM pin on the mikroBUS™ line.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/7segrgb_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/7-seg-rgb-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the 7SegRgb Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 7SegRgb Click driver.

#### Standard key functions :

- `c7segrgb_cfg_setup` This function initializes click configuration structure to init state.
```c
void c7segrgb_cfg_setup ( c7segrgb_cfg_t *cfg );
```

- `c7segrgb_init` This function initializes all necessary pins and peripherals used for this click.
```c
err_t c7segrgb_init ( c7segrgb_t *ctx, c7segrgb_cfg_t *cfg );
```

#### Example key functions :

- `c7segrgb_set_num` The function sets character and its color.
```c
void c7segrgb_set_num ( c7segrgb_t *ctx, uint8_t character, uint8_t green_brightness, uint8_t red_brightness, uint8_t blue_brightness );
```
 
- `c7segrgb_set_seven_seg` The function sets the state and color of every segment from click board object segment array data.
```c
void c7segrgb_set_seven_seg ( c7segrgb_t *ctx );
```

## Examples Description

> This click shows all ten digits on a full-color single 7 segment digit display. 
> Each segment has R, G, B LEDs that can be adjusted in 255 steps and the ability to control the brightness of all the LED.

**The demo application is composed of two sections :**

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
    Delay_ms( 3000 );
}
  
```

### Application Task

> This is an example which demonstrates the use of 7-SEG RGB Click board.
> This simple example shows all ten digits in different colors on 7-SEG RGB click.

```c

void application_task ( void )
{
    for ( uint8_t cnt_i = 0; cnt_i < 10; cnt_i++ )
    {
        for ( uint8_t cnt_j = 10; cnt_j > 0; cnt_j-- )
        {
            c7segrgb_set_num( &c7segrgb, CHARACTER_TABLE[ cnt_i ], 4 * cnt_i, 4 * cnt_j, cnt_i * cnt_j );
            Delay_ms( 100 );
        }
    }
    
    c7segrgb_set_num( &c7segrgb, C7SEGRGB_POINT, 10, 10, 10 );
    Delay_ms( 1000 );
    
    c7segrgb_set_num( &c7segrgb, C7SEGRGB_ZERO, 40, 40, 40 );
    Delay_ms( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_ONE, 40, 0, 0 );
    Delay_ms( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_TWO, 0, 40, 0 );
    Delay_ms( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_THREE, 0, 0, 40 );
    Delay_ms( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_FOUR, 40, 0, 40 );
    Delay_ms( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_FIVE, 0, 40, 40 );
    Delay_ms( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_SIX, 40, 40, 0 );
    Delay_ms( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_SEVEN, 20, 30, 40 );
    Delay_ms( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_EIGHT, 40, 15, 31 );
    Delay_ms( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_NINE, 20, 10, 30 );
    Delay_ms( 1000 );
}

```

## Note

> <pre>
> Additional Functions :
> void logic_one ( )  - Generic logic one function.
> void logic_zero ( ) - Generic logic zero function.
> </pre>

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.7SegRgb

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
