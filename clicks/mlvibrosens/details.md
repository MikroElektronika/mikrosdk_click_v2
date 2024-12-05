
---
# ML Vibro Sens Click

> ML Vibro Sens Click is a compact add-on board for motion sensing and vibration analysis. This board features the FXLS8974CF, a 3-axis low-g 12-bit digital accelerometer from NXP designed for precise motion detection and data collection. This Click board™ represents a machine learning training tool that communicates with the host MCU over an I2C interface, with selectable addresses and dual operating modes for interrupt signaling or motion detection. It features two DC motors - a balanced motor for generating steady baseline vibrations and an unbalanced motor for customizable vibration patterns controlled via PWM or PDM signals.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mlvibrosens_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ml-vibro-sens-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the ML Vibro Sens Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ML Vibro Sens Click driver.

#### Standard key functions :

- `mlvibrosens_cfg_setup` Config Object Initialization function.
```c
void mlvibrosens_cfg_setup ( mlvibrosens_cfg_t *cfg );
```

- `mlvibrosens_init` Initialization function.
```c
err_t mlvibrosens_init ( mlvibrosens_t *ctx, mlvibrosens_cfg_t *cfg );
```

- `mlvibrosens_default_cfg` Click Default Configuration function.
```c
err_t mlvibrosens_default_cfg ( mlvibrosens_t *ctx );
```

#### Example key functions :

- `mlvibrosens_get_int_pin` This function returns the interrupt pin logic state.
```c
uint8_t mlvibrosens_get_int_pin ( mlvibrosens_t *ctx );
```

- `mlvibrosens_get_data` This function reads accel X, Y, and Z axis data in g and temperature in degrees Celsius.
```c
err_t mlvibrosens_get_data ( mlvibrosens_t *ctx, mlvibrosens_data_t *data_out );
```

- `mlvibrosens_set_vibro_state` This function sets the vibro motors state.
```c
void mlvibrosens_set_vibro_state ( mlvibrosens_t *ctx, uint8_t state );
```

## Example Description

> This example demonstrates the use of the ML Vibro Sens Click board by capturing and logging
acceleration data on the X, Y, and Z axes, along with temperature readings. The data is output 
over USB UART and can be visualized in real-time using tools like SerialPlot. Additionally, 
the vibro motor state changes periodically, cycling through different vibration states for 
added feedback.

**The demo application is composed of two sections :**

### Application Init

> Initializes the communication interface and configures the ML Vibro Sens Click board 
with default settings. This setup enables an interrupt on the INT pin when data is ready,
sets the acceleration sensitivity to a +/-4G range, and sets the output data rate to 100 Hz.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mlvibrosens_cfg_t mlvibrosens_cfg;  /**< Click config object. */

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
    mlvibrosens_cfg_setup( &mlvibrosens_cfg );
    MLVIBROSENS_MAP_MIKROBUS( mlvibrosens_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == mlvibrosens_init( &mlvibrosens, &mlvibrosens_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MLVIBROSENS_ERROR == mlvibrosens_default_cfg ( &mlvibrosens ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Monitors the data-ready interrupt, retrieves acceleration and temperature data when available,
and logs it over USB UART in the format X;Y;Z;TEMP. After every 1000 data readings, the 
vibro motor state cycles through predefined states to demonstrate the motor's functionality.

```c
void application_task ( void )
{
    static uint8_t vibro_state = MLVIBROSENS_VIBRO_STATE_IDLE;
    static uint16_t result_num = 0;
    static mlvibrosens_data_t accel_data;
    
    // Wait for a data ready interrupt
    while ( mlvibrosens_get_int_pin ( &mlvibrosens ) );

    if ( MLVIBROSENS_OK == mlvibrosens_get_data ( &mlvibrosens, &accel_data ) )
    {
        log_printf ( &logger, "%f;%f;%f;%d;\r\n", accel_data.x, accel_data.y, 
                                                  accel_data.z, accel_data.temperature ); 
    }
    if ( ++result_num > 1000 )
    {
        result_num = 0;
        if ( ++vibro_state > MLVIBROSENS_VIBRO_STATE_BOTH )
        {
            vibro_state = MLVIBROSENS_VIBRO_STATE_IDLE;
        }
        mlvibrosens_set_vibro_state ( &mlvibrosens, vibro_state );
    }
}
```

## Note

> We recommend using the SerialPlot tool for data visualization. The temperature measurements
should be visualized independently. The data format for plotter is as follows: X;Y;Z;TEMP;

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MLVibroSens

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
