
---
# nvSRAM Click

> [nvSRAM Click](https://www.mikroe.com/?pid_product=MIKROE-4441) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4441&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This is an example that demonstrates the use of the nvSRAM Click board. In this example, we write and then read data from nvSRAM memory. Results are being sent to the Usart Terminal where you can track their changes. All data logs write on USB uart changes approximately for every 5 sec.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.nvSRAM

### Example Key Functions

- `nvsram_cfg_setup` Config Object Initialization function.
```c
void nvsram_cfg_setup ( nvsram_cfg_t *cfg );
```

- `nvsram_init` Initialization function.
```c
err_t nvsram_init ( nvsram_t *ctx, nvsram_cfg_t *cfg );
```

- `nvsram_send_cmd` The function sends the desired command to the CY14B101J2 1-Mbit (128K � 8) Serial (I2C) nvSRAM on nvSRAM Click board.
```c
void nvsram_send_cmd ( nvsram_t *ctx, uint8_t cmd );
```

- `nvsram_memory_write` The function writes a sequential data starting of the targeted 17-bit memory address
```c
void nvsram_memory_write ( nvsram_t *ctx, uint32_t mem_adr, uint8_t *p_tx_data, uint16_t n_bytes );
```

- `nvsram_memory_read` The function read a sequential data starting from the targeted 17-bit memory address
```c
void nvsram_memory_read ( nvsram_t *ctx, uint32_t mem_adr, uint8_t *p_rx_data, uint16_t n_bytes );
```

### Application Init

> Initialization driver enables - I2C, lock Serial Number write, disable Block Protection and enable Memory Write, also write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nvsram_cfg_t nvsram_cfg;  /**< Click config object. */

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
    mem_addr = 1024;

    // Click initialization.
    nvsram_cfg_setup( &nvsram_cfg );
    NVSRAM_MAP_MIKROBUS( nvsram_cfg, MIKROBUS_1 );
    err_t init_flag = nvsram_init( &nvsram, &nvsram_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_printf( &logger,  "  Serial Number Lock   \r\n" );
    log_printf( &logger, " None Block Protection \r\n" );
    nvsram_reg_write( &nvsram, NVSRAM_MEM_CTL_REG, NVSRAM_SNL | NVSRAM_BP_NONE );
    Delay_ms ( 100 );
    log_printf( &logger, " Enable Memory Write \r\n" );
    nvsram_enable_memory_write( &nvsram, NVSRAM_WRITE_MEMORY_ENABLE );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task \r\n" );
}
```

### Application Task

> Writing data to a memory address, then reading it back and logging it onto uart terminal.

```c
void application_task ( void ) 
{
    log_printf( &logger, "  Write data : %s \r\n", demo_data );
    nvsram_memory_write( &nvsram, mem_addr, &demo_data[ 0 ], 9 );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    Delay_ms ( 100 );

    nvsram_memory_read( &nvsram, mem_addr, &read_data[ 0 ], 9 );
    log_printf( &logger, "  Read data  : %s \r\n", read_data );
    log_printf( &logger, "----------------------- \r\n" );
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
