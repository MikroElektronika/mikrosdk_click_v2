
---
# Pot 3 Click

> [Pot 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3691) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3691&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This example gets voltage, calculates it to millivolts and then logs it to the terminal. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pot3

### Example Key Functions

- `pot3_cfg_setup` Config Object Initialization function. 
```c
void pot3_cfg_setup ( pot3_cfg_t *cfg );
``` 
 
- `pot3_init` Initialization function. 
```c
err_t pot3_init ( pot3_t *ctx, pot3_cfg_t *cfg );
```

- `pot3_read_adc` This function reads the result of AD conversion. 
```c
uint16_t pot3_read_adc ( pot3_t* ctx );
```
 
- `pot3_read_avg_adc` This function reads the averaged result of AD conversions. 
```c
uint16_t pot3_read_avg_adc ( pot3_t* ctx, uint16_t n_samples );
```

- `pot3_get_vout`  This function returns VOUT value calculated to millivolts. 
```c
uint16_t pot3_get_vout ( pot3_t* ctx, uint8_t vref_sel, uint16_t n_samples );
```

### Application Init

> Initializes device and sets required pins.


```c
void application_init ( void )
{
	log_cfg_t log_cfg;
    pot3_cfg_t pot3_cfg;

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

    pot3_cfg_setup( &pot3_cfg );
    POT3_MAP_MIKROBUS( pot3_cfg, MIKROBUS_1 );
    pot3_init( &pot3, &pot3_cfg );
}
```

### Application Task

> Reads VOUT value calculated to millivolts with 2000 conversions
> included in one measurement cycle. 

```c
void application_task ( void )
{
	voltage_mv = pot3_get_vout( &pot3, POT3_VREF_2V, 2000);
	log_printf( &logger, " VOUT : %d mV\r\n", voltage_mv );
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
