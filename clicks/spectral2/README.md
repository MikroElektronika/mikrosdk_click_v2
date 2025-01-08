
---
# Spectral 2 Click

> [Spectral 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2973) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2973&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application enables usage of multispectral color sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Spectral2

### Example Key Functions

- `spectral2_cfg_setup` Config Object Initialization function. 
```c
void spectral2_cfg_setup ( spectral2_cfg_t *cfg );
``` 
 
- `spectral2_init` Initialization function. 
```c
err_t spectral2_init ( spectral2_t *ctx, spectral2_cfg_t *cfg );
```

- `spectral2_default_cfg` Click Default Configuration function. 
```c
void spectral2_default_cfg ( spectral2_t *ctx );
```

- `spectral2_set_integration_time` Function for calculating integration time. 
```c
void spectral2_set_integration_time ( spectral2_t *ctx, uint8_t cur_time );
```
 
- `spectral2_get_data` Function for reading Data. 
```c
int16_t spectral2_get_data ( spectral2_t *ctx, uint8_t data_reg );
```

- `spectral2_get_calibrated_data` Function that reads calibrated data. 
```c
float spectral2_get_calibrated_data ( spectral2_t *ctx, uint8_t data_reg );
```

### Application Init

> Driver initialize, reset module and configuration measurement

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    spectral2_cfg_t cfg;
    uint8_t cfg_data;

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

    spectral2_cfg_setup( &cfg );
    SPECTRAL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spectral2_init( &spectral2, &cfg );

    spectral2_reset( &spectral2 );

    Delay_100ms( );
    log_printf( &logger, "--- System init ---\r\n" );

    cfg_data = ( SPECTRAL2_NORMAL_OPERATION | SPECTRAL2_INT_DISABLE |
                                   SPECTRAL2_GAIN_16X |
                                   SPECTRAL2_MODE_2 );

    spectral2_default_cfg( &spectral2, cfg_data );

    Delay_1sec( );
}
```

### Application Task

> Reads the brightness value with R, G, B, I, O and V filter, every 1 second, and logs on to USBUART.

```c
void application_task ( void )
{
    float f_data;

    //  Task implementation.

    log_printf( &logger, "-------------------\r\n" );

    f_data = spectral2_get_calibrated_data( &spectral2, SPECTRAL2_CALIBRATED_DATA_R );
    log_printf( &logger, "-- R ( Red data ) : %.2f \r\n", f_data );
    
    f_data = spectral2_get_calibrated_data( &spectral2, SPECTRAL2_CALIBRATED_DATA_G );
    log_printf( &logger, "-- G ( Green data ) : %.2f\r\n", f_data );
    
    f_data = spectral2_get_calibrated_data( &spectral2, SPECTRAL2_CALIBRATED_DATA_B );
    log_printf( &logger, "-- B ( Blue data ) : %.2f\r\n", f_data );
    
    f_data = spectral2_get_calibrated_data( &spectral2, SPECTRAL2_CALIBRATED_DATA_Y );
    log_printf( &logger, "-- Y ( Yellow data ) : %.2f\r\n", f_data );
    
    f_data = spectral2_get_calibrated_data( &spectral2, SPECTRAL2_CALIBRATED_DATA_O );
    log_printf( &logger, "-- O ( Orange data ) : %.2f\r\n", f_data );
    
    f_data = spectral2_get_calibrated_data( &spectral2, SPECTRAL2_CALIBRATED_DATA_V );
    log_printf( &logger, "-- V ( Violet data ) : %.2f\r\n", f_data );
    
    Delay_1sec( );
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
