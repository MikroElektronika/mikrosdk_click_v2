\mainpage Main Page
 
---
# FM click

FM Click with it’s Si4703 IC is a complete FM radio tuner in the form of add-on board. It supports worldwide FM band (76 – 108 MHz).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/fm_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/fm-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Fm Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Fm Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void fm_cfg_setup ( fm_cfg_t *cfg ); 
 
- Initialization function.
> FM_RETVAL fm_init ( fm_t *ctx, fm_cfg_t *cfg );

- Click Default Configuration function.
> void fm_default_cfg ( fm_t *ctx );


#### Example key functions :

- This function reads recived signal strength indicatior
> uint8_t fm_get_received_signal_strength_indicator ( fm_t *ctx );
 
- This function calculates current channel frequency based on band and space settings
> float fm_get_channel_frequency ( fm_t *ctx );

- This function reads CHANNEL bits from READCHAN register
> uint16_t fm_get_channel ( fm_t *ctx );

## Examples Description

> This click represent FM radio tuner which supports worldwide FM band (76 – 108 MHz)
> and has a set of features such as automatic frequency and gain control, seek tuning and volume control.

**The demo application is composed of two sections :**

### Application Init 

> Initializing I2C driver, powering up device, setting basic settings for Europe, 
> setting values of seek threshold, volume, snr threshold and impulse detection threshold.
> Seek and memorize 5 radio stations with a signal strength above the set limit.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    fm_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    fm_cfg_setup( &cfg );
    FM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fm_init( &fm, &cfg );
    
    Delay_ms( 500 );
    fm_default_cfg( &fm );

    memory = 0;
    mute = 0;
    fm_case_mute( &fm );
     
    for ( cnt = 0; cnt < 5;  )
    {
        log_printf( &logger, "seeking...\r\n" );
        do 
        {
            received_signal_strength_indicator = 0;
            fm_case_seek( &fm );
        }
        while ( received_signal_strength_indicator < SIGNAL_STRENGTH_LOWER_LIMIT ); //rssi value
        
        log_printf( &logger, "station found\r\n" );
        log_printf( &logger, "rssi: %u dBuV\r\n", received_signal_strength_indicator );
        log_printf( &logger, "channel frequency: %.2f MHz\r\n", channel_frequency );
        fm_case_memorize( );
        log_printf( &logger, "-----------------------\r\n" );
        Delay_ms( 100 );
        cnt++;
    }  
    
    mute = 1;
    fm_case_mute( &fm );
    log_printf( &logger, "playing memorized stations...\r\n\r\n" );
}
  
```

### Application Task

> Tunes all memorized stations. Switches the stations each 10 seconds.

```c

void application_task ( void )
{ 
    fm_case_station_1( &fm );
    Delay_ms( 10000 );
       
    fm_case_station_2( &fm );
    Delay_ms( 10000 );
    
    fm_case_station_3( &fm );
    Delay_ms( 10000 );
    
    fm_case_station_4( &fm );
    Delay_ms( 10000 );
    
    fm_case_station_5( &fm );
    Delay_ms( 10000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Fm

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
