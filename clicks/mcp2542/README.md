
---
# MCP2542 Click

> [MCP2542 Click](https://www.mikroe.com/?pid_product=MIKROE-2299) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2299&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : UART type

# Software Support

## Example Description

> This application use for comunication.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mcp2542

### Example Key Functions

- `mcp2542_cfg_setup` Config Object Initialization function. 
```c
void mcp2542_cfg_setup ( mcp2542_cfg_t *cfg );
``` 
 
- `mcp2542_init` Initialization function. 
```c
err_t mcp2542_init ( mcp2542_t *ctx, mcp2542_cfg_t *cfg );
```

- `mcp2542_default_cfg` Click Default Configuration function. 
```c
void mcp2542_default_cfg ( mcp2542_t *ctx );
```

- `mcp2542_generic_single_read` Generic single read function. 
```c
mcp2542_data_t mcp2542_generic_single_read ( mcp2542_t *ctx );
```
 
- `mcp2542_generic_single_write` Generic single write function. 
```c
void mcp2542_generic_single_write ( mcp2542_t *ctx, mcp2542_data_t tx_data );
```

- `mcp2542_generic_multi_write` Generic multi write function. 
```c
void mcp2542_generic_multi_write ( mcp2542_t *ctx, mcp2542_data_t *data_buf,  uart_length_t len );
```

### Application Init

> Driver intialization.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp2542_cfg_t cfg;

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

    //  Click initialization.

    mcp2542_cfg_setup( &cfg );
    MCP2542_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp2542_init( &mcp2542, &cfg );

     mcp2542_default_cfg( &mcp2542 );
}
```

### Application Task

> Checks if new data byte have received in rx buffer (ready for reading), and if ready than reads one byte from rx buffer. In second case aplication task writes message data via UART.

```c
void application_task ( void )
{
    uint8_t tmp;
    
    //  Task implementation.
    
#ifdef DEMO_APP_RECEIVER

       // RECEIVER - UART polling

       tmp =  mcp2542_generic_single_read( &mcp2542 );
       log_write( &logger, &tmp, LOG_FORMAT_BYTE );
#endif
#ifdef DEMO_APP_TRANSMITER

       // TRANSMITER - TX each 2 sec
       
       mcp2542_generic_multi_write( &mcp2542, demo_message, 9 );
       Delay_ms ( 1000 );
       Delay_ms ( 1000 );
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
