
---
# Environment 4 click

> Environment 4 Click is a compact add-on board combining 4th-generation SHT humidity and SGP air-quality sensing solutions from Sensirion. This board features SHT41A-AD1B and SGP41, an I2C-configurable high-accuracy relative humidity/temperature combined with a MOx-based gas sensor. The SHT41A-AD1B offers linearized digital output alongside temperature/humidity accuracy up to ±0.3°C/±2%RH. It performs best within the operating range of 5-60°C and 20-80%RH. With the help of SGP41, which features a temperature-controlled micro hotplate, it also provides a humidity-compensated VOC and NOx-based indoor air quality signal.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/environment4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/environment-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Environment 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Environment 4 Click driver.

#### Standard key functions :

- `environment4_cfg_setup` Config Object Initialization function.
```c
void environment4_cfg_setup ( environment4_cfg_t *cfg );
```

- `environment4_init` Initialization function.
```c
err_t environment4_init ( environment4_t *ctx, environment4_cfg_t *cfg );
```

#### Example key functions :

- `environment4_sht_read_meas_hp` This function reads the temperature and humidity measurements with high precision from SHT41A device.
```c
err_t environment4_sht_read_meas_hp ( environment4_t *ctx, float *temp, float *hum );
```

- `environment4_sgp_exe_conditioning` This function executes conditioning command for SGP41 device by using I2C serial interface.
```c
err_t environment4_sgp_exe_conditioning ( environment4_t *ctx, uint16_t comp_rh, uint16_t comp_t, uint16_t *sraw_voc );
```

- `environment4_sgp_meas_raw_signals` This function measures raw signals for SGP41 device by using I2C serial interface.
```c
err_t environment4_sgp_meas_raw_signals ( environment4_t *ctx, uint16_t comp_rh, uint16_t comp_t, uint16_t *sraw_voc, uint16_t *sraw_nox );
```

## Example Description

> This example demonstrates the use of Environment 4 click board by reading the temperature and humidity data and calculating VOC and NOx indexes.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, and reads and displays the SGP41 sensor unique serial number
and performs its build-in self-test. After that performs the SHT41 sensor software reset
and reads its unique serial number. Finally, it initializes the sensirion gas index algorithm
for VOC and NOx index calculation.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    environment4_cfg_t environment4_cfg;  /**< Click config object. */

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
    environment4_cfg_setup( &environment4_cfg );
    ENVIRONMENT4_MAP_MIKROBUS( environment4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == environment4_init( &environment4, &environment4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint16_t serial_num_sgp[ 3 ];
    if ( ENVIRONMENT4_OK == environment4_sgp_get_serial_num ( &environment4, serial_num_sgp ) )
    {
        log_printf ( &logger, " SGP Serial number: 0x%.4X%.4X%.4X\r\n", 
                     serial_num_sgp[ 0 ], serial_num_sgp[ 1 ], serial_num_sgp[ 2 ] );
    }
    
    uint8_t test_result_sgp;
    if ( ENVIRONMENT4_OK == environment4_sgp_exe_self_test ( &environment4, &test_result_sgp ) )
    {
        log_printf ( &logger, " SGP Self test result: " );
        if ( ENVIRONMENT4_SGP_SELF_TEST_OK == test_result_sgp )
        {
            log_printf ( &logger, "OK\r\n" );
        }
        else
        {
            if ( ENVIRONMENT4_SGP_SELF_TEST_VOC_PIXEL == test_result_sgp )
            {
                log_printf ( &logger, "VOC pixel fail; " );
            }
            if ( ENVIRONMENT4_SGP_SELF_TEST_NOX_PIXEL == test_result_sgp )
            {
                log_printf ( &logger, "NOx pixel fail; " );
            }
            log_printf ( &logger, "\r\n" );
        }
    }
    
    if ( ENVIRONMENT4_OK == environment4_sht_soft_reset ( &environment4 ) )
    {
        log_printf ( &logger, " SHT Software reset\r\n" );
        Delay_1sec ( );
    }
    
    uint32_t serial_num_sht;
    if ( ENVIRONMENT4_OK == environment4_sht_read_serial_num ( &environment4, &serial_num_sht ) )
    {
        log_printf ( &logger, " SHT Serial number: 0x%.8LX\r\n", serial_num_sht );
    }
    
    log_printf ( &logger, " Initialize Gas Index algorithm for VOC and NOx\r\n" );
    GasIndexAlgorithm_init ( &voc_params, GasIndexAlgorithm_ALGORITHM_TYPE_VOC );
    GasIndexAlgorithm_init ( &nox_params, GasIndexAlgorithm_ALGORITHM_TYPE_NOX );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the temperature (degC) and the relative humidity (%RH) data from SHT41 sensor with high precision.
For the first 10 seconds it executes NOx conditioning and after that it reads the raw signals for VOC and NOx
data and processes them with sensirion's gas index algorithm for calculating VOC and NOx indexes.
All data will be displayed on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float temperature, humidity;
    uint16_t comp_rh, comp_t, sraw_voc, sraw_nox;
    int32_t voc_index, nox_index;
    static uint8_t conditioning_num = 10;
    Delay_ms ( 1000 );
    if ( ENVIRONMENT4_OK == environment4_sht_read_meas_hp ( &environment4, &temperature, &humidity ) )
    {
        log_printf ( &logger, "\r\n Temperature: %.2f degC\r\n", temperature );
        log_printf ( &logger, " Humidity: %.2f %%RH\r\n", humidity );
        
        comp_rh = ( uint16_t ) ( humidity * ENVIRONMENT4_SHT_DATA_RESOLUTION / 
                                 ( ENVIRONMENT4_SHT_ABS_MAX_HUM - ENVIRONMENT4_SHT_ABS_MIN_HUM ) );
        comp_t = ( uint16_t ) ( ( temperature - ENVIRONMENT4_SHT_ABS_MIN_TEMP ) * ENVIRONMENT4_SHT_DATA_RESOLUTION / 
                                ( ENVIRONMENT4_SHT_ABS_MAX_TEMP - ENVIRONMENT4_SHT_ABS_MIN_TEMP ) );
        if ( conditioning_num ) 
        {
            if ( ENVIRONMENT4_OK == environment4_sgp_exe_conditioning ( &environment4, comp_rh, comp_t, &sraw_voc ) )
            {
                conditioning_num--;
            }
        } 
        else 
        {
            if ( ENVIRONMENT4_OK == environment4_sgp_meas_raw_signals ( &environment4, comp_rh, comp_t, &sraw_voc, &sraw_nox ) )
            {
                GasIndexAlgorithm_process( &voc_params, ( int32_t ) sraw_voc, &voc_index );
                GasIndexAlgorithm_process( &nox_params, ( int32_t ) sraw_nox, &nox_index );
                log_printf ( &logger, " VOC Index: %ld\r\n", voc_index );
                log_printf ( &logger, " NOx Index: %ld\r\n", nox_index );
            }
        }
    }
}
```

## Note

> Time required for reliably detecting VOC and NOx events on switching ON is typically less than 60 seconds.
Refer to the SGP41 sensor datasheet for more timing specifications.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Environment4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
