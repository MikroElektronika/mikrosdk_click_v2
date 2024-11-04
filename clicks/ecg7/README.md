\mainpage Main Page

---
# ECG 7 Click

> ECG 7 Click is a compact add-on board that records the heart's electrical activity. This board features the MCP6N16, a single zero-drift instrumentation amplifier with selectable gain from Microchip. In addition to the jack connector provided for connecting the cable with ECG electrodes, this Click board™ offers the possibility of connecting electrodes through screw terminals or an onboard header if the electrode connection does not match the jack connector. Besides, the user is allowed to process the output signal in analog or digital form.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ecg7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ecg-7-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the ECG 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ECG 7 Click driver.

#### Standard key functions :

- `ecg7_cfg_setup` Config Object Initialization function.
```c
void ecg7_cfg_setup ( ecg7_cfg_t *cfg );
```

- `ecg7_init` Initialization function.
```c
err_t ecg7_init ( ecg7_t *ctx, ecg7_cfg_t *cfg );
```

#### Example key functions :

- `ecg7_read_raw_adc` This function reads raw ADC value.
```c
err_t ecg7_read_raw_adc ( ecg7_t *ctx, uint16_t *raw_adc );
```

- `ecg7_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t ecg7_read_voltage ( ecg7_t *ctx, float *voltage );
```

- `ecg7_set_vref` This function sets the voltage reference for ECG 7 Click driver.
```c
err_t ecg7_set_vref ( ecg7_t *ctx, float vref );
```

## Example Description

> This example demonstrates the use of ECG 7 Click board by reading and displaying the voltage from VOUT BUFF which can be visualized on the SerialPlot application.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ecg7_cfg_t ecg7_cfg;  /**< Click config object. */

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
    ecg7_cfg_setup( &ecg7_cfg );
    ECG7_MAP_MIKROBUS( ecg7_cfg, MIKROBUS_1 );
    err_t init_flag = ecg7_init( &ecg7, &ecg7_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the output voltage and displays it on the USB UART (SerialPlot) every 4ms approximately.

```c

void application_task ( void )
{
    float ecg7_an_voltage = 0;
    if ( ECG7_OK == ecg7_read_voltage ( &ecg7, &ecg7_an_voltage ) ) 
    {
        log_printf( &logger, "%.3f\r\n", ecg7_an_voltage );
        Delay_ms ( 4 );
    }
}

```

## Note

> We recommend using the SerialPlot tool for data visualizing. Please make sure to set up ECG electrodes properly.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ECG7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
