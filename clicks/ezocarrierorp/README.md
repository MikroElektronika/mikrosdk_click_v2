\mainpage Main Page

---
# EZO Carrier ORP click

> EZO Carrier Click - ORP is a compact add-on board suitable for determining a liquid's oxidation/reduction potential in your application. This board features the EZO-ORP™, an ISO 11271 compliant embedded ORP circuit board from Atlas Scientific. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ezocarrierorp_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ezo-carrier-click-orp)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2023.
- **Type**          : UART type


# Software Support

We provide a library for the EZO Carrier ORP Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for EZO Carrier ORP Click driver.

#### Standard key functions :

- `ezocarrierorp_cfg_setup` Config Object Initialization function.
```c
void ezocarrierorp_cfg_setup ( ezocarrierorp_cfg_t *cfg );
```

- `ezocarrierorp_init` Initialization function.
```c
err_t ezocarrierorp_init ( ezocarrierorp_t *ctx, ezocarrierorp_cfg_t *cfg );
```

#### Example key functions :

- `ezocarrierorp_send_cmd` Send command function.
```c
void ezocarrierorp_send_cmd ( ezocarrierorp_t *ctx, uint8_t *cmd );
```

- `ezocarrierorp_send_cmd_with_par` Send command function with parameter.
```c
void ezocarrierorp_send_cmd_with_par ( ezocarrierorp_t *ctx, uint8_t *cmd, uint8_t *param_buf );
```

- `ezocarrierorp_send_cmd_check` Check the sent command.
```c
void ezocarrierorp_send_cmd_check ( ezocarrierorp_t *ctx, uint8_t *cmd );
```

## Example Description

> This example demonstrates the use of EZO Carrier ORP click board by processing
 the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the click default factory reset, and single point calibration 
  with a calibration solutio with 225 mV ORP value.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ezocarrierorp_cfg_t ezocarrierorp_cfg;  /**< Click config object. */

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
    ezocarrierorp_cfg_setup( &ezocarrierorp_cfg );
    EZOCARRIERORP_MAP_MIKROBUS( ezocarrierorp_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ezocarrierorp_init( &ezocarrierorp, &ezocarrierorp_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, "Device status \r\n" );
    ezocarrierorp_send_cmd( &ezocarrierorp, EZOCARRIERORP_CMD_STATUS );
    error_flag = ezocarrierorp_rsp_check( &ezocarrierorp, EZOCARRIERORP_RSP_OK );
    ezocarrierorp_error_check( error_flag );

    log_printf( &logger, "Factory reset \r\n" );
    ezocarrierorp_send_cmd( &ezocarrierorp, EZOCARRIERORP_CMD_FACTORY );
    error_flag = ezocarrierorp_rsp_check( &ezocarrierorp, EZOCARRIERORP_RSP_READY );
    ezocarrierorp_error_check( error_flag );

    log_printf( &logger, "Device info \r\n" );
    ezocarrierorp_send_cmd( &ezocarrierorp, EZOCARRIERORP_CMD_DEV_INFO );
    error_flag = ezocarrierorp_rsp_check( &ezocarrierorp, EZOCARRIERORP_RSP_OK );
    ezocarrierorp_error_check( error_flag );

    uint8_t n_cnt = 0;
    uint8_t last_reading[ APP_BUFFER_SIZE ] = { 0 };
    ezocarrierorp_clear_app_buf( );
    ezocarrierorp_send_cmd( &ezocarrierorp, EZOCARRIERORP_CMD_SINGLE_READ );
    ezocarrierorp_process ( &ezocarrierorp );
    strcpy( last_reading, app_buf );
    log_printf( &logger, "Place the probe into the calibration solution,\r\n" );
    log_printf( &logger, "for single-point calibration \r\n" );
    Delay_ms( 5000 );
    log_printf( &logger, "Waiting for stable readings \r\n" );
    while ( n_cnt <= 5 )
    {
        if ( EZOCARRIERORP_OK == ezocarrierorp_process ( &ezocarrierorp ) )
        {  
            if ( 0 == strstr( app_buf, last_reading ) )
            {
                n_cnt++;
            }
            else
            {
                strcpy( last_reading, app_buf );
                n_cnt = 0;
            }
        }
        log_printf( &logger, "- " );
        Delay_ms( 1000 );
        ezocarrierorp_clear_app_buf( );
    }

    #define CALIBRATION_VALUE   "225"
    log_printf( &logger, "\r\n Calibration \r\n" );
    ezocarrierorp_send_cmd_with_par( &ezocarrierorp, EZOCARRIERORP_CMD_CAL, CALIBRATION_VALUE );
    error_flag = ezocarrierorp_rsp_check( &ezocarrierorp, EZOCARRIERORP_RSP_OK );
    ezocarrierorp_error_check( error_flag );

    #define DISABLE_CONT_READ   "0"
    log_printf( &logger, "Disable continuous reading mode \r\n" );
    ezocarrierorp_send_cmd_with_par( &ezocarrierorp, EZOCARRIERORP_CMD_CONT_READ, DISABLE_CONT_READ );
    error_flag = ezocarrierorp_rsp_check( &ezocarrierorp, EZOCARRIERORP_RSP_OK );
    ezocarrierorp_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Initializes the driver, performs the click default factory reset, and single point calibration 
  with a calibration solutio with 225 mV ORP value.

```c
void application_task ( void ) 
{
    log_printf( &logger, "Reading... \r\n" );
    ezocarrierorp_send_cmd( &ezocarrierorp, EZOCARRIERORP_CMD_SINGLE_READ );
    error_flag = ezocarrierorp_rsp_check( &ezocarrierorp, EZOCARRIERORP_RSP_OK );
    ezocarrierorp_error_check( error_flag );
    Delay_ms( 5000 );
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.EZOCarrierORP

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
