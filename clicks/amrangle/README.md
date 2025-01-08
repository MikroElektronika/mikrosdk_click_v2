
---
# AMR Angle Click

> [AMR Angle Click](https://www.mikroe.com/?pid_product=MIKROE-4561) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4561&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Nikolic
- **Date**          : jan 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This demo application shows the performance of AMR Angle Click by reading and presenting the temperature and angle results on the UART log.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AMRAngle

### Example Key Functions

- `amrangle_cfg_setup` Config Object Initialization function.
```c
void amrangle_cfg_setup ( amrangle_cfg_t *cfg, uint8_t sel_toolchain );
```

- `amrangle_init` Initialization function.
```c
err_t amrangle_init ( amrangle_t *ctx, amrangle_cfg_t *cfg );
```

- `amrangle_default_cfg` Click Default Configuration function.
```c
void amrangle_default_cfg ( amrangle_t *ctx );
```

- `amrangle_angle_read` This function reads an angle in degrees.
```c
float amrangle_angle_read ( amrangle_t *ctx );
```

- `amrangle_read_vtp_temp` This function returns calculated temperature using vtp pin voltage.
```c
float amrangle_read_vtp_temp ( amrangle_t *ctx );
```

- `amrangle_gain_control_mode` This function sets the gain control mode pin which is used to compensate the sensor amplitude output for reduction of temperature variation.
```c
void amrangle_gain_control_mode ( amrangle_t *ctx, uint8_t gain_control );
```

### Application Init

> Starts up the UART LOG, SPI and ADC drivers. Performs the default settings like setting the adc vref, resolution and gpio pins.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    amrangle_cfg_t amrangle_cfg;    /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.

    amrangle_cfg_setup( &amrangle_cfg, AMRANGLE_ARM_TOOLCHAIN );  // Change when switching profile
    AMRANGLE_MAP_MIKROBUS( amrangle_cfg, MIKROBUS_1 );
    err_t init_flag = amrangle_init( &amrangle, &amrangle_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    amrangle_default_cfg( &amrangle );
    Delay_ms ( 500 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The application task consists of reading the temperature and angle data from the sensor and sending that data to the UART log every second.

```c
void application_task ( void ) 
{
    temperature_res = amrangle_read_vtp_temp( &amrangle );
    angle_res = amrangle_angle_read( &amrangle );
    log_printf( &logger, " Temperature: %.2f C\r\n", temperature_res );
    log_printf( &logger, " Angle: %.2f degrees\r\n", angle_res );
    log_printf( &logger, " --------------------------\r\n" );
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
