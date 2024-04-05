\mainpage Main Page
 
 

---
# Audio Amp 2 click

Audio Amp 2 click is a highly efficient class D audio amplifier, using the TDA7491, a dual BTL class-D audio amplifier IC, capable of delivering up to 20W to 8Ω load.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/audioamp2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/audioamp-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the AudioAmp2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AudioAmp2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void audioamp2_cfg_setup ( audioamp2_cfg_t *cfg ); 
 
- Initialization function.
> AUDIOAMP2_RETVAL audioamp2_init ( audioamp2_t *ctx, audioamp2_cfg_t *cfg );

#### Example key functions :

- Mode Set function
> uint8_t audioamp2_set_mode ( audioamp2_t *ctx, uint8_t sel_mode );
 
- Gain Set function
> uint8_t audioamp2_set_gain ( audioamp2_t *ctx, uint8_t sel_gain );

- Diagnostic Check function
> uint8_t audioamp2_check_diagnostic ( audioamp2_t *ctx );

## Examples Description

> This application amplifies the sound on the speakers.

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO driver and puts device in Standby Mode as default
> operation mode and selects 20dB as default gain selection.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    audioamp2_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    audioamp2_cfg_setup( &cfg );
    AUDIOAMP2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioamp2_init( &audioamp2, &cfg );
    Delay_ms ( 100 );
    
    log_printf( &logger, "AudioAmp 2 is initialized \r\n \r\n" );
    Delay_ms ( 200 );
}
  
```

### Application Task

> Activates Mute operation mode for 4 seconds and after that activates Play mode.
> When the device is in Play mode then changes the gain selection, first sets the minimum gain (20dB) for 8 seconds
> and then sets the maximum gain (32dB) for 8 seconds too.

```c

void application_task ( void )
{
    audioamp2_set_mode( &audioamp2, AUDIOAMP2_MUTE_MODE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    audioamp2_set_gain( &audioamp2, AUDIOAMP2_20DB_GAIN );
    audioamp2_set_mode( &audioamp2, AUDIOAMP2_PLAY_MODE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    audioamp2_set_gain( &audioamp2, AUDIOAMP2_32DB_GAIN );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

## Note

> Internally, the gain is set by changing the feedback resistors of the amplifier.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAmp2

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
