

---
# AudioAmp 3 click

AudioAmp 3 Click is a stereo audio amplifier, capable of delivering up to 79W per channel with the 4Ω load.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/audioamp3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/audioamp-3-click)

---


#### Click library 

- **Author**        : Mihajlo Djordjevic
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the AudioAmp3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AudioAmp3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void audioamp3_cfg_setup ( audioamp3_cfg_t *cfg ); 
 
- Initialization function.
> AUDIOAMP3_RETVAL audioamp3_init ( audioamp3_t *ctx, audioamp3_cfg_t *cfg );

- Click Default Configuration function.
> void audioamp3_default_cfg ( audioamp3_t *ctx );

#### Example key functions :

- This function power up the audio amplifier by sets to '1' state of the STB pin of the AudioAmp 3 click board.
> void audioamp3_power_up ( audioamp3_t *ctx );
 
- This function set the play mode for all channels by writing the appropriate value to 
- the target AUDIOAMP3_EXT_CTRL_REG_5 ( 0x0C ) register of TAS5414C-Q1 
- four channel digital audio amplifiers on AudioAmp 3 click board.
> AUDIOAMP3_STATUS_T audioamp3_set_play_mode ( audioamp3_t *ctx );

- This function set the gain level for all channels by writing the appropriate value 
- to the target AUDIOAMP3_EXT_CTRL_REG_1 ( 0x08 ) register of TAS5414C-Q1 
- four channel digital audio amplifiers on AudioAmp 3 click board.
> AUDIOAMP3_STATUS_T audioamp3_set_gain_lvl ( audioamp3_t *ctx, uint8_t gain_lvl );

## Examples Description

> 
> This is an example which demonstrates the use of AudioAmp 3 click board, stereo audio amplifier.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Application Init performs Logger and Click initialization.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    audioamp3_cfg_t cfg;

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
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 100 );

    //  Click initialization.

    audioamp3_cfg_setup( &cfg );
    AUDIOAMP3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioamp3_init( &audioamp3, &cfg );
    
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, "--- AudioAmp  3  Click ---\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
    
    audioamp3_power_up( &audioamp3 );
    log_printf( &logger, "          Power Up          \r\n" );
    log_printf( &logger, " ---------------------------\r\n\n" );
    Delay_100ms();
    
    audioamp3_set_channel_low_to_low( &audioamp3, AUDIOAMP3_MASK_BIT_SEL_CH_1 );
    log_printf( &logger, " Set channel 1 low-low state \r\n" );
    log_printf( &logger, " ---------------------------\r\n\n" );
    Delay_100ms();
    
    audioamp3_set_channel_low_to_low( &audioamp3, AUDIOAMP3_MASK_BIT_SEL_CH_2 );
    log_printf( &logger, " Set channel 2 low-low state \r\n" );
    log_printf( &logger, " ---------------------------\r\n\n" );
    Delay_100ms();
    
    audioamp3_set_channel_mute_mode( &audioamp3, AUDIOAMP3_MASK_BIT_SEL_ALL_CH );
    log_printf( &logger, "      Mute All Channels     \r\n" );
    log_printf( &logger, " ---------------------------\r\n\n" );
    Delay_100ms();
    
    audioamp3_run_channel_diagnostics( &audioamp3, AUDIOAMP3_MASK_BIT_SEL_ALL_CH );
    log_printf( &logger, "       Run Diagnostics      \r\n" );
    log_printf( &logger, " ---------------------------\r\n\n" );
    Delay_100ms();
    
    audioamp3_hw_reset( &audioamp3 );
    log_printf( &logger, "       Hardware Reset       \r\n" );
    log_printf( &logger, " ---------------------------\r\n\n" );
    Delay_100ms();
    
    audioamp3_read_all_diagnostics( &audioamp3, &data_out[ 0 ] );
    log_printf( &logger, "      Read Diagnostics      \r\n" );
    log_printf( &logger, " ---------------------------\r\n\n" );
    Delay_100ms();
    
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, "    Initialization  done  \r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
    
    audioamp3_set_play_mode( &audioamp3 );
    log_printf( &logger, " ---------------------------\r\n\n" );
    log_printf( &logger, "            Play            \r\n" );
    log_printf( &logger, " ---------------------------\r\n\n" );
    Delay_100ms();
}
  
```

### Application Task

>
> This is an example which waits for valid user input and executes functions based on set of valid commands.
> Results are being sent to the UART Terminal where you can track their changes.
> 

```c

void application_task ( void )
{
    for ( cnt = AUDIOAMP3_GAIN_VAL_MIN; cnt < AUDIOAMP3_GAIN_VAL_5; cnt++ )
    {
        status_flag = audioamp3_set_gain_lvl( &audioamp3, cnt );
        log_printf( &logger, "    -  Volume Up  -  \r\n" );
        Delay_ms( 2000 );
    }
	
    log_printf( &logger, " ---------------------------\r\n\n" );
    
    for ( cnt = AUDIOAMP3_GAIN_VAL_MAX; cnt > AUDIOAMP3_GAIN_VAL_0; cnt-- )
    {
        status_flag = audioamp3_set_gain_lvl( &audioamp3, cnt );
    
        log_printf( &logger, "    -  Volume Down  -  \r\n" );
        Delay_ms( 2000 );
    }
	
    log_printf( &logger, " ---------------------------\r\n\n" );
}  

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAmp3

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
