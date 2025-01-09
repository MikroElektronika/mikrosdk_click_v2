
---
# RS Transceiver Click

> [RS Transceiver Click](https://www.mikroe.com/?pid_product=MIKROE-5746) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5746&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example reads and processes data from RS Transceiver Click board&trade;.
> The library also includes a function for selecting the desired operating mode, 
> enabling/disabling the receiver or driver and data writing or reading.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RSTransceiver

### Example Key Functions

- `rstransceiver_cfg_setup` Config Object Initialization function.
```c
void rstransceiver_cfg_setup ( rstransceiver_cfg_t *cfg );
```

- `rstransceiver_init` Initialization function.
```c
err_t rstransceiver_init ( rstransceiver_t *ctx, rstransceiver_cfg_t *cfg );
```

- `rstransceiver_default_cfg` Click Default Configuration function.
```c
err_t rstransceiver_default_cfg ( rstransceiver_t *ctx );
```

- `rstransceiver_set_op_mode` RS Transceiver sets the operating mode function.
```c
err_t rstransceiver_set_op_mode ( rstransceiver_t *ctx, uint8_t op_mode );
```

- `rstransceiver_mode_full_duplex` RS Transceiver sets the Full-Duplex mode function.
```c
err_t rstransceiver_mode_full_duplex ( rstransceiver_t *ctx, uint8_t slew, uint8_t dir1, uint8_t term );
```

- `rstransceiver_device_enable` RS Transceiver enables the device function.
```c
void rstransceiver_device_enable ( rstransceiver_t *ctx );
```

### Application Init

> Initialization of I2C and UART module and log UART.
> After driver initialization, default settings turn on the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rstransceiver_cfg_t rstransceiver_cfg;  /**< Click config object. */

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
    rstransceiver_cfg_setup( &rstransceiver_cfg );
    RSTRANSCEIVER_MAP_MIKROBUS( rstransceiver_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rstransceiver_init( &rstransceiver, &rstransceiver_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( RSTRANSCEIVER_ERROR == rstransceiver_default_cfg ( &rstransceiver ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the RS Transceiver Click board&trade;.
> The app shows the device configured in loopback mode,
> sends a "MikroE" message, reads the received data and parses it.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( rstransceiver_generic_write( &rstransceiver, DEMO_MESSAGE, strlen( DEMO_MESSAGE ) ) )
    {
        if ( rstransceiver_generic_read( &rstransceiver, app_buf, strlen( DEMO_MESSAGE ) ) )
        {
            log_printf( &logger, "%s", app_buf );
            memset( app_buf, 0, PROCESS_BUFFER_SIZE );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
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
