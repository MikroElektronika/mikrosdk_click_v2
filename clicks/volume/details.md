
---
# Volume click

> Volume Click is a compact add-on board that provides the user with complete digital volume control. This board features the CS3310, a stereo digital volume control designed specifically for audio systems from Cirrus Logic.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/volume_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/volume-click)

---


#### Click library

- **Author**        : Stefan Nikolic
- **Date**          : nov 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Volume Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
This library contains API for Volume Click driver.
```

#### Standard key functions :

- Config Object Initialization function.
```
void volume_cfg_setup ( volume_cfg_t *cfg );
```

- Initialization function.
```
err_t volume_init ( volume_t *ctx, volume_cfg_t *cfg );
```

- Click Default Configuration function.
```
void volume_default_cfg ( volume_t *ctx );
```

#### Example key functions :

- Set volume gain function.
```
err_t volume_set_vol_gain ( volume_t *ctx, float volume_left_dB, float volume_right_dB );
```

- Power Up function.
```
void volume_power_up ( volume_t *ctx );
```

- Hardware MUTE function.
```
void volume_hw_mute ( volume_t *ctx, uint8_t mute_state );
```

## Examples Description

This example sets up the device and performs volume turn up and down.

**The demo application is composed of two sections :**

### Application Init

Initializes drivers and powers up the device.

```
void application_init ( void ) {
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

Circles the volume from -40 [dB] to 10 [dB] back and forth.

```
void application_task ( void ) {
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
                Delay_ms( 50 );
            } else {
                one_circle++;
                log_printf( &logger, " Turning volume down.\r\n" );
            }
        } else if ( left_speaker_gain >= -40 || right_speaker_gain >= -40 ) {
            volume_set_vol_gain( &volume, left_speaker_gain, right_speaker_gain );
            left_speaker_gain -= 0.5;
            right_speaker_gain -= 0.5;
            Delay_ms( 50 );
        } else one_circle++;
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Volume

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
