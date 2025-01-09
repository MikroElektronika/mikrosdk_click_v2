
---
# EEPROM 10 Click

> [EEPROM 10 Click](https://www.mikroe.com/?pid_product=MIKROE-5735) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5735&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of EEPROM 10 Click board by writing specified data to
  the memory and reading it back.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM10

### Example Key Functions

- `eeprom10_cfg_setup` Config Object Initialization function.
```c
void eeprom10_cfg_setup ( eeprom10_cfg_t *cfg );
```

- `eeprom10_init` Initialization function.
```c
err_t eeprom10_init ( eeprom10_t *ctx, eeprom10_cfg_t *cfg );
```

- `eeprom10_write_enable` EEPROM 10 write enable function.
```c
void eeprom10_write_enable( eeprom10_t *ctx );
```

- `eeprom10_write_n_byte` EEPROM 10 write desired number of data function.
```c
err_t eeprom10_write_n_byte ( eeprom10_t *ctx, uint16_t address, uint8_t *data_in, uint8_t len );
```

- `eeprom10_read_n_byte` EEPROM 10 read desired number of data function.
```c
err_t eeprom10_read_n_byte ( eeprom10_t *ctx, uint16_t address, uint8_t *data_out, uint8_t len );
```

### Application Init

> Initializes the driver and USB UART logging.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom10_cfg_t eeprom10_cfg;  /**< Click config object. */

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
    eeprom10_cfg_setup( &eeprom10_cfg );
    EEPROM10_MAP_MIKROBUS( eeprom10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == eeprom10_init( &eeprom10, &eeprom10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    eeprom10_write_enable( &eeprom10 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> In this example, we write and then read data from EEPROM memory.
  Results are being sent to the Usart Terminal where you can track their changes.
  All data logs write on USB UART changes approximately every second.

```c
void application_task ( void ) 
{
    err_t error_flag = EEPROM10_OK;
    
    error_flag = eeprom10_write_n_byte( &eeprom10, EEPROM10_TEST_ADDRESS, tx_data, 14 );
    if ( EEPROM10_OK == error_flag )
    {
        log_printf( &logger, " Write %s data to 0x%.4X address \r\n", tx_data, ( uint16_t ) EEPROM10_TEST_ADDRESS );
    }
    else
    {
        log_error( &logger, " Write operation failed!!! " );
    }
    Delay_ms ( 100 );
    
    error_flag = eeprom10_read_n_byte( &eeprom10, EEPROM10_TEST_ADDRESS, rx_data, 14 );
    if ( EEPROM10_OK == error_flag )
    {
        log_printf( &logger, " Read %s from 0x%.4X address \r\n", rx_data, ( uint16_t ) EEPROM10_TEST_ADDRESS );
    }
    else
    {
        log_error( &logger, " Read operation failed!!! " );
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
