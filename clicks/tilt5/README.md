
---
# Tilt 5 Click

> [Tilt 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6567) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6567&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2025.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the Tilt 5 Click board, which detects 
tilt motion using a ball switch sensor. The example initializes the device 
and continuously monitors the tilt state, logging changes between active and idle states.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Tilt5

### Example Key Functions

- `tilt5_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void tilt5_cfg_setup ( tilt5_cfg_t *cfg );
```

- `tilt5_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t tilt5_init ( tilt5_t *ctx, tilt5_cfg_t *cfg );
```

- `tilt5_get_out_pin` This function returns the OUT pin logic state.
```c
uint8_t tilt5_get_out_pin ( tilt5_t *ctx );
```

### Application Init

> Initializes the logger and configures the Tilt 5 Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tilt5_cfg_t tilt5_cfg;  /**< Click config object. */

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
    tilt5_cfg_setup( &tilt5_cfg );
    TILT5_MAP_MIKROBUS( tilt5_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == tilt5_init( &tilt5, &tilt5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads the tilt state and logs changes. The state toggles between 
"ACTIVE" when a tilt is detected and "IDLE" when the sensor is in its default position.

```c
void application_task ( void )
{
    static uint8_t old_state = TILT5_STATE_IDLE;
    uint8_t state = tilt5_get_out_pin ( &tilt5 );
    if ( state != old_state )
    {
        old_state = state;
        if ( TILT5_STATE_ACTIVE == state )
        {
            log_printf( &logger, "State: ACTIVE\r\n\n" );
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
