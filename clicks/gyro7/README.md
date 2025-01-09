
---
# Gyro 7 Click

> [Gyro 7 Click](https://www.mikroe.com/?pid_product=MIKROE-5145) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5145&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Gyro 7 Click board by reading and displaying
the values of X and Y axis in degrees per second and the chip internal temperature in Celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Gyro7

### Example Key Functions

- `gyro7_cfg_setup` Config Object Initialization function.
```c
void gyro7_cfg_setup ( gyro7_cfg_t *cfg );
```

- `gyro7_init` Initialization function.
```c
err_t gyro7_init ( gyro7_t *ctx, gyro7_cfg_t *cfg );
```

- `gyro7_default_cfg` Click Default Configuration function.
```c
err_t gyro7_default_cfg ( gyro7_t *ctx );
```

- `gyro7_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t gyro7_get_int_pin ( gyro7_t *ctx );
```

- `gyro7_read_gyroscope` This function reads the gyroscope X and Y axis in degrees per second (dps).
```c
err_t gyro7_read_gyroscope ( gyro7_t *ctx, float *x_axis, float *y_axis );
```

- `gyro7_read_temperature` This function reads the internal temperature in Celsius.
```c
err_t gyro7_read_temperature ( gyro7_t *ctx, float *temperature );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets the sample rate
to 40 Hz, gyroscope resolution to 374 dps, and enables the data ready interrupt.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gyro7_cfg_t gyro7_cfg;  /**< Click config object. */

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
    gyro7_cfg_setup( &gyro7_cfg );
    GYRO7_MAP_MIKROBUS( gyro7_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == gyro7_init( &gyro7, &gyro7_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( GYRO7_ERROR == gyro7_default_cfg ( &gyro7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt, then reads the values of X and Y gyroscope axis as well as
the chip internal temperature and displays the results on the USB UART. The data sample rate is
set to 40Hz by default, therefore the data is being read approximately every 25ms.

```c
void application_task ( void )
{
    if ( gyro7_get_int_pin ( &gyro7 ) )
    {
        float x_axis, y_axis, temperature;
        if ( GYRO7_OK == gyro7_read_gyroscope ( &gyro7, &x_axis, &y_axis ) )
        {
            log_printf( &logger, " X : %.2f dps\r\n", x_axis );
            log_printf( &logger, " Y : %.2f dps\r\n", y_axis );
        }
        if ( GYRO7_OK == gyro7_read_temperature ( &gyro7, &temperature ) )
        {
            log_printf( &logger, " Temperature : %.2f C\r\n\n", temperature );
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
