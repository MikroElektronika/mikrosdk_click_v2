
---
# ReRAM 2 Click

> [ReRAM 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4895) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4895&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for ReRAM 2 Click driver.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ReRAM2

### Example Key Functions

- `reram2_cfg_setup` Config Object Initialization function.
```c
void reram2_cfg_setup ( reram2_cfg_t *cfg );
```

- `reram2_init` Initialization function.
```c
err_t reram2_init ( reram2_t *ctx, reram2_cfg_t *cfg );
```

- `reram2_default_cfg` Click Default Configuration function.
```c
err_t reram2_default_cfg ( reram2_t *ctx );
```

- `reram2_read_device_id` ReRAM 2 read device ID function.
```c
err_t reram2_read_device_id ( reram2_t *ctx, reram2_dev_id_t *dev_id );
```

- `reram2_write_memory` ReRAM 2 write memory function.
```c
err_t reram2_write_memory ( reram2_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint16_t len );
```

- `reram2_read_memory` ReRAM 2 read memory function.
```c
err_t reram2_read_memory ( reram2_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint16_t len );
```

### Application Init

> Initializes SPI driver and log UART.
> After driver initialization the app set default settings, 
> performs device wake-up, check Device ID,
> set Write Enable Latch command and write demo_data string ( mikroE ), 
> starting from the selected memory_addr ( 1234 ).

```c
void application_init ( void )
{
    log_cfg_t log_cfg;        /**< Logger config object. */
    reram2_cfg_t reram2_cfg;  /**< Click config object. */

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
    reram2_cfg_setup( &reram2_cfg );
    RERAM2_MAP_MIKROBUS( reram2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == reram2_init( &reram2, &reram2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RERAM2_ERROR == reram2_default_cfg ( &reram2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    reram2_wake_up( &reram2 );
    Delay_ms ( 100 );
    
    if ( RERAM2_ERROR == reram2_check_device_id( &reram2 ) )
    {
        log_error( &logger, " Communication Error. " );
        log_info( &logger, " Please, run program again... " );
        for( ; ; );
    }

    reram2_send_command( &reram2, RERAM2_CMD_WREN );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    
    memory_addr = 1234;   
    log_printf( &logger, "\r\n  Write data : %s", demo_data );
    reram2_write_memory( &reram2, memory_addr, &demo_data[ 0 ], 9 );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> This is an example that demonstrates the use of the ReRAM 2 Click board&trade;.
> In this example, we read and display a data string, which we have previously written to memory, 
> starting from the selected memory_addr ( 1234 ).
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    static char rx_data[ 9 ] = { 0 };
    
    reram2_read_memory( &reram2, memory_addr, &rx_data[ 0 ], 9 );
    log_printf( &logger, "  Read data  : %s", rx_data ); 
    log_printf( &logger, "-----------------------\r\n" );
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
