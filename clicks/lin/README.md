
---
# LIN Click

> [LIN Click](https://www.mikroe.com/?pid_product=MIKROE-3816) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3816&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from LIN Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Lin

### Example Key Functions

- `lin_cfg_setup` Config Object Initialization function. 
```c
void lin_cfg_setup ( lin_cfg_t *cfg );
``` 
 
- `lin_init` Initialization function. 
```c
err_t lin_init ( lin_t *ctx, lin_cfg_t *cfg );
```

- `lin_generic_write` Generic write function. 
```c
void lin_generic_write ( lin_t *ctx, char *data_buf, uint16_t len );
```
 
- `lin_generic_read` Generic read function. 
```c
int32_t lin_generic_read ( lin_t *ctx, char *data_buf, uint16_t max_len );
```

- `lin_set_enable` Set enable pin state. 
```c
void lin_set_enable ( lin_t *ctx, uint8_t state );
```

### Application Init

> Initializes the driver and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    lin_cfg_t cfg;

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

    lin_cfg_setup( &cfg );
    LIN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lin_init( &lin, &cfg );
    Delay_ms ( 100 );
    
    lin_set_enable ( &lin, 1 );
    lin_set_wake_up ( &lin, 0 );
    Delay_ms ( 100 );
#ifdef DEMO_APP_RECEIVER
    log_info( &logger, "---- Receiver mode ----" );
#endif    
#ifdef DEMO_APP_TRANSMITTER
    log_info( &logger, "---- Transmitter mode ----" );
#endif   
}
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c
void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    lin_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    lin_generic_write( &lin, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_info( &logger, "---- Data sent ----" );
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
