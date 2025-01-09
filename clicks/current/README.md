
---
# Current Click

> [Current Click](https://www.mikroe.com/?pid_product=MIKROE-1396) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1396&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jovan Stajkovic
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that shows the capabilities of the Current Click board 
> by measuring current in miliampers. Current Click board can be used to safely
> measure DC current in the range of 2-2048mA depending on shunt resistor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Current

### Example Key Functions

- `current_cfg_setup` Config Object Initialization function. 
```c
void current_cfg_setup ( current_cfg_t *cfg );
``` 
 
- `current_init` Initialization function. 
```c
err_t current_init ( current_t *ctx, current_cfg_t *cfg );
```

- `current_get_current_data` Function is used to calculate current in mA. 
```c
float current_get_current_data ( current_t *ctx, float r_hunt );
```

### Application Init

> Initalizes SPI, LOG and Click drivers.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    current_cfg_t cfg;

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

    current_cfg_setup( &cfg );
    CURRENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    current_init( &current, &cfg );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "    Current  Click     \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}
```

### Application Task

> Measures DC current and displays the results on USB UART each second.

```c
void application_task ( void )
{
    curr = current_get_current_data( &current, CURRENT_RSHUNT_0_05 );
    
    if ( curr == CURRENT_OUT_OF_RANGE )
    {
        log_printf( &logger, "Out of range!\r\n" );
    }
    else
    {
       log_printf( &logger, " Current: %.2f mA\r\n", curr );
    }
    
    log_printf( &logger, "-----------------------\r\n" );
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
