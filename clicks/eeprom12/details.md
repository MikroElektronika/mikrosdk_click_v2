
---
# EEPROM 12 Click

> EEPROM 12 Click is a compact add-on board that contains a highly reliable, nonvolatile memory solution. This board features the M24256E, an EEPROM from STMicroelectronics. It is a 256Kbit (32KB) EEPROM with a page size of 64 bytes and an additional identification page with the same size. This identification page can be read or written and (later) permanently locked in read-only mode and can be used to store sensitive application parameters.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eeprom12_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/eeprom-12-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the EEPROM 12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for EEPROM 12 Click driver.

#### Standard key functions :

- `eeprom12_cfg_setup` Config Object Initialization function.
```c
void eeprom12_cfg_setup ( eeprom12_cfg_t *cfg );
```

- `eeprom12_init` Initialization function.
```c
err_t eeprom12_init ( eeprom12_t *ctx, eeprom12_cfg_t *cfg );
```

#### Example key functions :

- `eeprom12_memory_write` EEPROM 12 memory write function.
```c
err_t eeprom12_memory_write ( eeprom12_t *ctx, uint16_t mem_addr, uint8_t *data_in, uint8_t len );
```

- `eeprom12_memory_read` EEPROM 12 memory read function.
```c
err_t eeprom12_memory_read ( eeprom12_t *ctx, uint16_t mem_addr, uint8_t *data_out, uint8_t len );
```

## Example Description

> This example demonstrates the use of EEPROM 12 Click board™.
> The demo app writes specified data to the memory and reads it back.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C module, log UART, and additional pins.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom12_cfg_t eeprom12_cfg;  /**< Click config object. */

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
    eeprom12_cfg_setup( &eeprom12_cfg );
    EEPROM12_MAP_MIKROBUS( eeprom12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == eeprom12_init( &eeprom12, &eeprom12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application writes a desired number of bytes to the memory 
> and then verifies if it is written correctly
> by reading from the same memory location and displaying the memory content.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    uint8_t data_buf[ 128 ] = { 0 };
    memcpy( data_buf, DEMO_TEXT_MESSAGE_1, strlen( DEMO_TEXT_MESSAGE_1 ) );
    if ( EEPROM12_OK == eeprom12_memory_write( &eeprom12, STARTING_ADDRESS, 
                                                          data_buf, 
                                                          strlen( DEMO_TEXT_MESSAGE_1 ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    
    memset( data_buf, 0, sizeof( data_buf ) );
    Delay_ms ( 100 );
    if ( EEPROM12_OK == eeprom12_memory_read( &eeprom12, STARTING_ADDRESS, 
                                                         data_buf, 
                                                         strlen( DEMO_TEXT_MESSAGE_1 ) ) )
    {
        Delay_ms ( 100 );
        log_printf( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    memcpy( data_buf, DEMO_TEXT_MESSAGE_2, strlen( DEMO_TEXT_MESSAGE_2 ) );
    if ( EEPROM12_OK == eeprom12_memory_write( &eeprom12, STARTING_ADDRESS, 
                                                          data_buf, 
                                                          strlen( DEMO_TEXT_MESSAGE_2 ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    
    memset( data_buf, 0, sizeof( data_buf ) );
    Delay_ms ( 100 );
    if ( EEPROM12_OK == eeprom12_memory_read( &eeprom12, STARTING_ADDRESS, 
                                                         data_buf, 
                                                         strlen( DEMO_TEXT_MESSAGE_2 ) ) )
    {
        Delay_ms ( 100 );
        log_printf( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
