
---
# HAPTIC Click

> [HAPTIC Click](https://www.mikroe.com/?pid_product=MIKROE-2025) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2025&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application generate vibrations from the lower frequency range of the audio input. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Haptic

### Example Key Functions

- `haptic_cfg_setup` Config Object Initialization function. 
```c
void haptic_cfg_setup ( haptic_cfg_t *cfg );
``` 
 
- `haptic_init` Initialization function. 
```c
err_t haptic_init ( haptic_t *ctx, haptic_cfg_t *cfg );
```

- `haptic_enable` Enable the device function. 
```c
void haptic_enable (  haptic_t *ctx );
```
 
- `haptic_disable`  Disable the device function. 
```c
void haptic_disable ( haptic_t *ctx );
```

- `haptic_set_mode` Sets the Haptic Click to desired mode function. 
```c
void haptic_set_mode ( haptic_t *ctx, uint8_t sel_mode );
```

### Application Init

> Configures the Click board in Audio-to-Vibe mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    haptic_cfg_t cfg;

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

    haptic_cfg_setup( &cfg );
    HAPTIC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    haptic_init( &haptic, &cfg );

    log_printf( &logger, " Configuring the Click board...\r\n" );
    log_printf( &logger, "----------------------- \r\n" );
    
    haptic_enable( &haptic );
    haptic_set_mode( &haptic, HAPTIC_MODE_AUTOCAL );
    haptic_start_motor( &haptic );
    Delay_ms ( 500 );

    haptic_set_mode( &haptic, HAPTIC_MODE_AUDIOVIBE );
    haptic_enable_ac_coulping( &haptic );
    haptic_set_input_to_analog( &haptic );
    
    log_printf( &logger, " The Click board is configured in Audio-to-Vibe mode...\r\n" );
}
```

### Application Task

> An infinite loop.

```c
void application_task ( void )
{
    // Nothing to do here...
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
