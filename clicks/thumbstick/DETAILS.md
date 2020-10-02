
 

---
# Thumbstiick click

Thumbstick click is a high precision input device. It features a dual axis, spring return, pushbutton enabled joystick (similar to the ones used on joypads on popular gaming consoles), and a MCP3204 12-bit A/D converter.

It features a dual axis, spring return, pushbutton enabled joystick, and a MCP3204 12-bit A/D converter.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thumbstick_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/thumbstick-click>)

---

#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Thumbstick Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thumbstick Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thumbstick_cfg_setup ( thumbstick_cfg_t *cfg ); 
 
- Initialization function.
> THUMBSTICK_RETVAL thumbstick_init ( thumbstick_t *ctx, thumbstick_cfg_t *cfg );

#### Example key functions :

- Get state of thumbstick button function
> uint8_t thumbstick_button_state( thumbstick_t *ctx );
 
- Get thumbstick position function
> uint8_t thumbstick_get_position( thumbstick_t *ctx );

- Generic read 2 byte of data function
> uint16_t thumbstick_read_data( thumbstick_t *ctx, uint8_t channel );

## Examples Description

> The demo application shows reading the thumbstick position ..

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thumbstick_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    thumbstick_cfg_setup( &cfg );
    THUMBSTICK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thumbstick_init( &thumbstick, &cfg );
}
```

### Application Task

> It reads the position of the thumbstick,
>  - if it detects that the thumbstick has moved from the zero position,
>    it prints a message about the current position.
>  - It also checks the status of the switch button.

```c
void application_task ( void )
{
    uint8_t pos;
    uint8_t button_state;

    pos = thumbstick_get_position( &thumbstick );
    button_state = thumbstick_button_state( &thumbstick );

    if ( button_state == THUMBSTICK_PRESS_BUTTON )
    {
        log_printf( &logger, ">> Button is pressted \r\n" );
    }

    switch ( pos )
    {
        case THUMBSTICK_POSITION_TOP:
        {
            log_printf( &logger, ">> Position: [ TOP ] \r\n" );
            break;
        }
        case THUMBSTICK_POSITION_RIGHT:
        {
            log_printf( &logger, ">> Position: [ RIGHT ] \r\n" );
            break;
        }
        case THUMBSTICK_CHANNEL_BOTTOM:
        {
            log_printf( &logger, ">> Position: [ BOTTOM ] \r\n" );
            break;
        }
        case THUMBSTICK_CHANNEL_LEFT:
        {
            log_printf( &logger, ">> Position: [ LEFT ] \r\n" );
            break;
        }
    }
    Delay_ms( 30 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thumbstick

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
