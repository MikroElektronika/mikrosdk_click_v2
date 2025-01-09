
---
# Smart Buck 3 Click

> [Smart Buck 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5741) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5741&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Smart Buck 3 Click board&trade;.
> This driver provides functions for device configurations 
> and for the sets and reads the output voltage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartBuck3

### Example Key Functions

- `smartbuck3_cfg_setup` Config Object Initialization function.
```c
void smartbuck3_cfg_setup ( smartbuck3_cfg_t *cfg );
```

- `smartbuck3_init` Initialization function.
```c
err_t smartbuck3_init ( smartbuck3_t *ctx, smartbuck3_cfg_t *cfg );
```

- `smartbuck3_default_cfg` Click Default Configuration function.
```c
err_t smartbuck3_default_cfg ( smartbuck3_t *ctx );
```

- `smartbuck3_set_voltage` Smart Buck 3 set voltage function.
```c
err_t smartbuck3_set_voltage ( smartbuck3_t *ctx, uint16_t vout_mv );
```

- `smartbuck3_get_voltage` Smart Buck 3 get voltage function.
```c
err_t smartbuck3_get_voltage ( smartbuck3_t *ctx, uint16_t *vout_mv );
```

- `smartbuck3_set_operation_mode` Smart Buck 3 set operation mode function.
```c
err_t smartbuck3_set_operation_mode ( smartbuck3_t *ctx, uint8_t op_mode );
```

### Application Init

> Initialization of I2C module and log UART.
> After initializing the driver, the default configuration is executed 
> and the device is turned on.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartbuck3_cfg_t smartbuck3_cfg;  /**< Click config object. */

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
    smartbuck3_cfg_setup( &smartbuck3_cfg );
    SMARTBUCK3_MAP_MIKROBUS( smartbuck3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == smartbuck3_init( &smartbuck3, &smartbuck3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( SMARTBUCK3_ERROR == smartbuck3_default_cfg ( &smartbuck3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
    vout_mv = SMARTBUCK3_VOUT_MIN;
}
```

### Application Task

> This example demonstrates the use of the Smart Buck 3 Click board&trade;.
> Changes the output voltage every 3 seconds 
> and displays the current voltage output value.
> Results are sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( SMARTBUCK3_OK == smartbuck3_set_voltage( &smartbuck3, vout_mv ) )
    {
        Delay_ms ( 100 );
        if ( SMARTBUCK3_OK == smartbuck3_get_voltage( &smartbuck3, &vout_mv ) )
        {
            log_printf ( &logger, " Vout: %u mV\r\n", vout_mv );    
        }
    }
    vout_mv += 100;
    if ( vout_mv > SMARTBUCK3_VOUT_MAX )
    {
        vout_mv = SMARTBUCK3_VOUT_MIN;
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
