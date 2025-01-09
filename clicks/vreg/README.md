
---
# VREG Click

> [VREG Click](https://www.mikroe.com/?pid_product=MIKROE-2443) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2443&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of VREG Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Vreg

### Example Key Functions

- `vreg_cfg_setup` Config Object Initialization function. 
```c
void vreg_cfg_setup ( vreg_cfg_t *cfg );
``` 
 
- `vreg_init` Initialization function. 
```c
err_t vreg_init ( vreg_t *ctx, vreg_cfg_t *cfg );
```

- `vreg_get_adc` Get ADC value function. 
```c
uint16_t vreg_get_adc ( vreg_t *ctx, uint8_t channel );
```
 
- `vreg_set_out_voltage ` Set output voltage function. 
```c
void vreg_set_out_voltage  ( vreg_t *ctx, uint16_t value_dac );
```

- `vreg_set_output_voltage_procentage` Set output voltage procentage function. 
```c
void vreg_set_output_voltage_procentage ( vreg_t *ctx, uint8_t value_dac_pct );
```

### Application Init

> Initializes driver and sets output voltage.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    vreg_cfg_t cfg;

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

    vreg_cfg_setup( &cfg );
    VREG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vreg_init( &vreg, &cfg );

    vreg_stop_measuring( &vreg );
    log_printf( &logger, " Stop Measuring \r\n" );
    Delay_1sec( );

    log_printf( &logger, " Set Out Voltage \r\n" );
    vreg_set_out_voltage( &vreg, 600 );
    Delay_1sec( );

    log_printf( &logger, " Start Measuring \r\n" );
    vreg_start_measuring( &vreg );
    Delay_1sec( );
}
```

### Application Task

> Reads ADC data from all 3 channels, converts those values to voltage 
> and displays the results on USB UART.

```c
void application_task ( void )
{
    ch_reg = vreg_get_adc( &vreg, VREG_CHANNEL_0 );
    voltage = ch_reg / 182.0;
   
    log_printf( &logger, " CH Reg  : %.2f V\r\n", voltage );
    
    Delay_10ms( );

    ch_in = vreg_get_adc( &vreg, VREG_CHANNEL_2 );
    voltage = ch_in / 182.0;
    
    log_printf( &logger, " CH In   : %.2f V\r\n", voltage );
    
    Delay_10ms( );
    
    ch_out = vreg_get_adc( &vreg, VREG_CHANNEL_1 );
    voltage = ch_out / 182.0;
    
    log_printf( &logger, " CH Out  : %.2f V\r\n", voltage );
    
    Delay_1sec( );
    log_printf( &logger, " ---------------------- \r\n" );
}
```## Application Output

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
