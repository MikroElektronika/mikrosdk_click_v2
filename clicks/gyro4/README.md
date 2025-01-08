
---
# Gyro 4 Click

> [Gyro 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3661) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3661&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This application is a two-axis MEMS gyroscope for optical image stabilization.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Gyro4

### Example Key Functions

- `gyro4_cfg_setup` Config Object Initialization function. 
```c
void gyro4_cfg_setup ( gyro4_cfg_t *cfg );
``` 
 
- `gyro4_init` Initialization function. 
```c
err_t gyro4_init ( gyro4_t *ctx, gyro4_cfg_t *cfg );
```

- `gyro4_default_cfg` Click Default Configuration function. 
```c
void gyro4_default_cfg ( gyro4_t *ctx );
```

- `gyro4_spi_get` Getting register content. 
```c
uint8_t gyro4_spi_get ( gyro4_t *ctx, uint8_t register_address, uint8_t * register_buffer, uint16_t n_registers );
```
 
- `gyro4_get_temperature` Getting die temperature value. 
```c
uint8_t gyro4_get_temperature ( gyro4_t *ctx, float * temperature );
```

- `gyro4_get_axes` Getting axes values. 
```c
uint8_t gyro4_get_axes ( gyro4_t *ctx, float * x_axis, float * y_axis );
```

### Application Init

> Initializes SPI device

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    gyro4_cfg_t cfg;
    uint8_t initialize_flag;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gyro4_cfg_setup( &cfg );
    GYRO4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gyro4_init( &gyro4, &cfg );

    Delay_ms ( 500 );
    initialize_flag = gyro4_initialize( &gyro4 );
    if ( initialize_flag == 1 )
    {
        log_printf( &logger, "> App init fail \r\n" );
    }
    else if ( initialize_flag == 0 )
    {
        log_printf( &logger, "> App init done \r\n" );
    }
}
```

### Application Task

> Checks for data ready interrupt, gets axes and temperature data and logs those values

```c
void application_task ( )
{
    uint8_t int_flag;
    float x_axis;
    float y_axis;
    float die_temperature;
    char degrees_celsius[ 4 ] = { ' ', 176, 'C', 0x00 };
    char degrees_per_second[ 5 ] = { ' ', 176, '/', 's', 0x00 };

    int_flag = gyro4_int_get( &gyro4 );
    while ( int_flag == 1 )
    {
        int_flag = gyro4_int_get( &gyro4 );
    }
    
    gyro4_get_temperature( &gyro4, &die_temperature );
    gyro4_get_axes( &gyro4, &x_axis, &y_axis );

    log_printf( &logger, "\r\n" );
    log_printf( &logger, "> Die temperature : %.2f %c \r\n", die_temperature, degrees_celsius );
    log_printf( &logger, "> X axis : %.2f %c \r\n", x_axis, degrees_per_second );
    log_printf( &logger, "> Y axis : %.2f %c \r\n", y_axis, degrees_per_second );

    Delay_ms ( 500 );
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
