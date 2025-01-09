
---
# CO 2 Click

> [CO 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3196) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3196&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application enables usage of very accurate CO sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CO2

### Example Key Functions

- `co2_cfg_setup` Config Object Initialization function. 
```c
void co2_cfg_setup ( co2_cfg_t *cfg );
``` 
 
- `co2_init` Initialization function. 
```c
err_t co2_init ( co2_t *ctx, co2_cfg_t *cfg );
```

- `co2_read_adc` Function reads the converted data (CO) from the 12-bit AD converter. 
```c
void co2_read_adc ( co2_t *ctx, uint16_t *data_out );
```
 
- `co2_enable` Function puts the device to enabled or to disabled state. 
```c
void co2_enable ( co2_t *ctx, uint8_t state );
```

- `co2_get_co2_ppm` Function reads the CO converted data and calculates this value to the ppm. 
```c
 co2_get_co2_ppm ( co2_t *ctx, float *co2_data );
```

### Application Init

> Initializes I2C interface and performs the device configuration for properly working.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    co2_cfg_t cfg;
    uint8_t temp_w;

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

    co2_cfg_setup( &cfg );
    CO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    co2_init( &co2, &cfg );

    Delay_ms ( 500 );
    
    temp_w = CO2_WRITE_MODE;
    co2_generic_write( &co2, CO2_LOCK_REG, &temp_w, 1 );
    temp_w = CO2_STANDBY_MODE;
    co2_generic_write( &co2, CO2_MODECN_REG, &temp_w, 1 );
    temp_w = CO2_3500_OHM_TIA_RES | CO2_100_OHM_LOAD_RES;
    co2_generic_write( &co2, CO2_TIACN_REG, &temp_w, 1 );
    temp_w = CO2_VREF_EXT | CO2_50_PERCENTS_INT_ZERO | CO2_BIAS_POL_NEGATIVE | CO2_0_PERCENTS_BIAS;
    co2_generic_write( &co2, CO2_REFCN_REG, &temp_w, 1 );
    
    log_printf( &logger, "CO 2 is initialized\r\n\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> Gets CO (Carbon Monoxide) data as ppm value every 300 miliseconds.
> Results will be logged on UART. The CO value range is from 0 to 1000 ppm.

```c
void application_task ( void )
{
    float co2_value;
   
    co2_wait_i2c_ready( &co2 );
    co2_get_co2_ppm( &co2, &co2_value );
    
    log_printf( &logger, "CO : %.2f ppm\r\n", co2_value );
    Delay_ms ( 300 );
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
