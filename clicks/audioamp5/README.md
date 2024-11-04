\mainpage Main Page
 
 

---
# Audio Amp 5 Click

AudioAmp 5 Click is a stereo audio amplifier, capable of delivering up to 10W per channel with the 8Ω load.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/audioamp5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/audioamp-5-click)

---

#### Click library 

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the AudioAmp5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AudioAmp5 Click driver.
> The library performs the audio control of the Audio Amp 5 Click board.
> This library consists of the special commands for audio output control, for example to mute/turn on the outputs, 
> to select the desired output gain or mode.

#### Standard key functions :

- Config Object Initialization function.
> void audioamp5_cfg_setup ( audioamp5_cfg_t *cfg ); 
 
- Initialization function.
> AUDIOAMP5_RETVAL audioamp5_init ( audioamp5_t *ctx, audioamp5_cfg_t *cfg );

- Click Default Configuration function.
> void audioamp5_default_cfg ( audioamp5_t *ctx );


#### Example key functions :

- Function puts a device to the desired mode.
> void audioamp5_mode_select ( audioamp5_t *ctx, uint8_t state );

- Function performs a desired gain selection.
> void audioamp5_gain_select ( audioamp5_t *ctx, uint8_t state );

- Function to update the configuration of the module.
> void audioamp5_config_update ( audioamp5_t *ctx );

## Examples Description

> This example consist of sending special commands for audio output control, 
> selecting different output modes and turning on/off the audio output.

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO interface on the desired mikrobus selection,
> and performs a device init configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    audioamp5_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    audioamp5_cfg_setup( &cfg );
    AUDIOAMP5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioamp5_init( &audioamp5, &cfg );

    audioamp5_default_cfg( &audioamp5 );
    log_printf( &logger, "** Audio Amp 5 is initialized **\r\n" );
    Delay_ms ( 500 );
}
```

### Application Task

> Checks the entered command and, if the command is valid,
> performs a device configuration which the entered command determines.

```c
void application_task ( void )
{
    //  Task implementation.
    
    audioamp5_gain_select( &audioamp5, AUDIOAMP5_GAIN_26DB );
    audioamp5_config_update( &audioamp5 );
    log_printf( &logger, "** Gain value is 26dB **\r\n" );    

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    audioamp5_gain_select( &audioamp5, AUDIOAMP5_GAIN_20DB );
    audioamp5_config_update( &audioamp5 );
    log_printf( &logger, "** Gain value is 20dB **\r\n" );  
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Note

> After each command for device configuration, the command for configuration 
> updating will be executed.
> When BD Mode (0) is selected, the VIN supply voltage threshold is 7.5V.
> When Low-Idle-Current 1SPW Mode is selected, the VIN supply voltage threshold > is 3.4V.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAmp5

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
