\mainpage Main Page

---
# EEPROM 11 click

> EEPROM 11 Click is a compact add-on board with a highly reliable, nonvolatile memory solution. This board features the S-34C04AB, an EEPROM for DIMM serial presence detection from ABLIC. The EEPROM is internally organized as 2 pages of 256 words x 8-bit, and a capacity of 4Kbits and is an EE1004-1 JEDEC standard-compliant.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eeprom11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/eeprom-11-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the EEPROM 11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for EEPROM 11 Click driver.

#### Standard key functions :

- `eeprom11_cfg_setup` Config Object Initialization function.
```c
void eeprom11_cfg_setup ( eeprom11_cfg_t *cfg );
```

- `eeprom11_init` Initialization function.
```c
err_t eeprom11_init ( eeprom11_t *ctx, eeprom11_cfg_t *cfg );
```

- `eeprom11_default_cfg` Click Default Configuration function.
```c
err_t eeprom11_default_cfg ( eeprom11_t *ctx );
```

#### Example key functions :

- `eeprom11_page_write` EEPROM 11 page write function.
```c
err_t eeprom11_page_write ( eeprom11_t *ctx, uint8_t address, uint8_t *data_in );
```

- `eeprom11_clear_page` EEPROM 11 page clear function.
```c
err_t eeprom11_clear_page ( eeprom11_t *ctx, uint8_t address );
```

- `eeprom11_set_page_addr` EEPROM 11 set page address function.
```c
err_t eeprom11_set_page_addr ( eeprom11_t *ctx, uint8_t page_addr );
```

## Example Description

> This is an example that demonstrates the use of the EEPROM 11 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and USB UART logging, disables write protection.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom11_cfg_t eeprom11_cfg;  /**< Click config object. */

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
    eeprom11_cfg_setup( &eeprom11_cfg );
    EEPROM11_MAP_MIKROBUS( eeprom11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == eeprom11_init( &eeprom11, &eeprom11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EEPROM11_ERROR == eeprom11_default_cfg ( &eeprom11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Writes a desired number of data bytes to the EEPROM 11 memory into a specified address, 
  and verifies that it is written correctly by reading from the same memory location.

```c
void application_task ( void ) 
{
    err_t error_flag = EEPROM11_OK;
    uint8_t rx_data[ 16 ] = { 0 };
    uint8_t tx_data[ 16 ] = TX_DATA;
    
    eeprom11_clear_page( &eeprom11, MEMORY_ADDRESS );
    Delay_ms ( 1000 );
    error_flag = eeprom11_page_write( &eeprom11, MEMORY_ADDRESS, tx_data );
    if ( EEPROM11_OK == error_flag )
    {
        log_printf( &logger, " Write data: %s \r\n", tx_data );
    }
    else
    {
        log_error( &logger, " Write operation failed!!! " );
    }
    Delay_ms ( 1000 );
    
    error_flag = eeprom11_generic_read( &eeprom11, MEMORY_ADDRESS, rx_data, 15 );
    if ( EEPROM11_OK == error_flag )
    {
        log_printf( &logger, "Read data: %s \r\n", rx_data );
    }
    else
    {
        log_error( &logger, " Write operation failed!!! " );
    }
    log_printf( &logger, " - - - - - - - - - - - \r\n" );
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
