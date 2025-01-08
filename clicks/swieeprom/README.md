
---
# SWI EEPROM Click

> [SWI EEPROM Click](https://www.mikroe.com/?pid_product=MIKROE-4521) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4521&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of SWI EEPROM Click board by writing specified data to the memory and reading it back.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SWIEEPROM

### Example Key Functions

- `swieeprom_cfg_setup` Config Object Initialization function.
```c
void swieeprom_cfg_setup ( swieeprom_cfg_t *cfg );
```

- `swieeprom_init` Initialization function.
```c
err_t swieeprom_init ( swieeprom_t *ctx, swieeprom_cfg_t *cfg );
```

- `swieeprom_mem_write_page` This function writes data to the specified memory address page.
```c
err_t swieeprom_mem_write_page ( swieeprom_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t len );
```

- `swieeprom_mem_read` This function reads data from the specified memory address.
```c
err_t swieeprom_mem_read ( swieeprom_t *ctx, uint8_t start_addr, uint8_t *data_out, uint8_t len );
```

- `swieeprom_mem_clear` This function clears the whole memory to zero.
```c
err_t swieeprom_mem_clear ( swieeprom_t *ctx );
```

### Application Init

> Initializes the driver and logger and checks the communication.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */

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
    swieeprom.swi_reset = &swieeprom_reset;
    swieeprom.swi_start_stop = &swieeprom_start_stop;
    swieeprom.swi_logic_0 = &swieeprom_logic_write_0;
    swieeprom.swi_logic_1 = &swieeprom_logic_write_1;
    swieeprom.swi_logic_read = &swieeprom_logic_read;
    if ( SWIEEPROM_ERROR == swieeprom_init ( &swieeprom ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SWIEEPROM_ERROR == swieeprom_check_communication ( &swieeprom ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Writes the specified text message to the memory and reads it back. After that, erases
the whole memory and tries to read the same message verifying that the memory is erased.
All data is being displayed on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    uint8_t data_buf[ 8 ] = { 0 };
    // Write data to the specified address
    log_printf ( &logger, " Memory address: 0x%.2X\r\n", ( uint16_t ) STARTING_ADDRESS );
    memcpy ( data_buf, DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) );
    if ( SWIEEPROM_OK == swieeprom_mem_write_page ( &swieeprom, STARTING_ADDRESS, 
                                                    data_buf, strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    // Read data from the specified address to verify the previous memory write
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( SWIEEPROM_OK == swieeprom_mem_read ( &swieeprom, STARTING_ADDRESS, 
                                              data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n", data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    // Clear whole memory
    if ( SWIEEPROM_OK == swieeprom_mem_clear ( &swieeprom ) )
    {
        log_printf ( &logger, " Memory clear\r\n" );
        Delay_ms ( 100 );
    }
    // Read data from the specified address to verify the previous memory clear
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( SWIEEPROM_OK == swieeprom_mem_read ( &swieeprom, STARTING_ADDRESS, 
                                              data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}
```

### Note

> This application is written for the following MCUs and specifically for MIKROBUS 1:
STM32F407ZG, MK64FN1M0VDC12, TM4C129XNCZAD, GD32VF103VBT6, PIC32MX795F512L
In order to use it on another MCUs the pin_x functions must be defined in a way
it matches the required timing specifications for the Single Wire interface.

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
