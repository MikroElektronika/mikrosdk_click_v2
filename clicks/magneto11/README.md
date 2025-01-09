
---
# Magneto 11 Click

> [Magneto 11 Click](https://www.mikroe.com/?pid_product=MIKROE-5067) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5067&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Magneto 11 Click board by reading and displaying the magnetic field strength value.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto11

### Example Key Functions

- `magneto11_cfg_setup` Config Object Initialization function.
```c
void magneto11_cfg_setup ( magneto11_cfg_t *cfg );
```

- `magneto11_init` Initialization function.
```c
err_t magneto11_init ( magneto11_t *ctx, magneto11_cfg_t *cfg );
```

- `magneto11_default_cfg` Click Default Configuration function.
```c
err_t magneto11_default_cfg ( magneto11_t *ctx );
```

- `magneto11_get_magnetic_field` This function reads the magnetic field strength in milliTesla.
```c
err_t magneto11_get_magnetic_field ( magneto11_t *ctx, float *mag_field );
```

- `magneto11_set_sensitivity` This function writes specified data to the sensitivity register.
```c
err_t magneto11_set_sensitivity ( magneto11_t *ctx, uint8_t sensitivity );
```

- `magneto11_set_config` This function writes specified data to the config register.
```c
err_t magneto11_set_config ( magneto11_t *ctx, uint8_t config );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneto11_cfg_t magneto11_cfg;  /**< Click config object. */

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
    magneto11_cfg_setup( &magneto11_cfg );
    MAGNETO11_MAP_MIKROBUS( magneto11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == magneto11_init( &magneto11, &magneto11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETO11_ERROR == magneto11_default_cfg ( &magneto11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the magnetic field strength value in milliTesla and displays the results on the USB UART every 200ms approximately.

```c
void application_task ( void )
{
    float magnetic_field;
    if ( MAGNETO11_OK == magneto11_get_magnetic_field ( &magneto11, &magnetic_field ) )
    {
        log_printf ( &logger, " Magnetic Field: %.3f mT \r\n\n", magnetic_field );
        Delay_ms ( 200 );
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
