
---
# Speed Radar Click

> [Speed Radar Click](https://www.mikroe.com/?pid_product=MIKROE-5869) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5869&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of Speed Radar Click board by processing
> the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SpeedRadar

### Example Key Functions

- `speedradar_cfg_setup` Config Object Initialization function.
```c
void speedradar_cfg_setup ( speedradar_cfg_t *cfg );
```

- `speedradar_init` Initialization function.
```c
err_t speedradar_init ( speedradar_t *ctx, speedradar_cfg_t *cfg );
```

- `speedradar_default_cfg` Click Default Configuration function.
```c
err_t speedradar_default_cfg ( speedradar_t *ctx );
```

- `speedradar_send_command` Speed Radar send command function.
```c
err_t speedradar_send_command ( speedradar_t *ctx, uint8_t *cmd )
```

- `speedradar_get_direction` Speed Radar get direction function.
```c
uint8_t speedradar_get_direction ( speedradar_t *ctx )
```

- `speedradar_get_detection` Speed Radar get detection function.
```c
uint8_t speedradar_get_detection ( speedradar_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    speedradar_cfg_t speedradar_cfg;  /**< Click config object. */

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
    speedradar_cfg_setup( &speedradar_cfg );
    SPEEDRADAR_MAP_MIKROBUS( speedradar_cfg, MIKROBUS_1 );
    if ( UART_ERROR == speedradar_init( &speedradar, &speedradar_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SPEEDRADAR_ERROR == speedradar_default_cfg ( &speedradar ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    speedradar_process( &speedradar );
    speedradar_clear_app_buf( );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ---------------------- \r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application sends a command that returns and displays the speed [km/h] 
> and magnitude [dB] of the dominant movement for the forward and backward planes of the spectrum,
> measured frontal to the sensor.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    speedradar_send_command( &speedradar, SPEEDRADAR_CMD_GET_DETECTION_STR );
    Delay_ms ( 50 );
    speedradar_process( &speedradar );
    if ( app_buf_len >= PROCESS_C00_RSP_LEN  )
    {
        speedradar_adv_det_display( );
        speedradar_clear_app_buf( );
        Delay_ms ( 100 );
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
