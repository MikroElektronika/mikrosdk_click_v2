
---
# Touchpad 4 Click

> [Touchpad 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4752) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4752&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases ability of the device to read touch coordinates, 
active/inactive channels, and gesture informations.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Touchpad4

### Example Key Functions

- `touchpad4_cfg_setup` Config Object Initialization function.
```c
void touchpad4_cfg_setup ( touchpad4_cfg_t *cfg );
```

- `touchpad4_init` Initialization function.
```c
err_t touchpad4_init ( touchpad4_t *ctx, touchpad4_cfg_t *cfg );
```

- `touchpad4_default_cfg` Click Default Configuration function.
```c
err_t touchpad4_default_cfg ( touchpad4_t *ctx );
```

- `touchpad4_reset` Reset function.
```c
void touchpad4_reset ( touchpad4_t *ctx );
```

- `touchpad4_get_touch` Read touch informations.
```c
err_t touchpad4_get_touch ( touchpad4_t *ctx, touchpad4_info_t *touch_info );
```

- `touchpad_get_channels` Read channel information.
```c
err_t touchpad_get_channels ( touchpad4_t *ctx, uint32_t *channels );
```

### Application Init

> Initialize host communication modules(UART and I2C)  and additional pins,
for device control. Then resets device and set default configuration where
Channels and pins are mapped and configured, and set communication with device
only on touch/event. In the end one of 3 examples is set;

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    touchpad4_cfg_t touchpad4_cfg;  /**< Click config object. */

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
    touchpad4_cfg_setup( &touchpad4_cfg );
    TOUCHPAD4_MAP_MIKROBUS( touchpad4_cfg, MIKROBUS_1 );
    err_t init_flag = touchpad4_init( &touchpad4, &touchpad4_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    touchpad4_reset( &touchpad4 );

    init_flag = touchpad4_default_cfg ( &touchpad4 );
    if ( TOUCHPAD4_ERROR == init_flag ) 
    {
        log_error( &logger, " Configuration. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    example_selector = TOUCHPAD4_EXAMPLE_TOUCH;
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> There are 3 examples that shocaes ability of the device: 
 - Reading touch coorinates and addinal informations of touch strength, 
   and touch area and logging them,
 - Reading channel statuses and show them by logging them,
 - Reading gesture events and logging them;

```c
void application_task ( void ) 
{
    if ( !touchpad4_get_ready( &touchpad4 ) )
    {
        switch ( example_selector )
        {
            case TOUCHPAD4_EXAMPLE_TOUCH:
            {
                touchpad4_touch_reading( );
                break;
            }
            case TOUCHPAD4_EXAMPLE_CHANNEL:
            {
                touchpad4_channel_reading( );
                break;
            }
            case TOUCHPAD4_EXAMPLE_GESTURE:
            {
                touchpad4_gesture_reading( );
                break;
            }
            default:
            {
                log_error( &logger, " Select Example" );
                break;
            }
        } 
    }
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
