
---
# BT Audio 2 click

> BT Audio 2 Click is Bluetooth audio stream add on board based on BM62 module from Microchip. It's a Stereo Audio module which is fully qualified Bluetooth v5.0 dual-mode (BDR/EDR/BLE) to be added in any wireless audio and voice application. With features like high resolution up to 24-bit, 96 kHz audio data format, Bluetooth Low Energy data rate up to 1Mbits/s, connection of two hosts with HFP/A2DP profiles simultaneously, seamless serial data over UART interface and many more it's perfect solution for applications like portable speakers and headsets.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/btaudio2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/bt-audio-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : UART type


# Software Support

We provide a library for the BT Audio 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BT Audio 2 Click driver.

#### Standard key functions :

- `btaudio2_cfg_setup` Config Object Initialization function.
```c
void btaudio2_cfg_setup ( btaudio2_cfg_t *cfg );
```

- `btaudio2_init` Initialization function.
```c
err_t btaudio2_init ( btaudio2_t *ctx, btaudio2_cfg_t *cfg );
```

- `btaudio2_default_cfg` Click Default Configuration function.
```c
err_t btaudio2_default_cfg ( btaudio2_t *ctx );
```

#### Example key functions :

- `btaudio2_set_device_name` This function sets the local device name.
```c
err_t btaudio2_set_device_name ( btaudio2_t *ctx, uint8_t *device_name );
```

- `btaudio2_make_call` This function makes a call to the specified phone number.
```c
err_t btaudio2_make_call ( btaudio2_t *ctx, uint8_t database_index, uint8_t *phone_number );
```

- `btaudio2_volume_up` This function increases the volume of a specified gain mask.
```c
err_t btaudio2_volume_up ( btaudio2_t *ctx, uint8_t database_index, uint8_t mask );
```

## Example Description

> This example demonstrates the use of BT Audio 2 click board by reading the commands received from remote device and performing adequate actions accordingly.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and configures the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    btaudio2_cfg_t btaudio2_cfg;  /**< Click config object. */

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
    btaudio2_cfg_setup( &btaudio2_cfg );
    BTAUDIO2_MAP_MIKROBUS( btaudio2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == btaudio2_init( &btaudio2, &btaudio2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BTAUDIO2_OK != btaudio2_default_cfg ( &btaudio2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    if ( BTAUDIO2_OK != btaudio2_set_device_name ( &btaudio2, DEVICE_NAME ) )
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
    if ( BTAUDIO2_OK == btaudio2_read_event ( &btaudio2 ) ) 
    {
        btaudio2_event_handler ( &btaudio2 );
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
- Click.BTAudio2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
