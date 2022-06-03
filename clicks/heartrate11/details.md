
---
# Heart Rate 11 click

> Heart Rate 11 Click is a compact add-on board suitable for heart rate monitoring applications. This board features the OB1203, a multi-channel light sensor (LS/CS), a proximity sensor (PS), and a photoplethysmography sensor (PPG) from Renesas. It can be configured as an ambient light sensor to measure ambient light similar to the human eye experience or as an RGB color sensor. The OB1203 establishes communication to and from the module entirely through a standard I2C compatible interface and has a fully integrated biosensor for reflective photoplethysmography.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/heartrate11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/heart-rate-11-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Heart Rate 11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Heart Rate 11 Click driver.

#### Standard key functions :

- `heartrate11_cfg_setup` Config Object Initialization function.
```c
void heartrate11_cfg_setup ( heartrate11_cfg_t *cfg );
```

- `heartrate11_init` Initialization function.
```c
err_t heartrate11_init ( heartrate11_t *ctx, heartrate11_cfg_t *cfg );
```

- `heartrate11_default_cfg` Click Default Configuration function.
```c
err_t heartrate11_default_cfg ( heartrate11_t *ctx );
```

#### Example key functions :

- `heartrate11_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t heartrate11_get_int_pin ( heartrate11_t *ctx );
```

- `heartrate11_set_led_current` This function sets the maximal current of the selected LED.
```c
err_t heartrate11_set_led_current ( heartrate11_t *ctx, uint8_t led, float current );
```

- `heartrate11_read_fifo` This function reads a 24-bit data from the FIFO.
```c
err_t heartrate11_read_fifo ( heartrate11_t *ctx, uint32_t *fifo_data );
```

## Example Description

> This example demonstrates the use of Heart Rate 11 click board by reading and displaying the PPG1 (HR) values which can be visualized on the SerialPlot application.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration for heart rate measurement.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate11_cfg_t heartrate11_cfg;  /**< Click config object. */

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
    heartrate11_cfg_setup( &heartrate11_cfg );
    HEARTRATE11_MAP_MIKROBUS( heartrate11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == heartrate11_init( &heartrate11, &heartrate11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HEARTRATE11_ERROR == heartrate11_default_cfg ( &heartrate11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the data ready interrupt, then reads the values of PPG from FIFO and displays it on the USB UART (SerialPlot) every 32ms approximately.

```c
void application_task ( void )
{
    // Wait for the data ready interrupt indication
    while ( heartrate11_get_int_pin ( &heartrate11 ) );
    
    uint32_t ppg;
    if ( HEARTRATE11_OK == heartrate11_read_fifo ( &heartrate11, &ppg ) )
    {
        log_printf ( &logger, "%lu\r\n", ppg );
    }
}
```

## Note

> We recommend using the SerialPlot tool for data visualizing.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
