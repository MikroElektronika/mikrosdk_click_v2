
---
# RS232 2 Click

> [RS232 2 Click](https://www.mikroe.com/?pid_product=MIKROE-1582) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1582&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type

# Software Support

## Example Description

> This example reads and processes data from RS232 2 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs2322

### Example Key Functions

- `rs2322_cfg_setup` Config Object Initialization function. 
```c
void rs2322_cfg_setup ( rs2322_cfg_t *cfg );
``` 
 
- `rs2322_init` Initialization function. 
```c
err_t rs2322_init ( rs2322_t *ctx, rs2322_cfg_t *cfg );
```

- `rs2322_set_cts` This function sets CTS pin state. 
```c
void rs2322_set_cts ( rs2322_t *ctx, uint8_t state );
```
 
- `rs2322_get_dtr` This function get DTR pin state. 
```c
uint8_t rs2322_get_dtr ( rs2322_t *ctx );
```

- `rs2322_send_command` Function for send command. 
```c
void rs2322_send_command ( rs2322_t *ctx, char *command );
```

### Application Init

> Initializes driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rs2322_cfg_t cfg;

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

    rs2322_cfg_setup( &cfg );
    RS2322_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs2322_init( &rs2322, &cfg );
}
```

### Application Task

> Reads the received data.

```c
void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    rs2322_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITER
    rs2322_send_command( &rs2322, TEXT_TO_SEND );
    rs2322_process( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif    
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
