
---
# PAC1921 Click

> [PAC1921 Click](https://www.mikroe.com/?pid_product=MIKROE-2910) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2910&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases how to measure voltage, current or power (load) data using the 
  PAC1921 chip. Required modules are first initialized and after used to read and
  display the measured data. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PAC1921

### Example Key Functions

- `pac1921_cfg_setup` Config Object Initialization function. 
```c
void pac1921_cfg_setup ( pac1921_cfg_t *cfg );
``` 
 
- `pac1921_init` Initialization function. 
```c
err_t pac1921_init ( pac1921_t *ctx, pac1921_cfg_t *cfg );
```

- `pac1921_default_cfg` Click Default Configuration function. 
```c
void pac1921_default_cfg ( pac1921_t *ctx );
```

- This function writes data to the specified register address/es and saves the 
  state of the register/s so it doesn't write the same value/s twice.
> void pac1921_write_to_reg ( pac1921_t *ctx, uint8_t reg_addr, uint8_t *write_data, uint8_t len );
 
- This function gathers voltage/power data from the PAC1921 chip and, depending
  on the measurement mode, converts those raw values into a more suitable form.
> float pac1921_get_measured_data ( pac1921_t *ctx, uint8_t measurement_mode, uint8_t sample_num );

- `pac1921_set_int_pin` This function sets the digital output on the interrupt pin. 
```c
void pac1921_set_int_pin ( pac1921_t *ctx, uint8_t output );
```

### Application Init

> This function initializes and configures the logger and Click modules. Default settings
  are written to three control/configuration registers in the default_cfg(...) function. 

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    pac1921_cfg_t cfg;

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

    pac1921_cfg_setup( &cfg );
    PAC1921_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pac1921_init( &pac1921, &cfg );
    Delay_ms ( 100 );
    pac1921_default_cfg( &pac1921 );
    Delay_ms ( 100 );
}
```

### Application Task

> This function reads and displays voltage, current or power data from the chip, depending
  on the specified measurement mode and sample count. It does so every half a second. 

```c
void application_task ( )
{
    float read_data;

    read_data = pac1921_get_measured_data( &pac1921, PAC1921_MEASUREMENT_MODE_V_BUS_FREE_RUN,
                                                     PAC1921_SAMPLE_RATE_512 );

    if ( pac1921.aux.measurement_mode_old == PAC1921_MEASUREMENT_MODE_V_POWER_FREE_RUN )
    {
        log_printf( &logger, " * Power: %.2f W * \r\n", read_data );
    }
    else
    {
        log_printf( &logger, " * Voltage: %.2f mV * \r\n", read_data );
    }

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
