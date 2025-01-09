
---
# THERMO 5 Click

> [THERMO 5 Click](https://www.mikroe.com/?pid_product=MIKROE-2571) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2571&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This app measures internal and external temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.THERMO5

### Example Key Functions

- `thermo5_cfg_setup` Config Object Initialization function. 
```c
void thermo5_cfg_setup ( thermo5_cfg_t *cfg );
``` 
 
- `thermo5_init` Initialization function. 
```c
err_t thermo5_init ( thermo5_t *ctx, thermo5_cfg_t *cfg );
```

- `thermo5_default_cfg` Click Default Configuration function. 
```c
void thermo5_default_cfg ( thermo5_t *ctx );
```


 
- `thermo5_read_inter_temp` This function reads measurements made by internal diode. 
```c
float thermo5_read_inter_temp ( thermo5_t *ctx );
```

- `thermo5_read_extern_1_temp` This function reads measurements made by external 1 diode. 
```c
float thermo5_read_extern_1_temp ( thermo5_t *ctx );
```

- `thermo5_read_high_limit_stat` This function reads the High Limit Status register which utilises its lower nibble to represents which diodes have exceed their programmed high limit. 
```c
uint8_t thermo5_read_high_limit_stat ( thermo5_t *ctx );
```

### Application Init

> Initalizes device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo5_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    thermo5_cfg_setup( &cfg );
    THERMO5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo5_init( &thermo5, &cfg );
    Delay_ms ( 500 );
    log_printf( &logger, " Thermo 5 Click ready! \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that shows the most important functions that Thermo 5 Click has.

```c
void application_task ( void )
{
    float inter_temp;
    float exter_temp_1;
    float exter_temp_2;
    float exter_temp_3;

    inter_temp = thermo5_read_inter_temp( &thermo5 );
    log_printf( &logger, " Internal temperature :   %.2f \r\n", inter_temp );
    exter_temp_1 = thermo5_read_extern_1_temp( &thermo5 );
    log_printf( &logger, " External temperature 1 : %.2f \r\n", exter_temp_1 );
    exter_temp_2 = thermo5_read_extern_2_temp( &thermo5 );
    log_printf( &logger, " External temperature 2 : %.2f \r\n", exter_temp_2 );
    exter_temp_3 = thermo5_read_extern_3_temp( &thermo5 );
    log_printf( &logger, " External temperature 3 : %.2f \r\n", exter_temp_2 );
    log_printf( &logger, "---------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
