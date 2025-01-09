
---
# UVC Click

> [UVC Click](https://www.mikroe.com/?pid_product=MIKROE-4144) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4144&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This Click is capable of measuring UVC spectrum in the range of 220nm up to 280nm and light 
> intensity from 0mW/cm² up to 9.3mW/cm². With high sensitivity and good solar blindness, 
> it can be used for monitoring sterilization lamps. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Uvc

### Example Key Functions

- `uvc_cfg_setup` Config Object Initialization function. 
```c
void uvc_cfg_setup ( uvc_cfg_t *cfg );
``` 
 
- `uvc_init` Initialization function. 
```c
err_t uvc_init ( uvc_t *ctx, uvc_cfg_t *cfg );
```

- `uvc_read_raw_data` This function reads 12bit raw data. 
```c
uint16_t uvc_read_raw_data ( uvc_t *ctx );
```
 
- `uvc_get_voltage` This function calculate voltage from raw data. 
```c
float uvc_get_voltage ( uvc_t *ctx );
```

- `uvc_calculate_power` This function calculate power from voltage. 
```c
float uvc_calculate_power ( float voltage );
```

### Application Init

> Initializes the driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    uvc_cfg_t cfg;

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

    uvc_cfg_setup( &cfg );
    UVC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uvc_init( &uvc, &cfg );
}

  
```

### Application Task

> Reads sensor raw data and calculates voltage and power of UVC light.
> The measured values will be displayed on the USB UART every 1500 ms.

```c
void application_task ( void )
{
    uint16_t raw_data;
    float voltage;
    float power;
    
    raw_data = uvc_read_raw_data( &uvc );
    log_printf( &logger, "Raw data: %d\r\n", raw_data );
    
    voltage = uvc_get_voltage( &uvc );
    log_printf( &logger, "Voltage: %.4f mV\r\n", voltage );

    power = uvc_calculate_power( voltage );
    log_printf( &logger, "Power: %.4f mW/cm2\r\n", power );

    log_printf( &logger, "----------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 500 );
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
