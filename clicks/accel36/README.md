
---
# Accel 36 Click

> [Accel 36 Click](https://www.mikroe.com/?pid_product=MIKROE-6950) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6950&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Apr 2026.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Accel 36 Click board by reading and
displaying the accelerometer data (X, Y, and Z axis).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel36

### Example Key Functions

- `accel36_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void accel36_cfg_setup ( accel36_cfg_t *cfg );
```

- `accel36_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t accel36_init ( accel36_t *ctx, accel36_cfg_t *cfg );
```

- `accel36_default_cfg` This function executes a default configuration of Accel 36 Click board.
```c
err_t accel36_default_cfg ( accel36_t *ctx );
```

- `accel36_set_fsr` This function sets FSR by modifying bits[6:4] of Range and Resolution Control Register.
```c
err_t accel36_set_fsr ( accel36_t *ctx, uint8_t fsr );
```

- `accel36_set_odr` This function sets the ODR by modifying bits[3:0] of Rate register 1.
```c
err_t accel36_set_odr ( accel36_t *ctx, uint8_t odr );
```

- `accel36_get_accel` This function reads and converts the X, Y, Z acceleration data.
```c
err_t accel36_get_accel ( accel36_t *ctx, accel36_axes_t *accel );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel36_cfg_t accel36_cfg;  /**< Click config object. */

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
    accel36_cfg_setup( &accel36_cfg );
    ACCEL36_MAP_MIKROBUS( accel36_cfg, MIKROBUS_POSITION_ACCEL36 );
    err_t init_flag = accel36_init( &accel36, &accel36_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( ACCEL36_ERROR == accel36_default_cfg ( &accel36 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the accelerometer measurements.
The results are displayed on the USB UART every 100 ms.

```c
void application_task ( void )
{
    accel36_axes_t axes;

    if ( ACCEL36_OK == accel36_get_accel( &accel36, &axes ) )
    {
        log_printf( &logger, " X: %.3f g\r\n", axes.x );
        log_printf( &logger, " Y: %.3f g\r\n", axes.y );
        log_printf( &logger, " Z: %.3f g\r\n", axes.z );
        log_printf( &logger, " ---------------------------------\r\n" );
    }

    Delay_ms( 100 );
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
