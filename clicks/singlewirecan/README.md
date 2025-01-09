
---
# Single Wire CAN Click

> [Single Wire CAN Click](https://www.mikroe.com/?pid_product=MIKROE-4225) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4225&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrate the use of Single Wire CAN Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SingleWireCan

### Example Key Functions

- `singlewirecan_cfg_setup` Config Object Initialization function. 
```c
void singlewirecan_cfg_setup ( singlewirecan_cfg_t *cfg );
``` 
 
- `singlewirecan_init` Initialization function. 
```c
err_t singlewirecan_init ( singlewirecan_t *ctx, singlewirecan_cfg_t *cfg );
```

- `singlewirecan_set_operating_mode` The function set desired operating mode of NCV7356 Single Wire CAN Transceiver. 
```c
void singlewirecan_set_operating_mode ( singlewirecan_t *ctx, uint8_t op_mode );
```
 
- `singlewirecan_generic_write` This function write specified number of bytes. 
```c
void singlewirecan_generic_write ( singlewirecan_t *ctx, char *data_buf, uint16_t len );
```

- `singlewirecan_generic_read` This function reads a desired number of data bytes. 
```c
int32_t singlewirecan_generic_read ( singlewirecan_t *ctx, char *data_buf, uint16_t max_len );
```

### Application Init

> Initializes the driver and configures the Click for the normal operation mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    singlewirecan_cfg_t cfg;

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

    singlewirecan_cfg_setup( &cfg );
    SINGLEWIRECAN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    singlewirecan_init( &singlewirecan, &cfg );
    Delay_ms ( 100 );

    singlewirecan_set_operating_mode( &singlewirecan, SINGLEWIRECAN_OPERATING_MODE_NORMAL );
    log_info( &logger, "---- Normal Operation Mode ----" );
    Delay_ms ( 100 );
}
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c
void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    singlewirecan_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    singlewirecan_generic_write( &singlewirecan, TEXT_TO_SEND, 8 );
    log_info( &logger, "---- Data sent ----" );
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
