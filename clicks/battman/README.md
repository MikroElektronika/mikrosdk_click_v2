
---
# BATT-MAN Click

> [BATT-MAN Click](https://www.mikroe.com/?pid_product=MIKROE-2901) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2901&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : sep 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> BATT-MAN Click is a very versatile battery operated power manager. When powered via mikroBUS,
> it will charge the connected Li-Ion/Li-Po 3.7V battery, while providing the output voltage 
> on all its outputs at the same time.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BattMan

### Example Key Functions

- `battman_cfg_setup` Config Object Initialization function. 
```c
void battman_cfg_setup ( battman_cfg_t *cfg );
``` 
 
- `battman_init` Initialization function. 
```c
err_t battman_init ( battman_t *ctx, battman_cfg_t *cfg );
```

- `battman_set_enable` Controls the operation of the Click. 
```c
void battman_set_enable ( battman_t *ctx, uint8_t state );
```
 
- `battman_get_charging_indicator` Charging indicator status. 
```c
uint8_t battman_get_charging_indicator ( battman_t *ctx );
```

### Application Init

> Initializes the Click driver and logger utility and enables the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    battman_cfg_t cfg;

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

    battman_cfg_setup( &cfg );
    BATTMAN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    battman_init( &battman, &cfg );
    
    battman_set_enable( &battman, 1 );
    log_printf( &logger, "BATT-MAN Click enabled.\r\n" );
    chg_flag = 0;
}
```

### Application Task

> Checks the charging indicator status, and in relation to its state it displays an appropriate message on USB UART.

```c
void application_task ( void )
{
    if ( !battman_get_charging_indicator ( &battman ) )
    {
        if ( chg_flag == 1 )
        {
            log_printf( &logger, "Charging enabled.\r\n" );
        }
        chg_flag = 0;
    }
    else
    {
        if ( chg_flag == 0 )
        {
            log_printf( &logger, "Charging disabled.\r\n" );
        }
        chg_flag = 1;
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
