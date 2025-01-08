
---
# ADC 6 Click

> [ADC 6 Click](https://www.mikroe.com/?pid_product=MIKROE-2932) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2932&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This example collects data from the sensor, calculates the voltage to a digital value and then logs it.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC6

### Example Key Functions

- `adc6_cfg_setup` Config Object Initialization function.
```c
void adc6_cfg_setup ( adc6_cfg_t *cfg );
```

- `adc6_init` Initialization function.
```c
err_t adc6_init ( adc6_t *ctx, adc6_cfg_t *cfg );
```

- `adc6_default_cfg` Click Default Configuration function.
```c
void adc6_default_cfg ( adc6_t* ctx );
```

- `adc6_get_adc_data` Get data function
```c
uint32_t adc6_get_adc_data ( adc6_t* ctx );
```

- `adc6_read_reg` Generic read function
```c
uint32_t adc6_read_reg ( adc6_t* ctx, uint8_t register_address );
```

- `adc6_write_reg` Generic write function
```c
void adc6_write_reg ( adc6_t* ctx, uint8_t register_address, uint32_t transfer_data );
```

### Application Init

> Initializes driver and sets configuration which enables channel 0,
puts AIN0 on positive analog input and AIN1 on negative analog input,
enables internal reference voltage (approximately 2.65V (AVDD = 3.3V)),
and also enables bipolar operation mode and puts device on full power mode.
When the ADC is configured for unipolar operation, the output code is natural
(straight) binary with a zero differential input voltage 
resulting in a code of 0x00000000, a midscale voltage resulting in a code 
of 0x00800000, and a full-scale input voltage resulting in a code of 0x00FFFFFF.
When the ADC is configured for bipolar operation, the output code is offset
binary with a negative full-scale voltage resulting in a code of 0x00000000, 
a zero differential input voltage resulting in a code of 0x00800000, 
and a positive full-scale input voltage resulting in a code of 0x00FFFFFF.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    adc6_cfg_t cfg;

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

    adc6_cfg_setup( &cfg );
    ADC6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc6_init( &adc6, &cfg );
    adc6_default_cfg( &adc6 );

}
```

### Application Task

>  Gets 24-bit converted data in single read mode and logs data on USB UART. Repeats operation every 500 ms.


```c
void application_task ( void )
{
    uint32_t adc_value = 0;

    adc_value = adc6_get_adc_data( &adc6 );

    log_printf( &logger, "The ADC value is: 0x%.6LX\r\n", adc_value );

    Delay_ms ( 500 );
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
