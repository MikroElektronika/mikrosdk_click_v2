
---
# BT Audio click

If you are getting tired of all those cables you need just to listen to your favorite song over speakers.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/btaudio_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/bt-audio-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the BtAudio Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for BtAudio Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void btaudio_cfg_setup ( btaudio_cfg_t *cfg ); 
 
- Initialization function.
> BTAUDIO_RETVAL btaudio_init ( btaudio_t *ctx, btaudio_cfg_t *cfg );

#### Example key functions :

- Play next track function
> uint8_t btaudio_next_track ( btaudio_t *ctx );
 
- Increase volume function
> uint8_t btaudio_increase_volume ( btaudio_t *ctx );

- Decrease volume function
> uint8_t btaudio_decrease_volume ( btaudio_t *ctx );

## Examples Description

> This example reads and processes data from BT Audio clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and power module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    btaudio_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    btaudio_cfg_setup( &cfg );
    BTAUDIO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    btaudio_init( &btaudio, &cfg );
    Delay_ms( 1000 );

    log_printf( &logger, "      Power On       \r\n" );
    btaudio_set_power_on( &btaudio );
    Delay_ms( 5000 );

    log_printf( &logger, "-------------------- \r\n" );
    log_printf( &logger, "  Set Command mode   \r\n" );
    btaudio_set_cmd_mode( &btaudio, 1, buffer );
    Delay_ms( 1000 );

    log_printf( &logger, "-------------------- \r\n" );
    log_printf( &logger, "    Set Data mode    \r\n" );
    btaudio_set_cmd_mode( &btaudio, 0, buffer );
    Delay_ms( 1000 );

    log_printf( &logger, "-------------------- \r\n" );
    log_printf( &logger, "   Factory  Reset    \r\n" );
    btaudio_set_factory_defaults( &btaudio );
    Delay_ms( 1000 );
    log_printf( &logger, "-------------------- \r\n" );
}
  
```

### Application Task

> Demo of application controls.

```c

void application_task ( void )
{
    log_printf( &logger, "    - Volume Up -\r\n" );
    btaudio_increase_volume( &btaudio );
    Delay_ms( 3500 );

    btaudio_decrease_volume( &btaudio );
    log_printf( &logger, "   - Volume Down - \r\n" );
    Delay_ms( 3500 );

    btaudio_next_track( &btaudio );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "     Next Track     \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms( 3500 );

    btaudio_previous_track( &btaudio );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "   Previous Track   \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms( 3500 );

    btaudio_pause_play_track( &btaudio );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "  Play/Pause Track  \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms( 3500 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.BtAudio

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
