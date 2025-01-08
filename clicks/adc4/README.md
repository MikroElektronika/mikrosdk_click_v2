
---
# ADC 4 Click

> [ADC 4 Click](https://www.mikroe.com/?pid_product=MIKROE-2879) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2879&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This application is a converter from analog to digital multichannel 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Adc4

### Example Key Functions

- `adc4_cfg_setup` Config Object Initialization function. 
```c
void adc4_cfg_setup ( adc4_cfg_t *cfg );
``` 
 
- `adc4_init` Initialization function. 
```c
err_t adc4_init ( adc4_t *ctx, adc4_cfg_t *cfg );
```

- `adc4_default_cfg` Click Default Configuration function. 
```c
void adc4_default_cfg ( adc4_t *ctx );
```

- `adc4_get_err_pin` Error check function. 
```c
uint8_t adc4_get_err_pin( adc4_t *ctx );
```
 
- `adc4_get_config` Get configuration function. 
```c
void adc4_get_config( adc4_t *ctx, uint8_t reg_address, uint16_t *value );
```

- `adc4_get_voltage` Get voltage function. 
```c
uint16_t adc4_get_voltage( adc4_t *ctx, const float ref_voltage );
```

### Application Init

> Initializes ADC 4 driver and setups working mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    adc4_cfg_t cfg;

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

    adc4_cfg_setup( &cfg );
    ADC4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc4_init( &adc4, &cfg );

    Delay_ms ( 100 );

    adc4_default_cfg( &adc4 );

    voltage = 0;
}
```

### Application Task

> Sequential read of voltage. Information about
> current voltage is logget to UART. Operation is repeated each second. Settings are set
> to calculate and convert input voltage from CH0 with external referent voltage set by VREF jumper on the Click board.

```c
void application_task ( )
{
    voltage = adc4_get_voltage( &adc4, ADC4_VREF_4000MV);

    if ( adc4.sing_bit == 1 )
    {
        log_printf( &logger, "Voltage at CH0 : %d mV \r\n", voltage );
    }
    else
    {
        log_printf( &logger, "Voltage at CH0 : - %d mV \r\n", voltage );
    }

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
