
---
# Flash 6 Click

> [Flash 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4067) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4067&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application writes in memory and reads from memory.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash6

### Example Key Functions

- `flash6_cfg_setup` Config Object Initialization function. 
```c
void flash6_cfg_setup ( flash6_cfg_t *cfg );
``` 
 
- `flash6_init` Initialization function. 
```c
err_t flash6_init ( flash6_t *ctx, flash6_cfg_t *cfg );
```

- `flash6_write_memory_data` Function used for writing in memory. 
```c
void flash6_write_memory_data ( flash6_t *ctx, uint32_t addr, uint8_t *data_buf, uint16_t buf_size );
```
 
- `flash6_read_memory_data` Function used for reading from memory. 
```c
void flash6_read_memory_data ( flash6_t *ctx, uint32_t addr, uint8_t *data_buf, uint16_t buf_size );
```

- `flash6_erase_memory_segment` Function for eraseing segment. 
```c
void flash6_erase_memory_segment ( flash6_t *ctx, uint8_t segment, uint32_t start_addr );
```

### Application Init

> Initializes driver, resets device and tests communication.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    flash6_cfg_t cfg;

    uint8_t manufacture_id;
    uint8_t device_id;

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

    flash6_cfg_setup( &cfg );
    FLASH6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flash6_init( &flash6, &cfg );

    flash6_software_reset( &flash6 );
    Delay_ms ( 100 );

    flash6_get_manufacture_device_id( &flash6, &manufacture_id, &device_id );
    log_printf( &logger, "\r\n ------> MANUFACTURE ID: 0x%x \r\n", manufacture_id );
    log_printf( &logger, " ------> DEVICE ID: 0x%x \r\n \r\n", device_id );
    Delay_ms ( 1000 );
}
```

### Application Task

> Clears the memory sector, writes "MikroE" to device memory
> and then reads it and sends it to log every 2 sec.

```c
void application_task ( void )
{
    uint32_t start_addr;
    char read_buff[ 50 ];
    uint8_t cnt;
    
    start_addr = 0x002000;

    log_printf( &logger, " ---> Erase sector  \r\n" );
    flash6_erase_memory_segment( &flash6, FLASH6_CMD_SECTOR_ERASE_4KB, start_addr );
    Delay_ms ( 500 );
    
    log_printf( &logger, " ---> Write in memory ... \r\n" );
    flash6_write_memory_data( &flash6, start_addr, &write_buf[ 0 ], 9 );
    log_printf( &logger, " ---> Read from memory \r\n" );
    flash6_read_memory_data( &flash6, start_addr, read_buff, 9 );

    log_printf( &logger, "---->>>> " );
    
    log_printf( &logger, "%s ", read_buff );
    Delay_ms ( 100 );
    log_printf( &logger, "----------------------------------\r\n" );
    
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
