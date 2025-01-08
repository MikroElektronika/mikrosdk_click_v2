
---
# RN4870 Click

> [RN4870 Click](https://www.mikroe.com/?pid_product=MIKROE-2543) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2543&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART GSM/IOT type

# Software Support

## Example Description

> This example reads and processes data from RN4870 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rn4870

### Example Key Functions

- `rn4870_cfg_setup` Config Object Initialization function. 
```c
void rn4870_cfg_setup ( rn4870_cfg_t *cfg );
``` 
 
- `rn4870_init` Initialization function. 
```c
err_t rn4870_init ( rn4870_t *ctx, rn4870_cfg_t *cfg );
```

- `rn4870_read` This function gets message from 'void rn4870_receive function if flag was set. This function replaces '*' (character with end of string) with '0x00' and stores received message to process_buffer. 
```c
uint8_t rn4870_read ( rn4870_t *ctx, uint8_t *process_buffer );
```
 
- `rn4870_receive` The function receives character by waits for '#' - character to start parsing message, waits for '*' - character to stop parsing message and sets flag if whole and properly formated message is received. 
```c
void rn4870_receive ( rn4870_t *ctx, char tmp );
```

- `rn4870_connect` The function connects to slave device with desired register address by secures the connection and entering data stream mode. 
```c
void rn4870_connect ( rn4870_t *ctx, char *p_addr );
```

### Application Init

> Initializes UART driver. Initializes device and parser.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rn4870_cfg_t cfg;

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

    rn4870_cfg_setup( &cfg );
    RN4870_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rn4870_init( &rn4870, &cfg );

    dev_type = RN4870_DEVICETYPE_MASTER;

    if ( dev_type == RN4870_DEVICETYPE_MASTER )
    {
        rn4870_initialize( &rn4870, &RN4870_ADDR_MASTER[ 0 ] );
    }
    else if ( dev_type == RN4870_DEVICETYPE_SLAVE )
    {
        rn4870_initialize( &rn4870, &RN4870_ADDR_SLAVE[ 0 ] );
        ptr = &receive_buffer[ 7 ];
    }

    memset( &rn4870.device_buffer, 0, 255 );
    log_printf( &logger, " >>> app init done <<<  \r\n" );
}
```

### Application Task

> If 'MASTER' - connects to 'SLAVE', sends message and disconnects. If 'SLAVE' - waits for connect request 
> and message from 'MASTER' and LOGs received message.

```c
void application_task ( void )
{
    rn4870_process(  );
    if ( dev_type == RN4870_DEVICETYPE_MASTER )
    {
        rn4870_connect( &rn4870, &RN4870_ADDR_SLAVE[ 0 ] );
        log_printf( &logger, ">>> sending data  <<<\r\n" );
        rn4870_send( &rn4870, RN4870_MTYPE_MSG, RN4870_DTYPE_STRING, RN4870_ID_MASTER, &message_payload[ 0 ] );
        rn4870_disconnect( &rn4870 );
    }
    else if ( dev_type == RN4870_DEVICETYPE_SLAVE )
    {
        msg_flag = rn4870_read( &rn4870, &receive_buffer[ 0 ] );

        if ( msg_flag == 1 )
        {
            log_printf( &logger, ">>> data received <<<\r\n" );
            log_printf( &logger, ">>> data : " );
            log_printf( &logger, "%s\r\n", ptr );     
        }
    }
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
