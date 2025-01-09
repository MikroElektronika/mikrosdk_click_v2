
---
# Accel 15 Click

> [Accel 15 Click](https://www.mikroe.com/?pid_product=MIKROE-4501) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4501&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This library contains API for Accel 15 Click driver.
> The library initializes and defines the I2C or SPI bus drivers 
> to write and read data from registers. 
> The library also includes a function for reading X-axis, Y-axis, and Z-axis data. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel15

### Example Key Functions

- `accel15_cfg_setup` Config Object Initialization function.
```c
void accel15_cfg_setup ( accel15_cfg_t *cfg );
```

- `accel15_init` Initialization function.
```c
err_t accel15_init ( accel15_t *ctx, accel15_cfg_t *cfg );
```

- `accel15_default_cfg` Click Default Configuration function.
```c
err_t accel15_default_cfg ( accel15_t *ctx );
```

- `accel15_get_axis_data` Accel 15 get accelerometer axis function.
```c
err_t accel15_get_axis_data ( accel15_t *ctx, accel15_axis_t *axis );
```

- `accel15_generic_write` Accel 15 data writing function.
```c
err_t accel15_generic_write ( accel15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );
```

- `accel15_generic_read` Accel 15 data reading function.
```c
err_t accel15_generic_read ( accel15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );
```

### Application Init

> The initialization of I2C or SPI module, log UART, and additional pins. 
> After the driver init, the app checks communication, 
> sensor ID, and then executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    accel15_cfg_t accel15_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n-------------------------\r\n" );
    log_printf( &logger, "     Application Init    \r\n" );
    log_printf( &logger, "-------------------------\r\n" );

    // Click initialization.
    accel15_cfg_setup( &accel15_cfg );
    ACCEL15_MAP_MIKROBUS( accel15_cfg, MIKROBUS_1 );
    err_t init_flag  = accel15_init( &accel15, &accel15_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    if ( ACCEL15_ERROR == accel15_check_id( &accel15 ) ) 
    {
        log_printf( &logger, "   Communication ERROR   \r\n" );
        log_printf( &logger, "     Reset the device    \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
        for ( ; ; );
    }
    
    if ( ACCEL15_ERROR == accel15_default_cfg ( &accel15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf( &logger, "     Application Task    \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> Measures and displays acceleration data for X-axis, Y-axis, and Z-axis. 
> Results are being sent to the USART terminal where the user can track their changes. 
> This task repeats at data output rate which is set to 12.5 Hz.

```c
void application_task ( void ) 
{
    if ( ACCEL15_DRDY == accel15_get_int_1( &accel15 ) ) 
    {
        if ( ACCEL15_OK == accel15_get_axis_data( &accel15, &axis ) )
        {
            log_printf( &logger, "\tX : %d \r\n", axis.x );
            log_printf( &logger, "\tY : %d \r\n", axis.y );
            log_printf( &logger, "\tZ : %d \r\n", axis.z );
            log_printf( &logger, "-------------------------\r\n" );
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
