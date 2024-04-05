
---
# TFmini click

> TFmini Click is an adapter Click board™ used to interface a compatible ToF (Time of Flight) LiDAR sensor with the host MCU. This board features one four positions 1.25mm connector suitable for a TFmini LiDAR module (TFmini Plus and TFmini-S) specially made to measure an object's distance. Depending on the used LiDAR module, it is possible to achieve different measurement ranges and the use of a different serial interface, such as the UART or I2C. This Click board™ is suitable for various industrial environments like pedestrian detection, vehicle testing, and altitude.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/tfmini_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/tfmini-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2021.
- **Type**          : UART type


# Software Support

We provide a library for the TFmini Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for TFmini Click driver.

#### Standard key functions :

- `tfmini_cfg_setup` Config Object Initialization function.
```c
void tfmini_cfg_setup ( tfmini_cfg_t *cfg );
```

- `tfmini_init` Initialization function.
```c
err_t tfmini_init ( tfmini_t *ctx, tfmini_cfg_t *cfg );
```

- `tfmini_default_cfg` Click Default Configuration function.
```c
err_t tfmini_default_cfg ( tfmini_t *ctx );
```

#### Example key functions :

- `tfmini_get_firmware_version` This function reads the sensor firmware version.
```c
err_t tfmini_get_firmware_version ( tfmini_t *ctx, uint32_t *fw_version );
```

- `tfmini_get_measurement` This function reads the output data frame and obtains the distance, strength and temperature values from it.
```c
err_t tfmini_get_measurement ( tfmini_t *ctx, int16_t *distance, int16_t *strength, float *temperature );
```

- `tfmini_send_frame` This function sends a command frame to the sensor.
```c
err_t tfmini_send_frame ( tfmini_t *ctx, tfmini_frame_t frame );
```

## Example Description

> This example demonstrates the use of TFmini click board by reading the measurements from the attached TFmini-S or TFmini Plus sensors.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and the click board, and reads the firmware version of the attached sensor.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;        /**< Logger config object. */
    tfmini_cfg_t tfmini_cfg;  /**< Click config object. */

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
    tfmini_cfg_setup( &tfmini_cfg );
    TFMINI_MAP_MIKROBUS( tfmini_cfg, MIKROBUS_1 );
    tfmini_drv_interface_selection ( &tfmini_cfg, TFMINI_DRV_SEL_UART );
    if ( TFMINI_OK != tfmini_init( &tfmini, &tfmini_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TFMINI_OK != tfmini_default_cfg ( &tfmini ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint32_t fw_version = 0;
    if ( TFMINI_OK == tfmini_get_firmware_version ( &tfmini, &fw_version ) )
    {
        log_printf( &logger, " FW Version: 0x%.6LX\r\n", fw_version );
    }
    Delay_ms ( 1000 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the target distance, signal strength and the internal sensor temperature every 100ms approximately, and displays the results on the USB UART.

```c
void application_task ( void )
{
    int16_t distance = 0, strength = 0;
    float temperature = 0;
    if ( TFMINI_OK == tfmini_get_measurement ( &tfmini, &distance, &strength, &temperature ) ) 
    {
        log_printf( &logger, " Target distance: %d cm\r\n", distance );
        log_printf( &logger, " Signal strength: %d\r\n", strength );
        log_printf( &logger, " Sensor temperature: %.2f C\r\n\n", temperature );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TFmini

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
