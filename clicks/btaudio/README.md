\mainpage Main Page
 
---
# BT Audio click

If you are getting tired of all those cables you need just to listen to your favorite song over speakers.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/btaudio_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/bt-audio-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the BtAudio Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

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

> Initializes the driver and configures the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    btaudio_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    btaudio_cfg_setup( &cfg );
    BTAUDIO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    btaudio_init( &btaudio, &cfg );
    Delay_ms( 1000 );
    
    log_printf( &logger, "Power ON\r\n" );
    btaudio_set_power_on( &btaudio );
    btaudio_process( RESPONSE_NULL );
    
    log_printf( &logger, "Factory reset\r\n" );
    btaudio_set_factory_defaults( &btaudio );
    btaudio_process( RESPONSE_NULL );
    
    log_printf( &logger, "Set device name\r\n" );
    btaudio_set_device_name( &btaudio, "BT Audio click" );
    btaudio_reset( &btaudio );
    btaudio_process( RESPONSE_AOK );
    
    log_printf( &logger, "Set data mode\r\n" );
    btaudio_set_cmd_mode( &btaudio, 1 );
    btaudio_process( RESPONSE_NULL );
}
  
```

### Application Task

> Checks if there's any command received, then parses it and performs adequate actions.

```c

void application_task ( void )
{
    btaudio_process( RESPONSE_NULL );
} 

```

## Note

> We have used the Serial Bluetooth Terminal smartphone application for the test. 
> A smartphone and the click board must be paired in order to exchange messages
> with each other. So make sure to pair your device with the click board and
> connect to it using the Serial Bluetooth Terminal application, then you will be able 
> to send commands listed below.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.BtAudio

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
