
---
# Illuminance Click

> Illuminance Click is a compact add-on board that mimics how humans perceive light. This board features ams AG’s TSL2583, a very-high sensitivity light-to-digital converter that transforms light intensity to a digital signal output capable of the direct I2C interface. It combines one broadband photodiode (visible plus infrared) and one infrared-responding photodiode on a single CMOS integrated circuit capable of providing a near-photopic response over an effective 16-bit dynamic range (16-bit resolution).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/illuminance_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/illuminance-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Illuminance Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Illuminance Click driver.

#### Standard key functions :

- `illuminance_cfg_setup` Config Object Initialization function.
```c
void illuminance_cfg_setup ( illuminance_cfg_t *cfg );
```

- `illuminance_init` Initialization function.
```c
err_t illuminance_init ( illuminance_t *ctx, illuminance_cfg_t *cfg );
```

- `illuminance_default_cfg` Click Default Configuration function.
```c
err_t illuminance_default_cfg ( illuminance_t *ctx );
```

#### Example key functions :

- `illuminance_set_atime` This function sets the timing register for the selected integration time.
```c
err_t illuminance_set_atime ( illuminance_t *ctx, float atime_ms );
```

- `illuminance_set_gain` This function sets the gain level.
```c
err_t illuminance_set_gain ( illuminance_t *ctx, uint8_t gain );
```

- `illuminance_read_raw_data` This function checks if the data is ready and then reads the raw ADC data from two channels.
```c
err_t illuminance_read_raw_data ( illuminance_t *ctx, uint16_t *ch_0, uint16_t *ch_1 );
```

## Example Description

> This example demonstrates the use of Illuminance Click board by reading and displaying the RAW channels data measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    illuminance_cfg_t illuminance_cfg;  /**< Click config object. */

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
    illuminance_cfg_setup( &illuminance_cfg );
    ILLUMINANCE_MAP_MIKROBUS( illuminance_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == illuminance_init( &illuminance, &illuminance_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ILLUMINANCE_ERROR == illuminance_default_cfg ( &illuminance ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the data ready interrupt, then reads the RAW channels data measurements
and displays the results on the USB UART. By default, the data ready interrupt triggers 
upon every ADC cycle which will be performed every 200ms.

```c

void application_task ( void )
{
    if ( !illuminance_get_int_pin ( &illuminance ) )
    {
        uint16_t ch0 = 0;
        uint16_t ch1 = 0;
        if ( ILLUMINANCE_OK == illuminance_read_raw_data ( &illuminance, &ch0, &ch1 ) )
        {
            log_printf ( &logger, " CH0: %u\r\n", ch0 );
            log_printf ( &logger, " CH1: %u\r\n\n", ch1 );
        }
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Illuminance

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
