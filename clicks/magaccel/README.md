
---
# MagAccel Click

> [MagAccel Click](https://www.mikroe.com/?pid_product=MIKROE-6027) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6027&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Mag&Accel Click driver.
> The library initializes and defines the I2C drivers to 
> write and read data from registers, as well as the default 
> configuration for reading accelerator data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MagAccel

### Example Key Functions

- `magaccel_cfg_setup` Config Object Initialization function.
```c
void magaccel_cfg_setup ( magaccel_cfg_t *cfg );
```

- `magaccel_init` Initialization function.
```c
err_t magaccel_init ( magaccel_t *ctx, magaccel_cfg_t *cfg );
```

- `magaccel_default_cfg` Click Default Configuration function.
```c
err_t magaccel_default_cfg ( magaccel_t *ctx );
```

- `magaccel_get_axes_data` This function reads the accelerometer sensor axes data.
```c
err_t magaccel_get_axes_data ( magaccel_t *ctx, magaccel_axes_t *axes );
```

- `magaccel_set_op_mode` This function sets the desired operating mode of the sensor.
```c
err_t magaccel_set_op_mode ( magaccel_t *ctx, uint8_t op_mode );
```

- `magaccel_check_mag_field` This function checks the magnetic field y by reading the states of the FLD (AN) pin.
```c
uint8_t magaccel_check_mag_field ( magaccel_t *ctx );
```

### Application Init

> The initialization of the I2C module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magaccel_cfg_t magaccel_cfg;  /**< Click config object. */

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
    magaccel_cfg_setup( &magaccel_cfg );
    MAGACCEL_MAP_MIKROBUS( magaccel_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == magaccel_init( &magaccel, &magaccel_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGACCEL_ERROR == magaccel_default_cfg ( &magaccel ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "_________________\r\n" );
}
```

### Application Task

> This example demonstrates the use of the Mag&Accel Click board.
> Measures and displays acceleration data for the X-axis, Y-axis, and Z-axis 
> and the presence of a magnetic field. 
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( MAGACCEL_DATA_READY == magaccel_check_data_ready( &magaccel ) )
    {
        magaccel_axes_t acc_axis;
        magaccel_get_axes_data( &magaccel, &acc_axis );
        
        if ( MAGACCEL_DET_MAG_FIELD == magaccel_check_mag_field( &magaccel ) )
        {
            log_printf( &logger, " Presence of a magnetic field\r\n" );
            log_printf( &logger, "_________________\r\n" );
        }
        
        log_printf( &logger, " Accel X: %.2f mg\r\n", acc_axis.x );
        log_printf( &logger, " Accel Y: %.2f mg\r\n", acc_axis.y );
        log_printf( &logger, " Accel Z: %.2f mg\r\n", acc_axis.z );
        log_printf( &logger, "_________________\r\n" );
        Delay_ms ( 100 );
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
