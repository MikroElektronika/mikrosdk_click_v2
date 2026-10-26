
---
# VCP Monitor 7 Click

> [VCP Monitor 7 Click](https://www.mikroe.com/?pid_product=MIKROE-7073) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7073&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Aug 2026.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of VCP Monitor 7 Click board by measuring the
differential voltage present between the input terminals of the high common mode
difference amplifier.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.VCPMonitor7

### Example Key Functions

- `vcpmonitor7_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void vcpmonitor7_cfg_setup ( vcpmonitor7_cfg_t *cfg );
```

- `vcpmonitor7_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t vcpmonitor7_init ( vcpmonitor7_t *ctx, vcpmonitor7_cfg_t *cfg );
```

- `vcpmonitor7_enable_device` This function enables the differential amplifier output stage by setting the EN pin to the high logic level.
```c
void vcpmonitor7_enable_device ( vcpmonitor7_t *ctx );
```

- `vcpmonitor7_enable_ref` This function enables the reference buffer by setting the REN pin to the high logic level.
```c
void vcpmonitor7_enable_ref ( vcpmonitor7_t *ctx );
```

- `vcpmonitor7_read_voltage_avg` This function reads a desired number of ADC samples and calculates the average voltage level.
```c
err_t vcpmonitor7_read_voltage_avg ( vcpmonitor7_t *ctx, uint16_t num_conv, float *voltage_avg );
```

- `vcpmonitor7_read_diff_voltage` This function reads the average amplifier output voltage and converts it to the differential voltage.
```c
err_t vcpmonitor7_read_diff_voltage ( vcpmonitor7_t *ctx, float *diff_volt );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vcpmonitor7_cfg_t vcpmonitor7_cfg;  /**< Click config object. */

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
    vcpmonitor7_cfg_setup( &vcpmonitor7_cfg );
    VCPMONITOR7_MAP_MIKROBUS( vcpmonitor7_cfg, MIKROBUS_POSITION_VCPMONITOR7 );
    err_t init_flag = vcpmonitor7_init( &vcpmonitor7, &vcpmonitor7_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the differential input voltage and displays the results on the USB UART
approximately once per second.

```c
void application_task ( void ) 
{
    float diff_volt = 0;

    if ( VCPMONITOR7_OK == vcpmonitor7_read_diff_voltage ( &vcpmonitor7, &diff_volt ) ) 
    {
        log_printf( &logger, " Differential voltage : %.3f[V]\r\n\n", diff_volt );
    }
    else
    {
        log_printf( &logger, " Differential voltage read error.\r\n\n" );
    }

    Delay_ms ( 1000 );
}
```

### Note

> The input common mode voltage must be at least 4.3V above the board ground for
the amplifier to operate in the linear region.

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
