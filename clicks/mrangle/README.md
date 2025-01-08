
---
# MR Angle Click

> [MR Angle Click](https://www.mikroe.com/?pid_product=MIKROE-4634) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4634&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for the MR Angle Click driver.
> This demo application shows an example of angle measurement.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MrAngle

### Example Key Functions

- `mrangle_cfg_setup` Config Object Initialization function.
```c
void mrangle_cfg_setup ( mrangle_cfg_t *cfg );
```

- `mrangle_init` Initialization function.
```c
err_t mrangle_init ( mrangle_t *ctx, mrangle_cfg_t *cfg );
```

- `mrangle_default_cfg` Click Default Configuration function.
```c
void mrangle_default_cfg ( mrangle_t *ctx );
```

- `mrangle_get_angle` MR Angle get angle function.
```c
err_t mrangle_get_angle ( mrangle_t *ctx, float *angle );
```

- `mrangle_get_temperature` MR Angle get temperature function.
```c
err_t mrangle_get_temperature ( mrangle_t *ctx, float *temperature );
```

- `mrangle_powerdown_mode` MR Angle powerdown mode function.
```c
void mrangle_powerdown_mode ( mrangle_t *ctx, mrangle_powerdown_mode_value_t pd_mode );
```

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app performs default settings.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    mrangle_cfg_t mrangle_cfg;  /**< Click config object. */

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
    mrangle_cfg_setup( &mrangle_cfg );
    MRANGLE_MAP_MIKROBUS( mrangle_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == mrangle_init( &mrangle, &mrangle_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    mrangle_default_cfg ( &mrangle );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This is an example that shows the use of an MR Angle Click board&trade;.
> The application task consists of reading the angle measurements in degrees ( 0 - 180 ).
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    mrangle_get_angle( &mrangle, &angle );
    log_printf( &logger, " Angle: %.2f deg\r\n", angle );
    log_printf( &logger, "------------------\r\n" );
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
