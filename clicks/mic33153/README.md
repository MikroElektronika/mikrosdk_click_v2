
---
# MIC33153 Click

> [MIC33153 Click](https://www.mikroe.com/?pid_product=MIKROE-2887) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2887&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This app enables step-down (buck) converter.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Mic33153

### Example Key Functions

- `mic33153_cfg_setup` Config Object Initialization function. 
```c
void mic33153_cfg_setup ( mic33153_cfg_t *cfg );
``` 
 
- `mic33153_init` Initialization function. 
```c
err_t mic33153_init ( mic33153_t *ctx, mic33153_cfg_t *cfg );
```

- `mic33153_default_cfg` Click Default Configuration function. 
```c
void mic33153_default_cfg ( mic33153_t *ctx );
```

- `mic33153_write_dac` This function writes 12-bit value to DAC and that causes that output voltage be seted on determined value. 
```c
void mic33153_write_dac ( mic33153_t *ctx, const uint16_t value_dac );
```
 
- `mic33153_enable_out` This function enables or disables output voltage depending on the state value. 
```c
void mic33153_enable_out ( mic33153_t *ctx, uint8_t state );
```

- This function hecks state of PG (INT) pin. If state is 1 that means that output voltage is above 92% of its steady
- `mic33153_check_power_good` state voltage. If state is 0 that means that output voltage is below 86% of its steady state voltage. 
```c
uint8_t mic33153_check_power_good ( mic33153_t *ctx );
```

### Application Init

> Initializes Click driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    mic33153_cfg_t cfg;

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

    mic33153_cfg_setup( &cfg );
    MIC33153_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic33153_init( &mic33153, &cfg );
    Delay_ms ( 100 );
}
```

### Application Task

> Activates the output voltage of the device, and then sets output voltage to various different values.
> All data is being logged on USB UART.  

```c
void application_task ( void )
{
    mic33153_enable_out( &mic33153, MIC33153_OUT_ENABLE );
    
    mic33153_write_dac ( &mic33153, MIC33153_VOLTAGE_1000MV );
    log_printf( &logger, "Output voltage set to 1000mV\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    mic33153_write_dac ( &mic33153, MIC33153_VOLTAGE_1500MV );
    log_printf( &logger, "Output voltage set to 1500mV\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    mic33153_write_dac ( &mic33153, MIC33153_VOLTAGE_2000MV );
    log_printf( &logger, "Output voltage set to 2000mV\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    mic33153_write_dac ( &mic33153, MIC33153_VOLTAGE_2500MV );
    log_printf( &logger, "Output voltage set to 2500mV\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    mic33153_write_dac ( &mic33153, MIC33153_VOLTAGE_3000MV );
    log_printf( &logger, "Output voltage set to 3000mV\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    mic33153_write_dac ( &mic33153, MIC33153_VOLTAGE_3200MV );
    log_printf( &logger, "Output voltage set to 3200mV\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-----------------------------------\r\n" );
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
