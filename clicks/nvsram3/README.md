
---
# nvSRAM 3 Click

> [nvSRAM 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4497) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4497&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> The demo application shows how to write/read data to/from nvSRAM memory.
> It also sets RTC date and time, then reads it in an infinite loop and displays results on USB UART each second.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.nvSRAM3

### Example Key Functions

- `nvsram3_cfg_setup` Config Object Initialization function.
```c
void nvsram3_cfg_setup ( nvsram3_cfg_t *cfg );
```

- `nvsram3_init` Initialization function.
```c
err_t nvsram3_init ( nvsram3_t *ctx, nvsram3_cfg_t *cfg );
```

- `nvsram3_default_cfg` Click Default Configuration function.
```c
void nvsram3_default_cfg ( nvsram3_t *ctx );
```

- `nvsram3_memory_write` This function write a desired number of data bytes starting from the selected memory address by using I2C serial interface.
```c
err_t nvsram3_memory_write ( nvsram3_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint8_t n_bytes );
```

- `nvsram3_memory_read` This function reads a desired number of data bytes starting from the selected memory address by using I2C serial interface.
```c
err_t nvsram3_memory_read ( nvsram3_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint8_t n_bytes );
```

- `nvsram3_get_rtc_time` This function get RTC time data structure.
```c
void nvsram3_get_rtc_time ( nvsram3_t *ctx, nvsram3_rtc_time_t *rtc_time );
```

### Application Init

> Initializes device, reads the device ID, writes desired message to memory and sets RTC date and time.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nvsram3_cfg_t nvsram3_cfg;  /**< Click config object. */

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

    nvsram3_cfg_setup( &nvsram3_cfg );
    NVSRAM3_MAP_MIKROBUS( nvsram3_cfg, MIKROBUS_1 );
    err_t init_flag = nvsram3_init( &nvsram3, &nvsram3_cfg );
    
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "     nvSRAM 3 Click    \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    
    nvsram3_default_cfg ( &nvsram3 );
    Delay_ms ( 100 );
    
    log_printf( &logger, " DEVICE ID: 0x%.8LX\r\n", nvsram3_get_device_id( &nvsram3 ) );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 100 );
    
    memory_addr = 0x10000;
    
    log_printf( &logger, "  Write data : %s", demo_data );
    nvsram3_memory_write( &nvsram3, memory_addr, &demo_data[ 0 ], 9 );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 1000 );
    
    date.day_of_week = 4;
    date.day = 31;
    date.month = 12;
    date.year = 2020;
    nvsram3_set_rtc_date( &nvsram3, date );
    Delay_ms ( 100 );
    
    time.hours = 23;
    time.min = 59;
    time.sec = 50;
    nvsram3_set_rtc_time( &nvsram3, time );
    Delay_ms ( 100 );
}
```

### Application Task

> Reads current date and time and then reads the message that we have previusly stored in the memory.
> All data is being logged on USB UART.

```c
void application_task ( void )
{
    nvsram3_get_rtc_time( &nvsram3, &time );
    nvsram3_get_rtc_date( &nvsram3, &date );
    
    if ( time.sec != new_sec ) 
    {
        log_printf( &logger, "  Date      : %.2d-%.2d-%.4d\r\n", ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
        log_printf( &logger, "  Time      : %.2d:%.2d:%.2d\r\n", ( uint16_t ) time.hours, ( uint16_t ) time.min, ( uint16_t ) time.sec );
        log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
        new_sec = time.sec;
        
        if ( date.year != c_year ) 
        {
            log_printf( &logger, "     Happy New Year    \r\n" );
            c_year = date.year;
        } 
        else 
        {
            nvsram3_memory_read( &nvsram3, memory_addr, &rx_data[ 0 ], 9 );
            log_printf( &logger, "  Read data : %s", rx_data );    
        }
               
        log_printf( &logger, "-----------------------\r\n" );
    } 
    else 
    {
        Delay_ms ( 500 );    
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
