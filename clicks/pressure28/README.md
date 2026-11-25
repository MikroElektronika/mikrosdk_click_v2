
---
# Pressure 28 Click

> [Pressure 28 Click](https://www.mikroe.com/?pid_product=MIKROE-7097) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7097&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Aug 2026.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of the Pressure 28 Click board for measuring
gage pressure and temperature. The application starts a measurement session in
MODE1 and displays the results on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure28

### Example Key Functions

- `pressure28_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void pressure28_cfg_setup ( pressure28_cfg_t *cfg );
```

- `pressure28_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t pressure28_init ( pressure28_t *ctx, pressure28_cfg_t *cfg );
```

- `pressure28_default_cfg` This function executes a default configuration of Pressure 28 Click board.
```c
err_t pressure28_default_cfg ( pressure28_t *ctx );
```

- `pressure28_start_measurement` This function starts a measurement session in the selected mode.
```c
err_t pressure28_start_measurement ( pressure28_t *ctx, uint8_t mode );
```

- `pressure28_read_temperature` This function reads the compensated temperature result and converts it to degrees Celsius.
```c
err_t pressure28_read_temperature ( pressure28_t *ctx, float *temp );
```

- `pressure28_read_pressure` This function reads the compensated pressure result and converts it to millimeters of mercury.
```c
err_t pressure28_read_pressure ( pressure28_t *ctx, float *press );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure28_cfg_t pressure28_cfg;  /**< Click config object. */

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
    pressure28_cfg_setup( &pressure28_cfg );
    PRESSURE28_MAP_MIKROBUS( pressure28_cfg, MIKROBUS_POSITION_PRESSURE28 );
    err_t init_flag = pressure28_init( &pressure28, &pressure28_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE28_ERROR == pressure28_default_cfg ( &pressure28 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Restarts the measurement session, then reads and displays the pressure and
temperature results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float pressure = 0;
    float temperature = 0;

    /* The device converts temperature only once per measurement session, so the
     * session is restarted to refresh the temperature result */
    if ( PRESSURE28_OK != pressure28_reset_device( &pressure28 ) )
    {
        log_printf( &logger, " Failed to reset device.\r\n" );
    }
    else if ( PRESSURE28_OK != pressure28_start_measurement( &pressure28, PRESSURE28_DEFAULT_MODE ) )
    {
        log_printf( &logger, " Failed to start measurement.\r\n" );
    }
    else
    {
        if ( PRESSURE28_OK == pressure28_read_pressure( &pressure28, &pressure ) )
        {
            log_printf( &logger, " Pressure: %.3f mmHg\r\n", pressure );
        }
        else
        {
            log_printf( &logger, " Failed to read pressure.\r\n" );
        }
        if ( PRESSURE28_OK == pressure28_read_temperature( &pressure28, &temperature ) )
        {
            log_printf( &logger, " Temperature: %.2f degC\r\n\n", temperature );
        }
        else
        {
            log_printf( &logger, " Failed to read temperature.\r\n" );
        }
    }

    Delay_ms( 1000 );
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
