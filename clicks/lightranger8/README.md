\mainpage Main Page

---
# LightRanger 8 click

> LightRanger 8 Click is a compact add-on board that contains a ranging sensor with multi-target detection. This board features the VL53L3CX, the latest Time-of-Flight (ToF) product that embeds third-generation FlightSense patented technology from STMicroelectronics.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lightranger8_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lightranger-8-click)

---


#### Click library

- **Author**        : Stefan Nikolic
- **Date**          : jan 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the LightRanger8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LightRanger8 Click driver.

#### Standard key functions :

- `lightranger8_cfg_setup` Config Object Initialization function.
```c
void lightranger8_cfg_setup ( lightranger8_cfg_t *cfg );
```

- `lightranger8_init` Initialization function.
```c
LIGHTRANGER8_RETVAL lightranger8_init ( lightranger8_t *ctx, lightranger8_cfg_t *cfg );
```

- `lightranger8_default_cfg` Click Default Configuration function.
```c
void lightranger8_default_cfg ( lightranger8_t *ctx );
```

#### Example key functions :

- `lightranger8_set_measurement_timing_budget` This function sets the timing budget of the VL53Lx ranging sensor.
```c
LIGHTRANGER8_RETVAL lightranger8_set_measurement_timing_budget ( lightranger8_t *ctx, uint32_t budget_us );
```

- `lightranger8_start_measurement` This function enables the range measuring with the adjusted intermeasurement period.
```c
void lightranger8_start_measurement ( lightranger8_t *ctx, uint32_t period_ms );
```

- `lightranger8_get_distance` This function returns the corrected measured distance from the VL53Lx ranging sensor described in milimeters.
```c
uint16_t lightranger8_get_distance ( lightranger8_t *ctx );
```

## Example Description

> This demo application shows an example of distance measurement via VL53L3 ranging sensor.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module, log UART and additional pins.
After driver init, the app powers the device and performs
default settings of the ranging sensor including distance
mode and timing budget. The optional calibration helps
improvement of the accuracy on the targeted distance.
This process takes 10 second ( which can by modifed by
simply lowering the Delay_ms( 5000 ) value ) so the user can
place an object on the exact location. When calibration is
finished, device starts the measurement with intermeasurement
period set by the user.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;                           /**< Logger config object. */
    lightranger8_cfg_t lightranger8_cfg;         /**< Click config object. */

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

    lightranger8_cfg_setup( &lightranger8_cfg );
    LIGHTRANGER8_MAP_MIKROBUS( lightranger8_cfg, MIKROBUS_1 );
    err_t init_flag = lightranger8_init( &lightranger8, &lightranger8_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    lightranger8_power_on( &lightranger8 );
    log_printf( &logger, " Wait until the configuration of the chip is completed...\r\n" );
    if ( lightranger8_default_cfg( &lightranger8 ) != 0 ) {
        log_error( &logger, " Sensor config error. " );
        for ( ; ; );
    }
    lightranger8_set_distance_mode( &lightranger8, LIGHTRANGER8_DISTANCE_MODE_MEDIUM );
    lightranger8_set_measurement_timing_budget( &lightranger8, budget_us );
    Delay_ms( 1000 );

    log_printf( &logger, " -------------------------------------------------------------------------\r\n" );
    log_printf( &logger, " For calibration place an object at %.1f cm distance from sensor.\r\n", ( float )calibration_distance_mm / 10 );
    Delay_ms( 5000 );
    log_printf( &logger, " -------------------------------------------------------------------------\r\n" );
    log_printf( &logger, " ---------------    Sensor calibration is in progress...     ---------------\r\n" );
    Delay_ms( 5000 );
    lightranger8_calibrate_offset( &lightranger8, calibration_distance_mm, period_ms, &offset );
    Delay_ms( 500 );
    
    lightranger8_start_measurement( &lightranger8, period_ms );
    log_printf( &logger, " -------------------------------------------------------------------------\r\n" );
    log_printf( &logger, " -------------    Sensor measurement commencing...    -------------\r\n" );
    Delay_ms( 100 );
}

```

### Application Task

> A new data ready is checked as soon as possible which signals
the time required for the ranging sensor to perform the
measurement. An acqured distance is shown on the LOG with
the 2 seconds delay so the terminal is possible to read.

```c

void application_task ( void ) {
    uint16_t distance;
    
    while ( lightranger8_new_data_ready( &lightranger8 ) != 0 ) {
        Delay_1ms();
    }

    distance = lightranger8_get_distance( &lightranger8 );
    log_printf( &logger, " ----------------------\r\n" );
    log_printf( &logger, " Distance: %.1f cm \r\n", ( float )distance / 10 );
    Delay_ms( 2000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
