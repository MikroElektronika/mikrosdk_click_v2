
---
# Volume 2 Click

> [Volume 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4560) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4560&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Nikolic
- **Date**          : feb 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example shows how Volume 2 Click board can be used
for controlling the audio channels. Thanks to this, a
simple audio effect is created by switching volume from
right to left and vice versa.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Volume2

### Example Key Functions

- `volume2_cfg_setup` Config Object Initialization function.
```c
void volume2_cfg_setup ( volume2_cfg_t *cfg );
```

- `volume2_init` Initialization function.
```c
err_t volume2_init ( volume2_t *ctx, volume2_cfg_t *cfg );
```

- `volume2_default_cfg` Click Default Configuration function.
```c
void volume2_default_cfg ( volume2_t *ctx );
```

- `volume2_update_vol_data` This function updates the volume by using direct defined structure options.
```c
err_t volume2_update_vol_data ( volume2_t *ctx, volume2_vol_data_t update_data );
```

- `volume2_device_mute` This function is used to set mute on or off by controlling the mte pin.
```c
err_t volume2_device_mute ( volume2_t *ctx, uint8_t mte_state );
```

- `volume2_generic_write` This function writes a desired number of data bytes starting from the selected register by using I2C serial interface.
```c
err_t volume2_generic_write ( volume2_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );
```

### Application Init

> UART LOG and I2C drivers are initialized, following the
default configuration. By default, both channels are set
to 9 dB gain with zero cross detection enabled.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    volume2_cfg_t volume2_cfg;  /**< Click config object. */

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

    volume2_cfg_setup( &volume2_cfg );
    VOLUME2_MAP_MIKROBUS( volume2_cfg, MIKROBUS_1 );
    err_t init_flag = volume2_init( &volume2, &volume2_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    volume2_default_cfg( &volume2 );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The task performs and effect of switching the volume
from right to left channel and vice versa. Like playing
ping-pong with the sound.

```c
void application_task ( void ) 
{
    for ( rising_vol = 0 ; rising_vol < max_atten ; rising_vol++ ) {
        volume_upd_data.attenuation_ch1 = rising_vol;
        volume_upd_data.attenuation_ch2 = max_atten - rising_vol;
        volume2_update_vol_data( &volume2, volume_upd_data );
        Delay_ms ( 50 );
    }
    Delay_ms ( 1000 );
    for ( rising_vol = 0 ; rising_vol < max_atten ; rising_vol++ ) {
        volume_upd_data.attenuation_ch1 = max_atten - rising_vol;
        volume_upd_data.attenuation_ch2 = rising_vol;
        volume2_update_vol_data( &volume2, volume_upd_data );
        Delay_ms ( 50 );
    }
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
