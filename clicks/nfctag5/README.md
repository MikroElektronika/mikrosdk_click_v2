\mainpage Main Page

---
# NFC Tag 5 Click

> NFC Tag 5 Click is a compact add-on board that contains a compact NFC tag IC. This board features the M24LR64E-R, a dynamic NFC/RFID tag IC with a dual interface 64-Kbit EEPROM from STMicroelectronics. It features an I2C interface alongside an RF contactless interface operating at 13.56MHz, organized as 8192×8 bits in the I2C mode and 2048×32 bits in the ISO 15693 and ISO 18000-3 mode 1 RF mode. The M24LR64E-R also features an energy harvesting analog output and a user-configurable digital output pin, used as an interrupt, toggling during either RF write in progress or RF busy mode.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nfctag5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/nfc-tag-5-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the NFC Tag 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for NFC Tag 5 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of NFC Tag 5 Click board by programming the specified NDEF URI record to the memory, and showing the memory read/write feature.

**The demo application is composed of two sections :**

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

## Note

> Trying to write/read in RF mode (for example, processing NDEF URI record with a smartphone) while writing to memory over I2C is in progress can interrupt and block the I2C communication. 

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.NFCTag5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
