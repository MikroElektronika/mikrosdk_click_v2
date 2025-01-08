
---
# Ambient 16 Click

> [Ambient 16 Click](https://www.mikroe.com/?pid_product=MIKROE-4933) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4933&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This is an example that demonstrates the use of the Ambient 16 Click board 
> by measuring illuminance and displaying the value in Lux.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient16

### Example Key Functions

- `ambient16_cfg_setup` Config Object Initialization function.
```c
void ambient16_cfg_setup ( ambient16_cfg_t *cfg );
```

- `ambient16_init` Initialization function.
```c
err_t ambient16_init ( ambient16_t *ctx, ambient16_cfg_t *cfg );
```

- `ambient16_default_cfg` Click Default Configuration function.
```c
err_t ambient16_default_cfg ( ambient16_t *ctx );
```

- `ambient16_get_part_id` Ambient 16 get part ID function.
```c
err_t ambient16_get_part_id ( ambient16_t *ctx, uint8_t *part_id );
```

- `ambient16_set_gain` Ambient 16 set ADC gain function.
```c
err_t ambient16_set_gain ( ambient16_t *ctx, uint8_t data0_gain, uint8_t data1_gain );
```

- `ambient16_read_data` Ambient 16 get data in lux function.
```c
err_t ambient16_read_data ( ambient16_t *ctx, float *data0, float *data1 );
```

### Application Init

> Initializes I2C driver performs software reset and applies default settings.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient16_cfg_t ambient16_cfg;  /**< Click config object. */

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
    ambient16_cfg_setup( &ambient16_cfg );
    AMBIENT16_MAP_MIKROBUS( ambient16_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient16_init( &ambient16, &ambient16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT16_ERROR == ambient16_default_cfg ( &ambient16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint8_t id;
    ambient16_get_part_id( &ambient16, &id );
    
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " Part ID = 0x%.2X \r\n", ( uint16_t ) id );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    Delay_ms ( 500 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
}
```

### Application Task

> Demonstrates use of Ambient 16 Click board by reading data values of DATA0 and DATA1 in Lux
> every second, and logging it on the UART terminal.

```c
void application_task ( void ) 
{
    ambient16_read_data( &ambient16, &data0, &data1 );
    
    log_printf( &logger, " DATA 0 = %.2f lx    \r\n", data0 );
    log_printf( &logger, " DATA 1 = %.2f lx    \r\n", data1 );
    log_printf( &logger, "- - - - - - - - - - -\r\n" );
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
