
---
# Ecg 6 Click

> [Ecg 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4061) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4061&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> ECG 6 Click contain integrated electrocardiogram, pulse oximeter, 
> heart rate monitor sensor module.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ecg6

### Example Key Functions

- `ecg6_cfg_setup` Config Object Initialization function. 
```c
void ecg6_cfg_setup ( ecg6_cfg_t *cfg );
``` 
 
- `ecg6_init` Initialization function. 
```c
err_t ecg6_init ( ecg6_t *ctx, ecg6_cfg_t *cfg );
```

- `ecg6_default_cfg` Click Default Configuration function. 
```c
void ecg6_default_cfg ( ecg6_t *ctx );
```

- `ecg6_get_sample_data` This function gets one sample from FIFO. 
```c
void ecg6_get_sample_data ( ecg6_t *ctx, ecg6_element_t *element, uint8_t num_sample );
```
 
- `plot_ecg_data` Sends ECG sensor data to SerialPlot. 
```c
static void plot_ecg_data (  uint32_t ecg_data  );
```

- `plot_ppg_data` Sends PPG sensor data to SerialPlot. 
```c
static void plot_ppg_data (  uint32_t ir_data, uint32_t red_data  );
```

### Application Init

> Initialize I2C module and all necessary pins. Checking communication accuracy
> and running default configuration for measurement.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ecg6_cfg_t cfg;

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

    ecg6_cfg_setup( &cfg );
    ECG6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ecg6_init( &ecg6, &cfg );
    
    Delay_ms ( 1000 );
    
    DEMO_EXAMPLE = PPG_EXAMPLE;
   
    // Dummy read
    ecg6_check_path_id( &ecg6 );
    Delay_ms ( 100 );
    
    device_check = ecg6_check_path_id( &ecg6 );
    
    if ( device_check != 0 )
    {
       log_printf( &logger, " -- > Device ERROR!!! \r\n" );
       for ( ; ; );
    }
    log_printf( &logger, " -- > Device OK!!! \r\n" );

    if ( DEMO_EXAMPLE == ECG_EXAMPLE )
    {
        ecg6_default_cfg( &ecg6 );
    }
    else
    {
        ecg6_ppg_default_config( &ecg6 );
    }

    log_printf( &logger, " ---- Configuration done ----- \r\n" );
    Delay_ms ( 1000 );

    time_cnt = 0;
}
```

### Application Task

> Measures an ECG signal or PPG sensor and draws a graph on a SerialPlot

```c
void application_task ( void )
{
    ecg6_element_t sample;
    
    if ( ecg6_int_pin_state(&ecg6) == 0 ) {
        
        ecg6_get_sample_data( &ecg6, &sample, 0x00 );
    
        if ( DEMO_EXAMPLE == ECG_EXAMPLE )
        {
            plot_ecg_data( sample.element_1 );
        }
        
        else
        {
            plot_ppg_data( sample.element_1, sample.element_2 );
        }
    }
}
```

### Note

> When using ECG measurement - PPG measurement must be switched off ...
> Drawing speeds vary for PPG and ECG sensor.

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
