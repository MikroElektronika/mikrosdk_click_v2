
---
# BT-EZ Click

> [BT-EZ Click](https://www.mikroe.com/?pid_product=MIKROE-4038) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4038&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from BT-EZ Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BtEz

### Example Key Functions

- `btez_cfg_setup` Config Object Initialization function. 
```c
void btez_cfg_setup ( btez_cfg_t *cfg );
``` 
 
- `btez_init` Initialization function. 
```c
err_t btez_init ( btez_t *ctx, btez_cfg_t *cfg );
```

- `btez_generic_write` Generic write function. 
```c
void btez_generic_write ( btez_t *ctx, char *data_buf, uint16_t len );
```
 
- `btez_generic_read` Generic read function. 
```c
int32_t btez_generic_read ( btez_t *ctx, char *data_buf, uint16_t max_len );
```

- `btez_send_command` Send command function. 
```c
void btez_send_command ( btez_t *ctx, char *command );
```

### Application Init

> Initializes the driver and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    btez_cfg_t cfg;

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

    btez_cfg_setup( &cfg );
    BTEZ_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    btez_init( &btez, &cfg );
    Delay_ms ( 100 );

    log_printf( &logger, "Configuring the module...\r\n" );
    config_mode = 1;
    
    btez_module_reset( &btez );
    btez_process( );
    btez_send_command( &btez, CMD_PING );
    btez_process( );
    btez_send_command( &btez, CMD_DEVICE_NAME );
    btez_process( );
    btez_send_command( &btez, CMD_SAVE );
    btez_process( );
    btez_send_command( &btez, CMD_GDN );
    btez_process( );
    
    config_mode = 0;
    log_printf( &logger, "The module has been configured.\r\n" );
    Delay_1sec( );
}
```

### Application Task

> Checks for the received data, reads it and replies with a certain message.

```c
void application_task ( void )
{
    btez_process( );
}
``` 
### Note

> We have used the Serial Bluetooth Terminal smartphone application for the test. 
> A smartphone and the Click board must be paired in order to exchange messages with each other.

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
