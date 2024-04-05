\mainpage Main Page

---
# VAV Press click

VAV Press Click is a compact add-on board that contains a board-mount pressure sensor. This board features the LMIS025B, a low differential pressure sensor from First Sensor (part of TE Connectivity). It is based on thermal flow measurement of gas through a micro-flow channel integrated within the sensor chip. The innovative LMI technology features superior sensitivity, especially for ultra-low pressures ranging from 0 to 25Pa. The extremely low gas flow through the sensor ensures high immunity to dust contamination, humidity, and long tubing compared to other flow-based pressure sensors.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vav_press_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/vav-press-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the VavPress Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for VavPress Click driver.

#### Standard key functions :

- `vavpress_cfg_setup` Config Object Initialization function.
```c
void vavpress_cfg_setup ( vavpress_cfg_t *cfg );
```

- `vavpress_init` Initialization function.
```c
VAVPRESS_RETVAL vavpress_init ( vavpress_t *ctx, vavpress_cfg_t *cfg );
```

- `vavpress_default_cfg` Click Default Configuration function.
```c
void vavpress_default_cfg ( vavpress_t *ctx );
```

#### Example key functions :

- `vavpress_set_default_sensor_param` VAV Press set default sensor parameter function.
```c
VAVPRESS_RETVAL vavpress_set_default_sensor_param ( vavpress_t *ctx, vavpress_sensor_param_data_t *param_data );
```

- `vavpress_get_dif_press_and_temp` VAV Press get differential pressure and temperature function.
```c
VAVPRESS_RETVAL vavpress_get_dif_press_and_temp ( vavpress_t *ctx, vavpress_sensor_param_data_t *param_data, float *diff_press, float *temperature );
```

- `vavpress_retrieve_electronic_signature` VAV Press retrieve electronic signature function.
```c
VAVPRESS_RETVAL vavpress_retrieve_electronic_signature ( vavpress_t *ctx, vavpress_el_signature_data_t *el_signature_data );
```

## Example Description

> This library contains API for the Vav Press click driver.
> This demo application shows an example of 
> differential pressure and temperature measurement.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization and default settings, 
> the app display retrieve the electronic signature 
> and set the sensor parameters data.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;            /**< Logger config object. */
    vavpress_cfg_t vavpress_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    vavpress_cfg_setup( &vavpress_cfg );
    VAVPRESS_MAP_MIKROBUS( vavpress_cfg, MIKROBUS_1 );
    err_t init_flag = vavpress_init( &vavpress, &vavpress_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    vavpress_default_cfg ( &vavpress );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    vavpress_retrieve_electronic_signature( &vavpress, &el_signature_data );
    Delay_ms ( 100 );

    log_printf( &logger, "--------------------------------\r\n" );
    log_printf( &logger, " Firmware Version : %.3f        \r\n", el_signature_data.firmware_version );
    log_printf( &logger, " Pressure Range   : %d Pa       \r\n", el_signature_data.pressure_range );
    log_printf( &logger, " Part #           : %.11s       \r\n", el_signature_data.part_number );
    log_printf( &logger, " Lot #            : %.7s        \r\n", el_signature_data.lot_number );
    log_printf( &logger, " Output Type      : %c          \r\n", el_signature_data.output_type );
    log_printf( &logger, " Scale Factor     : %d          \r\n", el_signature_data.scale_factor );
    log_printf( &logger, " Calibration ID   : %.2s        \r\n", el_signature_data.calibration_id );
    log_printf( &logger, " Week number      : %d          \r\n", el_signature_data.week_number );
    log_printf( &logger, " Year number      : %d          \r\n", el_signature_data.year_number );
    log_printf( &logger, " Sequence number  : %d          \r\n", el_signature_data.sequence_number );
    log_printf( &logger, "--------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    param_data.scale_factor_temp = 72;
    param_data.scale_factor_press = el_signature_data.scale_factor;
    param_data.readout_at_known_temperature = 50;
    param_data.known_temperature_c = 24.0;
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that shows the use of a Vav Press click board™.
> Logs pressure difference value [ Pa ] and temperature [ degree Celsius ] value.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) {   
    err_t error_flag = vavpress_get_dif_press_and_temp( &vavpress, &param_data, &diff_press, &temperature );
    if ( error_flag == VAVPRESS_OK ) {
        log_printf( &logger, " Diff. Pressure    : %.4f Pa\r\n", diff_press );
        log_printf( &logger, " Temperature       : %.4f C\r\n", temperature );
        log_printf( &logger, "--------------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    } else {
        log_error( &logger, " Communcation Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.VavPress

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
