
---
# DAC 7 Click

> [DAC 7 Click](https://www.mikroe.com/?pid_product=MIKROE-3886) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3886&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mihajlo Djordjevic
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> DAC 7 Click carries the AD5624R 12-bit buffered Digital-to-Analog Converter 
> that converts digital value to the corresponding voltage level 
> using external voltage reference.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Dac7

### Example Key Functions

- `dac7_cfg_setup` Config Object Initialization function. 
```c
void dac7_cfg_setup ( dac7_cfg_t *cfg );
``` 
 
- `dac7_init` Initialization function. 
```c
err_t dac7_init ( dac7_t *ctx, dac7_cfg_t *cfg );
```

- `dac7_default_cfg` Click Default Configuration function. 
```c
void dac7_default_cfg ( dac7_t *ctx );
```

- `dac7_sw_reset` This function set software reset of selected channel of AD5624R Quad, 12-bit nanoDACs on DAC 7 Click board. 
```c
err_t dac7_sw_reset ( dac7_t *ctx );
```
 
- `dac7_set_power` This function set power mode of selected channel of AD5624R Quad, 12-bit nanoDACs on DAC 7 Click board. 
```c
err_t dac7_set_power ( dac7_t *ctx, uint8_t pwr_en, uint8_t sel_ch );
```

- `dac7_set_ch_voltage` This function set 12-bit value of 3-bit command definition to the target 3-bit address command of AD5624R Quad, 12-bit nanoDACs on DAC 7 Click board. 
```c
err_t dac7_set_ch_voltage ( dac7_t *ctx, uint8_t addr_ch, uint16_t vol_val, uint16_t v_ref_mv );
```

### Application Init

> Application Init performs Logger and Click initialization. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dac7_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    dac7_cfg_setup( &cfg );
    DAC7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac7_init( &dac7, &cfg );
    
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, " ------  DAC 7 Click  ------\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
    
    v_ref_sel = DAC7_VREF_5000mV;

    if ( dac7_sw_reset( &dac7 ) == DAC7_SUCCESS )
    {
        log_printf( &logger, "   Software reset   \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );
        for ( ; ; );
    }
    
    Delay_ms ( 500 );
    log_printf( &logger, "--------------------------\r\n\n" );

    
    if ( dac7_set_power( &dac7, DAC7_PWR_ON_ENABLE, DAC7_SELECT_CHANNEL_ALL ) == DAC7_SUCCESS )
    {
        log_printf( &logger, "   All channel Power On   \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );

        for ( ; ; );
    }

    Delay_ms ( 500 );
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, " -- Initialization  done. --\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> In this example, we adjust the DAC output voltage from 1000 mV to 4000 mV 
> for the channels, starting from channel A to channel D 
> and then set the DAC output voltage to 5000 mV for all channels.
> Results are being sent to UART Terminal where you can track their changes.
> All data logs write on USB UART changes every 5 sec.

```c
void application_task ( void )
{
    if ( dac7_set_ch_voltage ( &dac7, DAC7_ADDRESS_CHANNEL_A, 1000, v_ref_sel ) == DAC7_SUCCESS )
    {
        log_printf( &logger, "  Channel A : 1000 mV  \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );
        for ( ; ; );
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "--------------------------\r\n\n" );
    
    if ( dac7_set_ch_voltage ( &dac7, DAC7_ADDRESS_CHANNEL_B, 2000, v_ref_sel ) == DAC7_SUCCESS )
    {
        log_printf( &logger, "  Channel B : 2000 mV  \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );
        for ( ; ; );
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "--------------------------\r\n\n" );
    
    if ( dac7_set_ch_voltage ( &dac7, DAC7_ADDRESS_CHANNEL_C, 3000, v_ref_sel ) == DAC7_SUCCESS )
    {
        log_printf( &logger, "  Channel C : 3000 mV  \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );
        for ( ; ; );
    }
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "--------------------------\r\n\n" );
    
    if ( dac7_set_ch_voltage ( &dac7, DAC7_ADDRESS_CHANNEL_D, 4000, v_ref_sel ) == DAC7_SUCCESS )
    {
        log_printf( &logger, "  Channel D : 4000 mV  \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );
        for ( ; ; );
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "--------------------------\r\n\n" );

    if ( dac7_set_ch_voltage ( &dac7, DAC7_ADDRESS_CHANNEL_ALL, 5000, v_ref_sel ) == DAC7_SUCCESS )
    {
        log_printf( &logger, " All Channels: 5000 mV \r\n" );
    }
    else
    {
        log_printf( &logger, "   ERROR   \r\n" );
        for ( ; ; );
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "--------------------------\r\n\n" );
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
