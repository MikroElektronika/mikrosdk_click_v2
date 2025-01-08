
---
# Step Down 2 Click

> [Step Down 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3895) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3895&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example showcases how to initialize and use the Step Down 2 Click. The Click is a 
  step-down monolithic switching regulator able to deliver up to 2 A (DC). 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.StepDown2

### Example Key Functions

- `stepdown2_cfg_setup` Config Object Initialization function. 
```c
void stepdown2_cfg_setup ( stepdown2_cfg_t *cfg );
``` 
 
- `stepdown2_init` Initialization function. 
```c
err_t stepdown2_init ( stepdown2_t *ctx, stepdown2_cfg_t *cfg );
```

- `stepdown2_default_cfg` Click Default Configuration function. 
```c
void stepdown2_default_cfg ( stepdown2_t *ctx );
```

- `stepdown2_digital_read_rst` This function reads the digital signal from the RST pin. 
```c
uint8_t stepdown2_digital_read_rst ( stepdown2_t *ctx );
```
 
- `stepdown2_digital_write_cs` This function writes the specified digital signal to the CS pin. 
```c
void stepdown2_digital_write_cs ( stepdown2_t *ctx, uint8_t signal );
```

### Application Init

> This function initializes and configures the logger and Click modules. 

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    stepdown2_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    stepdown2_cfg_setup( &cfg );
    STEPDOWN2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stepdown2_init( &stepdown2, &cfg );

    stepdown2_digital_write_cs( &stepdown2, 1 );
    Delay_100ms( );
}
```

### Application Task

> This function checks error input on the RST pin and reports if the device is working properly
  or not. It does so every second. 

```c
void application_task ( )
{
    if ( stepdown2_digital_read_rst( &stepdown2 ) )
    {
        log_printf( &logger, " * The device works as it should. *\r\n" );
    }
    else 
    {
        log_printf( &logger, " * The device does not work as it should. *\r\n" );
    }

    Delay_1sec( );
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
