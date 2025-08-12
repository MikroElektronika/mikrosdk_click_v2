
---
# EEPROM 17 Click

> [EEPROM 17 Click](https://www.mikroe.com/?pid_product=MIKROE-6641) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6641&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of EEPROM 17 Click board by writing specified data to the memory and reading it back.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM17

### Example Key Functions

- `eeprom17_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void eeprom17_cfg_setup ( eeprom17_cfg_t *cfg );
```

- `eeprom17_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t eeprom17_init ( eeprom17_t *ctx, eeprom17_cfg_t *cfg );
```

- `eeprom17_write_memory` This function writes data to the EEPROM memory starting from the specified address.
```c
err_t eeprom17_write_memory ( eeprom17_t *ctx, uint8_t address, uint8_t *data_in, uint8_t len );
```

- `eeprom17_read_memory` This function reads data from the EEPROM memory starting from the specified address.
```c
err_t eeprom17_read_memory ( eeprom17_t *ctx, uint8_t address, uint8_t *data_out, uint16_t len );
```

- `eeprom17_select_bank` This function selects the active memory bank in the EEPROM.
```c
err_t eeprom17_select_bank ( eeprom17_t *ctx, uint8_t bank_sel );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom17_cfg_t eeprom17_cfg;  /**< Click config object. */

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
    eeprom17_cfg_setup( &eeprom17_cfg );
    EEPROM17_MAP_MIKROBUS( eeprom17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == eeprom17_init( &eeprom17, &eeprom17_cfg ) )
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
    static uint8_t bank_sel = EEPROM17_BANK_SEL_0; 
    uint8_t data_buf[ EEPROM17_MEM_PAGE_SIZE + 1 ] = { 0 };

    // Selecting memory bank
    eeprom17_select_bank ( &eeprom17, bank_sel );
    log_printf ( &logger, "\r\n Memory bank: %u\r\n", ( uint16_t ) bank_sel );
    log_printf ( &logger, " Memory address: 0x%.2X\r\n", ( uint16_t ) STARTING_ADDRESS );
    bank_sel ^= EEPROM17_BANK_SEL_1;

    // Write/Read first iterration
    if ( strlen ( DEMO_TEXT_MESSAGE_1 ) > EEPROM17_MEM_PAGE_SIZE )
    {
        memcpy ( data_buf, DEMO_TEXT_MESSAGE_1, EEPROM17_MEM_PAGE_SIZE );
    }
    else
    {
        memcpy ( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    }
    if ( EEPROM17_OK == eeprom17_write_memory ( &eeprom17, STARTING_ADDRESS, data_buf, EEPROM17_MEM_PAGE_SIZE ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( EEPROM17_OK == eeprom17_read_memory ( &eeprom17, STARTING_ADDRESS, data_buf, EEPROM17_MEM_PAGE_SIZE ) )
    {
        log_printf ( &logger, " Read data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );
    
    // Write/Read second iterration
    if ( strlen ( DEMO_TEXT_MESSAGE_2 ) > EEPROM17_MEM_PAGE_SIZE )
    {
        memcpy ( data_buf, DEMO_TEXT_MESSAGE_2, EEPROM17_MEM_PAGE_SIZE );
    }
    else
    {
        memcpy ( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    }
    if ( EEPROM17_OK == eeprom17_write_memory ( &eeprom17, STARTING_ADDRESS, data_buf, EEPROM17_MEM_PAGE_SIZE ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( EEPROM17_OK == eeprom17_read_memory ( &eeprom17, STARTING_ADDRESS, data_buf, EEPROM17_MEM_PAGE_SIZE ) )
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
