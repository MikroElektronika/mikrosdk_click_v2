\mainpage Main Page

---
# EEPROM 13 click

> EEPROM 13 Click is a compact add-on board that contains a highly reliable, nonvolatile memory solution. This board features the M24M01E, an electrically erasable programmable memory with enhanced hardware write protection for entire memory from STMicroelectronics. Its memory size of 1Mbit is organized as 128K words of 8bits each, with a page size of 256 bytes and an additional 256 bytes of identification page. The identification page can be used to store sensitive application parameters, which can be (later) permanently locked in read-only mode.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eeprom13_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/eeprom-13-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the EEPROM 13 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for EEPROM 13 Click driver.

#### Standard key functions :

- `eeprom13_cfg_setup` Config Object Initialization function.
```c
void eeprom13_cfg_setup ( eeprom13_cfg_t *cfg );
```

- `eeprom13_init` Initialization function.
```c
err_t eeprom13_init ( eeprom13_t *ctx, eeprom13_cfg_t *cfg );
```

#### Example key functions :

- `eeprom13_memory_write` This function writes a desired number of data bytes starting from the selected memory address.
```c
err_t eeprom13_memory_write ( eeprom13_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint8_t len );
```

- `eeprom13_memory_read` This function reads a desired number of data bytes starting from the selected memory address.
```c
err_t eeprom13_memory_read ( eeprom13_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint8_t len );
```

- `eeprom13_hw_write_enable` This function disabled hardware write protection of the entire memory.
```c
void eeprom13_hw_write_enable ( eeprom13_t *ctx );
```

## Example Description

> This example demonstrates the use of EEPROM 13 click board.
> The demo app writes specified data to the memory and reads it back.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C module, log UART, and additional pins.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom13_cfg_t eeprom13_cfg;  /**< Click config object. */

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
    eeprom13_cfg_setup( &eeprom13_cfg );
    EEPROM13_MAP_MIKROBUS( eeprom13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == eeprom13_init( &eeprom13, &eeprom13_cfg ) ) 
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
    if ( EEPROM13_OK == eeprom13_memory_write( &eeprom13, STARTING_ADDRESS, 
                                                          data_buf, 
                                                          strlen( DEMO_TEXT_MESSAGE_1 ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    
    memset( data_buf, 0, sizeof( data_buf ) );
    Delay_ms ( 100 );
    if ( EEPROM13_OK == eeprom13_memory_read( &eeprom13, STARTING_ADDRESS, 
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
    if ( EEPROM13_OK == eeprom13_memory_write( &eeprom13, STARTING_ADDRESS, 
                                                          data_buf, 
                                                          strlen( DEMO_TEXT_MESSAGE_2 ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    
    memset( data_buf, 0, sizeof( data_buf ) );
    Delay_ms ( 100 );
    if ( EEPROM13_OK == eeprom13_memory_read( &eeprom13, STARTING_ADDRESS, 
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
- Click.EEPROM13

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
