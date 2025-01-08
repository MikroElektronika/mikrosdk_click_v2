
---
# Peltier Click

> [Peltier Click](https://www.mikroe.com/?pid_product=MIKROE-3814) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3814&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application is ultralow power energy harvester and battery charger.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Peltier

### Example Key Functions

- `peltier_cfg_setup` Config Object Initialization function. 
```c
void peltier_cfg_setup ( peltier_cfg_t *cfg );
``` 
 
- `peltier_init` Initialization function. 
```c
err_t peltier_init ( peltier_t *ctx, peltier_cfg_t *cfg );
```

- `peltier_enable_ldo2` Enables LDO2 function. 
```c
void peltier_enable_ldo2 ( peltier_t *ctx );
```
 
- `peltier_disable_ldo2` Disables LDO2 function. 
```c
void peltier_disable_ldo2 ( peltier_t *ctx );
```

- `peltier_battery_charge` Check ongoing battery charge flag pin function. 
```c
uint8_t peltier_battery_charge ( peltier_t *ctx );
```

### Application Init

> Initializes GPIO driver, disables both 1.8V and 3.3V outputs and starts write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    peltier_cfg_t cfg;

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

    peltier_cfg_setup( &cfg );
    PELTIER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    peltier_init( &peltier, &cfg ); 
}
```

### Application Task

> This example demonstrates the use of Peltier Click board by first enableing 1.8V output, second 
  by enableing 3.3V output, then enabling both outputs and finally disabling both outputs in 5 seconds intervals. 

```c
void application_task ( void )
{
    log_printf( &logger, "   1.8V output    \r\n" );
    log_printf( &logger, "------------------\r\n" );
    peltier_enable_ldo1( &peltier );
    peltier_disable_ldo2( &peltier );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "   3.3V output    \r\n" );
    log_printf( &logger, "------------------\r\n" );
    peltier_disable_ldo1( &peltier );
    peltier_enable_ldo2( &peltier );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "   Both outputs   \r\n" );
    log_printf( &logger, "------------------\r\n" );
    peltier_enable_ldo1( &peltier );
    peltier_enable_ldo2( &peltier );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Disable  outputs \r\n" );
    log_printf( &logger, "------------------\r\n" );
    peltier_disable_ldo1( &peltier );
    peltier_disable_ldo2( &peltier );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
