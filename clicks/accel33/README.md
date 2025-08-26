
---
# Accel 33 Click

> [Accel 33 Click](https://www.mikroe.com/?pid_product=MIKROE-6629) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6629&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2025.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of the Accel 33 Click board by periodically reading
acceleration data from all three axes (X, Y, Z) and displaying the results on the UART terminal.
It waits for the data ready interrupt before reading new data to ensure synchronization.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel33

### Example Key Functions

- `accel33_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void accel33_cfg_setup ( accel33_cfg_t *cfg );
```

- `accel33_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t accel33_init ( accel33_t *ctx, accel33_cfg_t *cfg );
```

- `accel33_default_cfg` This function executes a default configuration of Accel 33 Click board.
```c
err_t accel33_default_cfg ( accel33_t *ctx );
```

- `accel33_get_int2_pin` This function returns the logic state of the INT2 pin.
```c
uint8_t accel33_get_int2_pin ( accel33_t *ctx );
```

- `accel33_set_odr` This function sets the accelerometer's output data rate.
```c
err_t accel33_set_odr ( accel33_t *ctx, uint8_t odr );
```

- `accel33_get_accel` This function reads and converts the raw acceleration data for all three axes.
```c
err_t accel33_get_accel ( accel33_t *ctx, accel33_axes_t *accel );
```

### Application Init

> Initializes the logger and the Accel 33 Click driver, then sets up the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel33_cfg_t accel33_cfg;  /**< Click config object. */

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
    accel33_cfg_setup( &accel33_cfg );
    ACCEL33_MAP_MIKROBUS( accel33_cfg, MIKROBUS_1 );
    err_t init_flag = accel33_init( &accel33, &accel33_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL33_ERROR == accel33_default_cfg ( &accel33 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt and reads acceleration values for the X, Y, and Z axes,
then displays the values in g units via the UART terminal. The INT2 pin is used to signal
when new data is ready to be read from the sensor.

```c
void application_task ( void )
{
    accel33_axes_t accel;
    // Wait for data ready interrupt
    while ( accel33_get_int2_pin ( &accel33 ) );

    if ( ACCEL33_OK == accel33_get_accel ( &accel33, &accel ) )
    {
        log_printf( &logger, " Accel X: %.3f g\r\n", accel.x );
        log_printf( &logger, " Accel Y: %.3f g\r\n", accel.y );
        log_printf( &logger, " Accel Z: %.3f g\r\n\n", accel.z );
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
