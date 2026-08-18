
---
# 3D Hall 17 Click

> [3D Hall 17 Click](https://www.mikroe.com/?pid_product=MIKROE-7024) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7024&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : May 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the 3D Hall 17 Click board by reading
and displaying the magnetic flux density on all three axes (X, Y, Z) in
Gauss, and the sensor die temperature in degrees Celsius.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.3DHall17

### Example Key Functions

- `c3dhall17_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void c3dhall17_cfg_setup ( c3dhall17_cfg_t *cfg );
```

- `c3dhall17_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t c3dhall17_init ( c3dhall17_t *ctx, c3dhall17_cfg_t *cfg );
```

- `c3dhall17_default_cfg` This function executes a default configuration of 3D Hall 17 Click board.
```c
err_t c3dhall17_default_cfg ( c3dhall17_t *ctx );
```

- `c3dhall17_set_op_mode` This function sets the operating mode of the device.
```c
err_t c3dhall17_set_op_mode ( c3dhall17_t *ctx, uint8_t mod1, uint8_t mod2 );
```

- `c3dhall17_get_data` This function reads and converts the magnetic flux density on all three axes and the die temperature.
```c
err_t c3dhall17_get_data ( c3dhall17_t *ctx, c3dhall17_data_t *data_out );
```

- `c3dhall17_hw_reset` This function performs a hardware reset of the device.
```c
void c3dhall17_hw_reset ( c3dhall17_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall17_cfg_t c3dhall17_cfg;  /**< Click config object. */

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
    c3dhall17_cfg_setup( &c3dhall17_cfg );
    C3DHALL17_MAP_MIKROBUS( c3dhall17_cfg, MIKROBUS_POSITION_3DHALL17 );
    if ( I2C_MASTER_ERROR == c3dhall17_init( &c3dhall17, &c3dhall17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C3DHALL17_ERROR == c3dhall17_default_cfg ( &c3dhall17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads data from the sensor and displays them on the USB UART every 200ms.

```c
void application_task ( void ) 
{
    c3dhall17_data_t meas_data;

    if ( C3DHALL17_OK == c3dhall17_get_data( &c3dhall17, &meas_data ) )
    {
        log_printf( &logger, " Bx: %.1f Gauss\r\n", meas_data.x_val );
        log_printf( &logger, " By: %.1f Gauss\r\n", meas_data.y_val );
        log_printf( &logger, " Bz: %.1f Gauss\r\n", meas_data.z_val );
        log_printf( &logger, " Temperature: %.1f degC\r\n", meas_data.temp_val );
        log_printf( &logger, " ---------------------------\r\n" );
        Delay_ms( 200 );
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
