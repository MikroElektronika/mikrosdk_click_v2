
---
# Ambient 23 Click

> [Ambient 23 Click](https://www.mikroe.com/?pid_product=MIKROE-5701) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5701&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Apr 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Ambient 23 Click board by measuring 
  the ambient light level in Lux.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient23

### Example Key Functions

- `ambient23_cfg_setup` Config Object Initialization function.
```c
void ambient23_cfg_setup ( ambient23_cfg_t *cfg );
```

- `ambient23_init` Initialization function.
```c
err_t ambient23_init ( ambient23_t *ctx, ambient23_cfg_t *cfg );
```

- `ambient23_default_cfg` Click Default Configuration function.
```c
err_t ambient23_default_cfg ( ambient23_t *ctx );
```

- `ambient23_reg_read` Ambient 23 register reading function.
```c
err_t ambient23_reg_read ( ambient23_t *ctx, uint8_t reg, uint16_t *data_out );
```

- `ambient23_calculate_res` Ambient 23 get conversion data function.
```c
err_t ambient23_calculate_res ( ambient23_t *ctx, float *conversion_mul );
```

- `ambient23_read_light_data` Ambient 23 get light data function.
```c
err_t ambient23_read_light_data ( ambient23_t *ctx, float *light_data );
```

### Application Init

> Initializes the driver, checks communication by reading part ID
  and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient23_cfg_t ambient23_cfg;  /**< Click config object. */

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
    ambient23_cfg_setup( &ambient23_cfg );
    AMBIENT23_MAP_MIKROBUS( ambient23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient23_init( &ambient23, &ambient23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint16_t part_id = 0;
    ambient23_reg_read( &ambient23, AMBIENT23_REG_DEVICE_ID, &part_id );
    if ( AMBIENT23_PART_ID != ( uint8_t ) part_id )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    if ( AMBIENT23_ERROR == ambient23_default_cfg ( &ambient23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Measuring ambient light level by reading data from the Ambient 23 Click board
  and displaying it using UART Serial terminal.

```c
void application_task ( void ) 
{
    float data_tmp;
    
    ambient23_read_light_data( &ambient23, &data_tmp );
    log_printf( &logger, "Data: %.2f lux\r\n", data_tmp );
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
