
---
# Thingstream Click

> [Thingstream Click](https://www.mikroe.com/?pid_product=MIKROE-3739) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3739&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from Thingstream Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thingstream

### Example Key Functions

- `thingstream_cfg_setup` Config Object Initialization function.
```c
void thingstream_cfg_setup ( thingstream_cfg_t *cfg ); 
```

- `thingstream_init` Initialization function.
```c
err_t thingstream_init ( thingstream_t *ctx, thingstream_cfg_t *cfg );
```

- `thingstream_reset_pin_state` Set RST pin state.
```c
void thingstream_reset_pin_state ( thingstream_t *ctx, uint8_t state );
```

- `thingstream_send_command` Send command.
```c
void thingstream_send_command ( thingstream_t *ctx, char *command );
```

- `thingstream_generic_parser` Generic parser function.
```c
thingstream_error_t thingstream_generic_parser ( char *rsp,  uint8_t command, uint8_t element, char *parser_buf );
```

### Application Init

> Initializes driver and power module.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thingstream_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    // Click initialization.
    thingstream_cfg_setup( &cfg );
    THINGSTREAM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thingstream_init( &thingstream, &cfg );

    thingstream_module_power( &thingstream, true );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " --->>> INFO.. \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_INFO );
    thingstream_process( );
    log_printf( &logger, "%s", current_parser_buf );
        
    log_printf( &logger, " --->>> CREATE.. \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_CREATE );
    thingstream_process( );
    log_printf( &logger, "%s", current_parser_buf );

    log_printf( &logger, " --->>> CONNECT.. \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_CONNECT );
    thingstream_process( );
    log_printf( &logger, "%s", current_parser_buf );

    log_printf( &logger, " --->>> GPS POWER.. \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_GPS_PWR );
    thingstream_process( );
    log_printf( &logger, "%s", current_parser_buf );

    log_printf( &logger, " --->>> SUBSCRIBE.. \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_SUBSCRIBE );
    thingstream_process( );
    log_printf( &logger, "%s", current_parser_buf );

    log_printf( &logger, " --->>> PUBLISH.. \r\n" );
    thingstream_send_command( &thingstream, THINGSTREAM_PUBLISH );
    thingstream_process( );
    log_printf( &logger, "%s", current_parser_buf );

    log_printf( &logger, " --->>> APP INIT <<<--- \r\n" );
}
```

### Application Task

> Reads the received data and parses it.

```c
void application_task ( void )
{
    thingstream_send_command( &thingstream, THINGSTREAM_GPS_INFO );  
    thingstream_process( );
    parser_application( current_parser_buf );
}
```

### Note

> The Click board needs to be registered with a redemption code to a Thingstream Domain.
> For more information please refer to the Thingstream Click user manual available on the product page.

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
