
---
# EEPROM 12 Click

> [EEPROM 12 Click](https://www.mikroe.com/?pid_product=MIKROE-5893) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5893&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of EEPROM 12 Click board&trade;.
> The demo app writes specified data to the memory and reads it back.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM12

### Example Key Functions

- `eeprom12_cfg_setup` Config Object Initialization function.
```c
void eeprom12_cfg_setup ( eeprom12_cfg_t *cfg );
```

- `eeprom12_init` Initialization function.
```c
err_t eeprom12_init ( eeprom12_t *ctx, eeprom12_cfg_t *cfg );
```

- `eeprom12_memory_write` EEPROM 12 memory write function.
```c
err_t eeprom12_memory_write ( eeprom12_t *ctx, uint16_t mem_addr, uint8_t *data_in, uint8_t len );
```

- `eeprom12_memory_read` EEPROM 12 memory read function.
```c
err_t eeprom12_memory_read ( eeprom12_t *ctx, uint16_t mem_addr, uint8_t *data_out, uint8_t len );
```

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
