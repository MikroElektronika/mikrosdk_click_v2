
---
# Relay 2 Click

> [Relay 2 Click](https://www.mikroe.com/?pid_product=MIKROE-1899) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1899&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> The application is composed of three sections :

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Relay2

### Example Key Functions

- `relay2_cfg_setup` Config Object Initialization function. 
```c
void relay2_cfg_setup ( relay2_cfg_t *cfg );
``` 
 
- `relay2_init` Initialization function. 
```c
err_t relay2_init ( relay2_t *ctx, relay2_cfg_t *cfg );
```

### Application Init

> Initializes driver. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    relay2_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    relay2_cfg_setup( &cfg );
    RELAY2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    relay2_init( &relay2, &cfg );
    log_info( &logger, "---- App Init Done ----" );
}
```

### Application Task

> Turns relays on and off.

```c
void application_task ( void )
{
    relay2_relay2_control(&relay2, 1 );
    relay2_relay1_control(&relay2, 1 );
    
    Delay_ms ( 1000 );
    
    relay2_relay2_control(&relay2, 0 );
    relay2_relay1_control(&relay2, 0 );
    
    Delay_ms ( 1000 );

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
