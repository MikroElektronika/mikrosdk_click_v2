\mainpage Main Page

---
# ADC 12 click

ADC 12 Click is a compact add-on board that contains a fully-featured, general-purpose analog-to-digital converter. This board features the ADS7828, a low-power 12-bit data acquisition device that features a serial I2C interface and an 8-channel multiplexer from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/adc-12-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the ADC12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ADC12 Click driver.

#### Standard key functions :

- `adc12_cfg_setup` Config Object Initialization function.
```c
void adc12_cfg_setup ( adc12_cfg_t *cfg );
```

- `adc12_init` Initialization function.
```c
ADC12_RETVAL adc12_init ( adc12_t *ctx, adc12_cfg_t *cfg );
```

#### Example key functions :

- `adc12_read_voltage` This function reads the voltage in milivolts from the desired channel.
```c
err_t adc12_read_voltage ( adc12_t *ctx, uint8_t ch, uint16_t vref, float *data_out );
```

- `adc12_read_raw_data` This function reads raw 12-bit ADC data from the desired channel. 
```c
err_t adc12_read_raw_data ( adc12_t *ctx, uint8_t ch, uint16_t *data_out );
```

- `adc12_set_sd_mode` This function sets the input mode.
```c
void adc12_set_sd_mode ( adc12_t *ctx, uint8_t sd_mode );
```

## Example Description

> This example demonstrates the use of ADC 12 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and sets the input and power-down modes.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc12_cfg_t adc12_cfg;  /**< Click config object. */

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

    adc12_cfg_setup( &adc12_cfg );
    ADC12_MAP_MIKROBUS( adc12_cfg, MIKROBUS_1 );
    err_t init_flag = adc12_init( &adc12, &adc12_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    adc12_set_sd_mode ( &adc12, ADC12_CMD_SD_SINGLE_END );
    adc12_set_pd_mode( &adc12, ADC12_CMD_PD_IRON_ADON );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the RAW ADC data and converts it to voltage in milivolts and displays
> both values on the USB UART every second.

```c

void application_task ( void )
{
    uint16_t raw_adc;
    float voltage;

    adc12_read_raw_data ( &adc12, ADC12_SINGLE_END_CH0, &raw_adc );
    adc12_read_voltage ( &adc12, ADC12_SINGLE_END_CH0, ADC12_INTERNAL_VREF, &voltage );
    
    log_printf( &logger, " RAW ADC: %u \r\n", raw_adc );
    log_printf( &logger, " Voltage from Channel 0: %.2f mV \r\n", voltage );
    log_printf( &logger, " ---------------------------\r\n" );
    Delay_ms( 1000 );
}

```

## Note

> With internal reference voltage set the click measures up to 2500 mV.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
