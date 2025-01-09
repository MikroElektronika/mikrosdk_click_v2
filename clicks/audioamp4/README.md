
---
# AudioAmp 4 Click

> [AudioAmp 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3271) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3271&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example switches device on & off and sets three different volumes.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAmp4

### Example Key Functions

- `audioamp4_cfg_setup` Config Object Initialization function. 
```c
void audioamp4_cfg_setup ( audioamp4_cfg_t *cfg );
``` 
 
- `audioamp4_init` Initialization function. 
```c
err_t audioamp4_init ( audioamp4_t *ctx, audioamp4_cfg_t *cfg );
```

- `audioamp4_default_cfg` Click Default Configuration function. 
```c
void audioamp4_default_cfg ( audioamp4_t *ctx );
```

- `audioamp4_set_channel` This function sets the volume channel. 
```c
err_t audioamp4_set_channel ( audioamp4_t *ctx, uint8_t channel );
```
 
- This function is used to switch device ON or OFF
err_t audioamp4_shutdown ( audioamp4_t *ctx, uint8_t state );

### Application Init

> Initializes GPIO interface, turns module ON and sets the volume value to 0.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    audioamp4_cfg_t cfg;

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

    audioamp4_cfg_setup( &cfg );
    AUDIOAMP4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioamp4_init( &audioamp4, &cfg );
    audioamp4_default_cfg( &audioamp4 );
}
```

### Application Task

> Turns device OFF & ON and sets three different volume values.

```c
void application_task ( void )
{
    log_info( &logger, "Turn on device:" );
    application_error_handler( audioamp4_shutdown( &audioamp4, AUDIOAMP4_SHUTDOWN_OFF ) );
    
    log_info( &logger, "Set volume channel 1:" );
    application_error_handler( audioamp4_set_channel( &audioamp4, AUDIOAMP4_VOLUME_CHANN_1 ) );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_info( &logger, "Set volume channel 5:" );
    application_error_handler( audioamp4_set_channel( &audioamp4, AUDIOAMP4_VOLUME_CHANN_5 ) );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_info( &logger, "Set volume channel 7:" );
    application_error_handler( audioamp4_set_channel( &audioamp4, AUDIOAMP4_VOLUME_CHANN_7 ) );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_info( &logger, "Turn off device:" );
    application_error_handler( audioamp4_shutdown( &audioamp4, AUDIOAMP4_SHUTDOWN_ON ) );
    Delay_ms ( 500 );
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
