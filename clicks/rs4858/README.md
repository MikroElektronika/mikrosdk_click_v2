
---
# RS485 8 Click

> [RS485 8 Click](https://www.mikroe.com/?pid_product=MIKROE-5752) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5752&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from RS485 8 Clicks.
  The library also includes a function for enabling/disabling 
  the receiver or driver and data writing or reading.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RS4858

### Example Key Functions

- `rs4858_cfg_setup` Config Object Initialization function.
```c
void rs4858_cfg_setup ( rs4858_cfg_t *cfg );
```

- `rs4858_init` Initialization function.
```c
err_t rs4858_init ( rs4858_t *ctx, rs4858_cfg_t *cfg );
```

- `rs4858_default_cfg` Click Default Configuration function.
```c
err_t rs4858_default_cfg ( rs4858_t *ctx );
```

- `rs4858_generic_write` RS485 8 data writing function.
```c
err_t rs4858_generic_write ( rs4858_t *ctx, uint8_t *data_in, uint16_t len );
```

- `rs4858_generic_read` RS485 8 data reading function.
```c
err_t rs4858_generic_read ( rs4858_t *ctx, uint8_t *data_out, uint16_t len );
```

- `rs4858_enable_device` RS485 8 enable the device function.
```c
void rs4858_enable_device ( rs4858_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rs4858_cfg_t rs4858_cfg;  /**< Click config object. */

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
    rs4858_cfg_setup( &rs4858_cfg );
    RS4858_MAP_MIKROBUS( rs4858_cfg, MIKROBUS_2 );
    if ( UART_ERROR == rs4858_init( &rs4858, &rs4858_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    rs4858_default_cfg ( &rs4858 );
    
#ifdef DEMO_APP_TRANSMITTER
    log_info( &logger, "---- Transmitter mode ----" );
#else
    log_info( &logger, "---- Receiver mode ----" );
#endif 
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the RS485 8 Click board.
  The app sends a "MikroE" message, reads the received data and parses it.
  Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    rs4858_generic_write( &rs4858, data_buf, strlen( data_buf ) );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    rs4858_process( );
#endif 
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
