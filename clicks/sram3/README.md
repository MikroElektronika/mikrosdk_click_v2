
---
# SRAM 3 Click

> [SRAM 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4293) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4293&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that shows the use of SRAM memory, using SRAM 3 Click. SRAM 3 Click is based on ANV32AA1W, and ANV32AA1W is a 1Mb serial SRAM with a non-volatile SONOS storage element included with each memory cell, 
organized as 128k words of 8 bits each. 
The devices are accessed by a high speed SPI-compatible bus. Specifically in this example, we used the high-speed SPI communication characteristics to write data to a specific registration address and read it.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SRAM3

### Example Key Functions

- `sram3_cfg_setup` Config Object Initialization function.
```c
void sram3_cfg_setup ( sram3_cfg_t *cfg );
```

- `sram3_init` Initialization function.
```c
err_t sram3_init ( sram3_t *ctx, sram3_cfg_t *cfg );
```

- `sram3_enable_write` This function is for enabling writing to memory, status register or user serial.
```c
void sram3_enable_write( sram3_t *ctx );
```

- `sram3_disable_write` Function for disabling writing to memory, status register or user serial.
```c
void sram3_disable_write( sram3_t *ctx );
```

- `sram3_protect_memory` Function which secures part of memory from writing.
```c
void sram3_protect_memory( sram3_t *ctx, uint8_t protect_range );
```

### Application Init

> Initialization SPI module, logger initalization and Click initialization.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;         /**< Logger config object. */
    sram3_cfg_t sram3_cfg;     /**< Click config object. */

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
    sram3_cfg_setup( &sram3_cfg );
    SRAM3_MAP_MIKROBUS( sram3_cfg, MIKROBUS_1 );
    err_t init_flag  = sram3_init( &sram3, &sram3_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {        
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    sram3_release_hold( &sram3 );
    Delay_ms ( 100 );
}
```

### Application Task

> First, we write the data to the registry address 0x00, and then we read the data from 0x00 address.

```c
void application_task ( void ) 
{
    char buff_out[ 10 ] = { 0 };
        
    log_printf( &logger, "Writing [ %s ] to memory...\r\n", buf );
    sram3_enable_write( &sram3 );
    sram3_write( &sram3, 0x00, &buf[0], 6 );

    Delay_ms ( 100 );
    sram3_read( &sram3, 0x00, &buff_out[0], 6 );
    Delay_ms ( 100 );
    log_printf( &logger, "Data read from memory: %s \r\n", buff_out );
    log_printf( &logger, "---------------------------------------------\r\n" );

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
