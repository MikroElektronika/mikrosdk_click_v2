
---
# Flash 7 Click

> [Flash 7 Click](https://www.mikroe.com/?pid_product=MIKROE-4440) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4440&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the Flash 7 Click board. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash7

### Example Key Functions

- `flash7_cfg_setup` Config Object Initialization function.
```c
void flash7_cfg_setup ( flash7_cfg_t *cfg );
```

- `flash7_init` Initialization function.
```c
err_t flash7_init ( flash7_t *ctx, flash7_cfg_t *cfg );
```

- `flash7_default_cfg` Click Default Configuration function.
```c
err_t flash7_default_cfg ( flash7_t *ctx );
```

- `flash7_send_command` Send command function.
```c
void flash7_send_command ( flash7_t *ctx, uint8_t cmd );
```

- `flash7_page_program` Page program function.
```c
uint8_t flash7_page_program ( flash7_t *ctx, uint32_t mem_addr, uint8_t *p_tx_data, uint16_t n_bytes );
```

- `flash7_read_memory` Read memory function.
```c
void flash7_read_memory ( flash7_t *ctx, uint32_t mem_addr, uint8_t *p_rx_data, uint16_t n_bytes );
```

### Application Init

> Initialization driver enables SPI, disables write protect and hold, performs whole chip erase, targets the memory address at "4096" for page program starting point and writes data which is also displayed on the log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    flash7_cfg_t flash7_cfg;  /**< Click config object. */

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

    flash7_cfg_setup( &flash7_cfg );
    FLASH7_MAP_MIKROBUS( flash7_cfg, MIKROBUS_1 );
    err_t init_flag  = flash7_init( &flash7, &flash7_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    flash7_default_cfg ( &flash7 );
    
    log_printf( &logger, " ----------------------- \r\n" );
    log_printf( &logger, " Chip Erase \r\n" );
    flash7_chip_erase( &flash7 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    memory_addr = 4096;
    
    log_printf( &logger, " ----------------------- \r\n" );
    log_printf( &logger, " Write data : %s ", demo_data );
    log_printf( &logger, " ----------------------- \r\n" );
    flash7_page_program( &flash7, memory_addr, demo_data, 9 );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------------- \r\n" );
}
```

### Application Task

> In this example, the data is read from the targeted memory address. The results are being sent to the Usart Terminal. This task repeats every 5 sec.

```c
void application_task ( void ) 
{
    flash7_read_memory( &flash7, memory_addr, rx_data, 9 );
    log_printf( &logger, " Read data : %s ", rx_data );
    log_printf( &logger, " ----------------------- \r\n" );
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
