
---
# EEPROM 8 Click

> [EEPROM 8 Click](https://www.mikroe.com/?pid_product=MIKROE-5073) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5073&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Popovic
- **Date**          : Mar 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of EEPROM 8 Click board by writing specified data to the memory and reading it back.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM8

### Example Key Functions

- `eeprom8_cfg_setup` Config Object Initialization function.
```c
void eeprom8_cfg_setup ( eeprom8_cfg_t *cfg );
```

- `eeprom8_init` Initialization function.
```c
err_t eeprom8_init ( eeprom8_t *ctx, eeprom8_cfg_t *cfg );
```

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
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
