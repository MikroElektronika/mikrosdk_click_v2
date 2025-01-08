
---
# FRAM 6 Click

> [FRAM 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4831) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4831&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of FRAM 6 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.FRAM6

### Example Key Functions

- `fram6_cfg_setup` Config Object Initialization function.
```c
void fram6_cfg_setup ( fram6_cfg_t *cfg );
```

- `fram6_init` Initialization function.
```c
err_t fram6_init ( fram6_t *ctx, fram6_cfg_t *cfg );
```

- `fram6_default_cfg` Click Default Configuration function.
```c
err_t fram6_default_cfg ( fram6_t *ctx );
```

- `fram6_memory_write` This function writes a desired number of data bytes starting from the selected memory address.
```c
err_t fram6_memory_write ( fram6_t *ctx, uint32_t address, uint8_t *data_in, uint16_t len );
```

- `fram6_memory_read` This function reads a desired number of data bytes starting from the selected memory address.
```c
err_t fram6_memory_read ( fram6_t *ctx, uint32_t address, uint8_t *data_out, uint16_t len );
```

- `fram6_set_block_protection` This function sets the block protection bits of the Status register.
```c
err_t fram6_set_block_protection ( fram6_t *ctx, uint8_t block_protect );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    fram6_cfg_t fram6_cfg;  /**< Click config object. */

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

    fram6_cfg_setup( &fram6_cfg );
    FRAM6_MAP_MIKROBUS( fram6_cfg, MIKROBUS_1 );
    
    if ( SPI_MASTER_ERROR == fram6_init( &fram6, &fram6_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    if ( FRAM6_ERROR == fram6_default_cfg ( &fram6 ) )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Writes a desired number of bytes to the memory and then verifies that it's written correctly
> by reading from the same memory location and displaying the memory content on the USB UART.

```c
void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };
    if ( FRAM6_OK == fram6_memory_write ( &fram6, STARTING_ADDRESS, 
                                          DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, "Data written to address 0x%.5lx: \t%s\r\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                             ( char * ) DEMO_TEXT_MESSAGE );
    }
    if ( FRAM6_OK == fram6_memory_read ( &fram6, STARTING_ADDRESS, 
                                         data_buf, strlen ( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf ( &logger, "Data read from address 0x%.5lx: \t%s\r\n\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                                         data_buf );
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
