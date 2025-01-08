
---
# BT Audio Click

> [BT Audio Click](https://www.mikroe.com/?pid_product=MIKROE-2399) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2399&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from BT Audio Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BtAudio

### Example Key Functions

- `btaudio_cfg_setup` Config Object Initialization function. 
```c
void btaudio_cfg_setup ( btaudio_cfg_t *cfg );
``` 
 
- `btaudio_init` Initialization function. 
```c
err_t btaudio_init ( btaudio_t *ctx, btaudio_cfg_t *cfg );
```

- `btaudio_next_track` Play next track function. 
```c
uint8_t btaudio_next_track( btaudio_t *ctx );
```
 
- `btaudio_increase_volume` Increase volume function. 
```c
uint8_t btaudio_increase_volume( btaudio_t *ctx );
```

- `btaudio_decrease_volume` Decrease volume function. 
```c
uint8_t btaudio_decrease_volume( btaudio_t *ctx );
```

### Application Init

> Initializes the driver and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    btaudio_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    btaudio_cfg_setup( &cfg );
    BTAUDIO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    btaudio_init( &btaudio, &cfg );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Power ON\r\n" );
    btaudio_set_power_on( &btaudio );
    btaudio_process( RESPONSE_NULL );
    
    log_printf( &logger, "Factory reset\r\n" );
    btaudio_set_factory_defaults( &btaudio );
    btaudio_process( RESPONSE_NULL );
    
    log_printf( &logger, "Set device name\r\n" );
    btaudio_set_device_name( &btaudio, "BT Audio Click" );
    btaudio_reset( &btaudio );
    btaudio_process( RESPONSE_AOK );
    
    log_printf( &logger, "Set data mode\r\n" );
    btaudio_set_cmd_mode( &btaudio, 1 );
    btaudio_process( RESPONSE_NULL );
}
```

### Application Task

> Checks if there's any command received, then parses it and performs adequate actions.

```c
void application_task ( void )
{
    btaudio_process( RESPONSE_NULL );
}
```

### Note

> We have used the Serial Bluetooth Terminal smartphone application for the test. 
> A smartphone and the Click board must be paired in order to exchange messages
> with each other. So make sure to pair your device with the Click board and
> connect to it using the Serial Bluetooth Terminal application, then you will be able 
> to send commands listed below.

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
