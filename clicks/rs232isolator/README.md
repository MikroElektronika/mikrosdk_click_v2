
---
# RS232 Isolator Click

> [RS232 Isolator Click](https://www.mikroe.com/?pid_product=MIKROE-2864) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2864&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type

# Software Support

## Example Description

> This example reads and processes data from RS232 Isolator Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rs232Isolator

### Example Key Functions

- `rs232isolator_cfg_setup` Config Object Initialization function. 
```c
void rs232isolator_cfg_setup ( rs232isolator_cfg_t *cfg );
``` 
 
- `rs232isolator_init` Initialization function. 
```c
err_t rs232isolator_init ( rs232isolator_t *ctx, rs232isolator_cfg_t *cfg );
```

- `rs232_2_set_rts` Function settings RTS state. 
```c
void rs232_2_set_rts ( rs232isolator_t *ctx, uint8_t state );
```
 
- `rs232_2_get_cts` Read CTS state. 
```c
uint8_t rs232_2_get_cts ( rs232isolator_t *ctx );
```

- `rs232isolator_send_command` Function for send command. 
```c
void rs232isolator_send_command ( rs232isolator_t *ctx, char *command );
```

### Application Init

> Initializes driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rs232isolator_cfg_t cfg;

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

    rs232isolator_cfg_setup( &cfg );
    RS232ISOLATOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs232isolator_init( &rs232isolator, &cfg );
}
```

### Application Task

> Reads the received data.

```c
void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    rs232isolator_process( );
#endif
    
#ifdef DEMO_APP_TRANSMITER
    rs232isolator_send_command( &rs232isolator, TEXT_TO_SEND );
    rs232isolator_process( );
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
