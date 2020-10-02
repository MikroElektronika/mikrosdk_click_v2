\mainpage Main Page
 
 

---
# AudioAmp 4 click

AudioAmp 4 click is a low-power audio amplifier with a digital volume control. It is equipped with the LM4860, an audio amplifier IC capable of delivering up to 1W of continuous power to an 8 Ω load.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/audioamp4_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/audioamp-4-click>)

---


#### Click library 

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the AudioAmp4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AudioAmp4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void audioamp4_cfg_setup ( audioamp4_cfg_t *cfg ); 
 
- Initialization function.
> AUDIOAMP4_RETVAL audioamp4_init ( audioamp4_t *ctx, audioamp4_cfg_t *cfg );

- Click Default Configuration function.
> void audioamp4_default_cfg ( audioamp4_t *ctx );


#### Example key functions :

- This function sets the volume channel.
> AUDIOAMP4_RETVAL audioamp4_set_channel ( audioamp4_t *ctx, uint8_t channel );
 
- This function is used to switch device ON or OFF
> AUDIOAMP4_RETVAL audioamp4_shutdown ( audioamp4_t *ctx, uint8_t state );

## Examples Description

> This example switches device on & off and sets three different volumes.


**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO interface, turns module ON and sets the volume value to 0.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    audioamp4_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    audioamp4_cfg_setup( &cfg );
    AUDIOAMP4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioamp4_init( &audioamp4, &cfg );
    audioamp4_default_cfg( &audioamp4 );
}
  
```

### Application Task

> Turns device OFF & ON and sets three different volume values.

```c

void application_task ( void )
{
    log_info( &logger, "Turn on device:" );
    application_error_handler( audioamp4_shutdown( &audioamp4, AUDIOAMP4_SHUTDOWN_OFF ) );
    
    log_info( &logger, "Set volume channel 1:" );
    application_error_handler( audioamp4_set_channel( &audioamp4, AUDIOAMP4_VOLUME_CHANN_1 ) );
    Delay_ms( 2000 );
    
    log_info( &logger, "Set volume channel 5:" );
    application_error_handler( audioamp4_set_channel( &audioamp4, AUDIOAMP4_VOLUME_CHANN_5 ) );
    Delay_ms( 2000 );
    
    log_info( &logger, "Set volume channel 7:" );
    application_error_handler( audioamp4_set_channel( &audioamp4, AUDIOAMP4_VOLUME_CHANN_7 ) );
    Delay_ms( 2000 );
    
    log_info( &logger, "Turn off device:" );
    application_error_handler( audioamp4_shutdown( &audioamp4, AUDIOAMP4_SHUTDOWN_ON ) );
    Delay_ms( 500 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAmp4

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
