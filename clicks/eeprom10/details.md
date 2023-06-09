
---
# EEPROM 10 click

> EEPROM 10 Click is a compact add-on board that contains the highest-density memory solution. This board features the N24C32, a 32Kb I2C CMOS Serial EEPROM from ON Semiconductor. It is internally organized as 128 pages of 32 bytes each, with a 32-byte page write buffer and a fast write time of up to 4ms. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eeprom10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/eeprom-10-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the EEPROM 10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for EEPROM 10 Click driver.

#### Standard key functions :

- `eeprom10_cfg_setup` Config Object Initialization function.
```c
void eeprom10_cfg_setup ( eeprom10_cfg_t *cfg );
```

- `eeprom10_init` Initialization function.
```c
err_t eeprom10_init ( eeprom10_t *ctx, eeprom10_cfg_t *cfg );
```

#### Example key functions :

- `eeprom10_write_enable` EEPROM 10 write enable function.
```c
void eeprom10_write_enable( eeprom10_t *ctx );
```

- `eeprom10_write_n_byte` EEPROM 10 write desired number of data function.
```c
err_t eeprom10_write_n_byte ( eeprom10_t *ctx, uint16_t address, uint8_t *data_in, uint8_t len );
```

- `eeprom10_read_n_byte` EEPROM 10 read desired number of data function.
```c
err_t eeprom10_read_n_byte ( eeprom10_t *ctx, uint16_t address, uint8_t *data_out, uint8_t len );
```

## Example Description

> This example demonstrates the use of EEPROM 10 click board by writing specified data to
  the memory and reading it back.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and USB UART logging.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom10_cfg_t eeprom10_cfg;  /**< Click config object. */

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
    eeprom10_cfg_setup( &eeprom10_cfg );
    EEPROM10_MAP_MIKROBUS( eeprom10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == eeprom10_init( &eeprom10, &eeprom10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    eeprom10_write_enable( &eeprom10 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> In this example, we write and then read data from EEPROM memory.
  Results are being sent to the Usart Terminal where you can track their changes.
  All data logs write on USB UART changes approximately every second.

```c
void application_task ( void ) 
{
    err_t error_flag = EEPROM10_OK;
    
    error_flag = eeprom10_write_n_byte( &eeprom10, EEPROM10_TEST_ADDRESS, tx_data, 14 );
    if ( EEPROM10_OK == error_flag )
    {
        log_printf( &logger, " Write %s data to 0x%.4X address \r\n", tx_data, ( uint16_t ) EEPROM10_TEST_ADDRESS );
    }
    else
    {
        log_error( &logger, " Write operation failed!!! " );
    }
    Delay_ms( 100 );
    
    error_flag = eeprom10_read_n_byte( &eeprom10, EEPROM10_TEST_ADDRESS, rx_data, 14 );
    if ( EEPROM10_OK == error_flag )
    {
        log_printf( &logger, " Read %s from 0x%.4X address \r\n", rx_data, ( uint16_t ) EEPROM10_TEST_ADDRESS );
    }
    else
    {
        log_error( &logger, " Read operation failed!!! " );
    }
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
