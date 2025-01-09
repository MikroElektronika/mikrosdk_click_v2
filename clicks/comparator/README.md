
---
# Comparator Click

> [Comparator Click](https://www.mikroe.com/?pid_product=MIKROE-1915) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1915&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> 
> This is an example which demonstrates the usage of Comparator Click board.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Comparator

### Example Key Functions

- `comparator_cfg_setup` Config Object Initialization function. 
```c
void comparator_cfg_setup ( comparator_cfg_t *cfg );
``` 
 
- `comparator_init` Initialization function. 
```c
err_t comparator_init ( comparator_t *ctx, comparator_cfg_t *cfg );
```

- `comparator_default_cfg` Click Default Configuration function. 
```c
void comparator_default_cfg ( comparator_t *ctx );
```

- `comparator_check_output_one` This function check and return state of the o1 ( AN ) pin of Comparator Click Board. 
```c
uint8_t comparator_check_output_one ( comparator_t *ctx );
```
 
- `comparator_check_output_two` This function check and return state of the o2 ( INT ) pin of Comparator Click Board. 
```c
uint8_t comparator_check_output_two ( comparator_t *ctx );
```

### Application Init

>
> Application Init performs Logger and Click initialization.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    comparator_cfg_t cfg;

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
    Delay_ms ( 500 );

    //  Click initialization.

    comparator_cfg_setup( &cfg );
    COMPARATOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    comparator_init( &comparator, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " --- Comparator Click --- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " -- Initialization done --\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

>
> Comparator Click checks state of the O1 and O2 pins. Results are being sent to the UART Terminal where you can track their changes. 
> All data logs write on USB UART and changes for every 1 sec.
> 

```c
void application_task ( void )
{
    out_state_one = comparator_check_output_one( &comparator );
    out_state_two = comparator_check_output_two( &comparator );
    
    log_printf( &logger, "   Output One: \r\n" );
    
    if ( out_state_one )
    {
        log_printf( &logger, "   High \r\n" );
    }
    else
    {
        log_printf( &logger, "   Low \r\n" );
    }
    
    Delay_ms ( 500 );
    
    log_printf( &logger, "   Output Two: \r\n" );
    
    if ( out_state_two )
    {
        log_printf( &logger, "   High \r\n" );
    }
    else
    {
        log_printf( &logger, "   Low \r\n" );
    }
    
    Delay_ms ( 500 );
    
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
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
