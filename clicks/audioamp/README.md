
---
# AudioAmp Click

> [AudioAmp Click](https://www.mikroe.com/?pid_product=MIKROE-2368) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2368&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> AudioAmp Click is a stereo audio amplifier which can be controlled by using this Click driver.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAmp

### Example Key Functions

- `audioamp_cfg_setup` Config Object Initialization function.
```c
void audioamp_cfg_setup ( audioamp_cfg_t *cfg ); 
```

- `audioamp_init` Initialization function.
```c
err_t audioamp_init ( audioamp_t *ctx, audioamp_cfg_t *cfg );
```

- `audioamp_set_volume` Set volume function.
```c
err_t audioamp_set_volume ( audioamp_t *ctx, uint8_t in_sel, uint8_t volume_level );
```

- `audioamp_power_on` Turn on the Audio Amp Click function.
```c
err_t audioamp_power_on ( audioamp_t *ctx );
```

- `audioamp_mute` Mute input function.
```c
err_t audioamp_mute ( audioamp_t *ctx );
```

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
