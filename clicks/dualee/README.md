
---
# Dual EE Click

> [Dual EE Click](https://www.mikroe.com/?pid_product=MIKROE-3762) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3762&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application writes data im memory and reads data from memory.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DualEE

### Example Key Functions

- `dualee_cfg_setup` Config Object Initialization function. 
```c
void dualee_cfg_setup ( dualee_cfg_t *cfg );
``` 
 
- `dualee_init` Initialization function. 
```c
err_t dualee_init ( dualee_t *ctx, dualee_cfg_t *cfg );
```

- `dualee_read` Generic write data function. 
```c
uint8_t dualee_read( dualee_t *ctx, uint32_t reg_address, uint8_t *data_buff, uint8_t n_bytes );
```
 
- `dualee_write` Generic write data function. 
```c
uint8_t dualee_write (  dualee_t *ctx, uint32_t reg_address, uint8_t *data_buff, uint8_t n_bytes );
```

### Application Init

> Initializes device init

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dualee_cfg_t cfg;

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

    dualee_cfg_setup( &cfg );
    DUALEE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dualee_init( &dualee, &cfg );

    log_printf( &logger, "*********** APPLICATION INIT ***********\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> Reads your command and then execute it

```c
void application_task ( )
{
    uint8_t write_dual;
    uint8_t read_dual;
    char demo_text[ 255 ];

    log_printf( &logger, "Writing data [MikroE]....\r\n" );
    write_dual = dualee_write( &dualee, page_address, write_data, 7 );
  
    if ( write_dual == DUALEE_ERROR_RW )
    {
        log_printf( &logger, "Error writing data!!!\r\n" );
        Delay_ms ( 1000 );
        return;
    }
    Delay_ms ( 100 );

    log_printf( &logger, "Reading data...\r\n" );
    read_dual = dualee_read( &dualee, page_address, demo_text, 7 );

    if ( read_dual == 0 )
    {
        log_printf( &logger, "Error reading data!!!\r\n" );
        Delay_ms ( 1000 );
        return;
    }
    Delay_ms ( 100 );
    log_printf( &logger, "Data from read page is: %s \r\n", demo_text );
    
    log_printf( &logger, "__________________________________\r\n" );
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
