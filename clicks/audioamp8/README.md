
---
# AudioAmp 8 Click

> [AudioAmp 8 Click](https://www.mikroe.com/?pid_product=MIKROE-4812) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4812&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for AudioAmp 8 Click driver.
> The library initializes and defines the I2C bus drivers 
> to write and read data from registers. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioAmp8

### Example Key Functions

- `audioamp8_cfg_setup` Config Object Initialization function.
```c
void audioamp8_cfg_setup ( audioamp8_cfg_t *cfg );
```

- `audioamp8_init` Initialization function.
```c
err_t audioamp8_init ( audioamp8_t *ctx, audioamp8_cfg_t *cfg );
```

- `audioamp8_default_cfg` Click Default Configuration function.
```c
err_t audioamp8_default_cfg ( audioamp8_t *ctx );
```

- `audioamp8_set_config_power_mode` AudioAmp 8 set power mode configuration function.
```c
err_t audioamp8_set_config_power_mode ( audioamp8_t *ctx, audioamp8_pwr_mon_cfg_t pwr_mode );
```

- `audioamp8_set_config_power_mode_profile` AudioAmp 8 set power mode profile configuration function.
```c
err_t audioamp8_set_config_power_mode_profile ( audioamp8_t *ctx, audioamp8_pwr_mod_profile_cfg_t pm_profile );
```

- `audioamp8_channel_monitoring` AudioAmp 8 monitors the status of the channel's function.
```c
err_t audioamp8_channel_monitoring ( audioamp8_t *ctx, uint8_t mon_ch, audioamp8_monitor_channel_t *ch_mon );
```

### Application Init

> The initialization of I2C  module, log UART, and additional pins. 
> After the driver init and then executes a default configuration, 
> the app performs a BTL signal configuration, configure power mode
> and configure power mode profile.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    audioamp8_cfg_t audioamp8_cfg;  /**< Click config object. */

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
    audioamp8_cfg_setup( &audioamp8_cfg );
    AUDIOAMP8_MAP_MIKROBUS( audioamp8_cfg, MIKROBUS_1 );
    err_t init_flag = audioamp8_init( &audioamp8, &audioamp8_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    if ( AUDIOAMP8_ERROR == audioamp8_default_cfg ( &audioamp8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> This is an example that shows the use of a AudioAmp 8 Click board&trade;.
> Display status monitoring for the channel 0 or channel 1.
> This task repeats every 2 seconds.

```c
void application_task ( void ) 
{
    channel_status_monitoring( AUDIOAMP8_SET_MON_CH_0 );
    Delay_ms ( 1000 );
}
```

## Additional Function
- `channel_status_monitoring` The function displays the status monitoring channel.
```c
static void channel_status_monitoring ( uint8_t ch_sel );
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
