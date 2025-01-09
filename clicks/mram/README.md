
---
# MRAM Click

> [MRAM Click](https://www.mikroe.com/?pid_product=MIKROE-2914) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2914&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This example writes and reads from the Mram Click and displays it on the terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MRAM

### Example Key Functions

- `mram_cfg_setup` Config Object Initialization function.
```c
void mram_cfg_setup ( mram_cfg_t *cfg ); 
```

- `mram_init` Initialization function.
```c
err_t mram_init ( mram_t *ctx, mram_cfg_t *cfg );
```

- `mram_default_cfg` Click Default Configuration function.
```c
void mram_default_cfg ( mram_t *ctx );
```

- `mram_write_data_bytes` Function writes n bytes of data from the buffer.
```c
void mram_write_data_bytes ( mram_t *ctx, const uint16_t address, uint8_t *buffer, const uint16_t nBytes);
```

- `mram_read_data_bytes` Function reads n bytes of data and saves it in buffer.
```c
void mram_read_data_bytes ( mram_t *ctx, const uint16_t address, uint8_t *buffer, const uint16_t n_bytes);
```

- `mram_enable_write_protect` Function enables or disables write protect.
```c
void mram_enable_write_protect ( mram_t *ctx, uint8_t state);
```

### Application Init

> Initializes Click driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mram_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mram_cfg_setup( &cfg );
    MRAM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mram_init( &mram, &cfg );
    mram_default_cfg( &mram );
}
```

### Application Task

> Writes 10 bytes of buffer data in memory with start address 0x0001. 
> Then reads 10 bytes from memory with start address 0x0001 and shows result on USB UART.

```c
void application_task ( void )
{
    uint8_t number_bytes_write;
    uint8_t number_bytes_read;
    uint16_t i;
    uint8_t data_write[ 10 ] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    uint8_t data_read[ 20 ] = { 0 };
    
    number_bytes_write = 10;
    number_bytes_read = 10;

    log_printf( &logger, " Data written!\r\n" );
    mram_write_data_bytes ( &mram, 0x0001, data_write, number_bytes_write );
    
    log_printf( &logger, " Read data:\r\n" );
    mram_read_data_bytes ( &mram, 0x0001, data_read, number_bytes_read );
    
    for ( i = 0; i < number_bytes_read; i++ )
    {
        log_printf( &logger, "%d ", ( uint16_t )data_read[ i ] );
    }
    
    log_printf( &logger, "\n" );

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
