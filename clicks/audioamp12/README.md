
---
# AudioAMP 12 Click

> [AudioAMP 12 Click](https://www.mikroe.com/?pid_product=MIKROE-5796) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5796&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jun 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of AudioAMP 12 Click board&trade;. 
> The library contains an API for switching between two gain settings 
> and device control selection between operation and standby mode.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAMP12

### Example Key Functions

- `audioamp12_cfg_setup` Config Object Initialization function.
```c
void audioamp12_cfg_setup ( audioamp12_cfg_t *cfg );
```

- `audioamp12_init` Initialization function.
```c
err_t audioamp12_init ( audioamp12_t *ctx, audioamp12_cfg_t *cfg );
```

- `audioamp12_default_cfg` Click Default Configuration function.
```c
void audioamp12_default_cfg ( audioamp12_t *ctx );
```

- `audioamp12_change_gain`  AudioAMP 12 changes the gain function.
```c
void audioamp12_change_gain ( audioamp12_t *ctx );
```

- `audioamp12_gain_select` AudioAMP 12 select gain level function.
```c
void audioamp12_gain_select ( audioamp12_t *ctx, audioamp12_gain_select_t sel_gain );
```

- `audioamp12_set_mode_operation` AudioAMP 12 set operation mode function.
```c
void audioamp12_set_mode_operation ( audioamp12_t *ctx );
```

### Application Init

> Initialization of GPIO module and log UART. After driver initialization, 
> the app sets default settings performs a power-up sequence, and sets the sound volume to 6 dB.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    audioamp12_cfg_t audioamp12_cfg;    /**< Click config object. */

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
    audioamp12_cfg_setup( &audioamp12_cfg );
    AUDIOAMP12_MAP_MIKROBUS( audioamp12_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == audioamp12_init( &audioamp12, &audioamp12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    audioamp12_default_cfg ( &audioamp12 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The app performs circles the volume switch between two gain settings, 
> 6 dB or 12 dB, every 5 seconds. 
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    audioamp12_gain_select( &audioamp12, AUDIOAMP12_GAIN_6_DB );
    log_printf( &logger, " Gain set to 6 dB.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    audioamp12_gain_select( &audioamp12, AUDIOAMP12_GAIN_12_DB );
    log_printf( &logger, " Gain set to 12 dB.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
