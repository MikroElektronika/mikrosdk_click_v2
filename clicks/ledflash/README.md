
---
# LED Flash Click

> [LED Flash Click](https://www.mikroe.com/?pid_product=MIKROE-2479) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2479&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application switching on and off led flash.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LedFlash

### Example Key Functions

- `ledflash_cfg_setup` Config Object Initialization function. 
```c
void ledflash_cfg_setup ( ledflash_cfg_t *cfg );
``` 
 
- `ledflash_init` Initialization function. 
```c
err_t ledflash_init ( ledflash_t *ctx, ledflash_cfg_t *cfg );
```

- `ledflash_char_supcap_enable` Charge Supercapacitor Enable function. 
```c
void ledflash_char_supcap_enable ( ledflash_t *ctx );
```
 
- `ledflash_flash_enable` Flash Enable function. 
```c
void ledflash_flash_enable ( ledflash_t *ctx );
```

- `ledflash_flash_rdy_flag` Check Flash Ready Flag function. 
```c
uint8_t ledflash_flash_rdy_flag ( ledflash_t *ctx );
```

### Application Init

> Initialization driver enables GPIO, starts write log and issues a warning. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ledflash_cfg_t cfg;

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

    ledflash_cfg_setup( &cfg );
    LEDFLASH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ledflash_init( &ledflash, &cfg );
    Delay_ms ( 100 );
    
    log_printf( &logger, "----------------------------------\r\n" );
    log_printf( &logger, " LED Flash Click \r\n" );
    log_printf( &logger, "----------------------------------\r\n" );
    log_printf( &logger, "/////////////////\r\n" );
    log_printf( &logger, " WARNING!!! \r\n" );
    log_printf( &logger, " DO NOT LOOK \r\n" );
    log_printf( &logger, " INTO THE LEDS, \r\n" );
    log_printf( &logger, " WHILE THAY ARE ON!!! \r\n" );
    log_printf( &logger, "/////////////////\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> This example demonstrates the use of LED Flash Click board by flashing
> with LEDs when ever supercapacitor is at a full voltage.

```c
void application_task (  )
{
    uint8_t state;
    
    log_printf( &logger, " Charge Supercapacitor Enable \r\n" );
    ledflash_char_supcap_enable( &ledflash );
    Delay_ms ( 1000 );
    state = ledflash_flash_rdy_flag( &ledflash );

    if ( state == 0 )
    {
        log_printf( &logger, " Flash ON! \r\n" );
        ledflash_flash_enable( &ledflash );
    }
    else
    {
        log_printf( &logger, " Flash OFF! \r\n" );
        ledflash_flash_disable( &ledflash );
    }
    log_printf( &logger, "----------------------------------\r\n" );
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
