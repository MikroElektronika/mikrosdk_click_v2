
---
# EVC Click

> [EVC Click](https://www.mikroe.com/?pid_product=MIKROE-3358) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3358&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application allows manipulation of 6 channel volume control .

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EVC

### Example Key Functions

- `evc_cfg_setup` Config Object Initialization function. 
```c
void evc_cfg_setup ( evc_cfg_t *cfg );
``` 
 
- `evc_init` Initialization function. 
```c
err_t evc_init ( evc_t *ctx, evc_cfg_t *cfg );
```

- `evc_default_cfg` Click Default Configuration function. 
```c
void evc_default_cfg ( evc_t *ctx );
```

- `evc_set_volume_part` This function sets the volume for the selected channel, uses two variables. 
```c
void evc_set_volume_part ( evc_t *ctx, uint8_t channel, uint8_t volume1, uint8_t volume2 );
```
 
- `evc_set_volume_full` This function sets the volume for the selected channel, uses one volume variables. 
```c
void evc_set_volume_full ( evc_t *ctx, uint8_t channel, int8_t volume );
```

- `evc_mute` This function mute and unmute the sound. 
```c
void evc_mute ( evc_t *ctx, uint8_t mute );
```

### Application Init

> Initialization driver init, default configuration and sets first volume.

```c
void application_init ( void )
{
log_cfg_t log_cfg;
    evc_cfg_t cfg;

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

    evc_cfg_setup( &cfg );
    EVC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    evc_init( &evc, &cfg );

    evc_default_cfg( &evc );
    log_printf( &logger, " \\-/-\\-/ START EQUALIZER \\-/-\\-/ ");
}
```

### Application Task

> Emulates user input and exectuyrd functions based on set of valid commands.

```c
void application_task ( void )
{
 //  Task implementation.

    test_change( &evc );

    play( &evc );
}
```

### Note
 
> Additional Functions : 
> void test_change ( )               - Emulates user input to change parameters.
> void mute( )                       - Mute nad 
> void play ( )                      - Start new settings of the cahnnel
> uint8_t get_current_channel ( )    - Return current channel.

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
