
---
# BUCK 6 Click

> [BUCK 6 Click](https://www.mikroe.com/?pid_product=MIKROE-2957) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2957&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> BUCK 6 Click is an advanced synchronous DC-DC step down (buck) converter, with a very wide input voltage range and reasonably high output current. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BUCK6

### Example Key Functions

- `buck6_cfg_setup` Config Object Initialization function. 
```c
void buck6_cfg_setup ( buck6_cfg_t *cfg );
``` 
 
- `buck6_init` Initialization function. 
```c
err_t buck6_init ( buck6_t *ctx, buck6_cfg_t *cfg );
```

- `buck6_get_rst` Gets reset. 
```c
uint8_t buck6_get_rst ( buck6_t *ctx  );
```
 
- `buck6_set_mode` Set mode. 
```c
void buck6_set_mode ( buck6_t *ctx, uint8_t mode );
```

- `buck6_set_max_voltage` Set maximum voltage. 
```c
void buck6_set_max_voltage ( buck6_t *ctx, uint8_t voltage );
```

### Application Init

> Initialization Driver init and settings chip on ACTIVE mode and setting the maximum range to 5V.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buck6_cfg_t cfg;

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

    buck6_cfg_setup( &cfg );
    BUCK6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck6_init( &buck6, &cfg );
}
```

### Application Task

> Sets the different ranges of the maximum voltage. 

```c
void application_task ( void )
{
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_2500mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_5000mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_7500mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_10000mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_7500mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck6_set_max_voltage( &buck6, BUCK6_MAX_RANGE_5000mV );
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
