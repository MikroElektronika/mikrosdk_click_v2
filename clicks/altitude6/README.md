
---
# Altitude 6 Click

> [Altitude 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4903) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4903&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This library contains API for Altitude 6 Click driver.
> The demo application reads and calculate 
> temperature, pressure and altitude data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Altitude6

### Example Key Functions

- `altitude6_cfg_setup` Config Object Initialization function.
```c
void altitude6_cfg_setup ( altitude6_cfg_t *cfg );
```

- `altitude6_init` Initialization function.
```c
err_t altitude6_init ( altitude6_t *ctx, altitude6_cfg_t *cfg );
```

- `altitude6_default_cfg` Click Default Configuration function.
```c
err_t altitude6_default_cfg ( altitude6_t *ctx );
```

- `altitude6_get_data` Altitude 6 get data function.
```c
err_t altitude6_get_data ( altitude6_t *ctx, float *temperature, float *pressure, float *altitude );
```

- `altitude6_get_raw_data` Altitude 6 get raw data function.
```c
err_t altitude6_get_raw_data ( altitude6_t *ctx, uint32_t *temp_data, uint32_t *press_data );
```

- `altitude6_get_calibration_data` Altitude 6 get calibration data function.
```c
err_t altitude6_get_calibration_data ( altitude6_t *ctx );
```

### Application Init

> Initializes I2C or SPI driver and log UART.
> After driver initialization the app set 
> driver interface setup and  default settings.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    altitude6_cfg_t altitude6_cfg;  /**< Click config object. */

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
    altitude6_cfg_setup( &altitude6_cfg );
    altitude6_drv_interface_selection( &altitude6_cfg, ALTITUDE6_DRV_SEL_I2C );
    ALTITUDE6_MAP_MIKROBUS( altitude6_cfg, MIKROBUS_1 );
    err_t init_flag  = altitude6_init( &altitude6, &altitude6_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ALTITUDE6_ERROR == altitude6_default_cfg ( &altitude6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that demonstrates the use of the Altitude 6 Click board&trade;.
> In this example, display the Altitude ( m ), 
> Pressure ( mBar ) and Temperature ( degree Celsius ) data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    static float temperature;
    static float pressure;
    static float altitude;
    
    if ( altitude6_get_data( &altitude6, &temperature, &pressure, &altitude ) == ALTITUDE6_OK )
    {
        log_printf( &logger, " Altitude    : %.2f m       \r\n", altitude );
        log_printf( &logger, " Pressure    : %.2f mbar    \r\n", pressure );
        log_printf( &logger, " Temperature : %.2f C       \r\n", temperature );
        log_printf( &logger, "----------------------------\r\n" );   
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
