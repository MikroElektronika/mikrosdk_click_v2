
---
# R Meter Click

> [R Meter Click](https://www.mikroe.com/?pid_product=MIKROE-2396) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2396&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jovan Stajkovic
- **Date**          : nov 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> Demo app measures and displays resistance of a resistor connected 
> to the R Meter Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rmeter

### Example Key Functions

- `rmeter_cfg_setup` Config Object Initialization function. 
```c
void rmeter_cfg_setup ( rmeter_cfg_t *cfg );
``` 
 
- `rmeter_init` Initialization function. 
```c
err_t rmeter_init ( rmeter_t *ctx, rmeter_cfg_t *cfg );
```

- `rmeter_default_cfg` Click Default Configuration function. 
```c
void rmeter_default_cfg ( rmeter_t *ctx );
```

- `rmeter_get_ohms` Get resistance in OHMs function. 
```c
float rmeter_get_ohms ( rmeter_t *ctx );
```
 
- `rmeter_avg_volt` Get average voltage function. 
```c
float rmeter_avg_volt ( rmeter_t *ctx );
```

- `rmeter_calc` Calculations function. 
```c
float rmeter_calc ( rmeter_t *ctx, uint32_t resFilt );
```

### Application Init

> Initalizes SPI, LOG and Click drivers

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rmeter_cfg_t cfg;

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

    rmeter_cfg_setup( &cfg );
    RMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rmeter_init( &rmeter, &cfg );

    Delay_ms ( 100 );
    log_printf( &logger, "----------------------- \r\n" );
    log_printf( &logger, "    R Meter  Click      \r\n" );
    log_printf( &logger, "----------------------- \r\n" );
}
```

### Application Task

> This is an example that shows the capabilities of the R Meter Click by 
> measuring resistance.

```c
void application_task ( void )
{
    ohms = rmeter_get_ohms( &rmeter );
    
    if ( ohms == RMETER_OVER_RANGE )
    {
        log_printf( &logger, " Over range! \r\n" );
    }
    else
    {
        log_printf( &logger, "Resistance: %.2f ohm \r\n", ohms );
    }
    
    log_printf( &logger, "----------------------- \r\n" );
    Delay_ms ( 1000 );
}
```

### Note

> R Meter Click is a handy tool but it is not to be used as a precision 
> instrument! The linearity of the OpAmp impacts the measurement.

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
