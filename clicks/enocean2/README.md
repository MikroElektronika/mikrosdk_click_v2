
---
# EnOcean 2 Click

> [EnOcean 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2521) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2521&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : UART GSM/IOT type

# Software Support

## Example Description

> This example reads and processes data from EnOcean 2 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EnOcean2

### Example Key Functions

- `enocean2_cfg_setup` Config Object Initialization function. 
```c
void enocean2_cfg_setup ( enocean2_cfg_t *cfg );
``` 
 
- `enocean2_init` Initialization function. 
```c
err_t enocean2_init ( enocean2_t *ctx, enocean2_cfg_t *cfg );
```

- `enocean2_init_rx_buff` EnOcean Serial Protocol ( ESP3 ) module initialization. 
```c
void enocean2_init_rx_buff ( enocean2_t *ctx, enocean2_ring_buffer_t *rb, enocean2_rx_data_t *rx_str );
```
 
- `enocean2_rx` The function push recieved character to ring buffer. 
```c
uint8_t enocean2_rx ( enocean2_ring_buffer_t *rb, uint8_t rx_data );
```

- `enocean2_packet_recieve` Implements state machine for recieving packets. It should be called in loop. 
```c
uint8_t enocean2_packet_recieve ( enocean2_t *ctx, enocean2_ring_buffer_t *rb );
```

### Application Init

> Initializes driver init and initializes chip and sets callback handler.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    enocean2_cfg_t cfg;

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

    enocean2_cfg_setup( &cfg );
    ENOCEAN2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    enocean2_init( &enocean2, &cfg );

    enocean2_rx_data.rx_buffer   = &rx_buffer[ 0 ];
    enocean2_rx_data.rx_size     = ENOCEAN2_RX_BUFFER_SIZE;
    enocean2_rx_data.data_buffer = &data_buffer[ 0 ];
    enocean2_rx_data.data_size   = ENOCEAN2_RX_BUFFER_SIZE;

    enocean2_init_rx_buff( &enocean2, &enocean2_rb, &enocean2_rx_data );
    enocean2_set_callback_handler( &enocean2, callback_handler );
}
```

### Application Task

> It checks if a switch is pressed, and logs an appropriate message to the uart terminal.

```c
void application_task ( void )
{
    enocean2_process( );
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
