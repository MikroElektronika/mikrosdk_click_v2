
---
# Qi Receiver Click

> [Qi Receiver Click](https://www.mikroe.com/?pid_product=MIKROE-2799) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2799&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application reads voltage, current and frequency.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.QiReceiver

### Example Key Functions

- `qireceiver_cfg_setup` Config Object Initialization function. 
```c
void qireceiver_cfg_setup ( qireceiver_cfg_t *cfg );
``` 
 
- `qireceiver_init` Initialization function. 
```c
err_t qireceiver_init ( qireceiver_t *ctx, qireceiver_cfg_t *cfg );
```

- `qireceiver_default_cfg` Click Default Configuration function. 
```c
void qireceiver_default_cfg ( qireceiver_t *ctx );
```

- `qireceiver_read_voltage` Function is used to measure current voltage in volt. 
```c
float qireceiver_read_voltage ( qireceiver_t *ctx );
```
 
- `qireceiver_read_current` Function is used to measure current amperage in mA. 
```c
 qireceiver_read_current ( qireceiver_t *ctx );
```

- `qireceiver_read_freq` Function is used to measure current frequency in hertz. 
```c
 qireceiver_read_freq ( qireceiver_t *ctx );
```

- `qireceiver_dev_enable` Function is used to enable the device. 
```c
void qireceiver_dev_enable ( qireceiver_t *ctx );
```

### Application Init

> Initalizes I2C driver, enables the device and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    qireceiver_cfg_t cfg;

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

    qireceiver_cfg_setup( &cfg );
    QIRECEIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    qireceiver_init( &qireceiver, &cfg );
    
    Delay_ms ( 100 );
    qireceiver_dev_enable( &qireceiver );
    log_printf( &logger, "-----------------\r\n" );
    log_printf( &logger, "Qi Receiver Click\r\n" );
    log_printf( &logger, "-----------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that shows the most important
        functions that Qi Receiver Click has, it mesures current voltage, amperage and frequency.

```c
void application_task ( void )
{
    float voltage;
    float current;
    float freq;
    
    voltage = qireceiver_read_voltage( &qireceiver );
    log_printf( &logger, "Voltage : %.2f V\r\n", voltage );

    current = qireceiver_read_current( &qireceiver );
    log_printf( &logger, "Current : %.2f mA\r\n", current );

    freq = qireceiver_read_freq( &qireceiver );
    log_printf( &logger, "Frequency : %.2f Hz\r\n", freq );
    
    log_printf( &logger, "-----------------\r\n" );
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
