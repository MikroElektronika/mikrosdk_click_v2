
---
# 3D Hall 4 Click

> [3D Hall 4 Click](https://www.mikroe.com/?pid_product=MIKROE-5925) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5925&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of 3D Hall 4 Click board by reading the magnetic field strength from 3 axes and the sensor internal temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.3DHall4

### Example Key Functions

- `c3dhall4_cfg_setup` Config Object Initialization function.
```c
void c3dhall4_cfg_setup ( c3dhall4_cfg_t *cfg );
```

- `c3dhall4_init` Initialization function.
```c
err_t c3dhall4_init ( c3dhall4_t *ctx, c3dhall4_cfg_t *cfg );
```

- `c3dhall4_default_cfg` Click Default Configuration function.
```c
err_t c3dhall4_default_cfg ( c3dhall4_t *ctx );
```

- `c3dhall4_read_data` This function reads the measurement status, 3-axes magnetic field data, and the chip internal temperature.
```c
err_t c3dhall4_read_data ( c3dhall4_t *ctx, c3dhall4_data_t *data_out );
```

- `c3dhall4_reg_write` This function writes a desired number of data bytes starting from the selected register by using SPI serial interface.
```c
err_t c3dhall4_reg_write ( c3dhall4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );
```

- `c3dhall4_reg_read` This function reads a desired number of data bytes starting from the selected register by using SPI serial interface.
```c
err_t c3dhall4_reg_read ( c3dhall4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall4_cfg_t c3dhall4_cfg;  /**< Click config object. */

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
    c3dhall4_cfg_setup( &c3dhall4_cfg );
    C3DHALL4_MAP_MIKROBUS( c3dhall4_cfg, MIKROBUS_1 );
    if ( C3DHALL4_OK != c3dhall4_init( &c3dhall4, &c3dhall4_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C3DHALL4_OK != c3dhall4_default_cfg ( &c3dhall4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads data from the sensor and displays them on the USB UART once per second.

```c
void application_task ( void )
{
    c3dhall4_data_t data_res;
    if ( C3DHALL4_OK == c3dhall4_read_data ( &c3dhall4, &data_res ) )
    {
        log_printf( &logger, " Status: 0x%.2X\r\n", data_res.status );
        log_printf( &logger, " X data: %.1f mT\r\n", data_res.x_data );
        log_printf( &logger, " Y data: %.1f mT\r\n", data_res.y_data );
        log_printf( &logger, " Z data: %.1f mT\r\n", data_res.z_data );
        log_printf( &logger, " Chip temperature: %.2f degC\r\n\n", data_res.chip_temp );
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
