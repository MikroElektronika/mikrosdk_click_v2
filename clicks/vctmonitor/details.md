
---
# VCT Monitor Click

> VCT Monitor Click is a compact add-on board that contains a highly integrated monitoring solution without compromising accuracy. This board features the LTC2990, an I2C configurable high-performance temperature, voltage, and current monitor from Analog Devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vctmonitor_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/vct-monitor-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the VCTMonitor Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for VCTMonitor Click driver.

#### Standard key functions :

- `vctmonitor_cfg_setup` Config Object Initialization function.
```c
void vctmonitor_cfg_setup ( vctmonitor_cfg_t *cfg );
```

- `vctmonitor_init` Initialization function.
```c
err_t vctmonitor_init ( vctmonitor_t *ctx, vctmonitor_cfg_t *cfg );
```

#### Example key functions :

- `vctmonitor_get_status` Gets status value.
```c
uint8_t vctmonitor_get_status ( vctmonitor_t *ctx );
```

- `vctmonitor_read_temperature` Get temperature function
```c
float vctmonitor_read_temperature ( vctmonitor_t *ctx );
```

- `vctmonitor_read_current` Current function
```c
float vctmonitor_read_current ( vctmonitor_t *ctx );
```

## Example Description

> This is an example which demonstrates the use of VCT Monitor Click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables the USB uart terminal and I2C. 

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    vctmonitor_cfg_t vctmonitor_cfg;  /**< Click config object. */

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
    vctmonitor_cfg_setup( &vctmonitor_cfg );
    VCTMONITOR_MAP_MIKROBUS( vctmonitor_cfg, MIKROBUS_1 );
    err_t init_flag = vctmonitor_init( &vctmonitor, &vctmonitor_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads temperature, current value, and differential voltage every 4 seconds.

```c

void application_task ( void ) {
    float temperature;
    float voltage;
    float current;
    
    voltage = vctmonitor_read_voltage_differential( &vctmonitor );
    log_printf( &logger, " Voltage    : %.2f mV \r\n", voltage );

    current = vctmonitor_read_current( &vctmonitor );
    log_printf( &logger, " Current    : %.2f mA \r\n", current );

    temperature = vctmonitor_read_temperature( &vctmonitor );
    log_printf( &logger, " Temperature: %.2f C \r\n", temperature );

    log_printf( &logger, "- - - - - - - - - - - -\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );     
}

```

## Note

> We used the next sets for the test:
>       - Power supply - 4V
>       - Current (Load) - 0A to 3A
>       - The temperature reads from the external MMBT3904 sensor

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.VCTMonitor

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
