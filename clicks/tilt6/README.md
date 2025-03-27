
---
# Tilt 6 Click

> [Tilt 6 Click](https://www.mikroe.com/?pid_product=MIKROE-6568) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6568&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2025.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the functionality of the Tilt 6 Click board, which detects 
tilt motion in multiple directions. The example continuously monitors tilt movements,
logging when the sensor detects a left tilt, right tilt, or remains idle.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Tilt6

### Example Key Functions

- `tilt6_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void tilt6_cfg_setup ( tilt6_cfg_t *cfg );
```

- `tilt6_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t tilt6_init ( tilt6_t *ctx, tilt6_cfg_t *cfg );
```

- `tilt6_get_tilt_state` This function returns the tilt switch state.
```c
uint8_t tilt6_get_tilt_state ( tilt6_t *ctx );
```

### Application Init

> Initializes the logger and configures the Tilt 6 Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tilt6_cfg_t tilt6_cfg;  /**< Click config object. */

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
    tilt6_cfg_setup( &tilt6_cfg );
    TILT6_MAP_MIKROBUS( tilt6_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == tilt6_init( &tilt6, &tilt6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads the tilt state and logs changes. The sensor can detect three states: "RIGHT TILT", "LEFT TILT", and "IDLE" indicating no tilt.

```c
void application_task ( void )
{
    static uint8_t old_state = TILT6_STATE_IDLE;
    uint8_t state = tilt6_get_tilt_state ( &tilt6 );
    if ( state != old_state )
    {
        old_state = state;
        if ( TILT6_STATE_RIGHT_TILT == state )
        {
            log_printf( &logger, "State: RIGHT TILT\r\n\n" );
        }
        else if ( TILT6_STATE_LEFT_TILT == state )
        {
            log_printf( &logger, "State: LEFT TILT\r\n\n" );
        }
        else
        {
            log_printf( &logger, "State: IDLE\r\n\n" );
        }
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
