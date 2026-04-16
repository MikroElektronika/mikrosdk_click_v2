
---
# Volume 3 Click

> [Volume 3 Click](https://www.mikroe.com/?pid_product=MIKROE-6818) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6818&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2025.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates control of the Volume 3 Click stereo attenuator.
The app enables zero-crossing and audio output, then sweeps left and right
volumes in opposite directions while logging their levels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Volume3

### Example Key Functions

- `volume3_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void volume3_cfg_setup ( volume3_cfg_t *cfg );
```

- `volume3_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t volume3_init ( volume3_t *ctx, volume3_cfg_t *cfg );
```

- `volume3_set_volume` This function sets the left and right channel volume levels in percents.
```c
err_t volume3_set_volume ( volume3_t *ctx, uint8_t volume_left, uint8_t volume_right );
```

- `volume3_set_gain` This function sets the left and right channel gain in dB.
```c
err_t volume3_set_gain ( volume3_t *ctx, float gain_left, float gain_right );
```

- `volume3_sound_enable` This function enables the audio output by setting the SEN pin high.
```c
void volume3_sound_enable ( volume3_t *ctx );
```

### Application Init

> Initializes the logger, configures the driver, and enables output with zero-crossing.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    volume3_cfg_t volume3_cfg;  /**< Click config object. */

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
    volume3_cfg_setup( &volume3_cfg );
    VOLUME3_MAP_MIKROBUS( volume3_cfg, MIKROBUS_POSITION_VOLUME3 );
    if ( SPI_MASTER_ERROR == volume3_init( &volume3, &volume3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    volume3_zero_crossing_enable ( &volume3 );
    volume3_sound_enable ( &volume3 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Gradually changes left and right volume in opposite directions, printing their values to the log.

```c
void application_task ( void )
{
    static int8_t volume = VOLUME3_VOLUME_MUTE;
    static int8_t step = 1;
    
    if ( VOLUME3_OK == volume3_set_volume ( &volume3, volume, VOLUME3_VOLUME_MAX - volume ) )
    {
        log_printf( &logger, " Volume [L/R]: %u/%u %%\r\n\n", 
                    ( uint16_t ) volume, ( uint16_t ) ( VOLUME3_VOLUME_MAX - volume ) );
        Delay_ms ( 100 );
    }

    volume += step;
    if ( ( volume > VOLUME3_VOLUME_MAX ) || ( volume < VOLUME3_VOLUME_MUTE ) )
    {
        Delay_ms ( 1000 );
        step = -step;
        volume += step;
        volume += step;
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
