
 

---
# AudioAmp 6 click

Audio Amp 6 click is a mono/subwoofer audio amplifier, capable of delivering up to 18.5W per channel with the 4Ω load. It is based on the TPA3138D2, a class-D integrated amplifier, which utilizes a highly efficient switching scheme.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/audioamp6_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/audioamp-6-click>)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the AudioAmp6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AudioAmp6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void audioamp6_cfg_setup ( audioamp6_cfg_t *cfg ); 
 
- Initialization function.
> AUDIOAMP6_RETVAL audioamp6_init ( audioamp6_t *ctx, audioamp6_cfg_t *cfg );


#### Example key functions :

- Sets device mode
> void audioamp6_set_mode( audioamp6_t *ctx, uint8_t mode );
 
- Enable or disable output
> void audioamp6_set_output( audioamp6_t *ctx, uint8_t out );

- Sets device gain
> void audioamp6_set_gain( audioamp6_t *ctx, uint8_t gain );

## Examples Description

> The demo application displays the volume change using AudioAmp 6 click.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Select mode and sets output on the enable state. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    audioamp6_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    audioamp6_cfg_setup( &cfg );
    AUDIOAMP6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioamp6_init( &audioamp6, &cfg );

    audioamp6_set_mode( &audioamp6, AUDIOAMP6_MODE_BD );
    audioamp6_set_output( &audioamp6, AUDIOAMP6_OUTPUT_ENABLE );

    log_info( &logger, "---- Start control AudioAmp 6 click ----" );
}
```

### Application Task

> Changes the gain settings ( 20dB - 26dB )

```c
void application_task ( void )
{
    //  Task implementation.

    log_printf( &logger, ">> Set gain 20 dB \r\n" );
    audioamp6_set_gain( &audioamp6, AUDIOAMP6_GAIN_20dB );
    Delay_ms( 2000 );
    log_printf( &logger, ">> Set gain 26 dB \r\n" );
    audioamp6_set_gain( &audioamp6, AUDIOAMP6_GAIN_26dB );
    Delay_ms( 2000 );
}
```

## Note

> Sets the input voltage from 3.5V to 14.4V.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAmp6

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
