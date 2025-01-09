
---
# Accel 20 Click

> [Accel 20 Click](https://www.mikroe.com/?pid_product=MIKROE-4888) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4888&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This library contains API for Accel 20 Click driver.
> The library initializes and defines the I2C or SPI bus drivers 
> to write and read data from registers. 
> The library also includes a function for reading X-axis, Y-axis, and Z-axis data. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel20

### Example Key Functions

- `accel20_cfg_setup` Config Object Initialization function.
```c
void accel20_cfg_setup ( accel20_cfg_t *cfg );
```

- `accel20_init` Initialization function.
```c
err_t accel20_init ( accel20_t *ctx, accel20_cfg_t *cfg );
```

- `accel20_default_cfg` Click Default Configuration function.
```c
err_t accel20_default_cfg ( accel20_t *ctx );
```

- `accel20_get_axis_data` Accel 20 get accelerometer axis function.
```c
err_t accel20_get_axis_data ( accel20_t *ctx, accel20_axis_t *axis );
```

- `accel20_set_output_data_rate` Accel 20 set output data rate function.
```c
err_t accel20_set_output_data_rate ( accel20_t *ctx, uint8_t odr );
```

- `accel20_set_accel_range` Accel 20 set accel range function.
```c
err_t accel20_set_accel_range ( accel20_t *ctx, uint8_t range );
```

### Application Init

> The initialization of I2C or SPI module, log UART, and additional pins. 
> After the driver init, the app executes a default configuration,
> checks communication and device ID. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    accel20_cfg_t accel20_cfg;  /**< Click config object. */

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
    accel20_cfg_setup( &accel20_cfg );
    ACCEL20_MAP_MIKROBUS( accel20_cfg, MIKROBUS_1 );
    err_t init_flag  = accel20_init( &accel20, &accel20_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    accel20_default_cfg ( &accel20 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "      Accel 20 Click     \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 100 ); 
    
    if ( accel20_check_id( &accel20 ) == ACCEL20_OK ) 
    {
        log_printf( &logger, "     Communication OK    \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
    }
    else 
    {
        log_printf( &logger, "   Communication ERROR   \r\n" );
        log_printf( &logger, "     Reset the device    \r\n" );
        log_printf( &logger, "-------------------------\r\n" );

        for ( ; ; );
    }
    
    log_printf( &logger, "       Accel Data:       \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 100 ); 
}
```

### Application Task

> This is an example that demonstrates the use of the Accel 20 Click board&trade;.
> Measures and displays acceleration data for X-axis, Y-axis, and Z-axis. 
> Results are being sent to the USART terminal where the user can track their changes. 
> This task repeats every 1 sec.

```c
void application_task ( void )
{
    static accel20_axis_t axis;
    
    if ( accel20_get_int_1( &accel20 ) == ACCEL20_INT1_DATA_READY )
    {
        accel20_get_axis_data( &accel20, &axis );
        log_printf( &logger, "\tX : %d \r\n\tY : %d \r\n\tZ : %d \r\n", axis.x, axis.y, axis.z );
        log_printf( &logger, "-------------------------\r\n" );
        Delay_ms ( 1000 );     
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
