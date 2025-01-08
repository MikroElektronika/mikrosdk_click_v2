
---
# MP3 2 Click

> [MP3 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4159) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4159&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstates the use of MP3 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mp32

### Example Key Functions

- `mp32_cfg_setup` Config Object Initialization function. 
```c
void mp32_cfg_setup ( mp32_cfg_t *cfg );
``` 
 
- `mp32_init` Initialization function. 
```c
err_t mp32_init ( mp32_t *ctx, mp32_cfg_t *cfg );
```

- `mp32_hw_reset` Reset the device function. 
```c
void mp32_hw_reset ( mp32_t *ctx );
```
 
- `mp32_rx_cmd` Received response data function. 
```c
void mp32_rx_cmd ( mp32_t *ctx, uint8_t *rd_data, uint8_t len );
```

- `mp32_tx_cmd` Write command function. 
```c
void mp32_tx_cmd ( mp32_t *ctx, uint8_t cmd, uint16_t spec_data );
```

### Application Init

> Initializes the driver and enables the Click board.
> Then sets the device to play songs from SD Card, and after that sets volume, and equalizer.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mp32_cfg_t cfg;

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

    mp32_cfg_setup( &cfg );
    MP32_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mp32_init( &mp32, &cfg );

    Delay_ms ( 500 );

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "       MP3 2 Click       \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_100ms( );

    mp32_hw_reset( &mp32 );
    Delay_ms ( 100 );
    
    mp32_set_device( &mp32, MP32_SDCARD );
    mp32_set_volume( &mp32, 50 );
    mp32_set_eq( &mp32, MP32_EQ_NORMAL );
    Delay_ms ( 100 );
}
```

### Application Task

> Demonstrates the use of play, play next, and pause modes.
> Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf( &logger, " >>> Play\r\n" );
    mp32_play_mode( &mp32 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " >>> Next song\r\n" );
    mp32_play_next( &mp32 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " >>> Pause\r\n" );
    mp32_pause_mode( &mp32 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );        
}
```

### Note

> A valid microSD Card that contains at least one mp3 sound on it needs to be inserted into the Click board.

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
