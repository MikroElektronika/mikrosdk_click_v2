
---
# AMR Angle click

AMR Angle Click is a compact add-on board containing an anisotropic magnetoresistive measurement solution ideal for either angle or linear position measurements. This board features the ADA4571, an AMR sensor with clean and amplified cosine and sine output signals related to a rotating magnetic field angle from Analog Devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/amr_angle_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/amr-angle-click)

---


#### Click library

- **Author**        : Stefan Nikolic
- **Date**          : jan 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the AMRAngle Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for AMRAngle Click driver.

#### Standard key functions :

- `amrangle_cfg_setup` Config Object Initialization function.
```c
void amrangle_cfg_setup ( amrangle_cfg_t *cfg, uint8_t sel_toolchain );
```

- `amrangle_init` Initialization function.
```c
AMRANGLE_RETVAL amrangle_init ( amrangle_t *ctx, amrangle_cfg_t *cfg );
```

- `amrangle_default_cfg` Click Default Configuration function.
```c
void amrangle_default_cfg ( amrangle_t *ctx );
```

#### Example key functions :

- `amrangle_angle_read` This function reads an angle in degrees.
```c
float amrangle_angle_read ( amrangle_t *ctx );
```

- `amrangle_read_vtp_temp` This function returns calculated temperature using vtp pin voltage.
```c
float amrangle_read_vtp_temp ( amrangle_t *ctx );
```

- `amrangle_gain_control_mode` This function sets the gain control mode pin which is used to compensate the sensor amplitude output for reduction of temperature variation.
```c
void amrangle_gain_control_mode ( amrangle_t *ctx, uint8_t gain_control );
```

## Example Description

> This demo application shows the performance of AMR Angle click by reading and presenting the temperature and angle results on the UART log.

**The demo application is composed of two sections :**

### Application Init

> Starts up the UART LOG, SPI and ADC drivers. Performs the default settings like setting the adc vref, resolution and gpio pins.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;              /**< Logger config object. */
    amrangle_cfg_t amrangle_cfg;    /**< Click config object. */

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

    amrangle_cfg_setup( &amrangle_cfg, AMRANGLE_ARM_TOOLCHAIN );  // Change when switching profile
    AMRANGLE_MAP_MIKROBUS( amrangle_cfg, MIKROBUS_1 );
    err_t init_flag = amrangle_init( &amrangle, &amrangle_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    amrangle_default_cfg( &amrangle );
    Delay_ms ( 500 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> The application task consists of reading the temperature and angle data from the sensor and sending that data to the UART log every second.

```c

void application_task ( void ) {
    temperature_res = amrangle_read_vtp_temp( &amrangle );
    angle_res = amrangle_angle_read( &amrangle );
    log_printf( &logger, " Temperature: %.2f C\r\n", temperature_res );
    log_printf( &logger, " Angle: %.2f degrees\r\n", angle_res );
    log_printf( &logger, " --------------------------\r\n" );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AMRAngle

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
