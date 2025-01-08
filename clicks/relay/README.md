
---
# Relay Click

> [Relay Click](https://www.mikroe.com/?pid_product=MIKROE-1370) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1370&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> Demo application is used to shows basic controls Relay Click

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Relay

### Example Key Functions

- `relay_cfg_setup` Config Object Initialization function. 
```c
void relay_cfg_setup ( relay_cfg_t *cfg );
``` 
 
- `relay_init` Initialization function. 
```c
err_t relay_init ( relay_t *ctx, relay_cfg_t *cfg );
```

- `relay_default_cfg` Click Default Configuration function. 
```c
void relay_default_cfg ( relay_t *ctx );
```

- `relay_set_state` Relay set state. 
```c
void relay_set_state ( relay_t *ctx, uint8_t relay, uint8_t state );
```

### Application Init

> Configuring Clicks and log objects. 
> Settings the Click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    relay_cfg_t cfg;

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

    relay_cfg_setup( &cfg );
    RELAY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    relay_init( &relay, &cfg );
    
    relay_default_cfg ( &relay );
    Delay_ms ( 1000 );
    Delay_ms ( 500 );
}
```

### Application Task

> Alternately sets relays to ON-OFF state...

```c
void application_task ( void )
{
    uint8_t cnt;
    
    //  Task implementation.
    
    for ( cnt = 1; cnt <= 2; cnt++)
    {
        log_info( &logger, "*** Relay %d state is ON \r\n", cnt);
        relay_set_state( &relay, cnt, RELAY_STATE_ON );
        Delay_ms ( 1000 );
        log_info( &logger, "*** Relay %d state is OFF \r\n", cnt);
        relay_set_state( &relay, cnt, RELAY_STATE_OFF );
        Delay_ms ( 200 );
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
