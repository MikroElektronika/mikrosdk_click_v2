
---
# NFC Tag 5 Click

> [NFC Tag 5 Click](https://www.mikroe.com/?pid_product=MIKROE-5230) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5230&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of NFC Tag 5 Click board by programming the specified NDEF URI record to the memory, and showing the memory read/write feature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NFCTag5

### Example Key Functions

- `nfctag5_cfg_setup` Config Object Initialization function.
```c
void nfctag5_cfg_setup ( nfctag5_cfg_t *cfg );
```

- `nfctag5_init` Initialization function.
```c
err_t nfctag5_init ( nfctag5_t *ctx, nfctag5_cfg_t *cfg );
```

- `nfctag5_default_cfg` Click Default Configuration function.
```c
err_t nfctag5_default_cfg ( nfctag5_t *ctx );
```

- `nfctag5_write_ndef_uri_record` This function writes specific NDEF URI record to the memory address specified with NTAG5LINK_NDEF_MESSAGE_START_ADDRESS macro.
```c
err_t nfctag5_write_ndef_uri_record ( nfctag5_t *ctx, uint8_t uri_prefix, uint8_t *uri_data, uint8_t data_len );
```

- `nfctag5_write_message_to_memory` This function writes specified number of data bytes to the user memory starting from @b block_addr.
```c
err_t nfctag5_write_message_to_memory ( nfctag5_t *ctx, uint16_t block_addr, uint8_t *message, uint16_t message_len );
```

- `nfctag5_read_message_from_memory` This function reads specified number of data bytes from the user memory starting from @b block_addr.
```c
err_t nfctag5_read_message_from_memory ( nfctag5_t *ctx, uint16_t block_addr, uint8_t *message, uint16_t message_len );
```

### Application Init

> Initializes the driver and logger and performs the Click default configuration which formats its user memory. After that it programs the specified NDEF URI record to the memory.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfctag5_cfg_t nfctag5_cfg;  /**< Click config object. */

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
    nfctag5_cfg_setup( &nfctag5_cfg );
    NFCTAG5_MAP_MIKROBUS( nfctag5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == nfctag5_init( &nfctag5, &nfctag5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( NFCTAG5_ERROR == nfctag5_default_cfg ( &nfctag5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    if ( NFCTAG5_OK == nfctag5_write_ndef_uri_record ( &nfctag5, NFCTAG5_URI_PREFIX_4, 
                                                       URI_DATA, strlen ( URI_DATA ) ) )
    {
        log_printf( &logger, " NDEF URI record \"https://%s\" has been written\r\n", ( char * ) URI_DATA );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Writes a desired number of data bytes to the memory and verifies that it is written correctly by reading from the same memory location and displaying the memory content
on the USB UART approximately every 5 seconds.

```c
void application_task ( void )
{
    uint8_t message_buf[ 100 ] = { 0 };
    if ( NFCTAG5_OK == nfctag5_write_message_to_memory ( &nfctag5, 
                                                         TEXT_MESSAGE_ADDRESS, 
                                                         TEXT_MESSAGE, 
                                                         strlen ( TEXT_MESSAGE ) ) )
    {
        log_printf( &logger, " \"%s\" has been written to memory address 0x%.4X \r\n", 
                    ( char * ) TEXT_MESSAGE, ( uint16_t ) TEXT_MESSAGE_ADDRESS );
    }
    if ( NFCTAG5_OK == nfctag5_read_message_from_memory ( &nfctag5,
                                                          TEXT_MESSAGE_ADDRESS, 
                                                          message_buf, 
                                                          strlen ( TEXT_MESSAGE ) ) )
    {
        log_printf( &logger, " \"%s\" has been read from memory address 0x%.4X \r\n\n", 
                    message_buf, ( uint16_t ) TEXT_MESSAGE_ADDRESS );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Trying to write/read in RF mode (for example, processing NDEF URI record with a smartphone) while writing to memory over I2C is in progress can interrupt and block the I2C communication. 

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
