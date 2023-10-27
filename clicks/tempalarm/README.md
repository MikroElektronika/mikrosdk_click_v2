\mainpage Main Page

---
# Temp Alarm click

> Temp Alarm Click is a compact add-on board that adds temperature alarm functionalities to your project. This board features the PTMP4718, a high-accuracy remote and local temperature sensor from Texas Instruments. This temperature sensor has pin-programmable alert thresholds, with a fault queue for debounce.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/tempalarm_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temp-alarm-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Temp Alarm Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Temp Alarm Click driver.

#### Standard key functions :

- `tempalarm_cfg_setup` Config Object Initialization function.
```c
void tempalarm_cfg_setup ( tempalarm_cfg_t *cfg );
```

- `tempalarm_init` Initialization function.
```c
err_t tempalarm_init ( tempalarm_t *ctx, tempalarm_cfg_t *cfg );
```

- `tempalarm_default_cfg` Click Default Configuration function.
```c
err_t tempalarm_default_cfg ( tempalarm_t *ctx );
```

#### Example key functions :

- `tempalarm_write_reg` Temp Alarm register writing function.
```c
err_t tempalarm_write_reg ( tempalarm_t *ctx, uint8_t reg, uint8_t data_in );
```

- `tempalarm_read_remote_temperature` Temp Alarm remote sensor read temperature function.
```c
err_t tempalarm_read_remote_temperature ( tempalarm_t *ctx, float *temperature );
```

- `tempalarm_set_alarm_high_limit` Temp Alarm remote sensor set limit high temperature function.
```c
err_t tempalarm_set_alarm_high_limit ( tempalarm_t *ctx, float max_temperature );
```

## Example Description

> This example demonstrates the use of Temp Alarm click board by reading and displaying
  the temperature measurements and monitoring it.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and sets the Local sensor critical temperature at 30 degC with hysteresis of 1 degC,
  and Remote sensor alarm temperature at 30 degC.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tempalarm_cfg_t tempalarm_cfg;  /**< Click config object. */

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
    tempalarm_cfg_setup( &tempalarm_cfg );
    TEMPALARM_MAP_MIKROBUS( tempalarm_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == tempalarm_init( &tempalarm, &tempalarm_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPALARM_ERROR == tempalarm_default_cfg ( &tempalarm ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the temperature measurement in degrees Celsius and displays the results on the USB UART
  approximately once per second. Monitoring alarm and critical state.

```c
void application_task ( void ) 
{
    uint8_t flag_data = 0; 
    int8_t local_temp = 0;
    float remote_temp = 0;
    tempalarm_get_alarms( &tempalarm, &flag_data );
    if ( TEMPALARM_ADC_BUSY_MASK != ( TEMPALARM_ADC_BUSY_MASK & flag_data ) )
    {
        tempalarm_read_temperature( &tempalarm, &local_temp );
        tempalarm_read_remote_temp( &tempalarm, &remote_temp );
        log_printf( &logger, " Local temperature : %d degC \r\n" , ( int16_t ) local_temp );
        log_printf( &logger, " Remote temperature : %.3f degC \r\n" , remote_temp );
        log_printf( &logger, " -------------------------------- \r\n" );
    }
    if ( TEMPALARM_PIN_STATE_LOW == tempalarm_get_alr_pin( &tempalarm ) )
    {
        log_printf( &logger, " Alarm is on, remote temperature  \r\n" );
        log_printf( &logger, "      is higher then 30 degC      \r\n" );
        log_printf( &logger, " -------------------------------- \r\n" );
    }
    if ( TEMPALARM_PIN_STATE_LOW == tempalarm_get_tcr_pin( &tempalarm ) )
    {
        log_printf( &logger, " Alarm is on, local temperature  \r\n" );
        log_printf( &logger, "      is higher then 30 degC      \r\n" );
        log_printf( &logger, " -------------------------------- \r\n" );
    }
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TempAlarm

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
