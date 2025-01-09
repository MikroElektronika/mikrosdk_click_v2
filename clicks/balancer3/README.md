
---
# Balancer 3 Click

> [Balancer 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3737) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3737&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application is device for 2-series cell lithium-ion battery.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Balancer3

### Example Key Functions

- `balancer3_cfg_setup` Config Object Initialization function.
```c
void balancer3_cfg_setup ( balancer3_cfg_t *cfg ); 
```
 
- `balancer3_init` Initialization function.
```c
balancer3_init ( balancer3_t *ctx, balancer3_cfg_t *cfg );
```

- `balancer3_enable_cell_balance` Cell Balance Enable function.
```c
void balancer3_enable_cell_balance ( balancer3_t *ctx, uint8_t state );
```

- `balancer3_check_overvoltage` Overvoltage Condition Check function.
```c
uint8_t balancer3_check_overvoltage ( balancer3_t *ctx );
```

### Application Init

> Initializes device coummunication and enables cell balancing.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    balancer3_cfg_t cfg;

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
    balancer3_cfg_setup( &cfg );
    BALANCER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    balancer3_init( &balancer3, &cfg );
         
    balancer3_enable_cell_balance( &balancer3, BALANCER3_CELL_BALANCE_EN );
    log_printf( &logger, "* Normal operation - Cell balance enabled *\r\n" );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Checks if overvoltage is occured and disables cell balancing. If overvoltage doesn't occur it enables cell balancing.

```c
void application_task ( void )
{
    static uint8_t old_ov_state = 0;
    uint8_t ov_state = balancer3_check_overvoltage( &balancer3 );
    if ( old_ov_state != ov_state )
    {
        old_ov_state = ov_state;
        if ( BALANCER3_OV_COND_NOT_DETECTED == ov_state )
        {
            log_printf( &logger, "* Normal operation - Cell balance enabled *\r\n" );
            balancer3_enable_cell_balance( &balancer3, BALANCER3_CELL_BALANCE_EN );
        }
        else
        {
            log_printf( &logger, "* Overvoltage condition - Cell balance disabled * \r\n" );
            balancer3_enable_cell_balance( &balancer3, BALANCER3_CELL_BALANCE_DIS );
        }
    }
    Delay_ms ( 1 );
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
