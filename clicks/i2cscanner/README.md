
---
# I2C Scanner

> I2C Scanner demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the I2C Scanner application.
It performs a scan of the I2C bus and logs all detected device addresses
over the USB UART interface.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.I2CScanner

### Example Key Functions

- `i2cscanner_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void i2cscanner_cfg_setup ( i2cscanner_cfg_t *cfg );
```

- `i2cscanner_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t i2cscanner_init ( i2cscanner_t *ctx, i2cscanner_cfg_t *cfg );
```

- `i2cscanner_scan_i2c` This function scans the I2C bus for available slave addresses and stores them into the scan structure.
```c
err_t i2cscanner_scan_i2c ( i2cscanner_t *ctx, i2cscanner_scan_t *scan );
```

### Application Init

> Initializes the logger and I2C Scanner driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cscanner_cfg_t i2cscanner_cfg;  /**< Click config object. */

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
    i2cscanner_cfg_setup( &i2cscanner_cfg );
    I2CSCANNER_MAP_MIKROBUS( i2cscanner_cfg, MIKROBUS_1 );
    if ( I2CSCANNER_OK != i2cscanner_init( &i2cscanner, &i2cscanner_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Scans the I2C bus and displays detected device addresses once per second.

```c
void application_task ( void )
{
    i2cscanner_scan_t scan;
    if ( I2CSCANNER_OK == i2cscanner_scan_i2c ( &i2cscanner, &scan ) )
    {
        log_printf ( &logger, "I2C device(s) found [%u]: ", scan.num_addr );
        for ( uint8_t cnt = 0; cnt < scan.num_addr; cnt++ )
        {
            log_printf ( &logger, "0x%.2X", scan.address[ cnt ] );
            if ( ( cnt + 1 ) < scan.num_addr )
            {
                log_printf ( &logger, ", " );
            }
            else
            {
                log_printf ( &logger, "\r\n" );
            }
        }
    }
    else
    {
        log_printf ( &logger, "No I2C devices found!\r\n" );
    }
    log_printf ( &logger, "-----------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

## Application Output

This application can be interfaced and monitored in two ways:
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
