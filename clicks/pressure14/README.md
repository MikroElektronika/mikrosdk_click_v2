
---
# Pressure 14 Click

> [Pressure 14 Click](https://www.mikroe.com/?pid_product=MIKROE-4424) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4424&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This examples used ABP2 Series are piezoresistive silicon pressure sensors offering a digital output for reading pressure over the specified full scale pressure span and temperature range. 
They are calibrated and temperature compensated for sensor offset, sensitivity, temperature effects and accuracy errors (which include non-linearity, repeatability and hysteresis) using an 
on-board Application Specific IntegratedCircuit (ASIC).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure14

### Example Key Functions

- `pressure14_cfg_setup` Config Object Initialization function.
```c
void pressure14_cfg_setup ( pressure14_cfg_t *cfg );
```

- `pressure14_init` Initialization function.
```c
err_t pressure14_init ( pressure14_t *ctx, pressure14_cfg_t *cfg );
```

- `pressure14_measure_cmd` This function sends output measurement command that causes the ABP2 series pressure sensor to exit standby mode and enter operating mode.
```c
void pressure14_measure_cmd ( pressure14_t *ctx );
```

- `pressure14_check_busy_flag_int` This function returns the INT pin state which indicates the End-of-conversion for ABP2 series pressure sensor on Pressure 14 Click board.
```c
uint8_t pressure14_check_busy_flag_int ( pressure14_t *ctx );
```

- `pressure14_read_press_and_temp` This function reads 24-bit pressure, 24-bit temperature data and 8-bit status register from the ABP2 series pressure sensor on Pressure 14 Click board.
```c
void pressure14_read_press_and_temp ( pressure14_t *ctx, uint8_t *status_byte, uint32_t *pressure_data, uint32_t *temp_data );
```

### Application Init

> Initialization driver enables I2C.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    pressure14_cfg_t pressure14_cfg;    /**< Click config object. */

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
    pressure14_cfg_setup( &pressure14_cfg );
    PRESSURE14_MAP_MIKROBUS( pressure14_cfg, MIKROBUS_1 );
    err_t init_flag = pressure14_init( &pressure14, &pressure14_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
		log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The output measurement command is sent first forcing the ABP2 pressure sensor to exit standby mode and enter operating mode. The device busy state is evaluated via the 
end-of-conversion pin ( INT ) following the pressure and temperature data acquisition and calculation. The results are being sent to the Usart Terminaland repeats every 5 seconds.

```c
void application_task ( void ) 
{
    pressure14_measure_cmd( &pressure14 );
    Delay_ms ( 10 );
    
    if ( pressure14_check_busy_flag_int( &pressure14 ) == 1 ) {
        pressure14_read_press_and_temp ( &pressure14, &status, &pressure_tmp, &temperature_tmp );    
        pressure = pressure14_get_pressure( pressure_tmp, PRESSURE14_CONV_UNIT_MILIBAR );
        temperature = pressure14_get_temperature( temperature_tmp, PRESSURE14_CONV_UNIT_CELSIUS );
    
        log_printf( &logger, " Pressure    : %.2f mbar \r\n", pressure );
        log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
        log_printf( &logger, "-------------------------\r\n" );
    }
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
