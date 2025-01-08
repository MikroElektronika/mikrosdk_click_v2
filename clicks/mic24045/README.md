
---
# MIC24045 Click

> [MIC24045 Click](https://www.mikroe.com/?pid_product=MIKROE-2574) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2574&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of MIC24045 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mic24045

### Example Key Functions

- `mic24045_cfg_setup` Config Object Initialization function. 
```c
void mic24045_cfg_setup ( mic24045_cfg_t *cfg );
``` 
 
- `mic24045_init` Initialization function. 
```c
err_t mic24045_init ( mic24045_t *ctx, mic24045_cfg_t *cfg );
```

- `mic24045_enable` Enable voltage output. 
```c
void mic24045_enable ( mic24045_t *ctx );
```

- `mic24045_get_vout` Get voltage. 
```c
float mic24045_get_vout ( mic24045_t *ctx );
```
 
- `mic24045_set_vout_decimal` Set voltage decimal. 
```c
void mic24045_set_vout_decimal ( mic24045_t *ctx, uint8_t dec );
```

- `mic24045_get_status` Get status function. 
```c
uint8_t mic24045_get_status ( mic24045_t *ctx );
```

### Application Init

> Initializes the driver and enables the voltage output.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mic24045_cfg_t cfg;

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

    mic24045_cfg_setup( &cfg );
    MIC24045_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic24045_init( &mic24045, &cfg );
    
    mic24045_enable( &mic24045 );
    log_printf( &logger, " Output enabled!\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> Changes the voltage output every 2 seconds and displays the current set value on the USB UART.

```c
void application_task ( void )
{
    for ( uint16_t cnt = MIC24045_MIN_VOUT_DEC; cnt <= MIC24045_MAX_VOUT_DEC; cnt += 15 )
    {
        mic24045_set_vout_decimal( &mic24045, cnt );
        Delay_ms ( 500 );
        current_voltage = mic24045_get_vout( &mic24045 );
    
        log_printf( &logger, " VOUT:    ~%.3f V\r\n", current_voltage );
        log_printf( &logger, "------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 500 );
    }
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
