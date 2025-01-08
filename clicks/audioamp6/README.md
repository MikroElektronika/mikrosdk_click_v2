
---
# AudioAmp 6 Click

> [AudioAmp 6 Click](https://www.mikroe.com/?pid_product=MIKROE-3448) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3448&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> The demo application displays the volume change using AudioAmp 6 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAmp6

### Example Key Functions

- `audioamp6_cfg_setup` Config Object Initialization function. 
```c
void audioamp6_cfg_setup ( audioamp6_cfg_t *cfg );
``` 
 
- `audioamp6_init` Initialization function. 
```c
err_t audioamp6_init ( audioamp6_t *ctx, audioamp6_cfg_t *cfg );
```

- `audioamp6_set_mode` Sets device mode. 
```c
void audioamp6_set_mode ( audioamp6_t *ctx, uint8_t mode );
```
 
- `audioamp6_set_output` Enable or disable output. 
```c
void audioamp6_set_output ( audioamp6_t *ctx, uint8_t out );
```

- `audioamp6_set_gain` Sets device gain. 
```c
void audioamp6_set_gain ( audioamp6_t *ctx, uint8_t gain );
```

### Application Init

> Configuring Clicks and log objects.
> Select mode and sets output on the enable state. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    audioamp6_cfg_t cfg;

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

    audioamp6_cfg_setup( &cfg );
    AUDIOAMP6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioamp6_init( &audioamp6, &cfg );

    audioamp6_set_mode( &audioamp6, AUDIOAMP6_MODE_BD );
    audioamp6_set_output( &audioamp6, AUDIOAMP6_OUTPUT_ENABLE );

    log_info( &logger, "---- Start control AudioAmp 6 Click ----" );
}
```

### Application Task

> Changes the gain settings ( 20dB - 26dB )

```c
void application_task ( void )
{
    //  Task implementation.

    log_printf( &logger, ">> Set gain 20 dB \r\n" );
    audioamp6_set_gain( &audioamp6, AUDIOAMP6_GAIN_20dB );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, ">> Set gain 26 dB \r\n" );
    audioamp6_set_gain( &audioamp6, AUDIOAMP6_GAIN_26dB );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Sets the input voltage from 3.5V to 14.4V.

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
