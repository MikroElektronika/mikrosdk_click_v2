
---
# LLC SPI Click

> [LLC SPI Click](https://www.mikroe.com/?pid_product=MIKROE-3298) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3298&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application is converter for logic signals.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Llcspi

### Example Key Functions

- `llcspi_cfg_setup` Config Object Initialization function. 
```c
void llcspi_cfg_setup ( llcspi_cfg_t *cfg );
``` 
 
- `llcspi_init` Initialization function. 
```c
err_t llcspi_init ( llcspi_t *ctx, llcspi_cfg_t *cfg );
```

- `llcspi_generic_write` LLC SPI write. 
```c
void llcspi_generic_write ( llcspi_t *ctx, uint8_t *p_buf, uint16_t n_bytes );
```
 
- `llcspi_generic_read` LLC SPI read. 
```c
void llcspi_generic_read ( llcspi_t *ctx, uint8_t *p_buf, uint16_t n_bytes );
```

- `llcspi_generic_transfer` LLC SPI transfer. 
```c
void llcspi_generic_transfer ( llcspi_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );
```

### Application Init

> Initialization device init

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    llcspi_cfg_t cfg;

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

    llcspi_cfg_setup( &cfg );
    LLCSPI_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    llcspi_init( &llcspi, &cfg );
}
```

### Application Task

> Counter passes through the loop and logs the value of the counter on the bargraph display

```c
void application_task ( void )
{
    uint16_t convert;
    uint8_t tmp[ 2 ];
    uint8_t cnt;

    // BarGraph display
    for ( cnt = 0; cnt <= 10; cnt++ )
    {
        convert  = ( uint16_t ) ( ( 1 << cnt ) - 1 );
        tmp[ 1 ] = ( convert & 0x00FF );
        tmp[ 0 ] = ( convert & 0xFF00 ) >> 8;
    
        llcspi_generic_write( &llcspi, tmp, 2 );
        
        Delay_ms ( 1000 );
    }
}
```

### Note
 
> Connection between BarGraph and LLC-SPI is made through SPI interface.
> You can connect a BarGraph Click to LLC-SPI Click with the wires to make connection between Click boards.
> We use the BarGraph Click to demonstrate the functions of the LLC-SPI Click.

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
