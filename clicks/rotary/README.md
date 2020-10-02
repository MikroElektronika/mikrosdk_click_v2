\mainpage Main Page
 
 

---
# Rotary click

Rotary click carries a 15-pulse incremental rotary encoder with detents, surrounded by a ring of 16 green LEDs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/rotary-click-group.png" height=300px>
</p>

> - [Product page - Rotary G click](<https://www.mikroe.com/rotary-g-click>)
> - [Product page - Rotary R click](<https://www.mikroe.com/rotary-r-click>)
> - [Product page - Rotary B click](<https://www.mikroe.com/rotary-b-click>)
> - [Product page - Rotary Y click](<https://www.mikroe.com/rotary-y-click>)
> - [Product page - Rotary O click](<https://www.mikroe.com/rotary-o-click>)

---


#### Click library 

- **Author**        : Nenad Filipovic
- **Date**          : nov 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Rotary Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rotary Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rotary_cfg_setup ( rotary_cfg_t *cfg ); 
 
- Initialization function.
> ROTARY_RETVAL rotary_init ( rotary_t *ctx, rotary_cfg_t *cfg );

#### Example key functions :

- Turn on led by position
> void rotaryr_turn_on_led_by_position ( rotary_t *ctx, uint8_t led_position );
 
-  Get led data state
> uint8_t rotaryr_button_push( rotary_t *ctx );

- Generic data write function
> void rotaryr_turn_on_led_by_data ( rotary_t *ctx, uint16_t write_data );

## Examples Description

> The demo application controls led on click with rotory on board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes SPI driver, set initial states, 
> set RST logic high and performs device configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rotary_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rotary_cfg_setup( &cfg );
    ROTARY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rotary_init( &rotary, &cfg );

    led_data = 0x0001;
    old_state = 0;
    new_state = 1;
    old__rot_state = 0;
    new_rotate_state = 1;
}
```

### Application Task

> Show functionality of Rotary_R Click, rotating and turn on/off led's,
> using the SPI interface.

```c
void application_task ( void )
{
    rotaryr_turn_on_led_by_data( &rotary, led_data );

    // Push button
    if ( rotaryr_button_push( &rotary ) )
    {
        new_state = 1;
        if ( new_state == 1 &&  old_state == 0 )
        {
            old_state = 1;
            led_state = ( led_state + 1 ) % 5;
            if ( led_state == 4 )
            {
                for ( old_state=0; old_state < 17; old_state++ )
                {
                    rotaryr_turn_on_led_by_data( &rotary, 0xAAAA );
                    Delay_100ms();
                    rotaryr_turn_on_led_by_data( &rotary, 0x5555 );
                    Delay_100ms();
                }

                for ( old_state=0; old_state < 17; old_state++ )
                {
                    rotaryr_turn_on_led_by_position( &rotary, old_state );
                    Delay_100ms();
                }

                led_state = 0;
                led_data = rotaryr_get_led_data( &rotary, led_state );
            }
            else
            {
                led_data = rotaryr_get_led_data( &rotary, led_state );
            }
        }
    }
    else
    {
        old_state = 0;
    }

    // Rotate Clockwise and CounterClockwise
    if ( rotaryr_get_eca_state( &rotary ) == rotaryr_get_ecb_state( &rotary ) )
    {
        old__rot_state = 0;
        start_status = rotaryr_get_eca_state( &rotary ) && rotaryr_get_ecb_state( &rotary );
    }
    else
    {
        new_rotate_state = 1;
        if ( new_rotate_state != old__rot_state )
        {
            old__rot_state = 1;
            if ( start_status != rotaryr_get_eca_state( &rotary ) )
            {
                led_data = ( led_data << 1 ) | ( led_data >> 15 );
            }
            else
            {
                led_data = ( led_data >> 1 ) | ( led_data << 15 );
            }
        }
    }
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rotary

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
