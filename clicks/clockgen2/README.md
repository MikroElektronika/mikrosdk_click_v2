
---
# Clock Gen 2 Click

> [Clock Gen 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3076) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3076&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application enables generation of square waved clock signal in range from 260 kHz to 66,6 MHz

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ClockGen2

### Example Key Functions

- `clockgen2_cfg_setup` Config Object Initialization function. 
```c
void clockgen2_cfg_setup ( clockgen2_cfg_t *cfg );
``` 
 
- `clockgen2_init` Initialization function. 
```c
err_t clockgen2_init ( clockgen2_t *ctx, clockgen2_cfg_t *cfg );
```

- `clockgen2_default_cfg` Click Default Configuration function. 
```c
void clockgen2_default_cfg ( clockgen2_t *ctx );
```

- `clockgen2_output_enable` Function for enabling/disabling of the clock output. 
```c
void clockgen2_output_enable ( clockgen2_t *ctx, uint8_t state );
```
 
- `clockgen2_auto_setting_preserve` Function used for enabling/disabling auto settings preservation. 
```c
void clockgen2_auto_setting_preserve ( clockgen2_t *ctx, uint8_t state );
```

- `clockgen2_set_prescaler` Function for setting the main clock prescaler. 
```c
void clockgen2_set_prescaler ( clockgen2_t *ctx, uint8_t val );
```

### Application Init

> Driver initialization.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    clockgen2_cfg_t cfg;

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

    clockgen2_cfg_setup( &cfg );
    CLOCKGEN2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    clockgen2_init( &clockgen2, &cfg );

    Delay_ms ( 100 );
}
```

### Application Task

> Changes the prescaler and enables/disables the clock output.

```c
void application_task ( void )
{
    //  Task implementation.

    char i;
     
     for ( i = 5; i< 8; i++ )
     {
       clockgen2_set_prescaler( &clockgen2, i );
       clockgen2_output_enable( &clockgen2, 1 );
       Delay_ms ( 1000 );
       Delay_ms ( 1000 );

       clockgen2_output_enable( &clockgen2, 0 );
       Delay_ms ( 1000 );
       Delay_ms ( 1000 );
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
