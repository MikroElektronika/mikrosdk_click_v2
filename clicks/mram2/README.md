
---
# MRAM 2 Click

> [MRAM 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4232) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4232&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of MRAM 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mram2

### Example Key Functions

- `mram2_cfg_setup` Config Object Initialization function.
```c
void mram2_cfg_setup ( mram2_cfg_t *cfg ); 
```

- `mram2_init` Initialization function.
```c
err_t mram2_init ( mram2_t *ctx, mram2_cfg_t *cfg );
```

- `mram2_wren` Write Enable function
```c
void mram2_wren ( mram2_t *ctx );
```

- `mram2_read` Read Data Bytes function
```c
void mram2_read ( mram2_t *ctx, uint32_t mem_adr, uint8_t *rd_data, uint8_t n_bytes );
```

- `mram2_write` Write Data Bytes function
```c
void mram2_write ( mram2_t *ctx, uint32_t mem_adr, uint8_t *wr_data, uint8_t n_bytes );
```

### Application Init

> Initializes the driver, sets the write protect and disables the hold signal.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mram2_cfg_t cfg;

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

    mram2_cfg_setup( &cfg );
    MRAM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mram2_init( &mram2, &cfg );

    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "   MRAM 2 Click     \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    mram2_write_protect( &mram2, MRAM2_WP_ENABLE );
    mram2_hold( &mram2, MRAM2_HLD_DISABLE );
    log_printf( &logger, "   Initialized      \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> Writes "MikroE" into the first 6 memory locations, and then reads it back 
> and displays it to the USB UART approximately every 5 seconds.

```c
void application_task ( void )
{
    mram2_wren( &mram2 );
    log_printf( &logger, "Write enabled!\r\n" );
    Delay_ms ( 100 );
    log_printf( &logger, "Writing \"%s\" to memory...\r\n", val_in );
    mram2_write( &mram2, 0x000000, &val_in[ 0 ], 6 );
    Delay_ms ( 100 );
    mram2_wrdi ( &mram2 );
    log_printf( &logger, "Write disabled!\r\n" );
    Delay_ms ( 100 );
    mram2_read ( &mram2, 0x000000, &val_out[ 0 ], 6 );
    log_printf( &logger, "Read data : %s\r\n", val_out );
    
    log_printf( &logger, "-------------------\r\n" );
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
