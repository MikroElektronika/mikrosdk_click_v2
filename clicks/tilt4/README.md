
---
# Tilt 4 Click

> [Tilt 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6026) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6026&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Tilt 4 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Tilt4

### Example Key Functions

- `tilt4_cfg_setup` Config Object Initialization function.
```c
void tilt4_cfg_setup ( tilt4_cfg_t *cfg );
```

- `tilt4_init` Initialization function.
```c
err_t tilt4_init ( tilt4_t *ctx, tilt4_cfg_t *cfg );
```

- `tilt4_read_int_state` This function reads the state of the interrupt pin of Tilt 4 Click board.
```c
uint8_t tilt4_read_int_state ( tilt4_t *ctx );
```

- `tilt4_set_led_state` This function sets the LED pin on the selected level level of Tilt 4 Click board.
```c
void tilt4_set_led_state ( tilt4_t *ctx, uint8_t pin_state );
```

### Application Init

> Initializes the driver and USB UART logger.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tilt4_cfg_t tilt4_cfg;  /**< Click config object. */

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
    tilt4_cfg_setup( &tilt4_cfg );
    TILT4_MAP_MIKROBUS( tilt4_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == tilt4_init( &tilt4, &tilt4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> As soon as the tilt switch state changes, it displays a corresponding message on the USB UART.

```c
void application_task ( void ) 
{
    uint8_t state = tilt4_read_int_state ( &tilt4 );
    if ( tilt4_switch_state != state )
    {
        tilt4_switch_state = state;
        
        if ( TILT4_SWITCH_ON == tilt4_switch_state )
        {
            log_printf( &logger, " Tilt switch ON!\r\n\n" );
            tilt4_set_led_state( &tilt4, TILT4_PIN_STATE_HIGH );
        }
        else
        {
            log_printf( &logger, " Tilt switch OFF!\r\n\n" );
            tilt4_set_led_state( &tilt4, TILT4_PIN_STATE_LOW );
        }
        Delay_ms ( 500 );
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
