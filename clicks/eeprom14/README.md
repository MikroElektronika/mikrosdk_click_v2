
---
# EEPROM 14 Click

> [EEPROM 14 Click](https://www.mikroe.com/?pid_product=MIKROE-6782) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6782&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates basic read and write operations on the EEPROM 14 Click.
The application writes predefined text messages into memory, then reads them back
and logs the results for verification.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM14

### Example Key Functions

- `eeprom14_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void eeprom14_cfg_setup ( eeprom14_cfg_t *cfg );
```

- `eeprom14_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t eeprom14_init ( eeprom14_t *ctx, eeprom14_cfg_t *cfg );
```

- `eeprom14_write_memory` This function writes a sequence of bytes to the device memory over I2C, starting at the selected 16-bit address.
```c
err_t eeprom14_write_memory ( eeprom14_t *ctx, uint16_t address, uint8_t *data_in, uint8_t len );
```

- `eeprom14_read_memory` This function reads a sequence of bytes from the device memory over I2C, starting at the selected 16-bit address.
```c
err_t eeprom14_read_memory ( eeprom14_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len );
```

### Application Init

> Initializes the logger, configures and initializes the EEPROM 14 Click.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom14_cfg_t eeprom14_cfg;  /**< Click config object. */

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
    eeprom14_cfg_setup( &eeprom14_cfg );
    EEPROM14_MAP_MIKROBUS( eeprom14_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == eeprom14_init( &eeprom14, &eeprom14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Writes and reads text messages from EEPROM memory, displaying the stored values via the UART logger.

```c
void application_task ( void )
{
    uint8_t data_buf[ EEPROM14_MEM_PAGE_SIZE + 1 ] = { 0 };

    log_printf ( &logger, " Memory address: 0x%.4X\r\n", STARTING_ADDRESS );
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    if ( EEPROM14_OK == eeprom14_write_memory ( &eeprom14, STARTING_ADDRESS, data_buf, EEPROM14_MEM_PAGE_SIZE ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( EEPROM14_OK == eeprom14_read_memory ( &eeprom14, STARTING_ADDRESS, data_buf, EEPROM14_MEM_PAGE_SIZE ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
    }
    Delay_ms ( 1000 );
    
    log_printf ( &logger, " Memory address: 0x%.4X\r\n", STARTING_ADDRESS );
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    if ( EEPROM14_OK == eeprom14_write_memory ( &eeprom14, STARTING_ADDRESS, data_buf, EEPROM14_MEM_PAGE_SIZE ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( EEPROM14_OK == eeprom14_read_memory ( &eeprom14, STARTING_ADDRESS, data_buf, EEPROM14_MEM_PAGE_SIZE ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
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
