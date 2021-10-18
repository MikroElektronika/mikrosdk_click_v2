\mainpage Main Page

---
# Hall Current 8 25A click

Hall Current 8 Click is a compact add-on board that contains a precise solution for AC/DC current sensing. This board features the TLI4971-A025T5, a high-precision coreless current sensor for industrial/consumer applications from Infineon Technologies. The TLI4971-A025T5 has an analog interface and two fast overcurrent detection outputs, which support the protection of the power circuitry. Galvanic isolation is also provided according to the magnetic sensing principle. Infineon's monolithic Hall technology enables accurate and highly linear measurement of currents with a full scale up to 25A. This Click board™ is suitable for AC/DC current measurement applications: electrical drives, general-purpose inverters, chargers, current monitoring, overload, over-current detection, and many more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent-825a_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hall-current-8-click-25a)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the HallCurrent825A Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for HallCurrent825A Click driver.

#### Standard key functions :

- `hallcurrent825a_cfg_setup` Config Object Initialization function.
```c
void hallcurrent825a_cfg_setup ( hallcurrent825a_cfg_t *cfg );
```

- `hallcurrent825a_init` Initialization function.
```c
HALLCURRENT825A_RETVAL hallcurrent825a_init ( hallcurrent825a_t *ctx, hallcurrent825a_cfg_t *cfg );
```

- `hallcurrent825a_default_cfg` Click Default Configuration function.
```c
void hallcurrent825a_default_cfg ( hallcurrent825a_t *ctx );
```

#### Example key functions :

- `hallcurrent825a_calibration` This function sets the calibration value into the offset data structure of the TLI4971 high precision coreless current sensor on Hall Current 8 25A Click board.
```c
HALLCURRENT825A_RETVAL hallcurrent825a_calibration ( hallcurrent825a_t *ctx, hallcurrent825a_offset_t *offset_val );
```

- `hallcurrent825a_get_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
HALLCURRENT825A_RETVAL hallcurrent825a_get_voltage ( hallcurrent825a_t *ctx, float *avr_voltage );

```

- `hallcurrent825a_get_current` This function reads results of AD conversion of the AN pin and converts them to proportional current level.
```c
HALLCURRENT825A_RETVAL hallcurrent825a_get_current ( hallcurrent825a_t *ctx, hallcurrent825a_offset_t *offset_val, float *current );
```

## Example Description

> This library contains API for Hall Current 8 25A Click driver. The library initializes and defines the ADC drivers. The library also includes a function for calibration, current measurement and overcurrent detection.

**The demo application is composed of two sections :**

### Application Init

> Initializes ADC driver, calibrate AD conversion of the AN pin and start to write log.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;                          /**< Logger config object. */
    hallcurrent825a_cfg_t hallcurrent825a_cfg;  /**< Click config object. */

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

   hallcurrent825a_cfg_setup( &hallcurrent825a_cfg );
   HALLCURRENT825A_MAP_MIKROBUS( hallcurrent825a_cfg, MIKROBUS_1 );
    if ( hallcurrent825a_init( &hallcurrent825a, &hallcurrent825a_cfg ) == ADC_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
   Delay_ms( 1000 );

   log_printf( &logger, "---------------------------\r\n" );
   log_printf( &logger, " Turn OFF the power supply \r\n" );
   Delay_ms( 5000 );
   
   log_printf( &logger, "---------------------------\r\n" );
   log_printf( &logger, "     Start Calibration     \r\n" );
   hallcurrent825a_calibration ( &hallcurrent825a, &offset_val );
   Delay_ms( 1000 );
   
   log_printf( &logger, "---------------------------\r\n");
   log_printf( &logger, " Turn ON the power supply  \r\n" );
   Delay_ms( 5000 );
   
   log_printf( &logger, "---------------------------\r\n");
   log_printf( &logger, "    Start measurements :   \r\n");
   log_printf( &logger, "---------------------------\r\n");
}

```

### Application Task

> This is an example that demonstrates the use of the Hall Current 8 25A click board. In this example, we read and display current data [A],  ADC value and AN pin voltage level [V]. Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) {
    float hallcurrent825a_current = 0;
    
    if ( hallcurrent825a_get_current ( &hallcurrent825a, &offset_val, &hallcurrent825a_current ) != ADC_ERROR ) {
        log_printf( &logger, "   Current     : %.2f [A]\r\n", hallcurrent825a_current );
    }
    
    uint16_t hallcurrent825a_an_value = 0;

    if ( hallcurrent825a_read_an_pin_value ( &hallcurrent825a, &hallcurrent825a_an_value ) != ADC_ERROR ) {
        log_printf( &logger, "   ADC Value   : %u\r\n", hallcurrent825a_an_value );
    }

    float hallcurrent825a_an_voltage = 0;

    if ( hallcurrent825a_read_an_pin_voltage ( &hallcurrent825a, &hallcurrent825a_an_voltage ) != ADC_ERROR ) {
        log_printf( &logger, "   AN Voltage  : %.2f [V]\r\n", hallcurrent825a_an_voltage );
    }
    log_printf( &logger, "---------------------------\r\n");
    Delay_ms( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent825A

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
