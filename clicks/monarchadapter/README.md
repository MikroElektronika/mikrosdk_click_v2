
---
# Monarch Adapter Click

> [Monarch Adapter Click](https://www.mikroe.com/?pid_product=MIKROE-4057) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4057&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from Monarch Adapter Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MonarchAdapter

### Example Key Functions

- `monarchadapter_cfg_setup` Config Object Initialization function. 
```c
void monarchadapter_cfg_setup ( monarchadapter_cfg_t *cfg );
``` 
 
- `monarchadapter_init` Initialization function. 
```c
err_t monarchadapter_init ( monarchadapter_t *ctx, monarchadapter_cfg_t *cfg );
```

- `monarchadapter_get_int_pin` Get INT pin state. 
```c
uint8_t monarchadapter_get_int_pin ( monarchadapter_t *ctx );
```
 
- `monarchadapter_get_rng_pin` Get RNG ( an ) pin state. 
```c
uint8_t monarchadapter_get_rng_pin ( monarchadapter_t *ctx );
```

- `monarchadapter_send_command` Function for send command. 
```c
void monarchadapter_send_command ( monarchadapter_t *ctx, char *command );
```

### Application Init

> Initializes the driver and checks the module firmware revision.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    monarchadapter_cfg_t cfg;

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

    monarchadapter_cfg_setup( &cfg );
    MONARCHADAPTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    monarchadapter_init( &monarchadapter, &cfg );

    monarchadapter_power_on( &monarchadapter );
    
    monarchadapter_send_command( &monarchadapter, MONARCH_CMD_AT );
    monarchadapter_process( );
    monarchadapter_send_command( &monarchadapter, MONARCH_CMD_ATE1 );
    monarchadapter_process( );
    monarchadapter_send_command( &monarchadapter, MONARCH_CMD_ATI );
    monarchadapter_process( );
    monarchadapter_send_command( &monarchadapter, MONARCH_CMD_ATI1 );
    monarchadapter_process( );
}
```

### Application Task

> Checks EPS Network Registration Status (+CEREG) every 3 seconds.

```c
void application_task ( void )
{
    monarchadapter_send_command( &monarchadapter, MONARCH_CMD_CEREG );
    monarchadapter_process( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Monarch GO and Monarch GO-GPS are certified for use on the Verizon network (LTE band 13) 
> with roadmap for global band support. Monarch module is not delivered as part of 
> the Click board package. For more information about module features please read 
> Monarch GO module specification.

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
