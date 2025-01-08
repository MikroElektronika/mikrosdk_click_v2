
---
# Fiber Opt Click

> [Fiber Opt Click](https://www.mikroe.com/?pid_product=MIKROE-1940) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1940&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of an Fiber Opt Click board by showing the communication between the two Click boards.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.FiberOpt

### Example Key Functions

- `fiberopt_cfg_setup` Config Object Initialization function.
```c
void fiberopt_cfg_setup ( fiberopt_cfg_t *cfg ); 
```

- `fiberopt_init` Initialization function.
```c
err_t fiberopt_init ( fiberopt_t *ctx, fiberopt_cfg_t *cfg );
```

- `fiberopt_generic_write` Generic single write function.
```c
err_t fiberopt_generic_write ( fiberopt_t *ctx, uint8_t *data_buf, uint16_t len );
```

- `fiberopt_generic_read` Generic single read function.
```c
err_t fiberopt_generic_read ( fiberopt_t *ctx, uint8_t *data_buf, uint16_t len );
```

### Application Init

> Initalizes device and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    fiberopt_cfg_t cfg;

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
    fiberopt_cfg_setup( &cfg );
    FIBEROPT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fiberopt_init( &fiberopt, &cfg );

#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> Depending on the selected application mode, it reads all the received data or 
sends the desired text message with the message counter once per second.

```c
void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    fiberopt_generic_write( &fiberopt, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms ( 1000 ); 
#else
    uint8_t rx_byte = 0;
    if ( 1 == fiberopt_generic_read( &fiberopt, &rx_byte, 1 ) )
    {
       log_printf( &logger, "%c", rx_byte );
    }
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
