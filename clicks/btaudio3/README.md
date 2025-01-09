
---
# BT Audio 3 Click

> [BT Audio 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4947) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4947&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of BT Audio 3 Click board by reading the commands received from remote device and performing adequate actions accordingly.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BTAudio3

### Example Key Functions

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

### Application Init

> Initializes the driver and configures the Click board.

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

### Note

> We have used the Serial Bluetooth Terminal smartphone application for the test. 
A smartphone and the Click board must be paired in order to exchange messages
with each other. So make sure to pair your device with the Click board and
connect it to using the Serial Bluetooth Terminal application, then you will be able 
to send commands listed below.

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
