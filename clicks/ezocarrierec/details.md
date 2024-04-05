
---
# EZO Carrier EC click

> EZO Carrier Click - Conductivity is a compact add-on board for measuring conductivity, salinity, and Total Dissolved Solids (TDS) in various applications from chemical production to hydroponics. This board features the EZO-EC™, an ISO 7888 compliant embedded conductivity circuit board from Atlas Scientific.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ezocarrierec_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ezo-carrier-click-conductivity)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2023.
- **Type**          : UART type


# Software Support

We provide a library for the EZO Carrier EC Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for EZO Carrier EC Click driver.

#### Standard key functions :

- `ezocarrierec_cfg_setup` Config Object Initialization function.
```c
void ezocarrierec_cfg_setup ( ezocarrierec_cfg_t *cfg );
```

- `ezocarrierec_init` Initialization function.
```c
err_t ezocarrierec_init ( ezocarrierec_t *ctx, ezocarrierec_cfg_t *cfg );
```

#### Example key functions :

- `ezocarrierec_send_cmd` Send command function.
```c
void ezocarrierec_send_cmd ( ezocarrierec_t *ctx, uint8_t *cmd );
```

- `ezocarrierec_send_cmd_with_par` Send command function with parameter.
```c
void ezocarrierec_send_cmd_with_par ( ezocarrierec_t *ctx, uint8_t *cmd, uint8_t *param_buf );
```

- `ezocarrierec_send_cmd_check` Check the sent command.
```c
void ezocarrierec_send_cmd_check ( ezocarrierec_t *ctx, uint8_t *cmd );
```

## Example Description

> This example demonstrates the use of EZO Carrier EC click board by processing
  the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the click default factory reset, and single point calibration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ezocarrierec_cfg_t ezocarrierec_cfg;  /**< Click config object. */

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
    ezocarrierec_cfg_setup( &ezocarrierec_cfg );
    EZOCARRIEREC_MAP_MIKROBUS( ezocarrierec_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ezocarrierec_init( &ezocarrierec, &ezocarrierec_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, "Device status \r\n" );
    ezocarrierec_send_cmd( &ezocarrierec, EZOCARRIEREC_CMD_STATUS );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );

    log_printf( &logger, "Factory reset \r\n" );
    ezocarrierec_send_cmd( &ezocarrierec, EZOCARRIEREC_CMD_FACTORY );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_READY );
    ezocarrierec_error_check( error_flag );

    #define PROBE_TYPE   "1.0"
    log_printf( &logger, "Seting Probe type \r\n" );
    ezocarrierec_send_cmd_with_par( &ezocarrierec, EZOCARRIEREC_CMD_SET_PROBE_TYPE, PROBE_TYPE );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );

    log_printf( &logger, "Device info \r\n" );
    ezocarrierec_send_cmd( &ezocarrierec, EZOCARRIEREC_CMD_DEV_INFO );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );

    #define DRY_CALIBRATION   "dry"
    log_printf( &logger, "Dry calibration \r\n" );
    ezocarrierec_send_cmd_with_par( &ezocarrierec, EZOCARRIEREC_CMD_CAL, DRY_CALIBRATION );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );

    uint8_t n_cnt = 0;
    uint8_t last_reading[ APP_BUFFER_SIZE ] = { 0 };
    ezocarrierec_clear_app_buf( );
    ezocarrierec_send_cmd( &ezocarrierec, EZOCARRIEREC_CMD_SINGLE_READ );
    ezocarrierec_process ( &ezocarrierec );
    strcpy( last_reading, app_buf );
    log_printf( &logger, "Single point calibration \r\n" );
    log_printf( &logger, "Waiting for stable readings \r\n" );
    while ( n_cnt <= 5 )
    {
        if ( EZOCARRIEREC_OK == ezocarrierec_process ( &ezocarrierec ) )
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
        Delay_ms ( 1000 );
        ezocarrierec_clear_app_buf( );
    }
    #define CALIBRATION_VALUE   "80"
    log_printf( &logger, "Calibration \r\n" );
    ezocarrierec_send_cmd_with_par( &ezocarrierec, EZOCARRIEREC_CMD_CAL, CALIBRATION_VALUE );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );

    #define DISABLE_CONT_READ   "0"
    log_printf( &logger, "Disable continuous reading mode \r\n" );
    ezocarrierec_send_cmd_with_par( &ezocarrierec, EZOCARRIEREC_CMD_CONT_READ, DISABLE_CONT_READ );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and processes all incoming conductivity data from the probe, and displays them on the USB UART in uS.

```c
void application_task ( void ) 
{
    log_printf( &logger, "Reading... \r\n" );
    ezocarrierec_send_cmd( &ezocarrierec, EZOCARRIEREC_CMD_SINGLE_READ );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );
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
- Click.EZOCarrierEC

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
