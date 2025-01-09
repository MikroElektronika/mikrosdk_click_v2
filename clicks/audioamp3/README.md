
---
# AudioAmp 3 Click

> [AudioAmp 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3901) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3901&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mihajlo Djordjevic
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> 
> This is an example which demonstrates the use of AudioAmp 3 Click board, stereo audio amplifier.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAmp3

### Example Key Functions

- `audioamp3_cfg_setup` Config Object Initialization function. 
```c
void audioamp3_cfg_setup ( audioamp3_cfg_t *cfg );
``` 
 
- `audioamp3_init` Initialization function. 
```c
err_t audioamp3_init ( audioamp3_t *ctx, audioamp3_cfg_t *cfg );
```

- `audioamp3_default_cfg` Click Default Configuration function. 
```c
void audioamp3_default_cfg ( audioamp3_t *ctx );
```

- `audioamp3_power_up` This function power up the audio amplifier by sets to '1' state of the STB pin of the AudioAmp 3 Click board. 
```c
void audioamp3_power_up ( audioamp3_t *ctx );
```
 
- This function set the play mode for all channels by writing the appropriate value to 
- the target AUDIOAMP3_EXT_CTRL_REG_5 ( 0x0C ) register of TAS5414C-Q1 
- `audioamp3_set_play_mode` four channel digital audio amplifiers on AudioAmp 3 Click board. 
```c
AUDIOAMP3_STATUS_T audioamp3_set_play_mode ( audioamp3_t *ctx );
```

- This function set the gain level for all channels by writing the appropriate value 
- to the target AUDIOAMP3_EXT_CTRL_REG_1 ( 0x08 ) register of TAS5414C-Q1 
- `audioamp3_set_gain_lvl` four channel digital audio amplifiers on AudioAmp 3 Click board. 
```c
AUDIOAMP3_STATUS_T audioamp3_set_gain_lvl ( audioamp3_t *ctx, uint8_t gain_lvl );
```

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
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
	
    log_printf( &logger, " ---------------------------\r\n\n" );
    
    for ( cnt = AUDIOAMP3_GAIN_VAL_MAX; cnt > AUDIOAMP3_GAIN_VAL_0; cnt-- )
    {
        status_flag = audioamp3_set_gain_lvl( &audioamp3, cnt );
    
        log_printf( &logger, "    -  Volume Down  -  \r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
	
    log_printf( &logger, " ---------------------------\r\n\n" );
}

``` 

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
