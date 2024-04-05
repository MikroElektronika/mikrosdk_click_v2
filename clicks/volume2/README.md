\mainpage Main Page

---
# Volume 2 click

> Volume 2 Click is a compact add-on board that provides the user with complete digital volume control. This board features the NJU72341, a 2-channel I2C configurable electronic volume IC with external mute control from NJRC.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/volume2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/volume-2-click)

---


#### Click library

- **Author**        : Stefan Nikolic
- **Date**          : feb 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Volume2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Volume2 Click driver.

#### Standard key functions :

- `volume2_cfg_setup` Config Object Initialization function.
```c
void volume2_cfg_setup ( volume2_cfg_t *cfg );
```

- `volume2_init` Initialization function.
```c
VOLUME2_RETVAL volume2_init ( volume2_t *ctx, volume2_cfg_t *cfg );
```

- `volume2_default_cfg` Click Default Configuration function.
```c
void volume2_default_cfg ( volume2_t *ctx );
```

#### Example key functions :

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

## Example Description

> This example shows how Volume 2 click board can be used
for controlling the audio channels. Thanks to this, a
simple audio effect is created by switching volume from
right to left and vice versa.

**The demo application is composed of two sections :**

### Application Init

> UART LOG and I2C drivers are initialized, following the
default configuration. By default, both channels are set
to 9 dB gain with zero cross detection enabled.

```c

void application_init ( void ) {
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

void application_task ( void ) {
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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Volume2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
