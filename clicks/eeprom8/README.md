\mainpage Main Page

---
# EEPROM 8 click

> EEPROM 8 Click is a compact add-on board that contains a highly reliable nonvolatile memory solution. This board features the CAV24C512, a 512-Kb electrically erasable programmable memory with enhanced hardware write protection for entire memory from ON Semiconductor. Internally organized as 65,536 words of 8 bits each, the CAV24C512 comes up with the compatible I2C serial interface. The CAV24C512 combines unprecedented data storage with excellent energy efficiency. It lasts one million full-memory read/write/erase cycles with more than 100 years of data retention.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eeprom8_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/eeprom-8-click)

---


#### Click library

- **Author**        : Stefan Popovic
- **Date**          : Mar 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the EEPROM 8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for EEPROM 8 Click driver.

#### Standard key functions :

- `eeprom8_cfg_setup` Config Object Initialization function.
```c
void eeprom8_cfg_setup ( eeprom8_cfg_t *cfg );
```

- `eeprom8_init` Initialization function.
```c
err_t eeprom8_init ( eeprom8_t *ctx, eeprom8_cfg_t *cfg );
```

#### Example key functions :

- `eeprom8_write_page` This function writes up to 128 bytes of data starting from the selected register.
```c
err_t eeprom8_write_page( eeprom8_t *ctx, uint16_t reg_addr, uint8_t *data_in );
```

- `eeprom8_read_random_byte` This function reads one byte data from the desired register.
```c
err_t eeprom8_read_random_byte( eeprom8_t *ctx, uint16_t reg_addr, uint8_t *data_out );
```

- `eeprom8_read_sequential` This function reads the desired number of bytes starting from the selected register.
```c
err_t eeprom8_read_sequential( eeprom8_t *ctx, uint16_t reg_addr, uint16_t n_bytes, uint8_t *data_out );
```

## Example Description

> This example demonstrates the use of EEPROM 8 click board by writing specified data to the memory and reading it back.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and USB UART logging.

```c

void application_init ( void ) 
{
    eeprom8_cfg_t eeprom8_cfg;  /**< Click config object. */
    log_cfg_t log_cfg;          /**< Logger config object. */
    
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
    
    //  Click initialization.
    eeprom8_cfg_setup( &eeprom8_cfg );
    EEPROM8_MAP_MIKROBUS( eeprom8_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == eeprom8_init( &eeprom8, &eeprom8_cfg ) )
    {
        log_error( &logger, " Communication Init " );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Task writes a desired number of data bytes to the EEPROM 8 memory and verifies that it is written correctly by reading from the same memory location and in case of successful read, displays the memory content on the USB UART. This is done in two passes.

```c

void application_task ( void ) 
{
    // Reset variables
    cnt = 0;
    memset( test_read_buffer, 0, sizeof ( test_read_buffer ) );
    addr_offset = TEST_MEM_LOCATION;
    
    // Initiate first pass 
    //  filling the eeprom addresses with zeros 
    if( EEPROM8_ERROR == run_first_pass( &eeprom8, test_write_buffer, test_read_buffer ) )
    {
        log_error( &logger, " First Pass Failed " );
    }
    
    // Initiate second pass 
    //  filling the eeprom addresses with values following arithmetic sequence with difference of 1 
    if( EEPROM8_ERROR == run_second_pass( &eeprom8, test_write_buffer, test_read_buffer ) )
    {
        log_error( &logger, " Second Pass Failed " );
    }
    
    log_printf( &logger, " \r\nInitiating new iteration\r\n " );
    Delay_ms( 6000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
