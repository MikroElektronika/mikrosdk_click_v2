
---
# AudioAmp click

> AudioAmp Click is a compact add-on board that can add a mono audio amplifier function to your application. This board features the LM48100Q-Q1, a Boomer™ mono 1.3W audio power amplifier with output fault detection and volume control from Texas Instruments. The AudioAmp Click has one dual 3.5mm audio input jack and, next to it, a screw terminal for connecting output wires to a 1.3W, 8 Ohm passive speaker. Each input has its own independent 32-step volume control.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/audioamp_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/audioamp-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the AudioAmp Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AudioAmp Click driver.

#### Standard key functions :

- `audioamp_cfg_setup` Config Object Initialization function.
```c
void audioamp_cfg_setup ( audioamp_cfg_t *cfg ); 
```

- `audioamp_init` Initialization function.
```c
err_t audioamp_init ( audioamp_t *ctx, audioamp_cfg_t *cfg );
```

#### Example key functions :

- `audioamp_set_volume` Set volume function.
```c
err_t audioamp_set_volume ( audioamp_t *ctx, uint8_t in_sel, uint8_t volume_level );
```

- `audioamp_power_on` Turn on the Audio Amp click function.
```c
err_t audioamp_power_on ( audioamp_t *ctx );
```

- `audioamp_mute` Mute input function.
```c
err_t audioamp_mute ( audioamp_t *ctx );
```

## Examples Description

> AudioAmp Click is a stereo audio amplifier which can be controlled by using this click driver.

**The demo application is composed of two sections :**

### Application Init 

> Performs driver and log module initialization, enables I2C, turns on the AudioAmp device and sends a message about init status.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;

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
    log_info( &logger, "---- Application Init... ----" );

    audioamp_cfg_t audioamp_cfg;

    //  Click initialization.

    audioamp_cfg_setup( &audioamp_cfg );
    AUDIOAMP_MAP_MIKROBUS( audioamp_cfg, MIKROBUS_1 );

    if ( audioamp_init( &audioamp, &audioamp_cfg ) == AUDIOAMP_INIT_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- Application Init Done. ----" );
    log_info( &logger, "---- Application Running... ----" );
    log_info( &logger, "---- Check your audio speaker. ----\n" );

    audioamp_power_on( &audioamp );
}

  
```

### Application Task

> This is a example which demonstrates the use and control of the AudioAmp Click board.

```c

void application_task ( void )
{
    log_info( &logger, "---- Volume level control testing... ----" );

    audioamp_set_volume( &audioamp, AUDIOAMP_IN_1 | AUDIOAMP_IN_2, 5 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    audioamp_set_volume( &audioamp, AUDIOAMP_IN_1 | AUDIOAMP_IN_2, 15 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    audioamp_set_volume( &audioamp, AUDIOAMP_IN_1 | AUDIOAMP_IN_2, 25 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    audioamp_set_volume( &audioamp, AUDIOAMP_IN_1 | AUDIOAMP_IN_2, 32 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_info( &logger, "---- Volume level control test done. ----" );
    log_info( &logger, "---- Input mute/unmute control testing... ----" );

    audioamp_mute( &audioamp );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    audioamp_unmute( &audioamp );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_info( &logger, "---- Input mute/unmute control test done. ----" );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAmp

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
