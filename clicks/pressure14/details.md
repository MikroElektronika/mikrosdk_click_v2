
---
# Pressure 14 click

Pressure 14 Click is a compact add-on board that contains a board-mount pressure sensor. This board features the ABP2LANT060PG2A3XX, a piezoresistive silicon pressure sensor offering a digital output for reading pressure over the specified full-scale pressure span and a temperature range from Honeywell Sensing and Productivity Solutions. This I2C configurable sensor is calibrated and temperature compensated for sensor offset, sensitivity, temperature effects, and accuracy errors, including non-linearity, repeatability, and hysteresis, using an on-board ASIC. This Click board™ is suitable for pressure measurements in automotive applications, industrial and consumer applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure14_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pressure-14-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Pressure14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Pressure14 Click driver.

#### Standard key functions :

- `pressure14_cfg_setup` Config Object Initialization function.
```c
void pressure14_cfg_setup ( pressure14_cfg_t *cfg );
```

- `pressure14_init` Initialization function.
```c
err_t pressure14_init ( pressure14_t *ctx, pressure14_cfg_t *cfg );
```

#### Example key functions :

- `pressure14_measure_cmd` This function sends output measurement command that causes the ABP2 series pressure sensor to exit standby mode and enter operating mode.
```c
void pressure14_measure_cmd ( pressure14_t *ctx );
```

- `pressure14_check_busy_flag_int` This function returns the INT pin state which indicates the End-of-conversion for ABP2 series pressure sensor on Pressure 14 click board.
```c
uint8_t pressure14_check_busy_flag_int ( pressure14_t *ctx );
```

- `pressure14_read_press_and_temp` This function reads 24-bit pressure, 24-bit temperature data and 8-bit status register from the ABP2 series pressure sensor on Pressure 14 click board.
```c
void pressure14_read_press_and_temp ( pressure14_t *ctx, uint8_t *status_byte, uint32_t *pressure_data, uint32_t *temp_data );
```

## Example Description

> This examples used ABP2 Series are piezoresistive silicon pressure sensors offering a digital output for reading pressure over the specified full scale pressure span and temperature range. 
They are calibrated and temperature compensated for sensor offset, sensitivity, temperature effects and accuracy errors (which include non-linearity, repeatability and hysteresis) using an 
on-board Application Specific IntegratedCircuit (ASIC).

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables I2C.

```c

void application_init ( void ) {
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

void application_task ( void ) {
    pressure14_measure_cmd( &pressure14 );
    Delay_ms( 10 );
    
    if ( pressure14_check_busy_flag_int( &pressure14 ) == 1 ) {
        pressure14_read_press_and_temp ( &pressure14, &status, &pressure_tmp, &temperature_tmp );    
        pressure = pressure14_get_pressure( pressure_tmp, PRESSURE14_CONV_UNIT_MILIBAR );
        temperature = pressure14_get_temperature( temperature_tmp, PRESSURE14_CONV_UNIT_CELSIUS );
    
        log_printf( &logger, " Pressure    : %.2f mbar \r\n", pressure );
        log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
        log_printf( &logger, "-------------------------\r\n" );
    }
    Delay_ms( 2000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
