
---
# Smart DOF 2 Click

> [Smart DOF 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5672) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5672&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This library contains API for Smart DOF 2 Click driver.
> The library initializes and defines the I2C or SPI bus drivers 
> to write and read data from registers. 
> The library also includes a function for reading 
> accelerometer and gyroscope X-axis, Y-axis, and Z-axis data
> and the temperature in degrees Celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartDOF2

### Example Key Functions

- `smartdof2_cfg_setup` Config Object Initialization function.
```c
void smartdof2_cfg_setup ( smartdof2_cfg_t *cfg );
```

- `smartdof2_init` Initialization function.
```c
err_t smartdof2_init ( smartdof2_t *ctx, smartdof2_cfg_t *cfg );
```

- `smartdof2_default_cfg` Click Default Configuration function.
```c
err_t smartdof2_default_cfg ( smartdof2_t *ctx );
```

- `smartdof2_get_acc_axis` Smart DOF 2 get accel sensor axes function.
```c
err_t smartdof2_get_acc_axis ( smartdof2_t *ctx, smartdof2_axis_t *acc_axis );
```

- `smartdof2_get_gyro_axis` Smart DOF 2 get gyro sensor axes function.
```c
err_t smartdof2_get_gyro_axis ( smartdof2_t *ctx, smartdof2_axis_t *gyro_axis );
```

- `smartdof2_get_temperature` Smart DOF 2 get temperature function.
```c
err_t smartdof2_get_temperature ( smartdof2_t *ctx, float *temperature );
```

### Application Init

> The initialization of I2C or SPI module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartdof2_cfg_t smartdof2_cfg;  /**< Click config object. */

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
    smartdof2_cfg_setup( &smartdof2_cfg );
    SMARTDOF2_MAP_MIKROBUS( smartdof2_cfg, MIKROBUS_1 );
    err_t init_flag = smartdof2_init( &smartdof2, &smartdof2_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTDOF2_ERROR == smartdof2_default_cfg ( &smartdof2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------------------\r\n" );
}
```

### Application Task

> This example demonstrates the use of the Smart DOF 2 Click board&trade;.
> Measures and displays acceleration and gyroscope data for X-axis, Y-axis, and Z-axis.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static smartdof2_axis_t acc_axis, gyro_axis;
    if ( SMARTDOF2_OK == smartdof2_get_acc_axis( &smartdof2, &acc_axis ) )
    {
        if ( SMARTDOF2_OK == smartdof2_get_gyro_axis( &smartdof2, &gyro_axis ) )
        {
            log_printf( &logger, " Accel X: %.2f mg | Gyro X: %.2f mdps\r\n", acc_axis.x, gyro_axis.x );
            log_printf( &logger, " Accel Y: %.2f mg | Gyro Y: %.2f mdps\r\n", acc_axis.y, gyro_axis.y );
            log_printf( &logger, " Accel Z: %.2f mg | Gyro Z: %.2f mdps\r\n", acc_axis.z, gyro_axis.z );
            log_printf( &logger, "--------------------------------------\r\n" );
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
