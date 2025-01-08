
---
# Power Reset Click

> [Power Reset Click](https://www.mikroe.com/?pid_product=MIKROE-3771) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3771&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> Reads PWR and RST pin states and performs a control of the timer counter depending on the pressed button.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PowerReset

### Example Key Functions

- `powerreset_cfg_setup` Config Object Initialization function. 
```c
void powerreset_cfg_setup ( powerreset_cfg_t *cfg );
``` 
 
- `powerreset_init` Initialization function. 
```c
err_t powerreset_init ( powerreset_t *ctx, powerreset_cfg_t *cfg );
```

- `powerreset_get_pwr` Power Check function. 
```c
powerreset_state_t powerreset_get_pwr ( powerreset_t *ctx );
```
 
- `powerreset_get_rst` Reset Check function. 
```c
powerreset_state_t powerreset_get_rst ( powerreset_t *ctx );
```

### Application Init

> Initializes device and logger module, prints Initialization done message.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    powerreset_cfg_t cfg;

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

    powerreset_cfg_setup( &cfg );
    POWERRESET_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    powerreset_init( &powerreset, &cfg );

    Delay_ms ( 100 );
    
    log_printf( &logger, "** Touch Button initialization done **\r\n");
    log_printf( &logger, "**************************************\r\n");
}
```

### Application Task

> Checks the states of the PWR and RST pins and logs every change.

```c
void application_task ( void )
{
    new_pwr_state = powerreset_get_pwr( &powerreset );
    new_rst_state = powerreset_get_rst( &powerreset );
    
    if ( new_pwr_state != pwr_state )
    {
        if ( new_pwr_state == POWERRESET_ACTIVE )
        {
            log_printf( &logger, "POWER ON\r\n" );
            Delay_ms ( 100 );
        }
        else if ( new_pwr_state == POWERRESET_INACTIVE )
        {
            log_printf( &logger, "POWER OFF\r\n" );
            Delay_ms ( 100 );
        }
        pwr_state = new_pwr_state;
    }

    if ( new_rst_state != rst_state )
    {
        if ( new_rst_state == POWERRESET_ACTIVE )
        {
            log_printf( &logger, "Reset occured!\r\n" );
            Delay_ms ( 100 );
        }
        rst_state = new_rst_state;
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
