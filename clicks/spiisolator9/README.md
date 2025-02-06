
---
# SPI Isolator 9 Click

> [SPI Isolator 9 Click](https://www.mikroe.com/?pid_product=MIKROE-6430) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6430&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2024.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of SPI Isolator 9 Click board by reading the device ID of the connected Accel 22 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SPIIsolator9

### Example Key Functions

- `spiisolator9_cfg_setup` Config Object Initialization function.
```c
void spiisolator9_cfg_setup ( spiisolator9_cfg_t *cfg );
```

- `spiisolator9_init` Initialization function.
```c
err_t spiisolator9_init ( spiisolator9_t *ctx, spiisolator9_cfg_t *cfg );
```

- `spiisolator9_write` This function writes a desired number of data bytes by using SPI serial interface.
```c
err_t spiisolator9_write ( spiisolator9_t *ctx, uint8_t *data_in, uint8_t len );
```

- `spiisolator9_read` This function reads a desired number of data bytes by using SPI serial interface.
```c
err_t spiisolator9_read ( spiisolator9_t *ctx, uint8_t *data_out, uint8_t len );
```

- `spiisolator9_write_then_read` This function writes and then reads a desired number of data bytes by using SPI serial interface.
```c
err_t spiisolator9_write_then_read ( spiisolator9_t *ctx, uint8_t *data_in, uint8_t in_len, 
                                                          uint8_t *data_out, uint8_t out_len );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    spiisolator9_cfg_t spiisolator9_cfg;  /**< Click config object. */

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
    spiisolator9_cfg_setup( &spiisolator9_cfg );
    SPIISOLATOR9_MAP_MIKROBUS( spiisolator9_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == spiisolator9_init( &spiisolator9, &spiisolator9_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and checks the device ID of the connected Accel 22 Click board, and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    spiisolator9_get_accel22_id ( &spiisolator9 );
    Delay_ms( 1000 );
}
```

### Note

> Make sure to provide a VCC power supply on the VOUT side.

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
