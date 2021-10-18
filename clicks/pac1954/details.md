
---
# PAC1954 click

PAC1954 Click is a compact add-on board that contains an energy monitoring solution. This board features the PAC1954, a four-channel DC power/energy monitor from Microchip Technology. It uses real-time calibration to minimize offset and gain errors with no input filters required for this device.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pac1954_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pac1954-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the PAC1954 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for PAC1954 Click driver.

#### Standard key functions :

- `pac1954_cfg_setup` Config Object Initialization function.
```c
void pac1954_cfg_setup ( pac1954_cfg_t *cfg );
```

- `pac1954_init` Initialization function.
```c
err_t pac1954_init ( pac1954_t *ctx, pac1954_cfg_t *cfg );
```

- `pac1954_default_cfg` Click Default Configuration function.
```c
err_t pac1954_default_cfg ( pac1954_t *ctx );
```

#### Example key functions :

- `pac1954_refresh_cmd` This function updates the readable registers for the VBUS, VSENSE, Power, accumulator 
outputs and accumulator count by issuing the REFRESH command. The values will be static until 
the next REFRESH command.
```c
err_t pac1954_refresh_cmd ( pac1954_t *ctx );
```

- `pac1954_get_calc_measurement` This function calls the function for getting the selected 
measurement data and performs all the necessary calculations to get 
the measurement value in standard unit.
```c
err_t pac1954_get_calc_measurement( pac1954_t *ctx, uint8_t meas_sel, uint8_t ch_sel, uint8_t avg_sel, uint8_t meas_mode, float *data_out );
```

- `pac1954_generic_write` This function writes a desired number of data bytes starting from
the selected register by using I2C serial interface.
```c
err_t pac1954_generic_write ( pac1954_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );
```

## Example Description

> This example demonstrates the use of PAC1954 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    pac1954_cfg_t pac1954_cfg;  /**< Click config object. */

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
    pac1954_cfg_setup( &pac1954_cfg );
    PAC1954_MAP_MIKROBUS( pac1954_cfg, MIKROBUS_1 );
    err_t init_flag = pac1954_init( &pac1954, &pac1954_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    pac1954_default_cfg ( &pac1954 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the voltage, current, and power from Channel 1 and displays all 
> values on the USB UART once per second.

```c

void application_task ( void )
{
    float vsource;
    float isense;
    float power;

    pac1954_refresh_cmd( &pac1954 );
    
    pac1954_get_calc_measurement( &pac1954, PAC1954_MEAS_SEL_V_SOURCE, 
                                            PAC1954_CH_SEL_CH_1, 
                                            PAC1954_AVG_SEL_ENABLE, 
                                            PAC1954_MEAS_MODE_BIPOLAR_FSR,
                                            &vsource );
    pac1954_get_calc_measurement( &pac1954, PAC1954_MEAS_SEL_I_SENSE, 
                                            PAC1954_CH_SEL_CH_1, 
                                            PAC1954_AVG_SEL_ENABLE, 
                                            PAC1954_MEAS_MODE_BIPOLAR_FSR, 
                                            &isense );
    pac1954_get_calc_measurement( &pac1954, PAC1954_MEAS_SEL_P_SENSE, 
                                            PAC1954_CH_SEL_CH_1, 
                                            0, 
                                            PAC1954_MEAS_MODE_BIPOLAR_FSR, 
                                            &power );
    
    log_printf( &logger, " Voltage: %.3f V\r\n", vsource );
    log_printf( &logger, " Current: %.3f A\r\n", isense );
    log_printf( &logger, " Power: %.3f W\r\n", power );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PAC1954

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
