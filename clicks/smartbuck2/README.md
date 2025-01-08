
---
# Smart Buck 2 Click

> [Smart Buck 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5871) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5871&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Smart Buck 2 Click board&trade;.
> This driver provides functions for device configurations 
> and for the sets and reads the output voltage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartBuck2

### Example Key Functions

- `smartbuck2_cfg_setup` Config Object Initialization function.
```c
void smartbuck2_cfg_setup ( smartbuck2_cfg_t *cfg );
```

- `smartbuck2_init` Initialization function.
```c
err_t smartbuck2_init ( smartbuck2_t *ctx, smartbuck2_cfg_t *cfg );
```

- `smartbuck2_default_cfg` Click Default Configuration function.
```c
err_t smartbuck2_default_cfg ( smartbuck2_t *ctx );
```

- `smartbuck2_set_voltage` Smart Buck 2 set voltage function.
```c
err_t smartbuck2_set_voltage ( smartbuck2_t *ctx, uint16_t vout_mv );
```

- `smartbuck2_get_voltage` Smart Buck 2 get voltage function.
```c
err_t smartbuck2_get_voltage ( smartbuck2_t *ctx, uint16_t *vout_mv );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartbuck2_cfg_t smartbuck2_cfg;  /**< Click config object. */

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
    smartbuck2_cfg_setup( &smartbuck2_cfg );
    SMARTBUCK2_MAP_MIKROBUS( smartbuck2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == smartbuck2_init( &smartbuck2, &smartbuck2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTBUCK2_ERROR == smartbuck2_default_cfg ( &smartbuck2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Smart Buck 2 Click board&trade;.
> The demo application changes the output voltage in steps of 100mv every 3 seconds 
> and displays the output voltage value.
> Results are sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( SMARTBUCK2_OK == smartbuck2_set_voltage( &smartbuck2, vout_mv ) )
    {
        Delay_ms ( 100 );
        if ( SMARTBUCK2_OK == smartbuck2_get_voltage( &smartbuck2, &vout_mv ) )
        {
            log_printf( &logger, " Output voltage: %u [mV]\r\n", vout_mv );
        }
    }
    vout_mv += DEMO_VOUT_STEP_100MV;
    if ( vout_mv > SMARTBUCK2_VOUT_MAX )
    {
        vout_mv = SMARTBUCK2_VOUT_MIN;
    }
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
