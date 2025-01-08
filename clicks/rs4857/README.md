
---
# RS485 7 Click

> [RS485 7 Click](https://www.mikroe.com/?pid_product=MIKROE-5659) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5659&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from RS485 7 Clicks.
> The library also includes a function for enabling/disabling 
> the receiver or driver and data writing or reading.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RS4857

### Example Key Functions

- `rs4857_cfg_setup` Config Object Initialization function.
```c
void rs4857_cfg_setup ( rs4857_cfg_t *cfg );
```

- `rs4857_init` Initialization function.
```c
err_t rs4857_init ( rs4857_t *ctx, rs4857_cfg_t *cfg );
```

- `rs4857_receiver_enable` RS485 7 enables the receiver function.
```c
void rs4857_receiver_enable ( rs4857_t *ctx );
```

- `rs4857_driver_enable` RS485 7 enables the driver function.
```c
void rs4857_driver_enable ( rs4857_t *ctx );
```

### Application Init

> Initializes driver performs wake-up module and enables the selected mode.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rs4857_cfg_t rs4857_cfg;  /**< Click config object. */

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
    rs4857_cfg_setup( &rs4857_cfg );
    RS4857_MAP_MIKROBUS( rs4857_cfg, MIKROBUS_1 );
    if ( UART_ERROR == rs4857_init( &rs4857, &rs4857_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    app_buf_len = 0;
    
    rs4857_termination_xy_enable( &rs4857 );
    rs4857_termination_ab_enable( &rs4857 );
    
    rs4857_receiver_enable( &rs4857 );
    rs4857_driver_enable( &rs4857 );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the RS485 7 Click board&trade;.
> The app sends a "MikroE" message, reads the received data and parses it.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{  
    if ( rs4857_generic_write( &rs4857, DEMO_MESSAGE, 10 ) )
    {
        rs4857_process( );
        if ( app_buf_len > 0 )
        {
            log_printf( &logger, "%s", app_buf );
            rs4857_clear_app_buf( );
        }
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Operation Mode: Full duplex. 
> Transmitter: Y and Z.
> Receiver: A and B.
> Wire connection: Y-A, Z-B.

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
