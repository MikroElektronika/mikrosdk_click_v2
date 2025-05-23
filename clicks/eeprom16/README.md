
---
# EEPROM 16 Click

> [EEPROM 16 Click](https://www.mikroe.com/?pid_product=MIKROE-6591) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6591&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2025.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of EEPROM 16 Click board by writing specified data to the memory and reading it back.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM16

### Example Key Functions

- `eeprom16_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void eeprom16_cfg_setup ( eeprom16_cfg_t *cfg );
```

- `eeprom16_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t eeprom16_init ( eeprom16_t *ctx, eeprom16_cfg_t *cfg );
```

- `eeprom16_default_cfg` This function executes a default configuration of EEPROM 16 Click board.
```c
err_t eeprom16_default_cfg ( eeprom16_t *ctx );
```

- `eeprom16_memory_write` This function writes a desired number of data bytes starting from the selected memory address.
```c
err_t eeprom16_memory_write ( eeprom16_t *ctx, uint16_t address, uint8_t *data_in, uint8_t len );
```

- `eeprom16_memory_read` This function reads a desired number of data bytes starting from the selected memory address.
```c
err_t eeprom16_memory_read ( eeprom16_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom16_cfg_t eeprom16_cfg;  /**< Click config object. */

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
    eeprom16_cfg_setup( &eeprom16_cfg );
    EEPROM16_MAP_MIKROBUS( eeprom16_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == eeprom16_init( &eeprom16, &eeprom16_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EEPROM16_ERROR == eeprom16_default_cfg ( &eeprom16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Writes a desired number of bytes to the memory and then verifies if it is written correctly
by reading from the same memory location and displaying the memory content on the USB UART.

```c
void application_task ( void )
{
    uint8_t data_buf[ EEPROM16_PAGE_SIZE + 1 ] = { 0 };
    log_printf ( &logger, "\r\n Memory address: 0x%.4X\r\n", ( uint16_t ) STARTING_ADDRESS );
    
    if ( EEPROM16_OK == eeprom16_memory_write ( &eeprom16, STARTING_ADDRESS, 
                                                DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", ( char * ) DEMO_TEXT_MESSAGE_1 );
    }
    if ( EEPROM16_OK == eeprom16_memory_read ( &eeprom16, STARTING_ADDRESS, 
                                               data_buf, strlen ( DEMO_TEXT_MESSAGE_1 ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n", data_buf );
    }

    if ( EEPROM16_OK == eeprom16_memory_write ( &eeprom16, STARTING_ADDRESS, 
                                                DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", ( char * ) DEMO_TEXT_MESSAGE_2 );
    }
    if ( EEPROM16_OK == eeprom16_memory_read ( &eeprom16, STARTING_ADDRESS, 
                                               data_buf, strlen ( DEMO_TEXT_MESSAGE_2 ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n", data_buf );
    }

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
