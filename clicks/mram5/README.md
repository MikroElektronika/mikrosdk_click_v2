
---
# MRAM 5 Click

> [MRAM 5 Click](https://www.mikroe.com/?pid_product=MIKROE-7098) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7098&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jul 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of MRAM 5 Click board by writing specified data to
the memory and reading it back.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MRAM5

### Example Key Functions

- `mram5_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void mram5_cfg_setup ( mram5_cfg_t *cfg );
```

- `mram5_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t mram5_init ( mram5_t *ctx, mram5_cfg_t *cfg );
```

- `mram5_default_cfg` This function executes a default configuration of MRAM 5 Click board.
```c
err_t mram5_default_cfg ( mram5_t *ctx );
```

- `mram5_memory_write` This function writes a desired number of data bytes starting from the selected memory address.
```c
err_t mram5_memory_write ( mram5_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint32_t len );
```

- `mram5_memory_read` This function reads a desired number of data bytes starting from the selected memory address.
```c
err_t mram5_memory_read ( mram5_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint32_t len );
```

- `mram5_write_enable` This function sets the write enable latch bit in the status register.
```c
err_t mram5_write_enable ( mram5_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mram5_cfg_t mram5_cfg;  /**< Click config object. */

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
    mram5_cfg_setup( &mram5_cfg );
    MRAM5_MAP_MIKROBUS( mram5_cfg, MIKROBUS_POSITION_MRAM5 );
    if ( SPI_MASTER_ERROR == mram5_init( &mram5, &mram5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MRAM5_ERROR == mram5_default_cfg ( &mram5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Writes a desired number of bytes to the memory and then verifies if it is written correctly
by reading from the same memory location and displaying the memory content on the USB UART.

```c
void application_task ( void )
{
    uint8_t data_buf[ DEMO_BUFFER_SIZE ] = { 0 };

    log_printf( &logger, "\r\n Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS );

    /* Write first DEMO message */
    memcpy( data_buf, DEMO_TEXT_MESSAGE_1, strlen( DEMO_TEXT_MESSAGE_1 ) );
    if ( MRAM5_OK == mram5_memory_write( &mram5, STARTING_ADDRESS, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );

    /* Read first DEMO message */
    memset( data_buf, 0, sizeof( data_buf ) );
    if ( MRAM5_OK == mram5_memory_read( &mram5, STARTING_ADDRESS, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
    }
    Delay_ms ( 1000 );

    /* Write second DEMO message */
    memcpy( data_buf, DEMO_TEXT_MESSAGE_2, strlen( DEMO_TEXT_MESSAGE_2 ) );
    if ( MRAM5_OK == mram5_memory_write( &mram5, STARTING_ADDRESS, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );

    /* Read second DEMO message */
    memset( data_buf, 0, sizeof( data_buf ) );
    if ( MRAM5_OK == mram5_memory_read( &mram5, STARTING_ADDRESS, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
    }

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
