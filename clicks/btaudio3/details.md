
---
# BT Audio 3 click

> BT Audio 3 Click is a compact add-on board with high-performing voice and audio post-processing capability for Bluetooth audio applications. This board features the BM83, a fully certified Bluetooth v5.0 stereo audio module from Microchip. The BM83 contains an onboard Bluetooth stack and audio profiles and supports 24-bit/96 kHz high-resolution audio formats to enable high-fidelity wireless audio. An integrated Digital Signal Processor (DSP) decodes AAC and SBC codecs and executes advanced audio and voice processing such as Wide-Band (WB) speech, Acoustic Echo Cancellation (AEC), and Noise Reduction (NR). Configured in Host mode, the BM83 allows data processing via the UART interface, and in addition, comes with many additional features such as audio control buttons, onboard microphones, LED indicators, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/btaudio3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/bt-audio-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2021.
- **Type**          : UART type


# Software Support

We provide a library for the BT Audio 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BT Audio 3 Click driver.

#### Standard key functions :

- `btaudio3_cfg_setup` Config Object Initialization function.
```c
void btaudio3_cfg_setup ( btaudio3_cfg_t *cfg );
```

- `btaudio3_init` Initialization function.
```c
err_t btaudio3_init ( btaudio3_t *ctx, btaudio3_cfg_t *cfg );
```

- `btaudio3_default_cfg` Click Default Configuration function.
```c
err_t btaudio3_default_cfg ( btaudio3_t *ctx );
```

#### Example key functions :

- `btaudio3_set_device_name` This function sets the local device name.
```c
err_t btaudio3_set_device_name ( btaudio3_t *ctx, uint8_t *device_name );
```

- `btaudio3_music_control` This function sends a music control command with a desired action.
```c
err_t btaudio3_music_control ( btaudio3_t *ctx, btaudio3_music_control_t action );
```

- `btaudio3_set_eq_mode` This function sets the equalizer mode.
```c
err_t btaudio3_set_eq_mode ( btaudio3_t *ctx, btaudio3_eq_mode_t eq_mode );
```

## Example Description

> This example demonstrates the use of BT Audio 3 click board by reading the commands received from remote device and performing adequate actions accordingly.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and configures the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    btaudio3_cfg_t btaudio3_cfg;  /**< Click config object. */

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
    btaudio3_cfg_setup( &btaudio3_cfg );
    BTAUDIO3_MAP_MIKROBUS( btaudio3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == btaudio3_init( &btaudio3, &btaudio3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BTAUDIO3_OK != btaudio3_default_cfg ( &btaudio3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    if ( BTAUDIO3_OK != btaudio3_set_device_name ( &btaudio3, DEVICE_NAME ) )
    {
        log_error( &logger, " Set device name." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads all the received events and parses them.

```c
void application_task ( void )
{
    if ( BTAUDIO3_OK == btaudio3_read_event ( &btaudio3 ) ) 
    {
        btaudio3_event_handler ( &btaudio3 );
    }
}
```

## Note

> We have used the Serial Bluetooth Terminal smartphone application for the test. 
A smartphone and the click board must be paired in order to exchange messages
with each other. So make sure to pair your device with the click board and
connect it to using the Serial Bluetooth Terminal application, then you will be able 
to send commands listed below.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BTAudio3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
