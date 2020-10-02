
---
# AudioAMP click

The AudioAMP Board features an on-board power amplifier LM386 designed for use in low voltage consumer applications.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/audioamp_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/audioamp-board>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the AudioAmp Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AudioAmp Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void audioamp_cfg_setup ( audioamp_cfg_t *cfg ); 
 
- Initialization function.
> AUDIOAMP_RETVAL audioamp_init ( audioamp_t *ctx, audioamp_cfg_t *cfg );

- Click Default Configuration function.
> void audioamp_default_cfg ( audioamp_t *ctx );


#### Example key functions :

- Set mux volume function
> void audioamp_set_volume ( audioamp_t *ctx, uint8_t volume_value )
 
- Set channel volume function
> void audioamp_set_volume_channel ( audioamp_t *ctx, uint8_t channel, uint8_t volume_value )

- Set normal opeation function
> void audioamp_set_normal_operation ( audioamp_t *ctx )

## Examples Description

> AudioAmp Click is a stereo audio amplifier 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C, turn on the Audio Amp click and start write log. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    audioamp_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    audioamp_cfg_setup( &cfg );
    AUDIOAMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioamp_init( &audioamp, &cfg );

    Delay_ms( 100 );

    log_printf( &logger, "~~~~~~~~~~~~~~~~~~~~~~\r\n " );
    log_printf( &logger, "    AudioAmp Click   \r\n " );
    log_printf( &logger, "~~~~~~~~~~~~~~~~~~~~~~\r\n" );

    log_printf( &logger, "       Power ON       \r\n" );
    
    audioamp_power_on( &audioamp );
    Delay_ms( 1000 );

    log_printf( &logger, "----------------------\r\n" );
}

  
```

### Application Task

> This is a example which demonstrates the use of AudioAmp Click board. 

```c

void application_task ( void )
{
    log_printf( &logger, " Set volume to lvl 15 \r\n" );
    log_printf( &logger, " for the next 10 sec. \r\n" );

    audioamp_set_volume( &audioamp, 15 );
    Delay_ms( 10000 );

    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " Set volume to lvl 5  \r\n" );
    log_printf( &logger, " for the next 15 sec. \r\n" );

    audioamp_set_volume( &audioamp, 5 );
    Delay_ms( 15000 );

    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " Set volume to lvl 10 \r\n" );
    log_printf( &logger, " for the next 20 sec. \r\n" );

    audioamp_set_volume( &audioamp, 10 );
    Delay_ms( 20000 );
    
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, "      Mute  mode      \r\n" );
    log_printf( &logger, " for the next 5 sec.  \r\n" );

    audioamp_mute_mode( &audioamp );
    Delay_ms( 5000 );
    
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, "     Unmute  mode     \r\n" );

    audioamp_unmute_mode( &audioamp );
    Delay_ms( 100 );

    log_printf( &logger, "----------------------\r\n" );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
} 

```