
---
# DAC 6 Click

> [DAC 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4206) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4206&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> DAC 6 Click carries 12-bit buffered Digital-to-Analog Converter. It converts digital value 
> to the corresponding voltage level using external voltage reference.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Dac6

### Example Key Functions

- `dac6_cfg_setup` Config Object Initialization function. 
```c
void dac6_cfg_setup ( dac6_cfg_t *cfg );
``` 
 
- `dac6_init` Initialization function. 
```c
err_t dac6_init ( dac6_t *ctx, dac6_cfg_t *cfg );
```

- `dac6_set_output` Function is used to set operation mode output channel and level. 
```c
float dac6_set_output ( dac6_t *ctx );
```
 
- `dac6_write_data` Sends 16-bit data to the device's input shift register. 
```c
void dac6_write_data ( dac6_t *ctx, uint16_t wr_data );
```

### Application Init

> Initalizes SPI driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dac6_cfg_t cfg;

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

    dac6_cfg_setup( &cfg );
    DAC6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac6_init( &dac6, &cfg );
}
```

### Application Task

> This example shows capabilities of DAC 6 Click by changeing
> output values from 0 to the maximum output range on all four channels.
> Output voltage is calculated by using the equation : 
> Vout = Vrefin * (set_out / 4095).

```c
void application_task ( void )
{
    for ( n_cnt = 0; n_cnt < 4096; n_cnt += 315 )
    {
        dac6.chan    = DAC6_CHANNEL_A;
        dac6.op_mod  = DAC6_WRITE_SPEC_UPDATE_OUTPUT;
        dac6.v_ref   = DAC6_V_REF_2048;
        dac6.set_out = n_cnt;
        
        v_out = dac6_set_output( &dac6 );
        
        log_printf( &logger, " Channel  A : VOUT ~ %.2f mV\r\n", v_out );
        log_printf( &logger, "--------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    for ( n_cnt = 0; n_cnt < 4096; n_cnt += 315 )
    {
        dac6.chan    = DAC6_CHANNEL_B;
        dac6.op_mod  = DAC6_WRITE_SPEC_UPDATE_OUTPUT;
        dac6.v_ref   = DAC6_V_REF_2048;
        dac6.set_out = n_cnt;
        
        v_out = dac6_set_output( &dac6 );
        
        log_printf( &logger, " Channel  B : VOUT ~ %.2f mV\r\n", v_out );
        log_printf( &logger, "--------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    for ( n_cnt = 0; n_cnt < 4096; n_cnt += 315 )
    {
        dac6.chan    = DAC6_CHANNEL_C;
        dac6.op_mod  = DAC6_WRITE_SPEC_UPDATE_OUTPUT;
        dac6.v_ref   = DAC6_V_REF_2048;
        dac6.set_out = n_cnt;
        
        v_out = dac6_set_output( &dac6 );
        
        log_printf( &logger, " Channel  C : VOUT ~ %.2f mV\r\n", v_out );
        log_printf( &logger, "--------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    for ( n_cnt = 0; n_cnt < 4096; n_cnt += 315 )
    {
        dac6.chan    = DAC6_CHANNEL_D;
        dac6.op_mod  = DAC6_WRITE_SPEC_UPDATE_OUTPUT;
        dac6.v_ref   = DAC6_V_REF_2048;
        dac6.set_out = n_cnt;
        
        v_out = dac6_set_output( &dac6 );
        
        log_printf( &logger, " Channel  D : VOUT ~ %.2f mV\r\n", v_out );
        log_printf( &logger, "--------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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
