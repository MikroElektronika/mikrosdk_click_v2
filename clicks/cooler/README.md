
---
# Cooler Click

> [Cooler Click](https://www.mikroe.com/?pid_product=MIKROE-6068) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6068&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2024.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Cooler Click board
 by reading the target object temperature and controlling the cooler.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Cooler

### Example Key Functions

- `cooler_cfg_setup` Config Object Initialization function.
```c
void cooler_cfg_setup ( cooler_cfg_t *cfg );
```

- `cooler_init` Initialization function.
```c
err_t cooler_init ( cooler_t *ctx, cooler_cfg_t *cfg );
```

- `cooler_default_cfg` Click Default Configuration function.
```c
err_t cooler_default_cfg ( cooler_t *ctx );
```

- `cooler_get_object_temperature` This function reads the object's temperature data in degrees Celsius.
```c
err_t cooler_get_object_temperature ( cooler_t *ctx, float *temperature );
```

- `cooler_set_out_state` This function controls the operation of the cooler - on/off.
```c
err_t cooler_set_out_state ( cooler_t *ctx, cooler_out_state_t out_state );
```

### Application Init

> The initialization of the I2C module, log UART, and additional pins.
 After the driver init, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    cooler_cfg_t cooler_cfg;  /**< Click config object. */

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
    cooler_cfg_setup( &cooler_cfg );
    COOLER_MAP_MIKROBUS( cooler_cfg, MIKROBUS_1 );
    err_t init_flag = cooler_init( &cooler, &cooler_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COOLER_ERROR == cooler_default_cfg ( &cooler ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application measures the temperature of the target object in degrees Celsius
 and enables a cooler if the temperature exceeds the temperature high limit value. 
 Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float temperature = 0;
    if ( COOLER_OK == cooler_get_object_temperature( &cooler, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f degC\r\n", temperature );
        log_printf( &logger, " Cooler: " );
        if ( COOLER_TEMP_HIGH_LIMIT < temperature )
        {
            if ( COOLER_OK == cooler_set_out_state( &cooler, COOLER_ENABLE ) )
            {
                log_printf( &logger, " Enabled.\r\n\n" );
            }
        }
        else
        {
            if ( COOLER_OK == cooler_set_out_state( &cooler, COOLER_DISABLE ) )
            {
                log_printf( &logger, " Disabled.\r\n\n" );
            }
        }
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
