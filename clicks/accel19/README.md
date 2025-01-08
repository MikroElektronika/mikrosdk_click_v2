
---
# Accel 19 Click

> [Accel 19 Click](https://www.mikroe.com/?pid_product=MIKROE-4949) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4949&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This library contains API for Accel 19 Click driver.
> The library initializes and defines the I2C or SPI bus drivers 
> to write and read data from registers. 
> The library also includes a function for reading X-axis, Y-axis, and Z-axis data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel19

### Example Key Functions

- `accel19_cfg_setup` Config Object Initialization function.
```c
void accel19_cfg_setup ( accel19_cfg_t *cfg );
```

- `accel19_init` Initialization function.
```c
err_t accel19_init ( accel19_t *ctx, accel19_cfg_t *cfg );
```

- `accel19_default_cfg` Click Default Configuration function.
```c
err_t accel19_default_cfg ( accel19_t *ctx );
```

- `accel19_get_axis_data` Accel 19 get accelerometer axis function.
```c
err_t accel19_get_axis_data ( accel19_t *ctx, accel19_axis_t *axis );
```

- `accel19_data_ready` Accel 19 data ready function.
```c
uint8_t accel19_data_ready (accel19_t *ctx );
```

- `accel19_set_control` Accel 19 set control function.
```c
err_t accel19_set_control ( accel19_t *ctx, uint8_t odr, uint8_t op_mode, uint8_t lp_mode );
```

### Application Init

> The initialization of I2C or SPI module, log UART, and additional pins. 
> After the driver init, the app executes a default configuration
> and checks communication and device ID.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    accel19_cfg_t accel19_cfg;  /**< Click config object. */

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
    accel19_cfg_setup( &accel19_cfg );
    ACCEL19_MAP_MIKROBUS( accel19_cfg, MIKROBUS_1 );
    err_t init_flag  = accel19_init( &accel19, &accel19_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 1000 );
    
    if ( ACCEL19_ERROR == accel19_default_cfg ( &accel19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    if ( ACCEL19_ERROR == accel19_check_device_id( &accel19 ) ) 
    {
        log_printf( &logger, "   Communication ERROR   \r\n" );
        log_printf( &logger, "     Reset the device    \r\n" );
        log_printf( &logger, "-------------------------\r\n" );

        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 1000 ); 
}
```

### Application Task

> This is an example that demonstrates the use of the Accel 19 Click board&trade;.
> Measures and displays acceleration data for X-axis, Y-axis, and Z-axis. 
> Results are being sent to the USART terminal where the user can track their changes. 
> This task repeats every 1 sec.

```c
void application_task ( void )
{
    static accel19_axis_t axis;
    
    if ( ACCEL19_STATUS_DRDY == accel19_data_ready( &accel19 ) )
    {
        accel19_get_axis_data( &accel19, &axis );
        log_printf( &logger, "\tX : %5d \r\n\tY : %5d \r\n\tZ : %5d \r\n", axis.x, axis.y, axis.z );
        log_printf( &logger, "-------------------------\r\n" );
        Delay_ms ( 1000 );     
    }
    Delay_ms ( 1 );  
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
