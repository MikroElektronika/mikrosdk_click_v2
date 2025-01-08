
---
# Timer Relay Click

> [Timer Relay Click](https://www.mikroe.com/?pid_product=MIKROE-5562) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5562&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the Timer Relay Click board by
  setting the relay timer to 2 seconds ON time, then holding it OFF for 2 more seconds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TimerRelay

### Example Key Functions

- `timerrelay_cfg_setup` Config Object Initialization function.
```c
void timerrelay_cfg_setup ( timerrelay_cfg_t *cfg );
```

- `timerrelay_init` Initialization function.
```c
err_t timerrelay_init ( timerrelay_t *ctx, timerrelay_cfg_t *cfg );
```

- `timerrelay_default_cfg` Click Default Configuration function.
```c
err_t timerrelay_default_cfg ( timerrelay_t *ctx );
```

- `timerrelay_set_wiper_pos` Timer Relay set wiper position function.
```c
err_t timerrelay_set_wiper_pos ( timerrelay_t *ctx, uint8_t wiper_pos );
```

- `timerrelay_activate_reset` Timer Relay reset timer function.
```c
void timerrelay_activate_reset ( timerrelay_t *ctx );
```

- `timerrelay_activate_trigger` Timer Relay activate trigger function.
```c
void timerrelay_activate_trigger ( timerrelay_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration,
  then setting the ON time to 2 seconds.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    timerrelay_cfg_t timerrelay_cfg;  /**< Click config object. */

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
    timerrelay_cfg_setup( &timerrelay_cfg );
    TIMERRELAY_MAP_MIKROBUS( timerrelay_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == timerrelay_init( &timerrelay, &timerrelay_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TIMERRELAY_ERROR == timerrelay_default_cfg ( &timerrelay ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    if ( TIMERRELAY_ERROR == timerrelay_set_delay( &timerrelay, 2 ) )
    {
        log_error( &logger, " Value configuration." );
        for ( ; ; );
    }
    
    timerrelay_activate_reset( &timerrelay );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example is activating the trigger every 4 seconds activating the relay timer.

```c
void application_task ( void )
{
    timerrelay_activate_trigger( &timerrelay );
    log_printf( &logger, " Trigger activated. \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
