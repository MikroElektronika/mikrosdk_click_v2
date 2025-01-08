
---
# AccelQvar Click

> [AccelQvar Click](https://www.mikroe.com/?pid_product=MIKROE-6025) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6025&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2023.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This library contains API for the AccelQvar Click driver. 
> The library initializes and defines the I2C and SPI drivers to write and read data 
> from registers and the default configuration for reading the accelerator data 
> and Qvar electrostatic sensor measurement.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AccelQvar

### Example Key Functions

- `accelqvar_cfg_setup` Config Object Initialization function.
```c
void accelqvar_cfg_setup ( accelqvar_cfg_t *cfg );
```

- `accelqvar_init` Initialization function.
```c
err_t accelqvar_init ( accelqvar_t *ctx, accelqvar_cfg_t *cfg );
```

- `accelqvar_default_cfg` Click Default Configuration function.
```c
err_t accelqvar_default_cfg ( accelqvar_t *ctx );
```

- `accelqvar_get_axes_data` This function reads the accelerometer sensor axes data.
```c
err_t accelqvar_get_axes_data ( accelqvar_t *ctx, accelqvar_axes_t *axes );
```

- `accelqvar_get_qvar_data` This function reads the Qvar electrostatic sensor data output.
```c
err_t accelqvar_get_qvar_data ( accelqvar_t *ctx, float *qvar );
```

### Application Init

> The initialization of I2C and SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accelqvar_cfg_t accelqvar_cfg;  /**< Click config object. */

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
    accelqvar_cfg_setup( &accelqvar_cfg );
    ACCELQVAR_MAP_MIKROBUS( accelqvar_cfg, MIKROBUS_1 );
    err_t init_flag = accelqvar_init( &accelqvar, &accelqvar_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );

    if ( ACCELQVAR_ERROR == accelqvar_default_cfg ( &accelqvar ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );

    log_info( &logger, " Application Task " );
    log_printf( &logger, "_________________\r\n" );
}
```

### Application Task

> This example demonstrates the use of the AccelQvar Click board.
> Measures and displays acceleration data for the X-axis, Y-axis, and Z-axis [mg] 
> and detects and displays a touch position and the strength of a touch.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    accelqvar_axes_t acc_axis;
    if ( ACCELQVAR_OK == accelqvar_get_axes_data( &accelqvar, &acc_axis ) )
    {
        log_printf( &logger, " Accel X: %.2f mg\r\n", acc_axis.x );
        log_printf( &logger, " Accel Y: %.2f mg\r\n", acc_axis.y );
        log_printf( &logger, " Accel Z: %.2f mg\r\n", acc_axis.z );
        log_printf( &logger, "_________________\r\n" );
    }

    float qvar = 0;
    if ( ACCELQVAR_OK == accelqvar_get_qvar_data( &accelqvar, &qvar ) )
    {
        if ( abs( qvar ) > ACCELQVAR_THOLD_DETECT_TOUCH )
        {
            uint8_t touch_strength = ( uint8_t ) ( abs( qvar ) / ACCELQVAR_THOLD_SENS );
            log_printf( &logger, " Touch position: " );
            if ( qvar < ACCELQVAR_TOUCH_ZERO )
            {
                log_printf( &logger, " Left\r\n" );
            }
            else
            {
                log_printf( &logger, " Right\r\n " );
            }
            log_printf( &logger, " Strength: " );
            while ( touch_strength )
            {
                log_printf( &logger, "|" );
                touch_strength--;
            }
            log_printf( &logger, "\r\n_________________\r\n" );
            Delay_ms ( 100 );
        }
    }
    Delay_ms ( 1000 );
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
