
---
# GNSS3 Click

> [GNSS3 Click](https://www.mikroe.com/?pid_product=MIKROE-1895) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1895&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : apr 2020.
- **Type**          : UART GPS/GNSS type

# Software Support

## Example Description

> This example demonstrates the use of GNSS 3 Click by reading and displaying the GPS coordinates.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Gnss3

### Example Key Functions

- `gnss3_cfg_setup` Config Object Initialization function. 
```c
void gnss3_cfg_setup ( gnss3_cfg_t *cfg );
``` 
 
- `gnss3_init` Initialization function. 
```c
err_t gnss3_init ( gnss3_t *ctx, gnss3_cfg_t *cfg );
```

- `gnss3_parse_gngga` GNSS 3 parse GNGGA function. 
```c
err_t gnss3_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );
```
 
- `gnss3_generic_read` Generic read function. 
```c
int32_t gnss3_generic_read ( gnss3_t *ctx, char *data_buf, uint16_t max_len );
```

- `gnss3_module_wakeup` Wake-up module. 
```c
void gnss3_module_wakeup ( gnss3_t *ctx );
```

### Application Init

> Initializes the driver and resets the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    gnss3_cfg_t cfg;

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

    gnss3_cfg_setup( &cfg );
    GNSS3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gnss3_init( &gnss3, &cfg );

    gnss3_module_wakeup( &gnss3 );
    Delay_ms ( 1000 );
}
```

### Application Task

> Reads the received data, parses the GNGGA info from it, and once it receives the position fix it will start displaying the coordinates on the USB UART.

```c
void application_task ( void )
{
    gnss3_process( &gnss3 );
    if ( app_buf_len > ( sizeof ( ( char * ) GNSS3_RSP_GNGGA ) + GNSS3_GNGGA_ELEMENT_SIZE ) ) 
    {
        gnss3_parser_application( app_buf );
    }
}
```

### Note

> The default baud rate for communication UART is set to 9600. If you receive
a Click board on which the default baud rate for UART is set differently,
you will need to change the setting in the gnss13_setup_cfg function.

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
