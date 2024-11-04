
---
# EERAM 3 Click

> EERAM 3 Click is a compact add-on board that contains EERAM memory designed to retain data during power loss without the aid of external batteries. This board features the 48L256, a serial EERAM with SRAM memory core, including hidden EEPROM backup from Microchip Technology.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eeram3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/eeram-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the EERAM3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for EERAM3 Click driver.

#### Standard key functions :

- `eeram3_cfg_setup` Config Object Initialization function.
```c
void eeram3_cfg_setup ( eeram3_cfg_t *cfg );
```

- `eeram3_init` Initialization function.
```c
err_t eeram3_init ( eeram3_t *ctx, eeram3_cfg_t *cfg );
```

- `eeram3_default_cfg` Click Default Configuration function.
```c
void eeram3_default_cfg ( eeram3_t *ctx );
```

#### Example key functions :

- `eeram3_memory_secure_write` This function securely writes a desired number of data bytes starting from the selected memory address.
```c
err_t eeram3_memory_secure_write ( eeram3_t *ctx, uint16_t address, uint8_t *data_in, uint8_t len );
```

- `eeram3_memory_secure_read` This function securely reads a desired number of data bytes starting from the selected memory address.
```c
err_t eeram3_memory_secure_read ( eeram3_t *ctx, uint16_t address, uint8_t *data_out, uint8_t len );
```

- `eeram3_set_block_protection` This function sets the block protection bits of the Status register.
```c
err_t eeram3_set_block_protection ( eeram3_t *ctx, uint8_t block_protect );
```

## Example Description

> This example demonstrates the use of EERAM 3 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;        /**< Logger config object. */
    eeram3_cfg_t eeram3_cfg;  /**< Click config object. */

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
    eeram3_cfg_setup( &eeram3_cfg );
    EERAM3_MAP_MIKROBUS( eeram3_cfg, MIKROBUS_1 );
    
    if ( SPI_MASTER_ERROR == eeram3_init( &eeram3, &eeram3_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    eeram3_default_cfg ( &eeram3 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Writes a desired number of bytes to the memory and then verifies that it's written correctly
> by reading from the same memory location and displaying the memory content on the USB UART.

```c

void application_task ( void )
{
    uint8_t data_buf[ 64 ] = { 0 };
    if ( EERAM3_OK == eeram3_memory_secure_write ( &eeram3, STARTING_ADDRESS, 
                                                   DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, "Data written to address 0x%.4X: %s\r\n", ( uint16_t ) STARTING_ADDRESS, 
                                                                          ( char * ) DEMO_TEXT_MESSAGE );
    }
    Delay_ms ( 100 );

    if ( EERAM3_OK == eeram3_memory_secure_read ( &eeram3, STARTING_ADDRESS, 
                                                  data_buf, strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, "Data read from address 0x%.4X: %s\r\n\n", ( uint16_t ) STARTING_ADDRESS, 
                                                                                      data_buf );
    }
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.EERAM3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
