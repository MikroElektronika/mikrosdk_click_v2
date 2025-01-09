
---
# Headphone AMP 2 Click

> [Headphone AMP 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5577) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5577&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jun 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Headphone AMP 2 Click board&trade;, 
> the headphone amplifier with BassMax and volume control.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HeadphoneAMP2

### Example Key Functions

- `headphoneamp2_cfg_setup` Config Object Initialization function.
```c
void headphoneamp2_cfg_setup ( headphoneamp2_cfg_t *cfg );
```

- `headphoneamp2_init` Initialization function.
```c
err_t headphoneamp2_init ( headphoneamp2_t *ctx, headphoneamp2_cfg_t *cfg );
```

- `headphoneamp2_default_cfg` Click Default Configuration function.
```c
err_t headphoneamp2_default_cfg ( headphoneamp2_t *ctx );
```

- `headphoneamp2_set_command` Headphone AMP 2 set the command function.
```c
err_t headphoneamp2_set_command ( headphoneamp2_t *ctx, headphoneamp2_cmd_t cmd_ctrl );
```

- `headphoneamp2_enable` Headphone AMP 2 enable the device function.
```c
void headphoneamp2_enable ( headphoneamp2_t *ctx );
```

- `headphoneamp2_disable` Headphone AMP 2 disable the device function.
```c
void headphoneamp2_disable ( headphoneamp2_t *ctx );
```

### Application Init

> The initialization of I2C module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    headphoneamp2_cfg_t headphoneamp2_cfg;  /**< Click config object. */

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
    headphoneamp2_cfg_setup( &headphoneamp2_cfg );
    HEADPHONEAMP2_MAP_MIKROBUS( headphoneamp2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == headphoneamp2_init( &headphoneamp2, &headphoneamp2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HEADPHONEAMP2_ERROR == headphoneamp2_default_cfg ( &headphoneamp2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Headphone AMP 2 Click board&trade;.
> The application wakes up the device, enables BassMax and Maximum Gain modes, 
> and switches the sound volume from level 1 to the max level.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static headphoneamp2_cmd_t cmd_ctrl;
    cmd_ctrl.wakes_up = HEADPHONEAMP2_CMD_ENABLE;
    cmd_ctrl.bass_max = HEADPHONEAMP2_CMD_ENABLE;
    cmd_ctrl.gain_max = HEADPHONEAMP2_CMD_ENABLE;
    cmd_ctrl.volume   = HEADPHONEAMP2_VOL_MUTE;
    
    log_printf( &logger, " Volume : " );
    for ( uint8_t volume = HEADPHONEAMP2_VOL_LVL_1; volume <= HEADPHONEAMP2_VOL_LVL_MAX; volume++ )
    {
        cmd_ctrl.volume = volume;
        if ( HEADPHONEAMP2_OK == headphoneamp2_set_command( &headphoneamp2, cmd_ctrl ) )
        {
            log_printf( &logger, "|" );
        }
        Delay_ms ( 1000 );
    }
    log_printf( &logger, "\r\n-------------------------\r\n" );
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
