
---
# UPS Click

> [UPS Click](https://www.mikroe.com/?pid_product=MIKROE-3001) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3001&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application is charger, that provides continuous power for a load connected to the output terminals.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ups

### Example Key Functions

- `ups_cfg_setup` Config Object Initialization function. 
```c
void ups_cfg_setup ( ups_cfg_t *cfg );
``` 
 
- `ups_init` Initialization function. 
```c
err_t ups_init ( ups_t *ctx, ups_cfg_t *cfg );
```

- `usp_set_mode` Functions for settings chip mode. 
```c
void usp_set_mode ( ups_t *ctx, uint8_t mode );
```
 
- `ups_get_power_good` Functions for reading PGD state. 
```c
uint8_t ups_get_power_good ( ups_t *ctx );
```

### Application Init

> Initializes Driver init and setting chip mode as ACTIVE

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ups_cfg_t cfg;

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

    ups_cfg_setup( &cfg );
    UPS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ups_init( &ups, &cfg );

    usp_set_mode( &ups, UPS_MODE_ACTIVE );
}
```

### Application Task

> Checks the state of PGD (Power Good), PGD goes high when Vout is within 6% of target value (4.98V)

```c
void application_task ( )
{
    uint8_t pgd_state;

    pgd_state = ups_get_power_good( &ups );

    if ( pgd_state != 0 )
    {
        log_printf( &logger, "---> Power Good \r\n" );
    }
    Delay_1sec( );
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
