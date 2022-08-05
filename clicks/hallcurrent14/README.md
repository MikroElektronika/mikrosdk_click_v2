\mainpage Main Page

---
# Hall Current 14 click

> Hall Current 14 Click is a compact add-on board that contains a precise solution for AC/DC current sensing. This board features the MCS1801, a fully integrated Hall-effect-based isolated linear current sensor designed for the current range of ±25A from Monolithic Power Systems (MPS). The galvanic isolation between the pins of the primary copper conductive path and the sensor leads allows the MCS1801 to replace optoisolators or other isolation devices. Applied current flowing through this copper conduction path generates a magnetic field that the differential Hall sensors convert into a proportional voltage, where after that, the user is given the option to process the output voltage as an analog or digital value.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent14_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hall-current-14-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2022.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the Hall Current 14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Hall Current 14 Click driver.

#### Standard key functions :

- `hallcurrent14_cfg_setup` Config Object Initialization function.
```c
void hallcurrent14_cfg_setup ( hallcurrent14_cfg_t *cfg );
```

- `hallcurrent14_init` Initialization function.
```c
err_t hallcurrent14_init ( hallcurrent14_t *ctx, hallcurrent14_cfg_t *cfg );
```

#### Example key functions :

- `hallcurrent14_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t hallcurrent14_read_voltage ( hallcurrent14_t *ctx, float *voltage );
```

- `hallcurrent14_set_vref` This function sets the voltage reference for Hall Current 14 click driver.
```c
err_t hallcurrent14_set_vref ( hallcurrent14_t *ctx, float vref );
```

- `hallcurrent14_read_current` This function reads the input current level [A] based on @b HALLCURRENT14_NUM_CONVERSIONS of voltage measurements.
```c
err_t hallcurrent14_read_current ( hallcurrent14_t *ctx, float *current );
```

## Example Description

> This example demonstrates the use of Hall Current 14 click board by reading and displaying the input current measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent14_cfg_t hallcurrent14_cfg;  /**< Click config object. */

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
    hallcurrent14_cfg_setup( &hallcurrent14_cfg );
    HALLCURRENT14_MAP_MIKROBUS( hallcurrent14_cfg, MIKROBUS_1 );
    err_t init_flag = hallcurrent14_init( &hallcurrent14, &hallcurrent14_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the input current measurements and displays the results on the USB UART approximately once per second.

```c

void application_task ( void )
{
    float current = 0;
    if ( HALLCURRENT14_OK == hallcurrent14_read_current ( &hallcurrent14, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f[A]\r\n\n", current );
        Delay_ms( 1000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
