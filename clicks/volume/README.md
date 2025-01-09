
---
# Volume Click

> [Volume Click](https://www.mikroe.com/?pid_product=MIKROE-4450) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4450&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Nikolic
- **Date**          : nov 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This example sets up the device and performs volume turn up and down.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Volume

### Example Key Functions

- `volume_cfg_setup` Config Object Initialization function.
```c
void volume_cfg_setup ( volume_cfg_t *cfg );
```

- `volume_init` Initialization function.
```c
err_t volume_init ( volume_t *ctx, volume_cfg_t *cfg );
```

- `volume_default_cfg` Click Default Configuration function.
```c
void volume_default_cfg ( volume_t *ctx );
```

- `volume_set_vol_gain` Set volume gain function.
```c
err_t volume_set_vol_gain ( volume_t *ctx, float volume_left_dB, float volume_right_dB );
```

- `volume_power_up` Power Up function.
```c
void volume_power_up ( volume_t *ctx );
```

- `volume_hw_mute` Hardware MUTE function.
```c
void volume_hw_mute ( volume_t *ctx, uint8_t mute_state );
```

### Application Init

> Initializes drivers and powers up the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    volume_cfg_t volume_cfg;  /**< Click config object. */

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

    volume_cfg_setup( &volume_cfg );
    VOLUME_MAP_MIKROBUS( volume_cfg, MIKROBUS_1 );
    err_t init_flag  = volume_init( &volume, &volume_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    volume_default_cfg ( &volume );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Circles the volume from -40 [dB] to 10 [dB] back and forth.

```c
void application_task ( void ) 
{
    left_speaker_gain  = -40;
    right_speaker_gain = -40;
    one_circle = 0;
    
    log_printf( &logger, " Turning volume up.\r\n" );
    while ( one_circle < 2 ) {
        if ( one_circle == 0 ) {
            if ( left_speaker_gain <= 10 || right_speaker_gain <= 10 ) {
                volume_set_vol_gain( &volume, left_speaker_gain, right_speaker_gain );
                left_speaker_gain += 0.5;
                right_speaker_gain += 0.5;
                Delay_ms ( 50 );
            } else {
                one_circle++;
                log_printf( &logger, " Turning volume down.\r\n" );
            }
        } else if ( left_speaker_gain >= -40 || right_speaker_gain >= -40 ) {
            volume_set_vol_gain( &volume, left_speaker_gain, right_speaker_gain );
            left_speaker_gain -= 0.5;
            right_speaker_gain -= 0.5;
            Delay_ms ( 50 );
        } else one_circle++;
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
