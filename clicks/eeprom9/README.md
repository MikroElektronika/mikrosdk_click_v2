
---
# EEPROM 9 Click

> [EEPROM 9 Click](https://www.mikroe.com/?pid_product=MIKROE-5681) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5681&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Mar 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the EEPROM 9 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM9

### Example Key Functions

- `eeprom9_cfg_setup` Config Object Initialization function.
```c
void eeprom9_cfg_setup ( eeprom9_cfg_t *cfg );
```

- `eeprom9_init` Initialization function.
```c
err_t eeprom9_init ( eeprom9_t *ctx, eeprom9_cfg_t *cfg );
```

- `eeprom9_set_write_enable` EEPROM 9 enable write function.
```c
err_t eeprom9_set_write_enable ( eeprom9_t *ctx, uint8_t en_write );
```

- `eeprom9_read_memory` EPROM 9 memory reading function.
```c
err_t eeprom9_read_memory ( eeprom9_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint8_t len );
```

- `eeprom9_block_erase` EEPROM 9 memory block erase function.
```c
err_t eeprom9_block_erase ( eeprom9_t *ctx, uint32_t block_addr );
```

### Application Init

> Initializes the driver and USB UART logging, disables hold and write protection.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom9_cfg_t eeprom9_cfg;  /**< Click config object. */
    id_data_t id_data;
    
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
    eeprom9_cfg_setup( &eeprom9_cfg );
    EEPROM9_MAP_MIKROBUS( eeprom9_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == eeprom9_init( &eeprom9, &eeprom9_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    eeprom9_read_identification( &eeprom9, &id_data );
    if ( EEPROM9_ST_MANUFACTURER_CODE != id_data.manufact_code )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    log_printf( &logger, " Manufacturer code: 0x%.2X \r\n", ( uint16_t ) id_data.manufact_code ); 
    
    log_printf( &logger, " Disabling Hold \r\n" );
    eeprom9_set_hold( &eeprom9, EEPROM9_HOLD_DISABLE );
    Delay_ms ( 100 );
    
    log_printf( &logger, " Disabling Write Protection \r\n" );
    eeprom9_set_write_protection( &eeprom9, EEPROM9_WRITE_PROTECT_DISABLE );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
}
```

### Application Task

> Writes a desired number of data bytes to the EEPROM 9 memory into a specified address, 
 and verifies that it is written correctly by reading from the same memory location.

```c
void application_task ( void )
{
    char rx_data[ 9 ] = { 0 };
    
    eeprom9_set_write_enable( &eeprom9, EEPROM9_WRITE_ENABLE );
    Delay_ms ( 10 );
    
    eeprom9_write_memory( &eeprom9, MEMORY_ADDRESS, demo_data, 9 );
    log_printf( &logger, " Write data: %s", demo_data );
    Delay_ms ( 100 );
    
    eeprom9_read_memory( &eeprom9, MEMORY_ADDRESS, rx_data, 9 );
    log_printf( &logger, " Read data: %s", rx_data );  
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
    
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
