
---
# RS485 3V3 Click

> [RS485 3V3 Click](https://www.mikroe.com/?pid_product=MIKROE-989) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-989&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from RS485 3V3 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RS4853V3

### Example Key Functions

- `rs4853v3_cfg_setup` Config Object Initialization function.
```c
void rs4853v3_cfg_setup ( rs4853v3_cfg_t *cfg );
```

- `rs4853v3_init` Initialization function.
```c
err_t rs4853v3_init ( rs4853v3_t *ctx, rs4853v3_cfg_t *cfg );
```

- `rs4853v3_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t rs4853v3_generic_read ( rs4853v3_t *ctx, char *data_buf, uint16_t max_len );
```

- `rs4853v3_send_command` This function sends a command by using UART serial interface.
```c
void rs4853v3_send_command ( rs4853v3_t *ctx, char *command );
```

### Application Init

> Initializes driver and wake-up module.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;
    rs4853v3_cfg_t cfg;

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

    //  Click initialization.

    rs4853v3_cfg_setup( &cfg );
    RS4853V3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs4853v3_init( &rs4853v3, &cfg );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "    Send data:    \r\n" );
    log_printf( &logger, "      MikroE      \r\n" );
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "  Transmit data   \r\n" );
    Delay_ms ( 1000 );

#endif
    
#ifdef DEMO_APP_RECEIVER 
    log_printf( &logger, "------------------\r\n" );

    log_printf( &logger, "   Receive data  \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
        
    log_printf( &logger, "------------------\r\n" );
}
```

### Application Task

> Reads the received data and parses it.

```c
void application_task ( void ) 
{  
#ifdef DEMO_APP_RECEIVER 
    rs4853v3_process( );
    if ( current_rsp_buf > 0 ) {
        log_printf( &logger, "%s", current_rsp_buf );
        rs4853v3_clear_current_rsp_buf( );
    }
#endif 

#ifdef DEMO_APP_TRANSMITTER
    rs4853v3_send_command( &rs4853v3, &demo_message[ 0 ] );
    log_printf( &logger, "\t%s",  &demo_message[ 0 ] );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "------------------\r\n" ); 
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
