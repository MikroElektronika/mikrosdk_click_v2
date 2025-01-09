
---
# SPI Isolator 5 Click

> [SPI Isolator 5 Click](https://www.mikroe.com/?pid_product=MIKROE-5179) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5179&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of SPI Isolator 5 Click board 
> by reading the manufacturer ID and device ID 
> of the connected Flash 11 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SPIIsolator5

### Example Key Functions

- `spiisolator5_cfg_setup` Config Object Initialization function.
```c
void spiisolator5_cfg_setup ( spiisolator5_cfg_t *cfg );
```

- `spiisolator5_init` Initialization function.
```c
err_t spiisolator5_init ( spiisolator5_t *ctx, spiisolator5_cfg_t *cfg );
```

- `spiisolator5_write` SPI Isolator 5 data writing function.
```c
err_t spiisolator5_write ( spiisolator5_t *ctx, uint8_t *data_in, uint8_t len ) 
```

- `spiisolator5_read` SPI Isolator 5 data reading function.
```c
err_t spiisolator5_read ( spiisolator5_t *ctx, uint8_t *data_out, uint8_t len_out ) 
```

- `spiisolator5_transfer` SPI Isolator 5 transfer function.
```c
err_t spiisolator5_transfer ( spiisolator5_t *ctx, uint8_t *data_in, uint8_t *data_out, uint8_t len )
```

### Application Init

> The initialization of SPI module, log UART, and additional pins.
> After the driver init, the app performs enabling a device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    spiisolator5_cfg_t spiisolator5_cfg;  /**< Click config object. */

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
    spiisolator5_cfg_setup( &spiisolator5_cfg );
    SPIISOLATOR5_MAP_MIKROBUS( spiisolator5_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == spiisolator5_init( &spiisolator5, &spiisolator5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    spiisolator5_enable( &spiisolator5 );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -----------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads and checks the manufacturer ID and 
> device ID of the connected Flash 11 Click board. 
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static uint8_t cmd_get_id[ 6 ] = { FLASH11_CMD_GET_ID };
    static uint8_t read_id[ 6 ] = { 0 };
    if ( SPIISOLATOR5_OK == spiisolator5_transfer( &spiisolator5, &cmd_get_id[ 0 ], &read_id[ 0 ], 6 ) )
    {
        if ( ( FLASH11_MANUFACTURER_ID == read_id[ 4 ] ) && ( FLASH11_DEVICE_ID == read_id[ 5 ] ) )
        {
            log_printf( &logger, " Manufacturer ID: 0x%.2X\r\n", ( uint16_t ) read_id[ 4 ] );
            log_printf( &logger, " Device ID: 0x%.2X    \r\n", ( uint16_t ) read_id[ 5 ] );
            log_printf( &logger, " -----------------------\r\n" );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
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
