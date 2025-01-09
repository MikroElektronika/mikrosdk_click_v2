
---
# iqRF Click

> [iqRF Click](https://www.mikroe.com/?pid_product=MIKROE-2586) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2586&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : UART type

# Software Support

## Example Description

> 
> RF transceiver - in first case reads one byte from RX buffer. 
> In the second case writes message data via UART.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.iqRF

### Example Key Functions

- `iqrf_cfg_setup` Config Object Initialization function. 
```c
void iqrf_cfg_setup ( iqrf_cfg_t *cfg );
``` 
 
- `iqrf_init` Initialization function. 
```c
err_t iqrf_init ( iqrf_t *ctx, iqrf_cfg_t *cfg );
```

- `iqrf_default_cfg` Click Default Configuration function. 
```c
void iqrf_default_cfg ( iqrf_t *ctx );
```

- `iqrf_generic_single_read` This function read one byte data. 
```c
iqrf_data_t iqrf_generic_single_read ( iqrf_t *ctx );
```
 
- `iqrf_generic_multi_write` This function writes data. 
```c
void iqrf_generic_multi_write ( iqrf_t *ctx, iqrf_data_t *data_buf,  uart_length_t len );
```

### Application Init

>
> Application Init performs Logger and Click initialization.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    iqrf_cfg_t cfg;

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
    log_printf( &logger, "------------------------------------\r\n" );
    log_printf( &logger, "--------  Application  Init --------\r\n" );
    Delay_ms ( 1000 );

    //  Click initialization.

    iqrf_cfg_setup( &cfg );
    IQRF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    iqrf_init( &iqrf, &cfg );
    
    log_printf( &logger, "------------------------------------\r\n" );
    log_printf( &logger, "------------ iqRF  Click -----------\r\n" );
    log_printf( &logger, "------------------------------------\r\n" );
    Delay_ms ( 1000 );
    
    iqrf_default_cfg ( &iqrf );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------- Initialization ----------\r\n" );
    log_printf( &logger, "------------------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

>
> Checks if new data byte has received in RX buffer ( ready for reading ),
> and if ready than reads one byte from RX buffer. In the second case, 
> the application task writes message data via UART. Results are being sent 
> to the Usart Terminal where you can track their changes.
> 

```c
void application_task ( void )
{
    iqrf_data_t tmp;
    
#ifdef DEMO_APP_RECEIVER

    // RECEIVER - UART polling

    tmp =  iqrf_generic_single_read( &iqrf );
    log_printf( &logger, " %c ", tmp );
        
#endif
        
#ifdef DEMO_APP_TRANSCEIVER

    // TRANSMITER - TX each 2 sec
        
    uint8_t cnt;
        
    for ( cnt = 0; cnt < 9; cnt ++ )
    {
        iqrf_generic_single_write( &iqrf, demo_message[ cnt ] );
        Delay_ms ( 100 );
    }
    
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
