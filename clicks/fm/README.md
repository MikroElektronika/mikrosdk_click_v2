\mainpage Main Page
 
---
# FM click

FM Click with it’s Si4703 IC is a complete FM radio tuner in the form of add-on board. It supports worldwide FM band (76 – 108 MHz).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/fm_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/fm-click>)

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

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    fm_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    fm_cfg_setup( &cfg );
    FM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fm_init( &fm, &cfg );

    Delay_ms( 500 );
    fm_default_cfg( &fm );
}
  
```

### Application Task

>  Changes the station every 3 seconds.

```c

void application_task ( void )
{ 
    for ( ; ; )
    {
        fm_case_seek( &fm );
        fm_seek( &fm );
        Delay_ms( 3000 );
    }
}  

```

## Note

> <pre>
> Additional Functions :
> 
> void fm_case_plus( )      - Increases volume
> void fm_case_minus( )     - Decreases volume
> void fm_case_seek( )      - Seeks next station
> void fm_case_tune( )      - Tunes default station
> void fm_case_memorize( )  - Memorizes current station
> void fm_case_station1( )  - Tunes memorized station 1
> void fm_case_station2( )  - Tunes memorized station 2
> void fm_case_station3( )  - Tunes memorized station 3
> void fm_case_station4( )  - Tunes memorized station 4
> void fm_case_station5( )  - Tunes memorized station 5
> void fm_case_mute( )      - Mutes device
> void fm_case_tune_up( )   - Fine tunes frequency
> void fm_case_tune_down( ) - Fine tunes frequency
> </pre>

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
