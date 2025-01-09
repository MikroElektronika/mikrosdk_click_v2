
---
# Accel 29 Click

> [Accel 29 Click](https://www.mikroe.com/?pid_product=MIKROE-5671) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5671&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2023.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Accel 29 Click board by reading and displaying the accelerometer data (X, Y, and Z axis) averaged from 100 samples.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel29

### Example Key Functions

- `accel29_cfg_setup` Config Object Initialization function.
```c
void accel29_cfg_setup ( accel29_cfg_t *cfg );
```

- `accel29_init` Initialization function.
```c
err_t accel29_init ( accel29_t *ctx, accel29_cfg_t *cfg );
```

- `accel29_default_cfg` Click Default Configuration function.
```c
err_t accel29_default_cfg ( accel29_t *ctx );
```

- `accel29_calibrate_offset` This function calibrates accel offset to the specified values by setting the OFSX/Y/Z registers.
```c
err_t accel29_calibrate_offset ( accel29_t *ctx, accel29_axes_t calib_axes );
```

- `accel29_get_avg_axes` This function reads a specified number of samples for accel X, Y, and Z axis data in g and averages them.
```c
err_t accel29_get_avg_axes ( accel29_t *ctx, uint16_t num_samples, accel29_axes_t *avg_axes );
```

### Application Init

> Initializes the driver, performs the Click default configuration, and calibrates the accel data offsets.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel29_cfg_t accel29_cfg;  /**< Click config object. */

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
    accel29_cfg_setup( &accel29_cfg );
    ACCEL29_MAP_MIKROBUS( accel29_cfg, MIKROBUS_1 );
    err_t init_flag = accel29_init( &accel29, &accel29_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL29_ERROR == accel29_default_cfg ( &accel29 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    accel29_axes_t calib_axes;
    calib_axes.x = ACCEL29_CALIB_X;
    calib_axes.y = ACCEL29_CALIB_Y;
    calib_axes.z = ACCEL29_CALIB_Z;
    if ( ACCEL29_ERROR == accel29_calibrate_offset ( &accel29, calib_axes ) )
    {
        log_error( &logger, " Calibrate offset." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays on the USB UART the accelerometer data (X, Y, and Z axis) averaged from 100 samples.

```c
void application_task ( void )
{
    accel29_axes_t axes;
    if ( ACCEL29_OK == accel29_get_avg_axes ( &accel29, ACCEL29_NUM_OF_SAMPLES, &axes ) )
    {
        log_printf( &logger, " X: %.1f g\r\n", axes.x );
        log_printf( &logger, " Y: %.1f g\r\n", axes.y );
        log_printf( &logger, " Z: %.1f g\r\n\n", axes.z );
    }
}
```

### Note

> This Click board should be used for high g applications of up to +-200g. It is not recommended for low g applications because of its high scale factor which is about 48.83 mg per LSB.

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
