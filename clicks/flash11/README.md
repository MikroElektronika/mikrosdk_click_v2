
---
# Flash 11 Click

> [Flash 11 Click](https://www.mikroe.com/?pid_product=MIKROE-5740) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5740&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Flash 11 Click board 
> The demo app writes specified data to the memory and reads it back.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash11

### Example Key Functions

- `flash11_cfg_setup` Config Object Initialization function.
```c
void flash11_cfg_setup ( flash11_cfg_t *cfg );
```

- `flash11_init` Initialization function.
```c
err_t flash11_init ( flash11_t *ctx, flash11_cfg_t *cfg );
```

- `flash11_default_cfg` Click Default Configuration function.
```c
err_t flash11_default_cfg ( flash11_t *ctx );
```

- `flash11_memory_write` Flash 11 memory write function.
```c
err_t flash11_memory_write ( flash11_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint32_t len );
```

- `flash11_memory_read` Flash 11 memory read function.
```c
err_t flash11_memory_read ( flash11_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint32_t len );
```

- `flash11_block_erase` Flash 11 block erase function.
```c
err_t flash11_block_erase ( flash11_t *ctx, uint8_t cmd_block_erase, uint32_t mem_addr );
```

### Application Init

> The initialization of SPI module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    flash11_cfg_t flash11_cfg;  /**< Click config object. */

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
    flash11_cfg_setup( &flash11_cfg );
    FLASH11_MAP_MIKROBUS( flash11_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == flash11_init( &flash11, &flash11_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FLASH11_ERROR == flash11_default_cfg ( &flash11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Flash 11 Click board&trade;.
> The demo application writes a desired number of bytes to the memory 
> and then verifies if it is written correctly
> by reading from the same memory location and displaying the memory content.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };
    log_printf( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS_1 );
    if ( FLASH11_OK == flash11_block_erase( &flash11, FLASH11_CMD_BLOCK_ERASE_4KB, STARTING_ADDRESS_1 ) )
    {
        log_printf( &logger, " Erase memory block (4KB)\r\n" );
    }
    
    memcpy( data_buf, DEMO_TEXT_MESSAGE_1, strlen( DEMO_TEXT_MESSAGE_1 ) );
    if ( FLASH11_OK == flash11_memory_write( &flash11, STARTING_ADDRESS_1, data_buf, sizeof( data_buf ) ) )
    {
       log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    
    memset( data_buf, 0, sizeof( data_buf ) );
    if ( FLASH11_OK == flash11_memory_read( &flash11, STARTING_ADDRESS_1, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    log_printf( &logger, " ----------------------------\r\n" );
    
    log_printf( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS_2 );
    if ( FLASH11_OK == flash11_block_erase( &flash11, FLASH11_CMD_BLOCK_ERASE_4KB, STARTING_ADDRESS_2 ) )
    {
        log_printf( &logger, " Erase memory block (4KB)\r\n" );
    }
    memcpy( data_buf, DEMO_TEXT_MESSAGE_2, strlen( DEMO_TEXT_MESSAGE_2 ) );
    if ( FLASH11_OK == flash11_memory_write( &flash11, STARTING_ADDRESS_2, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    
    memset( data_buf, 0, sizeof( data_buf ) );
    if ( FLASH11_OK == flash11_memory_read( &flash11, STARTING_ADDRESS_2, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    log_printf ( &logger, " ----------------------------\r\n" );
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
