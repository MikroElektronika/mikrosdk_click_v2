
---
# Buck Boost 2 Click

> [Buck Boost 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2963) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2963&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application enables use of DC-DC step-down/step-up regulator (buck/boost).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BuckBoost2

### Example Key Functions

- `buckboost2_cfg_setup` Config Object Initialization function. 
```c
void buckboost2_cfg_setup ( buckboost2_cfg_t *cfg );
``` 
 
- `buckboost2_init` Initialization function. 
```c
err_t buckboost2_init ( buckboost2_t *ctx, buckboost2_cfg_t *cfg );
```

- `buckboost2_default_cfg` Click Default Configuration function. 
```c
void buckboost2_default_cfg ( buckboost2_t *ctx );
```

- `buckboost2_set_mode` This function sets the working mode. 
```c
void buckboost2_set_mode ( buckboost2_t *ctx , uint8_t mode );
```
 
- `buckboost2_power_off` This function powers OFF the chip. 
```c
void buckboost2_power_off( buckboost2_t *ctx );
```

- `buckboost2_power_on` This function powers on the chip. 
```c
void buckboost2_power_on ( buckboost2_t *ctx  );
```

### Application Init

> Initializes Driver init and turn ON chip and settings mode with improvement current.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buckboost2_cfg_t cfg;

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

    buckboost2_cfg_setup( &cfg );
    BUCKBOOST2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buckboost2_init( &buckboost2, &cfg );

    buckboost2_power_on( &buckboost2 );
    buckboost2_set_mode( &buckboost2, BUCKBOOST2_WITH_IMPROVEMENT );
}
```

### Application Task

> The Click has a constant output voltage of 5V, no additional settings are required. 

```c
void application_task ( void )
{
    //  Task implementation.

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
