
---
# SPIRIT Click

> [SPIRIT Click](https://www.mikroe.com/?pid_product=MIKROE-2568) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2568&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from SPIRIT Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SPIRIT

### Example Key Functions

- `spirit_cfg_setup` Config Object Initialization function.
```c
void spirit_cfg_setup ( spirit_cfg_t *cfg );
```

- `spirit_init` Initialization function.
```c
err_t spirit_init ( spirit_t *ctx, spirit_cfg_t *cfg );
```

- `spirit_power_module` Function for power mode of SPIRIT Click.
```c
void spirit_power_module ( spirit_t *ctx, uint8_t power_state );
```

- `spirit_reset` Function for reseting SPIRIT Click.
```c
void spirit_reset ( spirit_t *ctx );
```

- `spirit_set_mode` Function for setting mode of SPIRIT Click.
```c
void spirit_set_mode ( spirit_t *ctx, uint8_t mode );
```

### Application Init

> Initializes the driver and configures the Click board.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;
    spirit_cfg_t cfg;

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

    spirit_cfg_setup( &cfg );
    SPIRIT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spirit_init( &spirit, &cfg );
    Delay_ms ( 1000 );

    log_info( &logger, "---- Configuring the module ----" );
    spirit_power_module( &spirit, SPIRIT_MODULE_WAKE_UP );
    spirit_reset( &spirit );
    spirit_set_mode( &spirit, SPIRIT_OPERATING_MODE );
    Delay_ms ( 1000 );
    log_printf( &logger, "COMMAND MODE\r\n" );
    spirit_send_cmd( &spirit, SPIRIT_CMD_ENTER_COMMAND_MODE );
    spirit_process( );
    log_printf( &logger, "FIRMWARE VERSION\r\n" );
    spirit_send_cmd( &spirit, SPIRIT_CMD_READ_MODULE_VERSION );
    spirit_process( );
    log_printf( &logger, "TXRX LED - OPEN DRAIN OUTPUT\r\n" );
    spirit_send_cmd_with_parameter( &spirit, SPIRIT_CMD_CFG_TXRX_LED, SPIRIT_PCFG_TXRXLED_OPEN_DRAIN );
    spirit_process( );
    log_printf( &logger, "STORE CONFIG\r\n" );
    spirit_send_cmd( &spirit, SPIRIT_CMD_STORE_CURRENT_CONFIG );
    spirit_process( );
    log_printf( &logger, "OPERATING MODE\r\n" );
    spirit_send_cmd( &spirit, SPIRIT_CMD_ENTER_OPERATING_MODE );
    spirit_process( );
    log_info( &logger, "---- The module has been configured ----" );
#ifdef DEMO_APP_RECEIVER
    log_info( &logger, "---- RECEIVER MODE ----" );
#endif 
#ifdef DEMO_APP_TRANSMITTER
    log_info( &logger, "---- TRANSMITTER MODE ----" );
#endif 
    Delay_ms ( 1000 );
}
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message every 2 seconds.

```c
void application_task ( void ) 
{
#ifdef DEMO_APP_RECEIVER
    spirit_process( );
#endif   
    
#ifdef DEMO_APP_TRANSMITTER 
    spirit_generic_write( &spirit, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_info( &logger, "---- The message has been sent ----" );
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
