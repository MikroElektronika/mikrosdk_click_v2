
---
# DAC 2 Click

> [DAC 2 Click](https://www.mikroe.com/?pid_product=MIKROE-1918) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1918&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> 
> This example code presents the usage of DAC 2 Click, and digital-to-analog converter.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Dac2

### Example Key Functions

- `dac2_cfg_setup` Config Object Initialization function. 
```c
void dac2_cfg_setup ( dac2_cfg_t *cfg );
``` 
 
- `dac2_init` Initialization function. 
```c
err_t dac2_init ( dac2_t *ctx, dac2_cfg_t *cfg );
```

- `dac2_default_cfg` Click Default Configuration function. 
```c
void dac2_default_cfg ( dac2_t *ctx );
```

- `dac2_default_cfg` This function executes default configuration for LTC2601 Click. 
```c
void dac2_default_cfg ( dac2_t *ctx );
```
 
- `dac2_write_output_voltage_procentage` This function required percentage value ( from 0% to 100% ) convert to digital input and transforms it to the output voltage from 0 to Vref [mV]. 
```c
void dac2_write_output_voltage_procentage ( dac2_t *ctx, uint8_t value_pct );
```

### Application Init

>
> Application Init performs Logger and Click initialization.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dac2_cfg_t cfg;

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
    Delay_ms ( 1000 );

    //  Click initialization.

    dac2_cfg_setup( &cfg );
    DAC2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac2_init( &dac2, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ----- DAC 2  Click ----- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    dac2_default_cfg( &dac2 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " -- Initialization done --\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

>
> This example of the DAC 2 communicates with MCU through the SPI communication, 
> send digital input ( form 0 to 100 with step 1 ) and transforms it 
> to the output voltage, ranging from 0 to Vref [mV].
> 

```c
void application_task ( void )
{
    uint16_t voltage_out;
    uint8_t value_pct;

    for ( value_pct = 0; value_pct <= 100; value_pct += 10 )
    {
        dac2_write_output_voltage_procentage( &dac2, value_pct );
        voltage_out = value_pct * 50;
        log_printf( &logger, "Voltage Output: %d mV\r\n", voltage_out );
        
        voltage_out = value_pct;
        log_printf( &logger, "Percentage Output: %d %%\r\n", voltage_out );
        
        log_printf( &logger, "--------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    log_printf( &logger, "###############################\r\n" );
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
