\mainpage Main Page

---
# Hall Current 10 click

Hall Current 10 Click is a compact add-on board that provides economical and precise AC or DC current sensing solutions. This board features the ACHS-7194, a fully integrated Hall-effect-based isolated linear current sensor designed for the current range of ±40A from Broadcom Limited. Inside ACHS-7194 is a precise, low-offset, linear Hall circuit with a copper conduction path located near the surface of the die. Applied current flowing through this copper conduction path generates a magnetic field that the differential Hall sensors convert into a proportional voltage, where after that, the user is given the option to process the output voltage as an analog or digital value. This Click board™ is suitable for AC or DC current-sensing in industrial, commercial, and communications systems.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hall-current-10-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the HallCurrent10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for HallCurrent10 Click driver.

#### Standard key functions :

- `hallcurrent10_cfg_setup` Config Object Initialization function.
```c
void hallcurrent10_cfg_setup ( hallcurrent10_cfg_t *cfg );
```

- `hallcurrent10_init` Initialization function.
```c
HALLCURRENT10_RETVAL hallcurrent10_init ( hallcurrent10_t *ctx, hallcurrent10_cfg_t *cfg );
```

- `hallcurrent10_default_cfg` Click Default Configuration function.
```c
void hallcurrent10_default_cfg ( hallcurrent10_t *ctx );
```

#### Example key functions :

- `hallcurrent10_read_adc` Hall Current 10 I2C ADC reading function.
```c
HALLCURRENT10_RETVAL hallcurrent10_read_adc ( hallcurrent10_t *ctx, uint16_t *read_adc );
```

- `hallcurrent10_get_adc_volatge` Hall Current 10 get ADC voltage function.
```c
HALLCURRENT10_RETVAL hallcurrent10_get_adc_voltage ( hallcurrent10_t *ctx, float *adc_vtg );
```

- `hallcurrent10_get_current` Hall Current 10 get current function.
```c
HALLCURRENT10_RETVAL hallcurrent10_get_current ( hallcurrent10_t *ctx, float *current );
```

## Example Description

> This library contains API for Hall Current 10 Click driver.
> The demo application reads ADC value, ADC voltage and current value.

**The demo application is composed of two sections :**

### Application Init

> Initializes I2C driver and log UART.
> After driver initialization the app set default settings.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;                      /**< Logger config object. */
    hallcurrent10_cfg_t hallcurrent10_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    hallcurrent10_cfg_setup( &hallcurrent10_cfg );
    HALLCURRENT10_MAP_MIKROBUS( hallcurrent10_cfg, MIKROBUS_1 );
    err_t init_flag = hallcurrent10_init( &hallcurrent10, &hallcurrent10_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_info( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    hallcurrent10_default_cfg ( &hallcurrent10 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 100 );
}

```

### Application Task

> This is an example that demonstrates the use of the Hall Current 10 Click board™.
> In this example, we read and display the ADC values and current ( mA ) data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{
    hallcurrent10_read_adc( &hallcurrent10, &adc_data );
    log_printf( &logger, " ADC Value   : %d \r\n", adc_data );
    Delay_ms( 100 );
    
    hallcurrent10_get_adc_volatge( &hallcurrent10, &adc_voltage );
    log_printf( &logger, " ADC Voltage : %.2f mV \r\n", adc_voltage );
    log_printf( &logger, "- - - - - - - - - - -  - -\r\n" );
    Delay_ms( 100 );
    
    hallcurrent10_get_current ( &hallcurrent10, &current );
    log_printf( &logger, " Current     : %.2f mA \r\n", current );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 2000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
