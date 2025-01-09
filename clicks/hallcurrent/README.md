
---
# Hall Current Click

> [Hall Current Click](https://www.mikroe.com/?pid_product=MIKROE-1578) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1578&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> The application is current sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent

### Example Key Functions

- `hallcurrent_cfg_setup` Config Object Initialization function.
```c
void hallcurrent_cfg_setup ( hallcurrent_cfg_t *cfg ); 
```

- `hallcurrent_init` Initialization function.
```c
err_t hallcurrent_init ( hallcurrent_t *ctx, hallcurrent_cfg_t *cfg );
```

- `hallcurrent_read_data` Generic read 16-bit data function
```c
uint16_t hallcurrent_read_data ( hallcurrent_t *ctx );
```

- `hallcurrent_check_status` Check status of read data function.
```c
uint8_t hallcurrent_check_status ( hallcurrent_t *ctx );
```

- `hallcurrent_read_current` Read electric current function
```c
float hallcurrent_read_current ( hallcurrent_t *ctx );
```

### Application Init

> Initialization driver enable's - SPI and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    hallcurrent_cfg_t cfg;

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
    hallcurrent_cfg_setup( &cfg );
    HALLCURRENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent_init( &hallcurrent, &cfg );
    
    HALLCURRENT_SET_DATA_SAMPLE_EDGE;
    
    log_printf( &logger,"------------------------\r\n" );
    log_printf( &logger,  "       Hall Current     \r\n" );
    log_printf( &logger, "------------------------\r\n" );
}
```

### Application Task

> This is an example which demonstrates the use of Hall Current Click board.

```c
void application_task ( void )
{
    log_printf( &logger, " Current : %.3f A \r\n", hallcurrent_read_current( &hallcurrent ) );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
}
```## Application Output

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
