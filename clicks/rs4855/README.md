
---
# RS485 5 Click

> [RS485 5 Click](https://www.mikroe.com/?pid_product=MIKROE-4156) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4156&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from RS485 5 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs4855

### Example Key Functions

- `rs4855_cfg_setup` Config Object Initialization function. 
```c
void rs4855_cfg_setup ( rs4855_cfg_t *cfg );
``` 
 
- `rs4855_init` Initialization function. 
```c
err_t rs4855_init ( rs4855_t *ctx, rs4855_cfg_t *cfg );
```

- `rs4855_generic_write` Generic write function. 
```c
void rs4855_generic_write ( rs4855_t *ctx, char *data_buf, uint16_t len );
```
 
- `rs4855_set_de_state` Sets DE pin to high or low state. 
```c
void rs4855_set_de_state ( rs4855_t *ctx, uint8_t state );
```

- `rs4855_set_re_state` Sets RE pin to high or low state. 
```c
void rs4855_set_re_state ( rs4855_t *ctx, uint8_t state );
```

### Application Init

> Initializes the driver and enables the selected mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rs4855_cfg_t cfg;

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

    rs4855_cfg_setup( &cfg );
    RS4855_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs4855_init( &rs4855, &cfg );

    Delay_ms ( 100 );

#ifdef DEMO_APP_RECEIVER
    rs4855_set_re_state( &rs4855, RS4855_PIN_STATE_LOW );
    rs4855_set_de_state( &rs4855, RS4855_PIN_STATE_LOW );
    log_info( &logger, "---- Receiver mode ----" );
#endif    
#ifdef DEMO_APP_TRANSMITTER
    rs4855_set_re_state( &rs4855, RS4855_PIN_STATE_HIGH );
    rs4855_set_de_state( &rs4855, RS4855_PIN_STATE_HIGH );
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
    rs4855_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    rs4855_generic_write( &rs4855, TEXT_TO_SEND, 8 );
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
