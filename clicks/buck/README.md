
---
# BUCK Click

> [BUCK Click](https://www.mikroe.com/?pid_product=MIKROE-1592) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1592&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> The demo application displays frequency change and voltage 
> regulation using a BUCK Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck

### Example Key Functions

- `buck_cfg_setup` Config Object Initialization function. 
```c
void buck_cfg_setup ( buck_cfg_t *cfg );
``` 
 
- `buck_init` Initialization function. 
```c
err_t buck_init ( buck_t *ctx, buck_cfg_t *cfg );
```

- `buck_default_cfg` Click Default Configuration function. 
```c
void buck_default_cfg ( buck_t *ctx );
```

- `buck_switch_frequency` Setting the switching frequency function. 
```c
void buck_switch_frequency( buck_t *ctx, uint8_t frequency );
```
 
- `buck_set_mode` Select buck mode (Disable / Enable). 
```c
void buck_set_mode( buck_t *ctx, uint8_t mode );
```

- `buck_get_power_good` Get state internal comparator function. 
```c
uint8_t buck_get_power_good( buck_t *ctx );
```

### Application Init

> Configuring Clicks and log objects.
> Settings the Click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buck_cfg_t cfg;

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

    buck_cfg_setup( &cfg );
    BUCK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck_init( &buck, &cfg );
    Delay_ms ( 100 );

    buck_software_reset( &buck );
    buck_default_cfg( &buck );
}
```

### Application Task

> This is a example which demonstrates the use of Buck Click board.
> Checks if it has reached the set output voltage and sets 
> a different frequency to the LT3976 chip every 5 sec.

```c
void application_task ( void )
{
    //  Task implementation.
    if ( buck_get_power_good( &buck ) == 1 )
    {
        log_info( &logger, "----  Power good output voltage!  ----" );
    }
    Delay_ms ( 1000 );

    log_info( &logger, "----  Switching frequency 400kHz!  ----" );
    buck_switch_frequency( &buck, BUCK_FREQ_400KHz );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_info( &logger, "----  Switching frequency 800kHz!  ----" );
    buck_switch_frequency( &buck, BUCK_FREQ_800KHz );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
