
---
# Flash 14 Click

> [Flash 14 Click](https://www.mikroe.com/?pid_product=MIKROE-6788) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6788&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2025.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Flash 14 Click board by writing specified data to the memory and reading it back.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash14

### Example Key Functions

- `flash14_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void flash14_cfg_setup ( flash14_cfg_t *cfg );
```

- `flash14_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t flash14_init ( flash14_t *ctx, flash14_cfg_t *cfg );
```

- `flash14_erase_memory` This function erases the selected amount of memory which contains the selected address.
```c
err_t flash14_erase_memory ( flash14_t *ctx, uint8_t erase_cmd, uint32_t address );
```

- `flash14_memory_write` This function writes a desired number of data bytes starting from the selected memory address.
```c
err_t flash14_memory_write ( flash14_t *ctx, uint32_t address, uint8_t *data_in, uint32_t len );
```

- `flash14_memory_read` This function reads a desired number of data bytes starting from the selected memory address.
```c
err_t flash14_memory_read ( flash14_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len );
```

### Application Init

> Initializes the driver and checks the communication by reading and verifying the device ID.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    flash14_cfg_t flash14_cfg;  /**< Click config object. */

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
    flash14_cfg_setup( &flash14_cfg );
    FLASH14_MAP_MIKROBUS( flash14_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == flash14_init( &flash14, &flash14_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FLASH14_ERROR == flash14_check_communication ( &flash14 ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Writes a desired number of bytes to the memory and then verifies if it is written correctly
by reading from the same memory location and displaying the memory content on the USB UART.
The whole 4KB sector of memory that contains the STARTING_ADDRESS will be erased before writing data.

```c
void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };

    log_printf ( &logger, " Memory address: 0x%.8LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    if ( FLASH14_OK == flash14_erase_memory ( &flash14, FLASH14_CMD_4B_SECTOR_ERASE_4KB, STARTING_ADDRESS ) )
    {
        log_printf ( &logger, " Erase memory sector (4KB)\r\n" );
    }
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    if ( FLASH14_OK == flash14_memory_write ( &flash14, STARTING_ADDRESS, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( FLASH14_OK == flash14_memory_read ( &flash14, STARTING_ADDRESS, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms ( 1000 );
    }

    log_printf ( &logger, " Memory address: 0x%.8LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    if ( FLASH14_OK == flash14_erase_memory ( &flash14, FLASH14_CMD_4B_SECTOR_ERASE_4KB, STARTING_ADDRESS ) )
    {
        log_printf ( &logger, " Erase memory sector (4KB)\r\n" );
    }
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    if ( FLASH14_OK == flash14_memory_write ( &flash14, STARTING_ADDRESS, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( FLASH14_OK == flash14_memory_read ( &flash14, STARTING_ADDRESS, data_buf, sizeof ( data_buf ) ) )
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
