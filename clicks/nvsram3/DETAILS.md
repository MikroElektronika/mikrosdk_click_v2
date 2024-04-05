
---
# nvSRAM 3 click

nvSRAM 3 Click is a compact add-on board that contains the most reliable nonvolatile memory.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nvsram3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/nvsram-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the nvSRAM3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for nvSRAM3 Click driver.

#### Standard key functions :

- `nvsram3_cfg_setup` Config Object Initialization function.
```c
void nvsram3_cfg_setup ( nvsram3_cfg_t *cfg );
```

- `nvsram3_init` Initialization function.
```c
NVSRAM3_RETVAL nvsram3_init ( nvsram3_t *ctx, nvsram3_cfg_t *cfg );
```

- `nvsram3_default_cfg` Click Default Configuration function.
```c
void nvsram3_default_cfg ( nvsram3_t *ctx );
```

#### Example key functions :

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

## Example Description

> The demo application shows how to write/read data to/from nvSRAM memory.
> It also sets RTC date and time, then reads it in an infinite loop and displays results on USB UART each second.

**The demo application is composed of two sections :**

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
    log_printf( &logger, "     nvSRAM 3 click    \r\n" );
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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.nvSRAM3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
