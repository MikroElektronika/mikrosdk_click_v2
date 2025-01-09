
---
# RNG Click

> [RNG Click](https://www.mikroe.com/?pid_product=MIKROE-4090) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4090&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This Click is a random number generator. The device contain potentiometer which control voltage
> so it generates a sequence of numbers or symbols that cannot be reasonably predicted better 
> by a random chance. Random number generators have applications in gambling, statistical sampling,
> computer simulation, cryptography, completely randomized design, and various other areas. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rng

### Example Key Functions

- `rng_cfg_setup` Config Object Initialization function. 
```c
void rng_cfg_setup ( rng_cfg_t *cfg );
``` 
 
- `rng_init` Initialization function. 
```c
err_t rng_init ( rng_t *ctx, rng_cfg_t *cfg );
```

- `rng_default_cfg` Click Default Configuration function. 
```c
void rng_default_cfg ( rng_t *ctx );
```

- `rng_get_voltage` This function gets voltage in millivolts. 
```c
float rng_get_voltage ( rng_t *ctx );
```
 
- `rng_set_config` This function sets configuration. 
```c
void rng_set_config ( rng_t *ctx, uint16_t conf_data );
```

- `rng_set_vref` This function sets desired vref. 
```c
void rng_set_vref ( rng_t *ctx, uint16_t vref_mv );
```

### Application Init

> Initializes driver, then sets configuration and voltage reference.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rng_cfg_t cfg;

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

    rng_cfg_setup( &cfg );
    RNG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rng_init( &rng, &cfg );

    rng_default_cfg( &rng );
}
```

### Application Task

> It reads ADC value from AIN0 channel then converts it to voltage and 
> displays the result on USB UART each second.

```c
void application_task ( void )
{
    float voltage;

    voltage = rng_get_voltage( &rng );

    log_printf( &logger, "Voltage from AIN0: %.2f mV\r\n", voltage );
    log_printf( &logger, "-----------------------\r\n" );
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
