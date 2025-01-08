
---
# Scanner Click

> [Scanner Click](https://www.mikroe.com/?pid_product=MIKROE-4108) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4108&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example reads data from Scanner Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Scanner

### Example Key Functions

- `scanner_cfg_setup` Config Object Initialization function. 
```c
void scanner_cfg_setup ( scanner_cfg_t *cfg );
``` 
 
- `scanner_init` Initialization function. 
```c
err_t scanner_init ( scanner_t *ctx, scanner_cfg_t *cfg );
```

- `scanner_clock` Pulse function. 
```c
void scanner_clock ( scanner_t *ctx );
```
 
- `scanner_serial_write_reg` Write function. 
```c
void scanner_serial_write_reg ( scanner_t *ctx, uint8_t reg_adr, uint8_t write_data );
```

- `scanner_read_pixel` Read pixels. 
```c
void scanner_read_pixel ( scanner_t *ctx, uint8_t *pixel_data );
```

### Application Init

> Initializes the driver and starts up the module.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    scanner_cfg_t cfg;

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
    log_info( &logger, "--->>> APP INIT <<<---\r\n" );

    //  Click initialization.

    scanner_cfg_setup( &cfg );
    SCANNER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    scanner_init( &scanner, &cfg );

    Delay_ms ( 300 );

    scanner_startup( &scanner );
    Delay_ms ( 100 );
    
    scanner_serial_write_reg( &scanner, SCANNER_REG_MODE, SCANNER_DATA_NORMAL_MODE );
    
    for ( uint8_t data_cnt = 0; data_cnt < 3; )
    {
        scanner_serial_write_reg( &scanner, SCANNER_REG_OFFSET_LEFT + ( 2 * data_cnt ), 25 );
        data_cnt++;
        scanner_serial_write_reg( &scanner, SCANNER_REG_GAIN_LEFT + ( 2 * data_cnt ), 25 );
        data_cnt++;
    }
    log_printf( &logger, "--->>> APP TASK <<<--- \r\n" );
}
```

### Application Task

> Reads the array of 102 pixels and displays the results on the USB UART as frequently as possible.

```c
void application_task ( void )
{
    uint8_t pixels[ 102 ];
    scanner_read_pixel( &scanner, pixels );
    
    log_printf( &logger, "left center right\r\n" );
    for ( uint8_t cnt = 0; cnt < 34; cnt++ )
    {
        log_printf( &logger, " %u   %u   %u \r\n", ( uint16_t ) pixels[ cnt ], 
                                                   ( uint16_t ) pixels[ cnt + 34 ], 
                                                   ( uint16_t ) pixels[ cnt + 68 ] );
    }
    log_printf( &logger, "----------------\r\n" );
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
