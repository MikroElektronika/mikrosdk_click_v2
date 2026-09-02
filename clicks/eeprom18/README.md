
---
# EEPROM 18 Click

> [EEPROM 18 Click](https://www.mikroe.com/?pid_product=MIKROE-7052) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7052&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jun 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of EEPROM 18 Click board by writing specified data to
the memory and reading it back.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM18

### Example Key Functions

- `eeprom18_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void eeprom18_cfg_setup ( eeprom18_cfg_t *cfg );
```

- `eeprom18_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t eeprom18_init ( eeprom18_t *ctx, eeprom18_cfg_t *cfg );
```

- `eeprom18_write_memory` This function writes a desired number of data bytes to the EEPROM memory starting from the selected address.
```c
err_t eeprom18_write_memory ( eeprom18_t *ctx, uint32_t address, uint8_t *data_in, uint16_t len );
```

- `eeprom18_read_memory` This function reads a desired number of data bytes from the EEPROM memory starting from the selected address.
```c
err_t eeprom18_read_memory ( eeprom18_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len );
```

- `eeprom18_write_status` This function writes a byte to the status register.
```c
err_t eeprom18_write_status ( eeprom18_t *ctx, uint8_t status );
```

- `eeprom18_read_status` This function reads the status register byte.
```c
err_t eeprom18_read_status ( eeprom18_t *ctx, uint8_t *status );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom18_cfg_t eeprom18_cfg;  /**< Click config object. */

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
    eeprom18_cfg_setup( &eeprom18_cfg );
    EEPROM18_MAP_MIKROBUS( eeprom18_cfg, MIKROBUS_POSITION_EEPROM18 );
    if ( SPI_MASTER_ERROR == eeprom18_init( &eeprom18, &eeprom18_cfg ) )
    {
        log_error( &logger, " Communication init." );
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
    uint8_t data_buf[ EEPROM18_PAGE_SIZE ] = { 0 };

    log_printf( &logger, "\r\n Memory address: 0x%.5lX\r\n", ( uint32_t ) STARTING_ADDRESS );

    /* Write first DEMO message */
    if ( strlen ( DEMO_TEXT_MESSAGE_1 ) > EEPROM18_PAGE_SIZE )
    {
        memcpy( data_buf, DEMO_TEXT_MESSAGE_1, EEPROM18_PAGE_SIZE );
    }
    else
    {
        memcpy( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    }
    if ( EEPROM18_OK == eeprom18_write_memory( &eeprom18, STARTING_ADDRESS, data_buf, strlen ( DEMO_TEXT_MESSAGE_1 ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );
    
    /* Read first DEMO message */
    memset( data_buf, 0, sizeof ( data_buf ) );
    if ( EEPROM18_OK == eeprom18_read_memory( &eeprom18, STARTING_ADDRESS, data_buf, strlen ( DEMO_TEXT_MESSAGE_1 ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
    }
    Delay_ms ( 1000 );
    
    /* Write second DEMO message */
    if ( strlen ( DEMO_TEXT_MESSAGE_2 ) > EEPROM18_PAGE_SIZE )
    {
        memcpy( data_buf, DEMO_TEXT_MESSAGE_2, EEPROM18_PAGE_SIZE );
    }
    else
    {
        memcpy( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    }
    if ( EEPROM18_OK == eeprom18_write_memory( &eeprom18, STARTING_ADDRESS, data_buf, strlen ( DEMO_TEXT_MESSAGE_2 ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );
    
    /* Read second DEMO message */
    memset( data_buf, 0, sizeof ( data_buf ) );
    if ( EEPROM18_OK == eeprom18_read_memory( &eeprom18, STARTING_ADDRESS, data_buf, strlen ( DEMO_TEXT_MESSAGE_2 ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
    }
    
    Delay_ms ( 1000 );    
}
```

### Note

> The identification page cannot be written once it has been
permanently locked with eeprom18_lock_id_page().

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
