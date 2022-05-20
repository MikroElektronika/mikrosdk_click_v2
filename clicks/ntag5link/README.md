\mainpage Main Page

---
# NTAG 5 Link click

> NTAG 5 Link Click is a compact add-on board that acts as a bridge between an NFC-enabled device and any I2C slave, such as a sensor or external memory. This board features the NTA5332, a highly integrated NFC IC which creates a secure standard-based link from the device to the cloud from NXP Semiconductors. Based on the NTAG 5 switch and operating at 13.56MHz, the NTA5332 represents an NFC Forum-compliant contactless tag that can be read and written by an NFC-enabled device at close range and by an ISO/IEC 15693-enabled industrial reader over a more extended range. It also incorporates an I2C interface with an I2C master features and AES mutual authentication, SRAM memory, and energy harvesting possibility, which means it can supply power to other components in the system.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ntag5link_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ntag-5-link-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the NTAG 5 Link Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for NTAG 5 Link Click driver.

#### Standard key functions :

- `ntag5link_cfg_setup` Config Object Initialization function.
```c
void ntag5link_cfg_setup ( ntag5link_cfg_t *cfg );
```

- `ntag5link_init` Initialization function.
```c
err_t ntag5link_init ( ntag5link_t *ctx, ntag5link_cfg_t *cfg );
```

- `ntag5link_default_cfg` Click Default Configuration function.
```c
err_t ntag5link_default_cfg ( ntag5link_t *ctx );
```

#### Example key functions :

- `ntag5link_write_ndef_uri_record` This function writes specific NDEF URI record to the memory address specified with NTAG5LINK_NDEF_MESSAGE_START_ADDRESS macro.
```c
err_t ntag5link_write_ndef_uri_record ( ntag5link_t *ctx, uint8_t uri_prefix, uint8_t *uri_data, uint8_t data_len );
```

- `ntag5link_write_message_to_memory` This function writes specified number of data bytes to the user memory starting from block_addr.
```c
err_t ntag5link_write_message_to_memory ( ntag5link_t *ctx, uint16_t block_addr, uint8_t *message, uint16_t message_len );
```

- `ntag5link_read_message_from_memory` This function reads specified number of data bytes from the user memory starting from @b block_addr.
```c
err_t ntag5link_read_message_from_memory ( ntag5link_t *ctx, uint16_t block_addr, uint8_t *message, uint16_t message_len );
```

## Example Description

> This example demonstrates the use of NTAG 5 Link click board by programming the specified NDEF URI record to the memory, and showing the memory read/write feature.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger and performs the click default configuration which 
enables the device and formats its user memory. After that it programs the specified NDEF URI record to the memory.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ntag5link_cfg_t ntag5link_cfg;  /**< Click config object. */

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
    ntag5link_cfg_setup( &ntag5link_cfg );
    NTAG5LINK_MAP_MIKROBUS( ntag5link_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ntag5link_init( &ntag5link, &ntag5link_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( NTAG5LINK_ERROR == ntag5link_default_cfg ( &ntag5link ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    if ( NTAG5LINK_OK == ntag5link_write_ndef_uri_record ( &ntag5link, NTAG5LINK_URI_PREFIX_4, 
                                                           URI_DATA, strlen ( URI_DATA ) ) )
    {
        log_printf( &logger, " NDEF URI record \"https://%s\" has been written\r\n", ( char * ) URI_DATA );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Writes a desired number of data bytes to the memory and verifies that it is written 
correctly by reading from the same memory location and displaying the memory content 
on the USB UART approximately every 5 seconds.

```c
void application_task ( void )
{
    uint8_t message_buf[ 100 ] = { 0 };
    if ( NTAG5LINK_OK == ntag5link_write_message_to_memory ( &ntag5link, 
                                                             TEXT_MESSAGE_ADDRESS, 
                                                             TEXT_MESSAGE, 
                                                             strlen ( TEXT_MESSAGE ) ) )
    {
        log_printf( &logger, " \"%s\" has been written to memory address 0x%.4X \r\n", 
                    ( char * ) TEXT_MESSAGE, ( uint16_t ) TEXT_MESSAGE_ADDRESS );
    }
    if ( NTAG5LINK_OK == ntag5link_read_message_from_memory ( &ntag5link, 
                                                              TEXT_MESSAGE_ADDRESS, 
                                                              message_buf, 
                                                              strlen ( TEXT_MESSAGE ) ) )
    {
        log_printf( &logger, " \"%s\" has been read from memory address 0x%.4X \r\n\n", 
                    message_buf, ( uint16_t ) TEXT_MESSAGE_ADDRESS );
    }
    Delay_ms ( 5000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.NTAG5Link

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
