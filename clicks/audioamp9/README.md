
---
# AudioAmp 9 Click

> [AudioAmp 9 Click](https://www.mikroe.com/?pid_product=MIKROE-5595) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5595&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the AudioAmp 9 Click board by 
 changing the gain level.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAmp9

### Example Key Functions

- `audioamp9_cfg_setup` Config Object Initialization function.
```c
void audioamp9_cfg_setup ( audioamp9_cfg_t *cfg );
```

- `audioamp9_init` Initialization function.
```c
err_t audioamp9_init ( audioamp9_t *ctx, audioamp9_cfg_t *cfg );
```

- `audioamp9_default_cfg` Click Default Configuration function.
```c
void audioamp9_default_cfg ( audioamp9_t *ctx );
```

- `audioamp9_shutdown_on` AudioAmp 9 shutdown on function.
```c
void audioamp9_shutdown_on ( audioamp9_t *ctx );
```

- `audioamp9_mute_off` AudioAmp 9 mute off function.
```c
void audioamp9_mute_off ( audioamp9_t *ctx );
```

- `audioamp9_set_gain_level` AudioAmp 9 set gain function.
```c
err_t audioamp9_set_gain_level ( audioamp9_t *ctx, uint8_t gain_level );
```

### Application Init

> Initializes the driver and performs default configuration putting AudioAmp 9 Click 
 into Gain 1 mode with unmuted output.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    audioamp9_cfg_t audioamp9_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    audioamp9_cfg_setup( &audioamp9_cfg );
    AUDIOAMP9_MAP_MIKROBUS( audioamp9_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == audioamp9_init( &audioamp9, &audioamp9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    audioamp9_default_cfg ( &audioamp9 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Controlling the volume of the speaker by setting the gain level, and increasing it 
 every 5 seconds until the maximum level is reached, then the sound is muted for 5 seconds.

```c
void application_task ( void ) 
{
    for ( uint8_t vol_lvl = AUDIOAMP9_GAIN_LEVEL1; vol_lvl <= AUDIOAMP9_GAIN_LEVEL4; vol_lvl++ )
    {
        audioamp9_set_gain_level( &audioamp9, vol_lvl );
        log_printf( &logger, " Volume gain level %d \r\n ", vol_lvl );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Sound is muted \r\n " );
    audioamp9_mute_on( &audioamp9 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Sound is unmuted \r\n " );
    audioamp9_mute_off( &audioamp9 );
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
