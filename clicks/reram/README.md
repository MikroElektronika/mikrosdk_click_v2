
---
# ReRAM Click

> [ReRAM Click](https://www.mikroe.com/?pid_product=MIKROE-3641) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3641&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nemanja Medakovic
- **Date**          : Oct 2019.
- **Type**          : SPI type

# Software Support

## Example Description

>
> This example demonstrates the use of the ReRAM Click board.
>

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Reram

### Example Key Functions

- `reram_cfg_setup` Configuration Object Setup function. 
```c
void reram_cfg_setup ( reram_cfg_t *cfg );
```

- `reram_init` Click Initialization function. 
```c
reram_err_t reram_init ( reram_t *ctx, reram_cfg_t *cfg );
```

- `reram_default_cfg` Click Default Configuration function. 
```c
void reram_default_cfg ( reram_t *ctx );
```

- `reram_send_cmd` Command Send function. 
```c
reram_err_t reram_send_cmd ( reram_t *ctx, reram_spi_data_t cmd_code );
```
 
- `reram_read_status` Status Read function. 
```c
reram_spi_data_t reram_read_status ( reram_t *ctx );
```

- `reram_write_memory` Memory Write function. 
```c
reram_err_t reram_write_memory ( reram_t *ctx, uint32_t mem_addr, reram_spi_data_t *data_in, uint16_t n_bytes );
```

### Application Init

>
> Initializes SPI serial interface and puts a device to the initial state.
> Data from 0 to 255 will be written in memory block from address 0x0 to address 0xFF.
>

```c
void application_init( void )
{
    reram_cfg_t reram_cfg;
    log_cfg_t logger_cfg;

    //  Click object initialization.
    reram_cfg_setup( &reram_cfg );
    RERAM_MAP_MIKROBUS( reram_cfg, MIKROBUS_1 );
    reram_init( &reram, &reram_cfg );

    //  Click start configuration.
    reram_default_cfg( &reram );

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( logger_cfg );
    log_init( &logger, &logger_cfg );
    
    reram_wake_up( &reram );
    
    uint32_t id_data = reram_read_id( &reram );
    
    if ( RERAM_ID_DATA != id_data )
    {
        log_printf( &logger, "***  ReRAM Error ID  ***\r\n" );
        for( ; ; );
    }
    else
    {    
        log_printf( &logger, "***  ReRAM Initialization Done  ***\r\n" );
        log_printf( &logger, "***********************************\r\n" );
    }


    reram_send_cmd( &reram, RERAM_CMD_WREN );
    Delay_ms ( 1000 );
}
```

### Application Task

>
> Reads same memory block starting from address 0x0 to address 0xFF and
> sends memory content to USB UART, to verify memory write operation.
>

```c
void application_task( void )
{
    reram_spi_data_t data_out;
    static uint16_t mem_addr = RERAM_MEM_ADDR_START;

    reram_read_memory( &reram, mem_addr, &data_out, 1 );

    log_printf( &logger, "* Memory Address [0x%X] : %u", mem_addr, data_out );
    log_write( &logger, "", LOG_FORMAT_LINE );

    if (mem_addr < 0xFF)
    {
        mem_addr++;
    }
    else
    {
        mem_addr = RERAM_MEM_ADDR_START;
    }

    Delay_ms ( 500 );
}
```

### Note

>
> Write Enable Latch is reset after the following operations:
>  - After 'Write Disable'command recognition.
>  - The end of writing process after 'Write Status' command recognition.
>  - The end of writing process after 'Write Memory' command recognition.
>
> Data will not be written in the protected blocks of the ReRAM array.
>  - Upper 1/4 goes from address 0x60000 to 0x7FFFF.
>  - Upper 1/2 goes from address 0x40000 to 0x7FFFF.
>  - The entire ReRAM array goes from address 0x00000 to 0x7FFFF.
>

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
