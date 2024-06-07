\mainpage Main Page

---
# Load Cell 8 click

> Load Cell 8 Click is a compact add-on board representing a weigh scale solution. This board features the ZSC31050, an advanced differential sensor signal conditioner from Renesas designed for high-precision signal conditioning in applications requiring detailed sensor-specific corrections. It excels in processing differential sensor signals for various resistive bridge sensors. The ZSC31050 is capable of highly accurate amplification, offering digital compensation of sensor offset, sensitivity, temperature drift, and non-linearity. It supports a broad signal range from 1mV/V to 275mV/V, making its use across industrial, medical, and consumer applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/loadcell8_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/load-cell-8-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Load Cell 8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Load Cell 8 Click driver.

#### Standard key functions :

- `loadcell8_cfg_setup` Config Object Initialization function.
```c
void loadcell8_cfg_setup ( loadcell8_cfg_t *cfg );
```

- `loadcell8_init` Initialization function.
```c
err_t loadcell8_init ( loadcell8_t *ctx, loadcell8_cfg_t *cfg );
```

- `loadcell8_default_cfg` Click Default Configuration function.
```c
err_t loadcell8_default_cfg ( loadcell8_t *ctx );
```

#### Example key functions :

- `loadcell8_read_raw_adc` This function reads raw ADC value by using I2C serial interface.
```c
err_t loadcell8_read_raw_adc ( loadcell8_t *ctx, uint32_t *raw_adc );
```

- `loadcell8_tare_scale` This function calculates the cell_data which is the raw ADC readings of the empty container by using I2C serial interface.
```c
err_t loadcell8_tare_scale ( loadcell8_t *ctx, loadcell8_data_t *cell_data );
```

- `loadcell8_calibration_weight` This function calibrates the weight by calculating the cell_data for the input calibration weight by using I2C serial interface.
```c
err_t loadcell8_calibration_weight ( loadcell8_t *ctx, uint16_t cal_val, loadcell8_data_t *cell_data );
```

## Example Description

> This example demonstrates the use of Load Cell 8 click by measuring the weight
 in grams of the goods from the load cell sensor connected to the click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and reads the tare scale of the empty container, and after
 that, it calibrates the weight scale with a known calibration weight.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    loadcell8_cfg_t loadcell8_cfg;  /**< Click config object. */

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
    loadcell8_cfg_setup( &loadcell8_cfg );
    LOADCELL8_MAP_MIKROBUS( loadcell8_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == loadcell8_init( &loadcell8, &loadcell8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LOADCELL8_ERROR == loadcell8_default_cfg ( &loadcell8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Remove all goods from the scale in the following 5 sec.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Calculating tare scale...\r\n" );
    if ( LOADCELL8_OK == loadcell8_tare_scale( &loadcell8, &cell_data ) )
    {
        log_printf( &logger, " Tarring complete!\r\n\n" );
    }
    else 
    {
        log_error( &logger, " Calculating tare scale." );
        for ( ; ; );
    }

    log_printf( &logger, " Place a %ug calibration weight on the scale in the following 5 sec.\r\n", 
                ( uint16_t ) LOADCELL8_WEIGHT_100G );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Calibrating weight...\r\n" );
    if ( LOADCELL8_OK == loadcell8_calibration_weight( &loadcell8, LOADCELL8_WEIGHT_100G, &cell_data ) ) 
    {
        log_printf( &logger, " Calibration complete!\r\n\n" );
    } 
    else 
    {
        log_error( &logger, " Calibrating weight." );
        for ( ; ; );
    }

    log_printf( &logger, " ___________________\r\n" );
    log_printf( &logger, " Start measurements:\r\n" );
    log_printf( &logger, " ___________________\r\n" );
    Delay_ms ( 500 );
}

```

### Application Task

> The demo application measures weight and shows the measurement of scales in grams [ g ].
  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    float weight_g = 0;
    if ( LOADCELL8_OK == loadcell8_get_weight( &loadcell8, &cell_data, &weight_g ) )
    {
        log_printf( &logger, " Weight : %.2f g \r\n", weight_g );
    }
    Delay_ms ( 100 );
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LoadCell8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
