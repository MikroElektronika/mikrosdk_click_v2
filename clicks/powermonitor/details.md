
---
# Power Monitor click

> Power Monitor Click is a compact add-on board that represents an ultra-precise power monitoring solution. This board features the INA228, a digital power monitor with a 20-bit delta-sigma ADC specifically designed for current-sensing applications from Texas Instruments. The INA228 reports current, bus voltage, temperature, power, energy, and charge accumulation while employing a precision ±0.5 % integrated oscillator, all while performing the needed calculations in the background. It can measure a full-scale differential input of ±163.84mV or ±40.96mV across a resistive shunt sense element, with common-mode voltage support up to +85V. This Click board™ is suitable for current-sensing applications in DC-DC converters, power inverters, telecom equipment, industrial measurements, and many more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/powermonitor_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/power-monitor-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the PowerMonitor Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for PowerMonitor Click driver.

#### Standard key functions :

- `powermonitor_cfg_setup` Config Object Initialization function.
```c
void powermonitor_cfg_setup ( powermonitor_cfg_t *cfg );
```

- `powermonitor_init` Initialization function.
```c
err_t powermonitor_init ( powermonitor_t *ctx, powermonitor_cfg_t *cfg );
```

- `powermonitor_default_cfg` Click Default Configuration function.
```c
err_t powermonitor_default_cfg ( powermonitor_t *ctx );
```

#### Example key functions :

- `powermonitor_get_vshunt` Power Monitor get shunt voltage function.
```c
err_t powermonitor_get_vshunt ( powermonitor_t *ctx, float *vshunt );
```

- `powermonitor_get_vbus` Power Monitor get bus voltage function.
```c
err_t powermonitor_get_vbus ( powermonitor_t *ctx, float *vbus );
```

- `powermonitor_get_current` Power Monitor get current function.
```c
err_t powermonitor_get_current ( powermonitor_t *ctx, float *current );
```

## Example Description

> This library contains API for Power Monitor Click driver.
> The library initializes and defines the I2C bus drivers 
> to write and read data from registers. 
> The library also includes a function for reading 
> Shunt and Bus voltage ( mV ), Current ( mA ), Power ( W ), Energy ( J ),   
> as well as the Temperature in degrees Celsius.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C  module, log UART, and additional pins. 
> After the driver init and then executes a default configuration, 
> the app checks communication, display Manufacturer, Stores Device and Revision ID. 

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;                    /**< Logger config object. */
    powermonitor_cfg_t powermonitor_cfg;  /**< Click config object. */
    static uint8_t manufacturer_id[ 2 ];
    static uint16_t dieid;
    static uint8_t rev_id;
    
    powermonitor.shunt = 0.28;

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
    powermonitor_cfg_setup( &powermonitor_cfg );
    POWERMONITOR_MAP_MIKROBUS( powermonitor_cfg, MIKROBUS_1 );
    err_t init_flag = powermonitor_init( &powermonitor, &powermonitor_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    powermonitor_default_cfg ( &powermonitor );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 100 );
    
    powermonitor_get_id( &powermonitor, &manufacturer_id, &dieid, &rev_id );
    log_printf( &logger, "  Manufacturer ID  : %.2s\r\n", manufacturer_id );
    log_printf( &logger, "  Stores Device ID : 0x%.3X\r\n", dieid );
    log_printf( &logger, "  Revision ID      : 0x%.1X\r\n", rev_id );
    log_printf( &logger, "----------------------------\r\n" );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that shows the use of a Power Monitor Click board™.
> Measures and displays Shunt voltage ( mV ), Bus voltage ( mV ), 
> Current ( mA ), Power ( W ), Energy ( J ) and Temperature ( degrees Celsius ). 
> Results are being sent to the USART terminal where the user can track their changes. 
> This task repeats every 2.5 sec.

```c

void application_task ( void ) 
{
    static float vshunt, vbus, current, power, energy, temperature;
    
    powermonitor_get_vshunt( &powermonitor, &vshunt );
    log_printf( &logger, " Shunt voltage : %.2f mV\r\n", vshunt );
    Delay_ms ( 100 ); 
    
    powermonitor_get_vbus( &powermonitor, &vbus );
    log_printf( &logger, " BUS voltage   : %.2f mV\r\n", vbus );
    Delay_ms ( 100 );
    
    powermonitor_get_current( &powermonitor, &current );
    log_printf( &logger, " Current       : %.2f mA\r\n", current );
    Delay_ms ( 100 ); 
    
    powermonitor_get_power( &powermonitor, &power );
    log_printf( &logger, " Power         : %.6f W\r\n", power );
    Delay_ms ( 100 ); 
    
    powermonitor_get_energy( &powermonitor, &energy );
    log_printf( &logger, " Energy        : %.6f J\r\n", energy );
    log_printf( &logger, "- - - - - - - - - - - - - - \r\n" );
    Delay_ms ( 100 ); 
    
    powermonitor_get_temperature( &powermonitor, &temperature );
    log_printf( &logger, " Temperature   : %.2f C\r\n", temperature );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PowerMonitor

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
