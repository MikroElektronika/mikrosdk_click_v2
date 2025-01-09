
---
# SPIRIT 2 Click

> [SPIRIT 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3598) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3598&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from SPIRIT2 2 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SPIRIT2

### Example Key Functions

- `spirit2_cfg_setup` Config Object Initialization function.
```c
void spirit2_cfg_setup ( spirit2_cfg_t *cfg );
```

- `spirit2_init` Initialization function.
```c
err_t spirit2_init ( spirit2_t *ctx, spirit2_cfg_t *cfg );
```

- `spirit2_power_module` Function for power mode of SPIRIT 2 Click.
```c
void spirit2_power_module ( spirit2_t *ctx, uint8_t power_state );
```

- `spirit2_reset` Function for reseting SPIRIT 2 Click.
```c
void spirit2_reset ( spirit2_t *ctx );
```

- `spirit2_set_mode` Function for setting mode of SPIRIT 2 Click.
```c
void spirit2_set_mode ( spirit2_t *ctx, uint8_t mode );
```

### Application Init

> Initializes driver and wake-up module.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;
    spirit2_cfg_t cfg;

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

    spirit2_cfg_setup( &cfg );
    SPIRIT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spirit2_init( &spirit2, &cfg );
    Delay_ms ( 1000 );

    log_info( &logger, "---- Configuring the module ----" );
    spirit2_power_module( &spirit2, SPIRIT2_MODULE_WAKE_UP );
    spirit2_reset( &spirit2 );
    spirit2_set_mode( &spirit2, SPIRIT2_OPERATING_MODE );
    Delay_ms ( 1000 );
    log_printf( &logger, "COMMAND MODE\r\n" );
    spirit2_send_cmd( &spirit2, SPIRIT2_CMD_ENTER_COMMAND_MODE );
    spirit2_process( );
    log_printf( &logger, "FIRMWARE VERSION\r\n" );
    spirit2_send_cmd( &spirit2, SPIRIT2_CMD_READ_MODULE_VERSION );
    spirit2_process( );
    log_printf( &logger, "TXRX LED - OPEN DRAIN OUTPUT\r\n" );
    spirit2_send_cmd_with_parameter( &spirit2, SPIRIT2_CMD_CFG_TXRX_LED, SPIRIT2_PCFG_TXRXLED_OPEN_DRAIN );
    spirit2_process( );
    log_printf( &logger, "STORE CONFIG\r\n" );
    spirit2_send_cmd( &spirit2, SPIRIT2_CMD_STORE_CURRENT_CONFIG );
    spirit2_process( );
    log_printf( &logger, "OPERATING MODE\r\n" );
    spirit2_send_cmd( &spirit2, SPIRIT2_CMD_ENTER_OPERATING_MODE );
    spirit2_process( );
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

> Reads the received data and parses it.

```c
void application_task ( void ) 
{
#ifdef DEMO_APP_RECEIVER
    spirit2_process( );
#endif   
    
#ifdef DEMO_APP_TRANSMITTER 
    spirit2_generic_write( &spirit2, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
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
