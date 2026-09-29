
---
# SPI Isolator 10 Click

> [SPI Isolator 10 Click](https://www.mikroe.com/?pid_product=MIKROE-7028) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7028&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jun 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of SPI Isolator 10 Click board by reading the
device ID of the connected Accel 22 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SPIIsolator10

### Example Key Functions

- `spiisolator10_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void spiisolator10_cfg_setup ( spiisolator10_cfg_t *cfg );
```

- `spiisolator10_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t spiisolator10_init ( spiisolator10_t *ctx, spiisolator10_cfg_t *cfg );
```

- `spiisolator10_write` This function writes a desired number of data bytes by using SPI serial interface.
```c
err_t spiisolator10_write ( spiisolator10_t *ctx, uint8_t *data_in, uint8_t len );
```

- `spiisolator10_read` This function reads a desired number of data bytes by using SPI serial interface.
```c
err_t spiisolator10_read ( spiisolator10_t *ctx, uint8_t *data_out, uint8_t len );
```

- `spiisolator10_write_then_read` This function writes and then reads a desired number of data bytes by using SPI serial interface.
```c
err_t spiisolator10_write_then_read ( spiisolator10_t *ctx, uint8_t *data_in, uint8_t in_len, uint8_t *data_out, uint8_t out_len );
```

- `spiisolator10_set_en_pin` This function sets the EN pin to the selected logic level.
```c
void spiisolator10_set_en_pin ( spiisolator10_t *ctx, uint8_t state );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    spiisolator10_cfg_t spiisolator10_cfg;  /**< Click config object. */

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
    spiisolator10_cfg_setup( &spiisolator10_cfg );
    SPIISOLATOR10_MAP_MIKROBUS( spiisolator10_cfg, MIKROBUS_POSITION_SPIISOLATOR10 );
    if ( SPI_MASTER_ERROR == spiisolator10_init( &spiisolator10, &spiisolator10_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and checks the device ID of the connected Accel 22 Click board, and displays the
results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    spiisolator10_get_accel22_id ( &spiisolator10 );
    Delay_ms( 1000 );
}
```

### Note

> Make sure to provide a VCC power supply on the B side.

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
