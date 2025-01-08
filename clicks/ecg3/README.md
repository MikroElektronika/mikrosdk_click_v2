
---
# ECG 3 Click

> [ECG 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3273) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3273&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This Click is made for ECG and HR, 
> equipped with an ultra-low power, single channel, integrated biopotential AFE, 
> with the ECG and R-to-R detection functionality. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ecg3

### Example Key Functions

- `ecg3_cfg_setup` Config Object Initialization function. 
```c
void ecg3_cfg_setup ( ecg3_cfg_t *cfg );
``` 
 
- `ecg3_init` Initialization function. 
```c
err_t ecg3_init ( ecg3_t *ctx, ecg3_cfg_t *cfg );
```

- `ecg3_default_cfg` Click Default Configuration function. 
```c
void ecg3_default_cfg ( ecg3_t *ctx );
```

- `ecg3_get_ecg` Function reads ECG data from FIFO register. 
```c
void ecg3_get_ecg ( ecg3_t *ctx, uint32_t *out_ecg );
```
 
- `ecg3_check_status` Function checks a status flag for the desired interrupt. 
```c
uint8_t ecg3_check_status ( ecg3_t *ctx, uint32_t bit_mask );
```

- `ecg3_get_rtor` Function reads Heart Rate and R - R data and calculates HR data to BPM, and RR data to ms. 
```c
void ecg3_get_rtor ( ecg3_t *ctx, uint16_t *out_hr, uint16_t *out_rr );
```

### Application Init

> Initializes SPI interface and performs the all necessary configuration for device to work properly.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ecg3_cfg_t cfg;

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

    ecg3_cfg_setup( &cfg );
    ECG3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ecg3_init( &ecg3, &cfg );

    ecg3_sw_reset( &ecg3 );
    ecg3_fifo_reset( &ecg3 );
    Delay_ms ( 100 );

    ecg3_default_cfg ( &ecg3 );
    Delay_ms ( 300 );
}
```

### Application Task

> Reads ECG Data every 8ms and sends this data to the serial plotter.

```c
void application_task ( void )
{
    ecg3_get_ecg( &ecg3, &ecg_data );

    plot_ecg( );
}
```

### Note

> Additional Functions :
>  - void plot_ecg() - Sends ECG Data to the serial plotter.
>  - void log_rtor_() - Sends Heart Rate and R - R Data to the uart terminal. 

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
