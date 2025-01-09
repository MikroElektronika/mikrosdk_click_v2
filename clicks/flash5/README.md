
---
# Flash 5 Click

> [Flash 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3780) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3780&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This application is for storing mass storage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash5

### Example Key Functions

- `flash5_cfg_setup` Config Object Initialization function. 
```c
void flash5_cfg_setup ( flash5_cfg_t *cfg );
``` 
 
- `flash5_init` Initialization function. 
```c
err_t flash5_init ( flash5_t *ctx, flash5_cfg_t *cfg );
```

- `flash5_page_read` Function for setting page read. 
```c
void flash5_page_read ( flash5_t *ctx, uint16_t page_num );
```
 
- `flash5_page_load_memory` Function for loading one page. 
```c
void flash5_page_load_memory ( flash5_t *ctx, uint16_t column_addr, uint8_t *data_buf, uint16_t buf_size );
```

- `flash5_write_status_data` Function for writing status data. 
```c
void flash5_write_status_data ( flash5_t *ctx, uint8_t status_cmd, uint8_t status_addr, uint8_t status_data );
```

### Application Init

> Initializes driver, resets device, erasing one page of memory, tests communication and configures device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    flash5_cfg_t cfg;
    uint8_t device_check = 0;

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

    flash5_cfg_setup( &cfg );
    FLASH5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flash5_init( &flash5, &cfg );

    log_printf( &logger, " - Reseting device... \r\n" );
 
    flash5_software_reset( &flash5 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " - Erasing memory... \r\n" );   
    
    flash5_send_cmd( &flash5, FLASH5_CMD_WRITE_ENABLE );
    flash5_erase_page_data( &flash5, 0x0001 );
    
    device_check = flash5_device_id_check( &flash5 );

    if ( device_check == FLASH5_DEVICE_OK )
    {
        log_printf( &logger, " - Device OK \r\n" );  
    }
    else
    {
        log_printf( &logger, " - Device Error \r\n" );  
        for( ; ; );
    }
    Delay_ms ( 100 );
    
    log_printf( &logger, " - Configuring device \r\n" );  

    flash5_write_status_data( &flash5, FLASH5_CMD_WRITE_REG_STATUS1, FLASH5_REG_STATUS_1, FLASH5_RS1_WRITE_PROTECTION_DISABLE | 
                                                                                          FLASH5_RS1_SRP1_ENABLE );
    flash5_write_status_data( &flash5, FLASH5_CMD_WRITE_REG_STATUS1, FLASH5_REG_STATUS_1, FLASH5_RS2_PAGE_READ_MODE );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "***** App init ***** \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    Delay_ms ( 500 );
}
```

### Application Task

> Writes "MikroE" to device memory and then reads it and sends it to log.

```c
void application_task ( )
{
    char read_buf[ 6 ];
    uint8_t n_counter;

    flash5_send_cmd( &flash5, FLASH5_CMD_WRITE_ENABLE );
    flash5_page_load_memory( &flash5, 0x000A, &write_buf[ 0 ], 6 );
    flash5_page_read_memory( &flash5, 0x000A, &read_buf[ 0 ], 6 );

    for( n_counter = 0; n_counter < 6; n_counter++ )
    {
        log_printf( &logger, " %c ", &read_buf[ n_counter ] );
        Delay_ms ( 100 );
    }
    
    log_printf( &logger, " \r\n" );
    log_printf( &logger, "------------------- \r\n" );
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
