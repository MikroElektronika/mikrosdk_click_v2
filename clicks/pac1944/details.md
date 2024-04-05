
---
# PAC1944 click

PAC1944 Click is a compact add-on board that contains an energy monitoring solution. This board features the PAC1944, a multi-channel DC power/energy monitor from Microchip Technology. It uses real-time calibration to minimize offset and gain errors with no input filters required for this device.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pac1944_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pac1944-click)

---


#### Click library

- **Author**        : Stefan Nikolic
- **Date**          : dec 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the PAC1944 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
This library contains API for PAC1944 Click driver.
```

#### Standard key functions :

- `pac1944_cfg_setup` Config Object Initialization function.
```c
void pac1944_cfg_setup ( pac1944_cfg_t *cfg );
```

- `pac1944_init` Initialization function.
```c
PAC1944_RETVAL pac1944_init ( pac1944_t *ctx, pac1944_cfg_t *cfg );
```

- `pac1944_default_cfg` Click Default Configuration function.
```c
void pac1944_default_cfg ( pac1944_t *ctx );
```

#### Example key functions :

- `pac1944_setup_config` PAC1944 setup config function.
```c
void pac1944_setup_config ( pac1944_t *ctx, pac1944_setup_t cfg_data );
```

- `pac1944_refresh_cmd` PAC1944 refresh command.
```c
void pac1944_refresh_cmd ( pac1944_t *ctx );
```

- `pac1944_get_calc_measurement` PAC1944 get calculated measurement function.
```c
float pac1944_get_calc_measurement ( pac1944_t *ctx, uint8_t meas_sel, uint8_t ch_sel, uint8_t avg_sel, uint8_t meas_mode );
```

## Examples Description

> This demo application shows an example of measuring voltage,
> current and power in a selected part of the circuit. Note that
> PAC1944 is a high side power monitor, therefore the desired
> channel should be connected accordingly.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module, log UART and additional pins.
> In addition, a default configuration is performed as followed:
> - Sample mode is 1024, adaptive accumulation;
> - INT pin is set as an alert;
> - SLW pin is set as slow sampling rate control;
> - All channels are on;
> - Channel 1 is set for bipolar measurements;
> - Channel 2 is set for bipolar measurements reduced by half;
> - Channel 3 and 4 are set for unipolar measurements.

```c
void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    pac1944_cfg_t pac1944_cfg;  /**< Click config object. */

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

    pac1944_cfg_setup( &pac1944_cfg );
    PAC1944_MAP_MIKROBUS( pac1944_cfg, MIKROBUS_1 );
    err_t init_flag = pac1944_init( &pac1944, &pac1944_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    pac1944_device_state( &pac1944, PAC1944_DEV_ENABLE );
    Delay_ms ( 100 );
    pac1944_default_cfg ( &pac1944 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The application sends a refresh command which stores the
> measurement data in registers. Measurements are acquired
> for voltage, current and power on channel 1 of PAC1944
> click board. The last 8 measurements are averaged and
> calculated in bipolar mode. Process is repeated every
> two seconds.

```c
void application_task ( void ) {
    float voltage_sens;
    float current_sens;
    float power_sens;
    
    pac1944_refresh_cmd( &pac1944 );
    
    voltage_sens = pac1944_get_calc_measurement( &pac1944, PAC1944_MEAS_SEL_V_SOURCE,
                                                           PAC1944_CH_SEL_CH_1,
                                                           PAC1944_AVG_SEL_ENABLE,
                                                           PAC1944_MEAS_MODE_BIPOLAR_FSR );
    
    current_sens = pac1944_get_calc_measurement( &pac1944, PAC1944_MEAS_SEL_I_SENSE,
                                                           PAC1944_CH_SEL_CH_1,
                                                           PAC1944_AVG_SEL_ENABLE,
                                                           PAC1944_MEAS_MODE_BIPOLAR_FSR );
    
    power_sens = pac1944_get_calc_measurement( &pac1944,   PAC1944_MEAS_SEL_P_SENSE,
                                                           PAC1944_CH_SEL_CH_1,
                                                           PAC1944_AVG_SEL_ENABLE,
                                                           PAC1944_MEAS_MODE_BIPOLAR_FSR );
    
    
    log_printf( &logger, "  Voltage :  %.6f   V \r\n", voltage_sens );
    log_printf( &logger, "  Current :  %.6f   A \r\n", current_sens );
    log_printf( &logger, "  Power   :  %.6f   W \r\n", power_sens );
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PAC1944

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
