
---
# BIG 7-SEG click

BIG 7-SEG R click is what you need if you want to add a seven-segment LED display to your project.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/big7segr_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/big-7-seg-r-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Big7Seg Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Big7Seg Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void big7seg_cfg_setup ( big7seg_cfg_t *cfg ); 
 
- Initialization function.
> BIG7SEG_RETVAL big7seg_init ( big7seg_t *ctx, big7seg_cfg_t *cfg );

#### Example key functions :

- Turn OFF BIG 7-SEG display
> void big7seg_display_off ( big7seg_t *ctx );
 
- Function write number
> void big7seg_write_data_number ( big7seg_t *ctx, uint8_t display_number );

- Function write character
> void big7seg_write_data_character ( big7seg_t *ctx, char display_char );

## Examples Description

> This application sets seven-segment leds on the display.

**The demo application is composed of two sections :**

### Application Init 

> Driver initializaion and turning on the display
> by setting PWM pin to logic 1 and prepare to communcation via SPI.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    big7seg_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    big7seg_cfg_setup( &cfg );
    BIG7SEG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    big7seg_init( &big7seg, &cfg );

    big7seg_set7seg( &big7seg );
    Delay_100ms( );
}
  
```

### Application Task

> This example shows functionality of the BIG 7-SEG R click,
> shows number or character on display.

```c

void application_task ( )
{
    uint8_t counter;

    big7seg_reset7seg( &big7seg );
    big7seg_display_on( &big7seg );
    Delay_1sec( );

    big7seg_write_data( &big7seg, 0x40 );
    Delay_1sec( );
    big7seg_write_data_character(  &big7seg, 'B' );
    Delay_1sec( );
    big7seg_write_data_character(  &big7seg, 'I' );
    Delay_1sec( );
    big7seg_write_data_character(  &big7seg, 'G' );
    Delay_1sec( );
    big7seg_write_data( &big7seg, 0x08 );
    Delay_1sec( );
    big7seg_write_data_number( &big7seg, 7 );
    Delay_1sec( );
    big7seg_write_data( &big7seg, 0x40 );
    Delay_1sec( );
    big7seg_write_data_character(  &big7seg, 'S' );
    Delay_1sec( );
    big7seg_write_data_character(  &big7seg, 'E' );
    Delay_1sec( );
    big7seg_write_data_character(  &big7seg, 'G' );
    Delay_1sec( );
    
    big7seg_write_data( &big7seg, 0x00 );
    Delay_1sec( );
    for ( counter = 65; counter < 91; counter ++ )
    {
        big7seg_write_data_character(  &big7seg, counter );
        Delay_1sec( );
    }

    big7seg_display_off( &big7seg );
    Delay_1sec( );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Big7Seg

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
