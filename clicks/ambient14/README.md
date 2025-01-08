
---
# Ambient 14 Click

> [Ambient 14 Click](https://www.mikroe.com/?pid_product=MIKROE-6255) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6255&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Ambient 14 Click board by measuring the illuminance level (Lux) and the proximity data on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient14

### Example Key Functions

- `ambient14_cfg_setup` Config Object Initialization function.
```c
void ambient14_cfg_setup ( ambient14_cfg_t *cfg );
```

- `ambient14_init` Initialization function.
```c
err_t ambient14_init ( ambient14_t *ctx, ambient14_cfg_t *cfg );
```

- `ambient14_default_cfg` Click Default Configuration function.
```c
err_t ambient14_default_cfg ( ambient14_t *ctx );
```

- `ambient14_read_proximity` This function reads the raw proximity data. The higher the value, the closer the detected object is.
```c
err_t ambient14_read_proximity ( ambient14_t *ctx, uint16_t *prox_data );
```

- `ambient14_read_als_ir` This function reads the raw ALS and IR data.
```c
err_t ambient14_read_als_ir ( ambient14_t *ctx, uint16_t *als_data, uint16_t *ir_data );
```

- `ambient14_get_illuminance` This function calculates the illuminance level (Lux) from ALS data counts input.
```c
err_t ambient14_get_illuminance ( ambient14_t *ctx, uint16_t als_data, float *illuminance );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient14_cfg_t ambient14_cfg;  /**< Click config object. */

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
    ambient14_cfg_setup( &ambient14_cfg );
    AMBIENT14_MAP_MIKROBUS( ambient14_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient14_init( &ambient14, &ambient14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT14_ERROR == ambient14_default_cfg ( &ambient14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the proximity, ALS, and IR raw data counts when data is ready.
Calculates the illuminance level in Lux from ALS data counts and displays the results on the USB UART approximately every 500ms.

```c
void application_task ( void )
{
    uint16_t proximity = 0;
    uint16_t als_data = 0;
    uint16_t ir_data = 0;
    float illuminance = 0;
    
    // Enable and wait for proximity interrupt
    ambient14_write_reg ( &ambient14, AMBIENT14_REG_INTENAB, AMBIENT14_INTENAB_PIEN );
    while ( ambient14_get_int_pin ( &ambient14 ) );

    // Read proximity data and clear interrupts
    if ( AMBIENT14_OK == ambient14_read_proximity ( &ambient14, &proximity ) )
    {
        log_printf ( &logger, " Proximity: %u\r\n", proximity );
    }
    ambient14_clear_interrupts ( &ambient14 );

    // Enable and wait for ALS interrupt
    ambient14_write_reg ( &ambient14, AMBIENT14_REG_INTENAB, AMBIENT14_INTENAB_AIEN );
    while ( ambient14_get_int_pin ( &ambient14 ) );

    // Read ALS and IR data counts, calculates illuminance level, and clear interrupts
    if ( AMBIENT14_OK == ambient14_read_als_ir ( &ambient14, &als_data, &ir_data ) )
    {
        log_printf ( &logger, " ALS: %u\r\n", als_data );
        log_printf ( &logger, " IR: %u\r\n", ir_data );
        if ( AMBIENT14_OK == ambient14_get_illuminance ( &ambient14, als_data, &illuminance ) )
        {
            log_printf ( &logger, " Illuminance: %.1f Lux\r\n\n", illuminance );
        }
    }
    ambient14_clear_interrupts ( &ambient14 );
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
