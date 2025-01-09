
---
# Hz to V Click

> [Hz to V Click](https://www.mikroe.com/?pid_product=MIKROE-2890) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2890&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the use of Hz to V Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HzToV

### Example Key Functions

- `hztov_cfg_setup` Config Object Initialization function. 
```c
void hztov_cfg_setup ( hztov_cfg_t *cfg );
``` 
 
- `hztov_init` Initialization function. 
```c
err_t hztov_init ( hztov_t *ctx, hztov_cfg_t *cfg );
```

- `hztov_set_enable` Set enable pin state. 
```c
void hztov_set_enable ( hztov_t *ctx, uint8_t state );
```

- `hztov_read_voltage` Read voltage function. 
```c
float hztov_read_voltage ( hztov_t *ctx );
```
 
- `hztov_set_input_frequency` Changing the output voltage function. 
```c
void hztov_set_input_frequency ( hztov_t *ctx, uint16_t freq );
```

### Application Init

> Initializes the driver and enables the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    hztov_cfg_t cfg;

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

    hztov_cfg_setup( &cfg );
    HZTOV_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hztov_init( &hztov, &cfg );
    
    hztov_set_enable ( &hztov, HZTOV_ENABLE );
    
    fin = HZTOV_MIN_FREQ;
    
    Delay_ms ( 100 );
}
```

### Application Task

> Sets the PWM frequency then reads the voltage from VO pin and logs all data on USB UART.

```c
void application_task ( void )
{
    if ( fin > HZTOV_MAX_FREQ )
        fin = HZTOV_MIN_FREQ;
    hztov_set_input_frequency( &hztov, fin );
    Delay_ms ( 1000 );
    log_printf( &logger, "Frequency: %u Hz \r\n", fin );
    voltage = 0;
    for ( uint8_t cnt = 0; cnt < 100; cnt++ )
    {
        voltage += hztov_read_voltage( &hztov );
    }
    log_printf( &logger, "Voltage: %.2f V \r\n", voltage / 100.0 );
    log_printf( &logger, "-------------------\r\n" );
    
    fin += 1000;
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> In order to set PWM frequency down to 1 kHz, the user will probably need to lower the main MCU clock frequency.
> The output voltage may vary, depending on the offset potentiometer setting on the Click.

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
