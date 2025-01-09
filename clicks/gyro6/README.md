
---
# Gyro 6 Click

> [Gyro 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4827) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4827&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Gyro 6 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Gyro6

### Example Key Functions

- `gyro6_cfg_setup` Config Object Initialization function.
```c
void gyro6_cfg_setup ( gyro6_cfg_t *cfg );
```

- `gyro6_init` Initialization function.
```c
err_t gyro6_init ( gyro6_t *ctx, gyro6_cfg_t *cfg );
```

- `gyro6_default_cfg` Click Default Configuration function.
```c
err_t gyro6_default_cfg ( gyro6_t *ctx );
```

- `gyro6_get_axis` This function reads the gyroscope values for all three axis.
```c
err_t gyro6_get_axis ( gyro6_t *ctx, float *x_axis, float *y_axis, float *z_axis );
```

- `gyro6_read_die_temperature` This function reads the chip internal temperature.
```c
err_t gyro6_read_die_temperature ( gyro6_t *ctx, float *temperature );
```

- `gyro6_set_low_power_mode` This function enables low power mode and sets the sample rate and average sample data.
```c
err_t gyro6_set_low_power_mode ( gyro6_t *ctx, uint8_t sample_rate, uint8_t average );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    gyro6_cfg_t gyro6_cfg;  /**< Click config object. */

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
    gyro6_cfg_setup( &gyro6_cfg );
    GYRO6_MAP_MIKROBUS( gyro6_cfg, MIKROBUS_1 );
    err_t init_flag  = gyro6_init( &gyro6, &gyro6_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    if ( GYRO6_ERROR == gyro6_default_cfg ( &gyro6 ) )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data to be ready, then reads the values of all three axis
> and displays the results on the USB UART. The data sample rate is set to 10Hz by default,
> therefore the data is being read approximately every 100ms.

```c
void application_task ( void )
{
    if ( gyro6_get_int_pin ( &gyro6 ) )
    {
        float x_axis_value = 0;
        float y_axis_value = 0;
        float z_axis_value = 0;

        if ( GYRO6_OK == gyro6_get_axis ( &gyro6, &x_axis_value, &y_axis_value, &z_axis_value ) )
        {
            log_printf( &logger, " X : %.2f\r\n", x_axis_value );
            log_printf( &logger, " Y : %.2f\r\n", y_axis_value );
            log_printf( &logger, " Z : %.2f\r\n\n", z_axis_value );
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
