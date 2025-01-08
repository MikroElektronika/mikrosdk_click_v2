
---
# Buck 12 Click

> [Buck 12 Click](https://www.mikroe.com/?pid_product=MIKROE-3652) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3652&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This demo application reads the voltage in [mV] at the input and output terminals.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck12

### Example Key Functions

- `buck12_cfg_setup` Config Object Initialization function. 
```c
void buck12_cfg_setup ( buck12_cfg_t *cfg );
``` 
 
- `buck12_init` Initialization function. 
```c
err_t buck12_init ( buck12_t *ctx, buck12_cfg_t *cfg );
```

- `buck12_default_cfg` Click Default Configuration function. 
```c
void buck12_default_cfg ( buck12_t *ctx );
```

- `buck12_control` This function for enable or disable device. 
```c
void buck12_control ( buck12_t *ctx, uint8_t ctrl );
```
 
- `buck12_get_channel_adc` This function reads ADC on the channel. 
```c
uint16_t buck12_get_channel_adc ( buck12_t *ctx, uint8_t channel );
```

- `buck12_get_voltage` This function gets Voltage. 
```c
float buck12_get_voltage ( buck12_t *ctx, uint8_t select_volt );
```

### Application Init

> Configuring Clicks and log objects.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buck12_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    buck12_cfg_setup( &cfg );
    BUCK12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck12_init( &buck12, &cfg );

    buck12_control( &buck12, BUCK12_ENABLE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Application Task

> Reads the voltage in [mV] at the input and output terminals.
> This data logs to the USBUART every 2 sec.

```c
void application_task ( void )
{
    float voltage;

    voltage = buck12_get_voltage( &buck12, BUCK12_INPUT_VOLTAGE );
    
    log_printf( &logger, "* Vin : %f mV \r\n ", voltage);
    
    voltage = buck12_get_voltage( &buck12, BUCK12_OUTPUT_VOLTAGE );

    log_printf( &logger, "* Vout : %f mV \r\n ", voltage);

    log_printf( &logger, "--------------------------\r\n");
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
