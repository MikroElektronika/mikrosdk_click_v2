
---
# EEPROM 13 Click

> [EEPROM 13 Click](https://www.mikroe.com/?pid_product=MIKROE-5885) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5885&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of EEPROM 13 Click board.
> The demo app writes specified data to the memory and reads it back.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM13

### Example Key Functions

- `eeprom13_cfg_setup` Config Object Initialization function.
```c
void eeprom13_cfg_setup ( eeprom13_cfg_t *cfg );
```

- `eeprom13_init` Initialization function.
```c
err_t eeprom13_init ( eeprom13_t *ctx, eeprom13_cfg_t *cfg );
```

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
