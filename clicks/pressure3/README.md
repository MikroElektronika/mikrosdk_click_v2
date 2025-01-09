
---
# Pressure 3 Click

> [Pressure 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2293) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2293&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This application is digital barometric pressure sensor. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure3

### Example Key Functions

- `pressure3_cfg_setup` Config Object Initialization function. 
```c
void pressure3_cfg_setup ( pressure3_cfg_t *cfg );
``` 
 
- `pressure3_init` Initialization function. 
```c
err_t pressure3_init ( pressure3_t *ctx, pressure3_cfg_t *cfg );
```

- `pressure3_default_cfg` Click Default Configuration function. 
```c
void pressure3_default_cfg ( pressure3_t *ctx );
```

- `pressure3_get_t_p_data` Get temperature pressure. 
```c
void pressure3_get_t_p_data ( pressure3_t *ctx, float *temperature, float *presure, pressure3_coeff_t *coeff_struct );
```
 
- `pressure3_get_coefficients` Get coefficients. 
```c
void pressure3_get_coefficients ( pressure3_t *ctx, pressure3_coeff_t *coeff_struct );
```

- `pressure3_get_measurement_data` Read the coefficients value for calculation function. 
```c
int32_t pressure3_get_measurement_data ( pressure3_t *ctx, uint8_t mbs_reg_addr );
```

### Application Init

> Initialization device, set default configuration and start to write log. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure3_cfg_t cfg;

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

    pressure3_cfg_setup( &cfg );
    PRESSURE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure3_init( &pressure3, &cfg );
    pressure3_default_cfg( &pressure3 );
}
```

### Application Task

> This is an example which demonstrates the use of Pressure 3 Click board.
     Measured pressure and temperature data from the DPS310 sensor on Pressure 3 Click board.
     Results are being sent to the Usart Terminal where you can track their changes.
     All data logs write on usb uart changes for every 3 sec.

```c
void application_task ( void )
{
    float pressure;
    float temperature;

    pressure3_get_t_p_data( &pressure3, &temperature, &pressure, &coeff_struct );
    
    log_printf( &logger, " * Pressure: %.2f mbar * \r\n", pressure );
    log_printf( &logger, " * Temperature: %.2f C * \r\n", temperature );
    log_printf( &logger, " ----------------------- \r\n" );

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
