
---
# Buck-Boost 3 Click

> [Buck-Boost 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3277) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3277&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application sets buck-boost voltages.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BuckBoost3

### Example Key Functions

- `buckboost3_cfg_setup` Config Object Initialization function. 
```c
void buckboost3_cfg_setup ( buckboost3_cfg_t *cfg );
``` 
 
- `buckboost3_init` Initialization function. 
```c
err_t buckboost3_init ( buckboost3_t *ctx, buckboost3_cfg_t *cfg );
```

- `buckboost3_enable` This function enable/disable device. 
```c
void buckboost3_enable ( buckboost3_t *ctx, uint8_t state );
```

- `buckboost3_get_interrupt_state` This function gets intterupt pin state. 
```c
uint8_t buckboost3_get_interrupt_state ( buckboost3_t *ctx );
```

### Application Init

> Initialization driver init and enable device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buckboost3_cfg_t cfg;

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

    buckboost3_cfg_setup( &cfg );
    BUCKBOOST3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buckboost3_init( &buckboost3, &cfg );
    
    buckboost3_enable ( &buckboost3, BUCKBOOST3_DEVICE_ENABLE );
    log_info( &logger, " Device enabled " );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Application Task

> It checks if the input voltage is below the operating voltage.

```c
void application_task ( void )
{
    if ( !buckboost3_get_interrupt_state( &buckboost3 ) )
    {
        log_error( &logger, " Low input voltage !!!" );
    }
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
