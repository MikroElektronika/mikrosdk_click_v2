
---
# Buck 3 Click

> [Buck 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2971) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2971&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Buck 3 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck3

### Example Key Functions

- `buck3_cfg_setup` Config Object Initialization function. 
```c
void buck3_cfg_setup ( buck3_cfg_t *cfg );
``` 
 
- `buck3_init` Initialization function. 
```c
err_t buck3_init ( buck3_t *ctx, buck3_cfg_t *cfg );
```

- `buck3_default_cfg` Click Default Configuration function. 
```c
void buck3_default_cfg ( buck3_t *ctx );
```

- `buck3_set_device_state` Function for setting device mode. 
```c
void buck3_set_device_state( buck3_t *ctx, uint8_t state );
```
 
- `buck3_get_power_good` Function reads state of PGD pin. 
```c
uint8_t buck3_get_power_good( buck3_t *ctx );
```

### Application Init

> Initializes the driver and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buck3_cfg_t cfg;

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

    buck3_cfg_setup( &cfg );
    BUCK3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck3_init( &buck3, &cfg );

    buck3_default_cfg( &buck3 );
    log_info( &logger, "---- Buck 3 is activated ----" );
    Delay_1sec( );
}
```

### Application Task

> Checks the PGD pin state which signalize the undervoltage or overvoltage fault or
> the thermal shutdown condition. 
> If there's any of the above faults detected it logs a desired message on USB UART.

```c
void application_task ( void )
{
    if ( !buck3_get_power_good( &buck3 ) )
    {
        log_info ( &logger, "---- Overvoltage or thermal shutdown detected ----" );
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
