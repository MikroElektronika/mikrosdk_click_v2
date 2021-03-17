\mainpage Main Page
 
---
# c4Dot-matrix r click

4Dot-Matrix R click is a display device Click board™, which contains a four-digit dot matrix display module, labeled as SLO2016.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/4dotmatrixr_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/4dot-matrix-r-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the c4dotmatrixr Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for c4dotmatrixr Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c4dotmatrixr_cfg_setup ( c4dotmatrixr_cfg_t *cfg ); 
 
- Initialization function.
> C4DOTMATRIXR_RETVAL c4dotmatrixr_init ( c4dotmatrixr_t *ctx, c4dotmatrixr_cfg_t *cfg );

- Click Default Configuration function.
> void c4dotmatrixr_default_cfg ( c4dotmatrixr_t *ctx );


#### Example key functions :

- 4DotMatrix Char Write.
> void c4dot_write_char ( c4dotmatrixr_t *ctx, uint8_t char_num, uint8_t char_value );
 
- 4DotMatrix Char 0 Write.
> void c4dot_write_char0 ( c4dotmatrixr_t *ctx, uint8_t char_value );

- 4DotMatrix Text Write.
> void c4dot_write_text ( c4dotmatrixr_t *ctx, uint8_t *text_to_write );

## Examples Description

> This module has a 5x7 dot matrix, with very closely spaced, bright red pixel elements.

**The demo application is composed of two sections :**

### Application Init 

> Click driver init and setting mBus pins to appropriate logic levels. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c4dotmatrixr_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    c4dotmatrixr_cfg_setup( &cfg );
    C4DOTMATRIXR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c4dotmatrixr_init( &c4dotmatrixr, &cfg );
    c4dotmatrixr_default_cfg ( &c4dotmatrixr );
}
  
```

### Application Task

> Text MikroElektronika slides from left to right and then numbers from -20 to 20 are displayed on 4 Dot Matrix click 

```c

void application_task ( void )
{
    int8_t i;
    
    for ( i = 0; i < 21; i++ )
    {
        c4dot_write_text(  &c4dotmatrixr, text + i );
        Delay_ms( 150 );
    }
        
        // Clear and delay.
    c4dot_clear_display( &c4dotmatrixr );
    Delay_ms( 500 );
        
        // Write some numbers on the display.
    for ( i = -20; i <= 20; i++ )
    {
        c4dot_write_int_dec( &c4dotmatrixr, i );
        Delay_ms( 150 );
    }

    c4dot_clear_display( &c4dotmatrixr );
    Delay_ms( 500 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.c4dotmatrixr

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
