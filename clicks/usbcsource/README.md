\mainpage Main Page

---
# USB-C Source click

> USB-C Source Click is a compact add-on board that contains a standalone autonomous USB power delivery controller. This board features the STUSB4700, an independent USB power delivery controller optimized as a provider to negotiate a given amount of power to be sourced to an inquiring consumer device from STMicroelectronics.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/usbcsource_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/usb-c-source-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the USBCSource Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for USBCSource Click driver.

#### Standard key functions :

- `usbcsource_cfg_setup` Config Object Initialization function.
```c
void usbcsource_cfg_setup ( usbcsource_cfg_t *cfg );
```

- `usbcsource_init` Initialization function.
```c
err_t usbcsource_init ( usbcsource_t *ctx, usbcsource_cfg_t *cfg );
```

#### Example key functions :

- `usbcsource_hw_reset` HW reset function.
```c
void usbcsource_hw_reset ( usbcsource_t *ctx );
```

- `usbcsource_get_alert_status` Get alert status function.
```c
void usbcsource_get_alert_status ( usbcsource_t *ctx, alert_status_t *alert_status_data );
```

- `usbcsource_set_pdo_config` Set PDO configuration function.
```c
uint8_t usbcsource_set_pdo_config ( usbcsource_t *ctx, pdo_config_t pdo_cfg_data );
```

## Example Description

> This is an example that demonstrates the use of the USB-C Source Click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables - I2C, set hardware reset and default configuration and display configuration of the five PDOs, also write log.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcsource_cfg_t usbcsource_cfg;  /**< Click config object. */

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
    usbcsource_cfg_setup( &usbcsource_cfg );
    USBCSOURCE_MAP_MIKROBUS( usbcsource_cfg, MIKROBUS_1 );
    err_t init_flag = usbcsource_init( &usbcsource, &usbcsource_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    usbcsource_hw_reset( &usbcsource );
    Delay_ms ( 500 );
    usbcsource_default_config( &usbcsource );
    Delay_ms ( 500 );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_pdo_config( &usbcsource, USBCSOURCE_SEL_PDO1, &pdo_data );
    log_printf( &logger, " PDO 1 - Voltage = %.2f V \r\n", pdo_data.vtg_data );
    log_printf( &logger, " PDO 1 - Current = %.2f A \r\n", pdo_data.curr_data );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_pdo_config( &usbcsource, USBCSOURCE_SEL_PDO2, &pdo_data );
    log_printf( &logger, " PDO 2 - Voltage = %.2f V \r\n", pdo_data.vtg_data );
    log_printf( &logger, " PDO 2 - Current = %.2f A \r\n", pdo_data.curr_data );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_pdo_config( &usbcsource, USBCSOURCE_SEL_PDO3, &pdo_data );
    log_printf( &logger, " PDO 3 - Voltage = %.2f V \r\n", pdo_data.vtg_data );
    log_printf( &logger, " PDO 3 - Current = %.2f A \r\n", pdo_data.curr_data );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_pdo_config( &usbcsource, USBCSOURCE_SEL_PDO4, &pdo_data );
    log_printf( &logger, " PDO 4 - Voltage = %.2f V \r\n", pdo_data.vtg_data );
    log_printf( &logger, " PDO 4 - Current = %.2f A \r\n", pdo_data.curr_data );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_pdo_config( &usbcsource, USBCSOURCE_SEL_PDO5, &pdo_data );
    log_printf( &logger, " PDO 5 - Voltage = %.2f V \r\n", pdo_data.vtg_data );
    log_printf( &logger, " PDO 5 - Current = %.2f A \r\n", pdo_data.curr_data );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> In this example, we show port status, monitoring, and connections. All data logs write on USB uart changes every 5 sec.

```c

void application_task ( void ) {
    usbcsource_get_port_status( &usbcsource, &port_status );
    display_port_status( );
    Delay_ms ( 100 );
    log_printf( &logger, "- - - - - - - - - - - - - - " );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_monitoring_status( &usbcsource, &monitor_status );
    display_monitoring_status( );
    Delay_ms ( 100 );
    log_printf( &logger, "- - - - - - - - - - - - - - " );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_connection_status( &usbcsource, &conn_status );
    display_connection_status( );
    Delay_ms ( 100 );
    log_printf( &logger, "- - - - - - - - - - - - - - " );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.USBCSource

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
