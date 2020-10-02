
 

---
# Joystick 2 click

Joystick 2 Click is a smart navigation key concept based on SKRHABE010 by Alps, a 4-direction joystick switch with Center-push Function.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/joystick2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/joystick-2-click>)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Joystick2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Joystick2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void joystick2_cfg_setup ( joystick2_cfg_t *cfg ); 
 
- Initialization function.
> JOYSTICK2_RETVAL joystick2_init ( joystick2_t *ctx, joystick2_cfg_t *cfg );

- Click Default Configuration function.
> void joystick2_default_cfg ( joystick2_t *ctx );


#### Example key functions :

- Functions for configuration joystick
> void joystick2_set_cfg_register ( joystick2_t *ctx, uint8_t cfg_data );
 
- Functions for get Joystick position
> uint8_t joystick2_get_position ( joystick2_t *ctx );

- Functions for read interrupt state
> uint8_t joystick2_get_interrupt_state ( joystick2_t *ctx );

## Examples Description

> The demo application shows reading the joistick position ..

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Reset device and settings the click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    joystick2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    joystick2_cfg_setup( &cfg );
    JOYSTICK2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    joystick2_init( &joystick2, &cfg );

    joystick2_reset( &joystick2 );
    joystick2_default_cfg( &joystick2 );
    log_info( &logger, "---- JOYSTICK START ----" );
}
```

### Application Task

> It reads the position of the joystick,
> if it detects that the joystick has moved from the zero position,
> it prints a message about the current position.

```c
void application_task ( void )
{
    uint8_t joystick_pos;

    //  Task implementation.

    joystick_pos = joystick2_get_position( &joystick2 );

    switch ( joystick_pos )
    {
        case JOYSTICK2_BUTTON_ACTIVE:
        {
            log_info( &logger, "--- Button is pressed!!! ---" );
            Delay_ms( 300 );
            break;
        }
        case JOYSTICK2_POSITION_RIGHT:
        {
            log_info( &logger, "--- Joystick position [RIGHT] ---" );
            Delay_ms( 300 );
            break;
        }
        case JOYSTICK2_POSITION_LEFT:
        {
            log_info( &logger, "--- Joystick position [LEFT] ---" );
            Delay_ms( 300 );
            break;
        }
        case JOYSTICK2_POSITION_UP:
        {
            log_info( &logger, "--- Joystick position [UP] ---" );
            Delay_ms( 300 );
            break;
        }
        case JOYSTICK2_POSITION_DOWN:
        {
            log_info( &logger, "--- Joystick position [DOWN] ---" );
            Delay_ms( 300 );
            break;
        }
    }
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Joystick2

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
