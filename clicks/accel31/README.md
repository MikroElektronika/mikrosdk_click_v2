
---
# Accel 31 Click

> [Accel 31 Click](https://www.mikroe.com/?pid_product=MIKROE-6410) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6410&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2024.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Accel 31 Click board by reading and displaying 
the accelerometer data (X, Y, and Z axis) and a temperature measurement in degrees Celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel31

### Example Key Functions

- `accel31_cfg_setup` Config Object Initialization function.
```c
void accel31_cfg_setup ( accel31_cfg_t *cfg );
```

- `accel31_init` Initialization function.
```c
err_t accel31_init ( accel31_t *ctx, accel31_cfg_t *cfg );
```

- `accel31_default_cfg` Click Default Configuration function.
```c
err_t accel31_default_cfg ( accel31_t *ctx );
```

- `accel31_get_data` This function reads the accelerometer and temperature measurement data.
```c
err_t accel31_get_data ( accel31_t *ctx, accel31_data_t *data_out );
```

- `accel31_set_accel_odr` This function sets the accel measurement output data rate.
```c
err_t accel31_set_accel_odr ( accel31_t *ctx, uint8_t odr );
```

- `accel31_set_accel_fsr` This function sets the accel measurement full scale range.
```c
err_t accel31_set_accel_fsr ( accel31_t *ctx, uint8_t fsr );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel31_cfg_t accel31_cfg;  /**< Click config object. */

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
    accel31_cfg_setup( &accel31_cfg );
    ACCEL31_MAP_MIKROBUS( accel31_cfg, MIKROBUS_1 );
    err_t init_flag = accel31_init( &accel31, &accel31_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL31_ERROR == accel31_default_cfg ( &accel31 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Checks for a new data ready indication and then reads the accelerometer and temperature
measurements. The results are displayed on the USB UART at 12.5 Hz output data rate.

```c
void application_task ( void )
{
    accel31_data_t meas_data;
    if ( ACCEL31_OK == accel31_get_data ( &accel31, &meas_data ) )
    {
        log_printf( &logger, " Accel X: %.3f g\r\n", meas_data.accel.x );
        log_printf( &logger, " Accel Y: %.3f g\r\n", meas_data.accel.y );
        log_printf( &logger, " Accel Z: %.3f g\r\n", meas_data.accel.z );
        log_printf( &logger, " Temperature: %d degC\r\n\n", ( int16_t ) meas_data.temperature );
        Delay_ms ( 80 );
    }
}
```

### Note

> The Click board determines the communication protocol at the first communication check
after power-up. In the case of I2C, the IC responds with NACK on the first check,
which blocks the I2C bus on some MCUs. Re-running the program (without power cycling
the Click board power supply) should unlock the communication and solve this issue.

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
