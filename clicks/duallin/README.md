
---
# Dual LIN Click

> [Dual LIN Click](https://www.mikroe.com/?pid_product=MIKROE-3870) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3870&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type

# Software Support

## Example Description

> This example reads and processes data from Dual LIN Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DualLin

### Example Key Functions

- `duallin_cfg_setup` Config Object Initialization function. 
```c
void duallin_cfg_setup ( duallin_cfg_t *cfg );
``` 
 
- `duallin_init` Initialization function. 
```c
err_t duallin_init ( duallin_t *ctx, duallin_cfg_t *cfg );
```

- `duallin_bus1_status` Sets state of RST pin. 
```c
void duallin_bus1_status( duallin_t *ctx, uint8_t state );
```
 
- `duallin_bus2_status` Sets state of  CS pin. 
```c
void duallin_bus2_status( duallin_t *ctx, uint8_t state );
```

- `duallin_send_command` Send command. 
```c
void duallin_send_command ( duallin_t *ctx, char *command );
```

### Application Init

> Initializes driver, and sets bus.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    duallin_cfg_t cfg;

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

    duallin_cfg_setup( &cfg );
    DUALLIN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    duallin_init( &duallin, &cfg );

    duallin_bus1_status( &duallin, DUALLIN_PIN_STATE_HIGH );
    duallin_bus2_status( &duallin, DUALLIN_PIN_STATE_LOW );
    Delay_ms ( 100 );
}
```

### Application Task

> Reads the received data.

```c
void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    duallin_process( );
#endif    

#ifdef DEMO_APP_TRANSMITER
    duallin_process( );

    if ( send_data_cnt = 2 )
    {
        duallin_send_command( &duallin, TEXT_TO_SEND );
        duallin_process( );
        send_data_cnt = 0;
    }
    else
    {
        send_data_cnt++;
    }    
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
