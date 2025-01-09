
---
# nvSRAM 2 Click

> [nvSRAM 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4423) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4423&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example using nvSRAM 2 Click based on CY14B101Q which is combines a 1-Mbit nvSRAM with a nonvolatile element in each memory cell with serial SPI interface. The memory is organized as 128K words of 8 bits each.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.nvSRAM2

### Example Key Functions

- `nvsram2_cfg_setup` Config Object Initialization function.
```c
void nvsram2_cfg_setup ( nvsram2_cfg_t *cfg );
```

- `nvsram2_init` Initialization function.
```c
err_t nvsram2_init ( nvsram2_t *ctx, nvsram2_cfg_t *cfg );
```

- `nvsram2_default_cfg` Click Default Configuration function.
```c
err_t nvsram2_default_cfg ( nvsram2_t *ctx );
```

- `nvsram2_hold` The function enables hold operation by setting the state of the HOLD ( PWM ) pin depending on the function argument.
```c
void nvsram2_hold ( nvsram2_t *ctx, uint8_t en_hold );
```

- `nvsram2_set_cmd` The function sends desired command to the CY14B101Q2A memory on nvSRAM 2 Click board.
```c
void nvsram2_set_cmd ( nvsram2_t *ctx, uint8_t cmd );
```

- `nvsram2_read_id` The function performs the device ID read of the CY14B101Q2A memory on nvSRAM 2 Click board.
```c
uint32_t nvsram2_read_id ( nvsram2_t *ctx );
```

### Application Init

> Initializes SPI and UART LOG, sets CS and PWM pins as outputs. Disables hold, sets write enable latch, targets the memory address at 12345 ( 0x00003039 ) for burst write starting point and writes data which is also displayed on the log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;               /**< Logger config object. */
    nvsram2_cfg_t nvsram2_cfg;       /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    nvsram2_cfg_setup( &nvsram2_cfg );
    NVSRAM2_MAP_MIKROBUS( nvsram2_cfg, MIKROBUS_1 );
    err_t init_flag  = nvsram2_init( &nvsram2, &nvsram2_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    nvsram2_default_cfg ( &nvsram2 );
    log_info( &logger, " Application Task " );

    memory_addr = 12345;

    nvsram2_burst_write( &nvsram2, memory_addr, demo_data, 9 );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "-> Write data : %s \r\n", demo_data );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that demonstrates the use of the nvSRAM 2 Click board. In this example, the data is read from the targeted memory address. The results are being sent to the Usart Terminal. This task repeats every 5 sec.

```c
void application_task ( void ) 
{
    nvsram2_burst_read( &nvsram2, memory_addr, rx_data, 9 );
    log_printf( &logger, "-----------------------\r\n"  );
    log_printf( &logger, "<- Read data  : %s \r\n", rx_data );
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
