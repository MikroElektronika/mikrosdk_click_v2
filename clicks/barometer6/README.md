
---
# Barometer 6 Click

> [Barometer 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4978) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4978&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the Barometer 6 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer6

### Example Key Functions

- `barometer6_cfg_setup` Config Object Initialization function.
```c
void barometer6_cfg_setup ( barometer6_cfg_t *cfg );
```

- `barometer6_init` Initialization function.
```c
err_t barometer6_init ( barometer6_t *ctx, barometer6_cfg_t *cfg );
```

- `barometer6_default_cfg` Click Default Configuration function.
```c
err_t barometer6_default_cfg ( barometer6_t *ctx );
```

- `barometer6_hardware_reset` Barometer 6 hardware reset function.
```c
void barometer6_hardware_reset ( barometer6_t *ctx );
```

- `barometer6_set_mode` Barometer 6 set operation mode function.
```c
void barometer6_set_mode ( barometer6_t *ctx, uint8_t mode );
```

- `barometer6_read_temperature_value` Barometer 6 get temperature value function.
```c
void barometer6_read_temperature_value ( barometer6_t *ctx, float *temp_out );
```

### Application Init

> Initalizes SPI or I2C driver, applies default settings and reads Chip ID.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer6_cfg_t barometer6_cfg;  /**< Click config object. */

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
    barometer6_cfg_setup( &barometer6_cfg );
    BAROMETER6_MAP_MIKROBUS( barometer6_cfg, MIKROBUS_1 );
    err_t init_flag  = barometer6_init( &barometer6, &barometer6_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    barometer6_default_cfg ( &barometer6 );
    
    barometer6_read_id( &barometer6, &dev_id );
    if ( BAROMETER6_ID_VALUE != dev_id )
    {
        log_printf( &logger, " Device communication Error " );
        for ( ; ; );
    }
    
    log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " Device ID : 0x%.2X \r\n", ( uint16_t ) dev_id );
    log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Demonstrates use of Barometer 6 Click board by reading pressure and temperature data seconds 
> and logging it on the UART terminal.

```c
void application_task ( void )
{
    float pressure;
    float temperature;
    
    barometer6_read_temperature_value( &barometer6, &temperature );
    barometer6_read_preassure_value( &barometer6, &pressure );
        
    log_printf( &logger, " Temperature : %.2f C    \r\n", temperature );
    log_printf( &logger, " Pressure    : %.2f mBar \r\n", pressure );
    log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
    
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
