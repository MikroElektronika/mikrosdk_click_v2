
---
# Gyro 9 Click

> [Gyro 9 Click](https://www.mikroe.com/?pid_product=MIKROE-5881) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5881&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This library contains API for Gyro 9 Click driver.
> The library initializes and defines the I2C and SPI bus drivers to 
> write and read data from registers, as well as the default 
> configuration for reading gyroscope data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Gyro9

### Example Key Functions

- `gyro9_cfg_setup` Config Object Initialization function.
```c
void gyro9_cfg_setup ( gyro9_cfg_t *cfg );
```

- `gyro9_init` Initialization function.
```c
err_t gyro9_init ( gyro9_t *ctx, gyro9_cfg_t *cfg );
```

- `gyro9_default_cfg` Click Default Configuration function.
```c
err_t gyro9_default_cfg ( gyro9_t *ctx );
```

- `gyro9_get_gyro_axis` Gyro 9 get gyro sensor axes function.
```c
err_t gyro9_get_gyro_axis ( gyro9_t *ctx, gyro9_axis_t *gyro_axis );
```

- `gyro9_get_axis_data` Gyro 9 get gyro data function.
```c
err_t gyro9_get_axis_data ( gyro9_t *ctx, gyro9_axis_data_t *gyro_axis );
```

- `gyro9_get_data_ready` Gyro 9 get data ready function.
```c
uint8_t gyro9_get_data_ready ( gyro9_t *ctx );
```

### Application Init

> The initialization of I2C or SPI module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gyro9_cfg_t gyro9_cfg;  /**< Click config object. */

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
    gyro9_cfg_setup( &gyro9_cfg );
    GYRO9_MAP_MIKROBUS( gyro9_cfg, MIKROBUS_1 );
    err_t init_flag = gyro9_init( &gyro9, &gyro9_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( GYRO9_ERROR == gyro9_default_cfg ( &gyro9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "_________________\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Gyro 9 Click board&trade;.
> Measures and displays gyroscope angular rate for X-axis, Y-axis, and Z-axis.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    gyro9_axis_t gyro_axis;
    if ( gyro9_get_data_ready( &gyro9 ) )
    {
        if ( GYRO9_OK == gyro9_get_gyro_axis( &gyro9, &gyro_axis ) )
        {
            log_printf( &logger, " Gyro X: %.2f pds\r\n", gyro_axis.x );
            log_printf( &logger, " Gyro Y: %.2f pds\r\n", gyro_axis.y );
            log_printf( &logger, " Gyro Z: %.2f pds\r\n", gyro_axis.z );
            log_printf( &logger, "_________________\r\n" );
            Delay_ms ( 1000 );
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
