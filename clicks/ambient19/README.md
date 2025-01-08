
---
# Ambient 19 Click

> [Ambient 19 Click](https://www.mikroe.com/?pid_product=MIKROE-5245) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5245&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Ambient 19 Click board by measuring the ambient light level in Lux.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient19

### Example Key Functions

- `ambient19_cfg_setup` Config Object Initialization function.
```c
void ambient19_cfg_setup ( ambient19_cfg_t *cfg );
```

- `ambient19_init` Initialization function.
```c
err_t ambient19_init ( ambient19_t *ctx, ambient19_cfg_t *cfg );
```

- `ambient19_default_cfg` Click Default Configuration function.
```c
err_t ambient19_default_cfg ( ambient19_t *ctx );
```

- `ambient19_measure_light_level` This function reads the raw ALS data from two channels and then measures the light level in lux based on those readings.
```c
err_t ambient19_measure_light_level ( ambient19_t *ctx, uint16_t *lux );
```

- `ambient19_read_raw_proximity` This function reads the raw PS and IR data of the proximity sensor.
```c
err_t ambient19_read_raw_proximity ( ambient19_t *ctx, uint16_t *ps_data, uint16_t *ir_data );
```

- `ambient19_clear_interrupts` This function clears all interrupts by clearing the INT_FLAG register.
```c
err_t ambient19_clear_interrupts ( ambient19_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient19_cfg_t ambient19_cfg;  /**< Click config object. */

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
    ambient19_cfg_setup( &ambient19_cfg );
    AMBIENT19_MAP_MIKROBUS( ambient19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient19_init( &ambient19, &ambient19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT19_ERROR == ambient19_default_cfg ( &ambient19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt, then reads the ambient light level in Lux as well as the raw proximity data of PS and IR leds and displays the results on the USB UART. 
By default, the data ready interrupt triggers upon every ADC cycle which will be performed every 500ms approximately.

```c
void application_task ( void )
{
    if ( !ambient19_get_int_pin ( &ambient19 ) )
    {
        uint16_t lux, ps_data, ir_data;
        if ( AMBIENT19_OK == ambient19_measure_light_level ( &ambient19, &lux ) )
        {
            log_printf ( &logger, "\r\n Ambient light level [Lux]: %u\r\n", lux );
        }
        if ( AMBIENT19_OK == ambient19_read_raw_proximity ( &ambient19, &ps_data, &ir_data ) )
        {
            log_printf ( &logger, " PS data: %u\r\n", ps_data );
            log_printf ( &logger, " IR data: %u\r\n", ir_data );
        }
        ambient19_clear_interrupts ( &ambient19 );
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
