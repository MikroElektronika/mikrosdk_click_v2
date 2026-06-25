
---
# Flash 15 Click

> [Flash 15 Click](https://www.mikroe.com/?pid_product=MIKROE-6955) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6955&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the Flash 15 Click board for basic
flash memory operations. The application disables memory protection,
erases a memory page, writes text data to the selected page and column,
and then reads the written data back from memory.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash15

### Example Key Functions

- `flash15_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void flash15_cfg_setup ( flash15_cfg_t *cfg );
```

- `flash15_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t flash15_init ( flash15_t *ctx, flash15_cfg_t *cfg );
```

- `flash15_memory_write` This function writes a desired number of data bytes starting from the selected memory page and column.
```c
err_t flash15_memory_write ( flash15_t *ctx, uint16_t page, uint16_t column, uint8_t *data_in, uint16_t len );
```

- `flash15_memory_read` This function reads a desired number of data bytes starting from the selected memory page and column.
```c
err_t flash15_memory_read ( flash15_t *ctx, uint16_t page, uint16_t column, uint8_t *data_out, uint16_t len );
```

- `flash15_erase_memory` This function erases the memory block which contains the selected page address.
```c
err_t flash15_erase_memory ( flash15_t *ctx, uint16_t page );
```

### Application Init

> Initializes the logger and Flash 15 Click driver, checks device communication, and disables memory protection.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    flash15_cfg_t flash15_cfg;  /**< Click config object. */

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
    flash15_cfg_setup( &flash15_cfg );
    FLASH15_MAP_MIKROBUS( flash15_cfg, MIKROBUS_POSITION_FLASH15 );
    if ( SPI_MASTER_ERROR == flash15_init( &flash15, &flash15_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FLASH15_ERROR == flash15_check_communication ( &flash15 ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }

    log_printf ( &logger, " Disable memory protection\r\n" );
    flash15_set_feature ( &flash15, FLASH15_REG_PROTECTION, FLASH15_PROTECTION_NONE );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Erases the selected memory page, writes demo text messages to flash memory, and reads the stored data back for verification.

```c
void application_task ( void )
{
    uint8_t data_buf[ 64 ] = { 0 };

    log_printf ( &logger, " Memory page: 0x%.4X, column: 0x%.4X\r\n", START_PAGE, START_COLUMN );
    if ( FLASH15_OK == flash15_erase_memory ( &flash15, START_PAGE ) )
    {
        log_printf ( &logger, " Erase memory page\r\n" );
    }
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    if ( FLASH15_OK == flash15_memory_write ( &flash15, START_PAGE, START_COLUMN, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( FLASH15_OK == flash15_memory_read ( &flash15, START_PAGE, START_COLUMN, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms ( 1000 );
    }

    log_printf ( &logger, " Memory page: 0x%.4X, column: 0x%.4X\r\n", START_PAGE, START_COLUMN );
    if ( FLASH15_OK == flash15_erase_memory ( &flash15, START_PAGE ) )
    {
        log_printf ( &logger, " Erase memory page\r\n" );
    }
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    if ( FLASH15_OK == flash15_memory_write ( &flash15, START_PAGE, START_COLUMN, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( FLASH15_OK == flash15_memory_read ( &flash15, START_PAGE, START_COLUMN, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
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
