
---
# EEPROM 11 Click

> [EEPROM 11 Click](https://www.mikroe.com/?pid_product=MIKROE-5889) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5889&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This is an example that demonstrates the use of the EEPROM 11 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM11

### Example Key Functions

- `eeprom11_cfg_setup` Config Object Initialization function.
```c
void eeprom11_cfg_setup ( eeprom11_cfg_t *cfg );
```

- `eeprom11_init` Initialization function.
```c
err_t eeprom11_init ( eeprom11_t *ctx, eeprom11_cfg_t *cfg );
```

- `eeprom11_default_cfg` Click Default Configuration function.
```c
err_t eeprom11_default_cfg ( eeprom11_t *ctx );
```

- `eeprom11_page_write` EEPROM 11 page write function.
```c
err_t eeprom11_page_write ( eeprom11_t *ctx, uint8_t address, uint8_t *data_in );
```

- `eeprom11_clear_page` EEPROM 11 page clear function.
```c
err_t eeprom11_clear_page ( eeprom11_t *ctx, uint8_t address );
```

- `eeprom11_set_page_addr` EEPROM 11 set page address function.
```c
err_t eeprom11_set_page_addr ( eeprom11_t *ctx, uint8_t page_addr );
```

### Application Init

> Initializes the driver and USB UART logging, disables write protection.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom11_cfg_t eeprom11_cfg;  /**< Click config object. */

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
    eeprom11_cfg_setup( &eeprom11_cfg );
    EEPROM11_MAP_MIKROBUS( eeprom11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == eeprom11_init( &eeprom11, &eeprom11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EEPROM11_ERROR == eeprom11_default_cfg ( &eeprom11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Writes a desired number of data bytes to the EEPROM 11 memory into a specified address, 
  and verifies that it is written correctly by reading from the same memory location.

```c
void application_task ( void ) 
{
    err_t error_flag = EEPROM11_OK;
    uint8_t rx_data[ 16 ] = { 0 };
    uint8_t tx_data[ 16 ] = TX_DATA;
    
    eeprom11_clear_page( &eeprom11, MEMORY_ADDRESS );
    Delay_ms ( 1000 );
    error_flag = eeprom11_page_write( &eeprom11, MEMORY_ADDRESS, tx_data );
    if ( EEPROM11_OK == error_flag )
    {
        log_printf( &logger, " Write data: %s \r\n", tx_data );
    }
    else
    {
        log_error( &logger, " Write operation failed!!! " );
    }
    Delay_ms ( 1000 );
    
    error_flag = eeprom11_generic_read( &eeprom11, MEMORY_ADDRESS, rx_data, 15 );
    if ( EEPROM11_OK == error_flag )
    {
        log_printf( &logger, "Read data: %s \r\n", rx_data );
    }
    else
    {
        log_error( &logger, " Write operation failed!!! " );
    }
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
    
    Delay_ms ( 1000 );
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
