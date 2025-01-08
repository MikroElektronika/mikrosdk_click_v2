
---
# CAN Bus Click

> [CAN Bus Click](https://www.mikroe.com/?pid_product=MIKROE-4640) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4640&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This library contains API for CAN Bus Click board&trade;.
> This example transmits/receives and processes data from CAN Bus Click.
> The library initializes and defines the 
> UART bus drivers to transmit or receive data. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CanBus

### Example Key Functions

- `canbus_cfg_setup` Config Object Initialization function.
```c
void canbus_cfg_setup ( canbus_cfg_t *cfg );
```

- `canbus_init` Initialization function.
```c
err_t canbus_init ( canbus_t *ctx, canbus_cfg_t *cfg );
```

- `canbus_default_cfg` Click Default Configuration function.
```c
void canbus_default_cfg ( canbus_t *ctx );
```

- `canbus_send_data` CAN Bus send data function.
```c
err_t canbus_send_data ( canbus_t *ctx, char *tx_data );
```

- `canbus_set_high_speed_mode` CAN Bus high speed mode function.
```c
err_t canbus_set_high_speed_mode ( canbus_t *ctx );
```

- `canbus_set_low_current_standby_mode` CAN Bus low current standby mode function.
```c
err_t canbus_set_low_current_standby_mode ( canbus_t *ctx );
```

### Application Init

> Initializes driver, wake-up module, and set high-speed operation mode.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;        /**< Logger config object. */
    canbus_cfg_t canbus_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.

    canbus_cfg_setup( &canbus_cfg );
    CANBUS_MAP_MIKROBUS( canbus_cfg, MIKROBUS_1 );
    err_t init_flag  = canbus_init( &canbus, &canbus_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    canbus_default_cfg ( &canbus );
    app_buf_len = 0;
    app_buf_cnt = 0;
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    canbus_set_high_speed_mode( &canbus );
    Delay_ms ( 100 );
    
    #ifdef TRANSMIT
    
        log_printf( &logger, "    Send data:    \r\n" );
        log_printf( &logger, "      MikroE      \r\n" );
        log_printf( &logger, "------------------\r\n" );
        log_printf( &logger, "  Transmit data   \r\n" );
        Delay_ms ( 1000 );

    #endif
        
    #ifdef RECIEVER

        log_printf( &logger, "   Receive data  \r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    
    #endif
        
    log_printf( &logger, "------------------\r\n" );
}
```

### Application Task

> Transmitter/Receiver task depends on uncommented code.
> Receiver logging each received byte to the UART for data logging,
> while transmitted send messages every 2 seconds.

```c
void application_task ( void ) 
{
   #ifdef TRANSMIT
    
        canbus_send_data( &canbus, demo_message );
        log_printf( &logger, "\t%s", demo_message );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        log_printf( &logger, "------------------\r\n" );    
    
    #endif
    
    #ifdef RECIEVER
    
        canbus_process( );

        if ( app_buf_len > 0 ) {
            log_printf( &logger, "%s", app_buf );
            canbus_clear_app_buf(  );
        }
    
    #endif
}
```

## Additional Function

- `canbus_clear_app_buf` Function clears memory of app_buf.
```c
static void canbus_clear_app_buf ( void );
```

- `canbus_process` The general process of collecting presponce that a module sends.
```c
static err_t canbus_process ( void );
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
