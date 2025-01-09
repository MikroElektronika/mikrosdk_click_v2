
---
# tRF Click

> [tRF Click](https://www.mikroe.com/?pid_product=MIKROE-1535) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1535&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : UART type

# Software Support

## Example Description

> 
> This is a example which demonstrates the use of Trf Click board.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Trf

### Example Key Functions

- `trf_cfg_setup` Config Object Initialization function. 
```c
void trf_cfg_setup ( trf_cfg_t *cfg );
``` 
 
- `trf_init` Initialization function. 
```c
err_t trf_init ( trf_t *ctx, trf_cfg_t *cfg );
```

- `trf_default_cfg` Click Default Configuration function. 
```c
void trf_default_cfg ( trf_t *ctx );
```

- `trf_generic_single_read` Generic single read function. 
```c
trf_data_t trf_generic_single_read ( trf_t *ctx );
```
 
- `trf_generic_single_write` Generic single write function. 
```c
void trf_generic_single_write ( trf_t *ctx, trf_data_t tx_data );
```

- `trf_generic_multi_write` Generic multi write function. 
```c
void trf_generic_multi_write ( trf_t *ctx, trf_data_t *data_buf,  uart_length_t len );
```

### Application Init

>
> Configuring Clicks and log objects.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    trf_cfg_t cfg;

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
    log_printf( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    trf_cfg_setup( &cfg );
    TRF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    trf_init( &trf, &cfg );
}
```

### Application Task

>
> Checks if new data byte have received in rx buffer (ready for reading),
> and if ready than reads one byte from rx buffer. In second case aplication task writes
> message data via UART.
> 

```c
void application_task ( void )
{
    trf_data_t tmp;
    uint8_t cnt;
    
#ifdef DEMO_APP_RECEIVER

    // RECEIVER - UART polling

    tmp =  trf_generic_single_read( &trf );
    log_printf( &logger, " %c ", tmp );
    
#endif
#ifdef DEMO_APP_TRANSMITER

    // TRANSMITER - TX each 2 sec
       
    for ( cnt = 0; cnt < 9; cnt ++ )
    {
        trf_generic_single_write( &trf, demo_message[ cnt ] );
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
