
---
# Nano LR Click

> [Nano LR Click](https://www.mikroe.com/?pid_product=MIKROE-4514) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4514&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from Nano LR Clicks. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NanoLR

### Example Key Functions

- `nanolr_cfg_setup` Config Object Initialization function. 
```c
void nanolr_cfg_setup ( nanolr_cfg_t *cfg );
``` 
 
- `nanolr_init` Initialization function. 
```c
err_t nanolr_init ( nanolr_t *ctx, nanolr_cfg_t *cfg );
```

- `nanolr_default_cfg` Click Default Configuration function. 
```c
void nanolr_default_cfg ( nanolr_t *ctx );
```

- `nanolr_send_data` This function sends data command depends on the chosen network protocol. 
```c
void nanolr_send_data ( nanolr_t *ctx, uint8_t *tx_data, uint8_t length );
```
 
- `nanolr_uart_isr` This function reads response bytes from the device and sets flag after each received byte. 
```c
void nanolr_uart_isr ( nanolr_t *ctx );
```

- `nanolr_rsp_rdy` This function checks if the response is ready. 
```c
uint8_t nanolr_rsp_rdy ( nanolr_t *ctx );
```

### Application Init

> Initializes the driver, and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    nanolr_cfg_t cfg;

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

    nanolr_cfg_setup( &cfg );
    NANOLR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nanolr_init( &nanolr, &cfg );

    nanolr_default_cfg( &nanolr );

    log_printf( &logger,  "----  Nano LR Click ----\r\n" );

#ifdef DEMO_APP_RECEIVER
    log_printf( &logger,  "---- RECEIVER MODE ----\r\n" );
#endif
    
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger,  "---- TRANSMITER MODE ----\r\n" );
#endif 
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends a desired message
> every 2 seconds. All data is being displayed on the USB UART.

```c
void application_task ( void )
{    
#ifdef DEMO_APP_RECEIVER
    nanolr_process( );
#endif

#ifdef DEMO_APP_TRANSMITTER
    nanolr_send_data( &nanolr, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_printf( &logger, "The message \"%s\" has been sent!\r\n", ( uint8_t * ) TEXT_TO_SEND );
    log_printf( &logger, "------------------------------------------------------------\r\n" );
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
