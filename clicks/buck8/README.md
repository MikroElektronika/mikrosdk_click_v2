
---
# Buck 8 Click

> [Buck 8 Click](https://www.mikroe.com/?pid_product=MIKROE-2997) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2997&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> Demo application shows basic usage of BUCK 8 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck8

### Example Key Functions

- `buck8_cfg_setup` Config Object Initialization function. 
```c
void buck8_cfg_setup ( buck8_cfg_t *cfg );
``` 
 
- `buck8_init` Initialization function. 
```c
err_t buck8_init ( buck8_t *ctx, buck8_cfg_t *cfg );
```

- `buck8_default_cfg` Click Default Configuration function. 
```c
void buck8_default_cfg ( buck8_t *ctx );
```

- `buck8_get_state` Get state of pin. 
```c
uint8_t buck8_get_state( buck8_t *ctx );
```
 
- `buck8_set_power_mode` Function settings mode . 
```c
void buck8_set_power_mode( buck8_t *ctx, uint8_t mode );
```

### Application Init

> Configures the driver and enables the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buck8_cfg_t cfg;

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

    buck8_cfg_setup( &cfg );
    BUCK8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck8_init( &buck8, &cfg );

    buck8_default_cfg( &buck8 );
}
```

### Application Task

> Reads the VOUT state and parses it on USB UART.

```c
void application_task ( void )
{
    uint8_t pg_state;
    
    pg_state = buck8_get_state( &buck8 );
    
    if ( pg_state == 1 )
    {
        log_info( &logger, "VOUT is below 92.2%% of VIN" );
    }
    else
    {
        log_info( &logger, "VOUT is above 92.2%% of VIN" );
    }
    
    Delay_1sec();
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
