
---
# Step Up Click

> [Step Up Click](https://www.mikroe.com/?pid_product=MIKROE-3709) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3709&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application enables usage of DC-DC step-up (boost) regulator.>

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.StepUp

### Example Key Functions

- `stepup_cfg_setup` Config Object Initialization function. 
```c
void stepup_cfg_setup ( stepup_cfg_t *cfg );
``` 
 
- `stepup_init` Initialization function. 
```c
err_t stepup_init ( stepup_t *ctx, stepup_cfg_t *cfg );
```

- `stepup_default_cfg` Click Default Configuration function. 
```c
void stepup_default_cfg ( stepup_t *ctx );
```

- `stepup_get_percent` This function calculates ouput value in percent. 
```c
float stepup_get_percent ( uint16_t out_value );
```
 
- `stepup_en_set` This function sets the EN pin state. 
```c
void stepup_en_set ( stepup_t *ctx, uint8_t pin_state );
```

- `stepup_set_out` This function sets output value. 
```c
uint8_t stepup_set_out ( stepup_t *ctx, uint16_t out_value );
```

### Application Init

> Initializes SPI driver, sets config word, initializes and configures the device

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    stepup_cfg_t cfg;
    
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
    log_info( &logger, "Application Init" );

    //  Click initialization.

    stepup_cfg_setup( &cfg );
    STEPUP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stepup_init( &stepup, &cfg );
    
    stepup_default_cfg( &stepup );

    Delay_ms ( 100 );
    log_info( &logger, "Application Task" );
}
```

### Application Task

> Sets 3 different boost precentage value to device, value changes every 10 seconds.


```c
void application_task ( void )
{
    log_info( &logger, "Setting DAC boost to 10%%" );
    stepup_set_percentage( &stepup, 10 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_info( &logger, "Setting DAC boost to 60%%" );
    stepup_set_percentage( &stepup, 60 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_info( &logger, "Setting DAC boost to 30%%" );
    stepup_set_percentage( &stepup, 30 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Additional Functions :
> 
> stepup_logPercent() - calls 'stepup_getPercent()' function to get output
> value in expressed as percentage and logs that value. 

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
