
---
# BUCK 7 Click

> [BUCK 7 Click](https://www.mikroe.com/?pid_product=MIKROE-3094) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3094&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This demo application controls the voltage at the output using the BUCK 7 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BUCK7

### Example Key Functions

- `buck7_cfg_setup` Config Object Initialization function. 
```c
void buck7_cfg_setup ( buck7_cfg_t *cfg );
``` 
 
- `buck7_init` Initialization function. 
```c
err_t buck7_init ( buck7_t *ctx, buck7_cfg_t *cfg );
```

- `buck7_default_cfg` Click Default Configuration function. 
```c
void buck7_default_cfg ( buck7_t *ctx );
```

- `buck7_set_output_voltage` Function for settings output voltage. 
```c
void buck7_set_output_voltage ( buck7_t *ctx, uint16_t voltage );
```
 
- `buck7_enable` Function for enable chip. 
```c
void buck7_enable( buck7_t *ctx );
```

- `buck7_set_mode` Function for settings chip mode. 
```c
void buck7_set_mode( buck7_t *ctx, uint8_t mode );
```

### Application Init

> Initializes Driver init, reset chip, enable chip and set mode

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buck7_cfg_t cfg;

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

    buck7_cfg_setup( &cfg );
    BUCK7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck7_init( &buck7, &cfg );

    buck7_enable( &buck7 );
    buck7_set_mode( &buck7, BUCK7_MODE_PWM );
}
```

### Application Task

> Sets output voltage to 5V, 10V, 15V, 20V, 25V every 3 seconds.
> It is necessary to set the input voltage on 2.7V + maximum output voltage.

```c
void application_task ( )
{
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_5V );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_10V );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_15V );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_20V );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_25V );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_20V );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_15V );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck7_set_output_voltage( &buck7, 0x0BB8 ); /* 10 V */
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
