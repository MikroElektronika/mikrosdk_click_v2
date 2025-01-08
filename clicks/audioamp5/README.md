
---
# Audio Amp 5 Click

> [AudioAmp 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3401) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3401&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example consist of sending special commands for audio output control, 
> selecting different output modes and turning on/off the audio output.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAmp5

### Example Key Functions

- `audioamp5_cfg_setup` Config Object Initialization function. 
```c
void audioamp5_cfg_setup ( audioamp5_cfg_t *cfg );
``` 
 
- `audioamp5_init` Initialization function. 
```c
err_t audioamp5_init ( audioamp5_t *ctx, audioamp5_cfg_t *cfg );
```

- `audioamp5_default_cfg` Click Default Configuration function. 
```c
void audioamp5_default_cfg ( audioamp5_t *ctx );
```

- `audioamp5_mode_select` Function puts a device to the desired mode. 
```c
void audioamp5_mode_select ( audioamp5_t *ctx, uint8_t state );
```

- `audioamp5_gain_select` Function performs a desired gain selection. 
```c
void audioamp5_gain_select ( audioamp5_t *ctx, uint8_t state );
```

- `audioamp5_config_update` Function to update the configuration of the module. 
```c
void audioamp5_config_update ( audioamp5_t *ctx );
```

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

### Note

> After each command for device configuration, the command for configuration 
> updating will be executed.
> When BD Mode (0) is selected, the VIN supply voltage threshold is 7.5V.
> When Low-Idle-Current 1SPW Mode is selected, the VIN supply voltage threshold > is 3.4V.

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
