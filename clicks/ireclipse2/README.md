
---
# IR Eclipse 2 Click

> [IR Eclipse 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6047) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6047&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the IR Eclipse 2 Click board
> by detecting eclipse states.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IREclipse2

### Example Key Functions

- `ireclipse2_cfg_setup` Config Object Initialization function.
```c
void ireclipse2_cfg_setup ( ireclipse2_cfg_t *cfg );
```

- `ireclipse2_init` Initialization function.
```c
err_t ireclipse2_init ( ireclipse2_t *ctx, ireclipse2_cfg_t *cfg );
```

- `ireclipse2_get_state` This function detects eclipse states.
```c
uint8_t ireclipse2_get_state ( ireclipse2_t *ctx );
```

- `ireclipse2_enable` This function enables the transmitter of the photo-microsensor.
```c
void ireclipse2_enable ( ireclipse2_t *ctx );
```

- `ireclipse2_disable` This function disables the transmitter of the photo-microsensor.
```c
void ireclipse2_disable ( ireclipse2_t *ctx );
```

### Application Init

> Initialization of GPIO module, log UART and enables the transmitter of the photo-microsensor.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ireclipse2_cfg_t ireclipse2_cfg;  /**< Click config object. */

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
    ireclipse2_cfg_setup( &ireclipse2_cfg );
    IRECLIPSE2_MAP_MIKROBUS( ireclipse2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == ireclipse2_init( &ireclipse2, &ireclipse2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    ireclipse2_enable( &ireclipse2 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> When the beam from the transmitter is eclipsed by placing an object in
> the gap ( like a piece of paper ), the counter is incremented by one 
> when the sensor is triggered.

```c
void application_task ( void ) 
{
    ecls_state = ireclipse2_get_state( &ireclipse2 );
    if ( cmp_state != ecls_state )
    {
        if ( IRECLIPSE2_STATE_ECLIPSE == ecls_state )
        {
            log_printf( &logger, " Counter: %u\n", cnt );
            cnt++;
        }
        cmp_state = ecls_state;
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
