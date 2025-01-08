
---
# Ambient 15 Click

> [Ambient 15 Click](https://www.mikroe.com/?pid_product=MIKROE-4967) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4967&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Ambient 15 Click board by measuring the ambient light level in Lux.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient15

### Example Key Functions

- `ambient15_cfg_setup` Config Object Initialization function.
```c
void ambient15_cfg_setup ( ambient15_cfg_t *cfg );
```

- `ambient15_init` Initialization function.
```c
err_t ambient15_init ( ambient15_t *ctx, ambient15_cfg_t *cfg );
```

- `ambient15_default_cfg` Click Default Configuration function.
```c
err_t ambient15_default_cfg ( ambient15_t *ctx );
```

- `ambient15_set_atime` This function sets the timing register for the selected integration time.
```c
err_t ambient15_set_atime ( ambient15_t *ctx, float atime_ms );
```

- `ambient15_set_gain` This function sets the gain level.
```c
err_t ambient15_set_gain ( ambient15_t *ctx, uint8_t gain );
```

- `ambient15_measure_light_level` This function reads the raw ADC data from two channels and then measures the light level in lux based on those readings.
```c
err_t ambient15_measure_light_level ( ambient15_t *ctx, uint16_t *lux );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient15_cfg_t ambient15_cfg;  /**< Click config object. */

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
    ambient15_cfg_setup( &ambient15_cfg );
    AMBIENT15_MAP_MIKROBUS( ambient15_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient15_init( &ambient15, &ambient15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT15_ERROR == ambient15_default_cfg ( &ambient15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt, then reads the ambient light level in Lux
and displays the results on the USB UART. By default, the data ready interrupt triggers
upon every ADC cycle which will be performed every 200ms.

```c
void application_task ( void )
{
    if ( !ambient15_get_int_pin ( &ambient15 ) )
    {
        uint16_t lux;
        if ( AMBIENT15_OK == ambient15_measure_light_level ( &ambient15, &lux ) )
        {
            log_printf ( &logger, " Ambient light level [Lux]: %u\r\n\n", lux );
        }
    }
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
