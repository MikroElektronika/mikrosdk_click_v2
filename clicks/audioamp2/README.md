
---
# Audio Amp 2 Click

> [AudioAmp 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3077) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3077&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application amplifies the sound on the speakers.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAmp2

### Example Key Functions

- `audioamp2_cfg_setup` Config Object Initialization function. 
```c
void audioamp2_cfg_setup ( audioamp2_cfg_t *cfg );
``` 
 
- `audioamp2_init` Initialization function. 
```c
err_t audioamp2_init ( audioamp2_t *ctx, audioamp2_cfg_t *cfg );
```

- `audioamp2_set_mode` Mode Set function. 
```c
uint8_t audioamp2_set_mode( audioamp2_t *ctx, uint8_t sel_mode );
```
 
- `audioamp2_set_gain` Gain Set function. 
```c
uint8_t audioamp2_set_gain( audioamp2_t *ctx, uint8_t sel_gain );
```

- `audioamp2_check_diagnostic` Diagnostic Check function. 
```c
uint8_t audioamp2_check_diagnostic( audioamp2_t *ctx );
```

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

### Note

> Internally, the gain is set by changing the feedback resistors of the amplifier.

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
