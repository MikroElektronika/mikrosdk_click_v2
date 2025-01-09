
---
# ECG Click

> [ECG Click](https://www.mikroe.com/?pid_product=MIKROE-2455) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2455&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of ECG Click board. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ecg

### Example Key Functions

- `ecg_cfg_setup` Config Object Initialization function. 
```c
void ecg_cfg_setup ( ecg_cfg_t *cfg );
``` 
 
- `ecg_init` Initialization function. 
```c
err_t ecg_init ( ecg_t *ctx, ecg_cfg_t *cfg );
```

- `ecg_default_cfg` Click Default Configuration function. 
```c
void ecg_default_cfg ( ecg_t *ctx );
```

- `ecg_generic_read` This function read ADC data. 
```c
ecg_data_t ecg_generic_read ( ecg_t *ctx );
```
 
- `ecg_default_cfg` This function executes default configuration for ECG Click. 
```c
void ecg_default_cfg ( ecg_t *ctx );
```

- `ecg_init` This function initializes all necessary pins and peripherals used for this Click. 
```c
err_t ecg_init ( ecg_t *ctx, ecg_cfg_t *cfg );
```

### Application Init

> Initializes Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ecg_cfg_t cfg;

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

    ecg_cfg_setup( &cfg );
    Delay_ms ( 200 );
    ECG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ecg_init( &ecg, &cfg );
    Delay_ms ( 200 );

    time_read = 0;
}
```

### Application Task

> Reads ADC sends results on serial plotter.

```c
void application_task ( void )
{
    time_read++;
    read_adc = ecg_generic_read( &ecg );
    plot_res( read_adc , time_read);

    Delay_ms ( 5 );
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
