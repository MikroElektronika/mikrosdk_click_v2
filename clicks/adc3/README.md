
---
# ADC 3 Click

> [ADC 3 Click](https://www.mikroe.com/?pid_product=MIKROE-1894) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1894&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> 
> ADC 3 example code shows usage of analog-to-digital converter.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Adc3

### Example Key Functions

- `adc3_cfg_setup` Config Object Initialization function. 
```c
void adc3_cfg_setup ( adc3_cfg_t *cfg );
``` 
 
- `adc3_init` Initialization function. 
```c
err_t adc3_init ( adc3_t *ctx, adc3_cfg_t *cfg );
```

- `adc3_default_cfg` Click Default Configuration function. 
```c
void adc3_default_cfg ( adc3_t *ctx );
```

- `adc3_default_cfg` This function is used to initiate general call reset. 
```c
void adc3_default_cfg ( adc3_t *ctx );
```
 
- `adc3_read_voltage` This function is used to read ADC value and calculate voltage. 
```c
float adc3_read_voltage ( adc3_t *ctx, uint8_t channel, uint8_t resolution, uint8_t gain );
```

### Application Init

>
> Application Init performs Logger and Click initialization.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    adc3_cfg_t cfg;

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
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 100 );

    //  Click initialization.

    adc3_cfg_setup( &cfg );
    ADC3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc3_init( &adc3, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ------ ADC 3 Click ----- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    adc3_default_cfg( &adc3 );
    Delay_ms ( 100 );
    
    log_printf( &logger, " -- Initialization done --\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

>
> This is an example that shows the capabilities of the ADC 3 Click 
> by taking voltage measurements from all four channel. Results are being sent to the UART Terminal 
> where you can track their changes. All data logs write on USB UART and changes for every 1 sec.
> 

```c
void application_task ( void )
{
    read_volt = adc3_read_voltage( &adc3, ADC3_SELECT_CHANNEL_1, ADC3_SAMPLE_RATE_12, ADC3_PGA_GAIN_X1 );
    Delay_ms ( 100 );
    log_printf( &logger, "Channel 1 : %0.2f  V \r\n", read_volt );

    read_volt = adc3_read_voltage( &adc3, ADC3_SELECT_CHANNEL_2, ADC3_SAMPLE_RATE_12, ADC3_PGA_GAIN_X1 );
    Delay_ms ( 100 );
    log_printf( &logger, "Channel 2 : %0.2f  V \r\n", read_volt );
    
    read_volt = adc3_read_voltage( &adc3, ADC3_SELECT_CHANNEL_3, ADC3_SAMPLE_RATE_12, ADC3_PGA_GAIN_X1 );
    Delay_ms ( 100 );
    log_printf( &logger, "Channel 3 : %0.2f  V \r\n", read_volt );
    
    read_volt = adc3_read_voltage( &adc3, ADC3_SELECT_CHANNEL_4, ADC3_SAMPLE_RATE_12, ADC3_PGA_GAIN_X1 );
    Delay_ms ( 100 );
    log_printf( &logger, "Channel 4 : %0.2f  V \r\n", read_volt );
    
    log_printf( &logger, "--------------------------\r\n" );
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
