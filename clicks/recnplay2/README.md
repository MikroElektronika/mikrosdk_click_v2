
---
# Rec N Play 2 Click

> [Rec N Play 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6167) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6167&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2024.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Rec N Play 2 Click board by 
 recording and then playing recorded sound.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RecNPlay2

### Example Key Functions

- `recnplay2_cfg_setup` Config Object Initialization function.
```c
void recnplay2_cfg_setup ( recnplay2_cfg_t *cfg );
```

- `recnplay2_init` Initialization function.
```c
err_t recnplay2_init ( recnplay2_t *ctx, recnplay2_cfg_t *cfg );
```

- `recnplay2_default_cfg` Click Default Configuration function.
```c
void recnplay2_default_cfg ( recnplay2_t *ctx );
```

- `recnplay2_set_pl_pin` This function sets the PL pin on the selected level of Rec N Play 2 Click board.
```c
void recnplay2_set_pl_pin ( recnplay2_t *ctx, uint8_t pin_state );
```

- `recnplay2_record_sound` This function is used to record sound with Rec N Play 2 Click board.
```c
err_t recnplay2_record_sound ( recnplay2_t *ctx, uint16_t rec_len );
```

- `recnplay2_play_sound` This function is used to play recorded sounds with Rec N Play 2 Click board.
```c
err_t recnplay2_play_sound ( recnplay2_t *ctx, uint16_t play_len );
```

### Application Init

> Initializes the driver, performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    recnplay2_cfg_t recnplay2_cfg;  /**< Click config object. */

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
    recnplay2_cfg_setup( &recnplay2_cfg );
    RECNPLAY2_MAP_MIKROBUS( recnplay2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == recnplay2_init( &recnplay2, &recnplay2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    recnplay2_default_cfg ( &recnplay2 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Recording sound for 5 seconds, then playing it back.

```c
void application_task ( void ) 
{
    log_printf( &logger, " Recording... \r\n" );
    recnplay2_record_sound( &recnplay2, RECORDING_LEN );
    Delay_ms ( 1000 );

    log_printf( &logger, " Playing... \r\n" );
    recnplay2_play_sound( &recnplay2, RECORDING_LEN );
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
