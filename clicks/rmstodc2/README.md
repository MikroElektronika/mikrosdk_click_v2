\mainpage Main Page

---
# RMS to DC 2 click

> RMS to DC 2 Click is a compact add-on board that converts the RMS of the input signal into a DC voltage. This board features the AD8436, a low-cost, low-power, true RMS-to-DC converter from Analog Devices. The AD8436 is a translinear precision, low-power, true RMS-to-DC converter that delivers true RMS or average rectified value of AC waveform. It features high accuracy, a wide dynamic input range (100μV rms to 3V rms), a wide bandwidth of up to 1MHz, and more. This Click board™ makes the perfect solution for the development of various true RMS digital multimeter applications, panel meters and gauges, AC + DC measurement applications, a true RMS measurement of an audio signal, and other similar applications that require accurate RMS value readings.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rmstodc2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rms-to-dc-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2023.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the RMS to DC 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RMS to DC 2 Click driver.

#### Standard key functions :

- `rmstodc2_cfg_setup` Config Object Initialization function.
```c
void rmstodc2_cfg_setup ( rmstodc2_cfg_t *cfg );
```

- `rmstodc2_init` Initialization function.
```c
err_t rmstodc2_init ( rmstodc2_t *ctx, rmstodc2_cfg_t *cfg );
```

#### Example key functions :

- `rmstodc2_set_vref` This function sets the voltage reference for RMS to DC 2 click driver.
```c
err_t rmstodc2_set_vref ( rmstodc2_t *ctx, float vref );
```

- `rmstodc2_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t rmstodc2_read_voltage ( rmstodc2_t *ctx, float *voltage );
```

## Example Description

> This example demonstrates the use of the RMS to DC 2 click board by measuring the RMS voltage of the input signal.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rmstodc2_cfg_t rmstodc2_cfg;  /**< Click config object. */

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
    rmstodc2_cfg_setup( &rmstodc2_cfg );
    RMSTODC2_MAP_MIKROBUS( rmstodc2_cfg, MIKROBUS_1 );
    err_t init_flag = rmstodc2_init( &rmstodc2, &rmstodc2_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the RMS voltage of the input signal and displays the results on the USB UART approximately once per second.

```c

void application_task ( void )
{
    float voltage = 0;
    if ( RMSTODC2_OK == rmstodc2_read_voltage ( &rmstodc2, &voltage ) ) 
    {
        log_printf( &logger, " RMS voltage : %.3f[V]\r\n\n", voltage * RMSTODC2_RMS_VOLTAGE_COEF );
        Delay_ms( 1000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RMStoDC2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
