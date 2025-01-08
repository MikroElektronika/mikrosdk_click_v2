
---
# Surface Temp Click

> [Surface Temp Click](https://www.mikroe.com/?pid_product=MIKROE-4205) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4205&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Surface Temp Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SurfaceTemp

### Example Key Functions

- `surfacetemp_cfg_setup` Config Object Initialization function. 
```c
void surfacetemp_cfg_setup ( surfacetemp_cfg_t *cfg );
``` 
 
- `surfacetemp_init` Initialization function. 
```c
err_t surfacetemp_init ( surfacetemp_t *ctx, surfacetemp_cfg_t *cfg );
```

- `surfacetemp_get_temperature` Getting temperature value. 
```c
float surfacetemp_get_temperature ( surfacetemp_t *ctx );
```
 
- `surfacetemp_set_hysteresis` Setting hysteresis value. 
```c
uint8_t surfacetemp_set_hysteresis ( surfacetemp_t *ctx, uint8_t hysteresis );
```

- `surfacetemp_setup` Device initialization. 
```c
uint8_t surfacetemp_setup ( surfacetemp_t *ctx );
```

### Application Init

> Initalizes the driver and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    surfacetemp_cfg_t cfg;

    uint8_t status;

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

    surfacetemp_cfg_setup( &cfg );
    SURFACETEMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    surfacetemp_init( &surfacetemp, &cfg );

    status = surfacetemp_setup( &surfacetemp );

    surfacetemp_set_high_threshold( &surfacetemp, 40.00 );
    surfacetemp_set_low_threshold( &surfacetemp, 10.00 );
    surfacetemp_set_critical_threshold( &surfacetemp, 70.00 );
    surfacetemp_set_hysteresis( &surfacetemp, 0 );

    if ( status == 0 )
    {
        log_printf( &logger, "--- INIT DONE --- \r\n" );
    }
    else
    {
        log_printf( &logger, "--- INIT ERROR --- \r\n" );
        for( ; ; );
    }
    Delay_ms ( 1000 );
}
```

### Application Task

> Reads the temperature in Celsius and displays the value on the USB UART each second.

```c
void application_task ( void )
{
    float temperature;

    temperature = surfacetemp_get_temperature( &surfacetemp );
    log_printf( &logger, "> Temperature : %.2f \r\n", temperature );
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
