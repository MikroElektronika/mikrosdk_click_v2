
---
# MIC23099 Click

> [MIC23099 Click](https://www.mikroe.com/?pid_product=MIKROE-2765) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2765&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> 
> This example shows usage of MIC23099 Click as step-down/step-up voltage regulator.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mic23099

### Example Key Functions

- `mic23099_cfg_setup` Config Object Initialization function. 
```c
void mic23099_cfg_setup ( mic23099_cfg_t *cfg );
``` 
 
- `mic23099_init` Initialization function. 
```c
err_t mic23099_init ( mic23099_t *ctx, mic23099_cfg_t *cfg );
```

- `mic23099_default_cfg` Click Default Configuration function. 
```c
void mic23099_default_cfg ( mic23099_t *ctx );
```

- `mic23099_default_cfg` This function executes default configuration for MIC23099 Click. 
```c
void mic23099_default_cfg ( mic23099_t *ctx );
```
 
- `mic23099_check_power_good` This function checks the state of Power Good output pin. 
```c
uint8_t mic23099_check_power_good ( mic23099_t *ctx );
```

### Application Init

>
> Application Init performs Logger and Click initialization.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mic23099_cfg_t cfg;

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
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 1000 );

    //  Click initialization.

    mic23099_cfg_setup( &cfg );
    MIC23099_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic23099_init( &mic23099, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ---- MIC23099 Click ---- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    mic23099_default_cfg( &mic23099 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " -- Initialization done --\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

>
> This example demonstrates the use of MIC23099 Click board by checking 
> the state of power good pin and sends note via UART Terminal 
> if the state is low.
> 

```c
void application_task ( void )
{
    uint8_t new_stat = 0;
    uint8_t old_stat = 1;
    
    new_stat = mic23099_check_power_good( &mic23099 );

    if ( new_stat == 1 && old_stat == 0 )
    {
        old_stat = 1;
    }

    if ( new_stat == 0 && old_stat == 1 )
    {
        log_printf( &logger, " Change  battery  and  reset. \r\n" );
        log_printf( &logger, "------------------------------\r\n" );
        old_stat = 0;
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
