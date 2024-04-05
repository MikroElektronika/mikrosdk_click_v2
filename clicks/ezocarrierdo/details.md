
---
# EZO Carrier DO click

> EZO Carrier Click - Oxygen is a compact add-on board suitable for determining the dissolved oxygen of a liquid in your application. This board features the EZO-DO™, an ISO 5814 compliant embedded dissolved oxygen circuit board from Atlas Scientific.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ezocarrierdo_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ezo-carrier-click-oxygen)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2023.
- **Type**          : UART type


# Software Support

We provide a library for the EZO Carrier DO Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for EZO Carrier DO Click driver.

#### Standard key functions :

- `ezocarrierdo_cfg_setup` Config Object Initialization function.
```c
void ezocarrierdo_cfg_setup ( ezocarrierdo_cfg_t *cfg );
```

- `ezocarrierdo_init` Initialization function.
```c
err_t ezocarrierdo_init ( ezocarrierdo_t *ctx, ezocarrierdo_cfg_t *cfg );
```

#### Example key functions :

- `ezocarrierdo_send_cmd` Send command function.
```c
void ezocarrierdo_send_cmd ( ezocarrierdo_t *ctx, uint8_t *cmd );
```

- `ezocarrierdo_send_cmd_with_par` Send command function with parameter.
```c
void ezocarrierdo_send_cmd_with_par ( ezocarrierdo_t *ctx, uint8_t *cmd, uint8_t *param_buf );
```

- `ezocarrierdo_send_cmd_check` Check the sent command.
```c
void ezocarrierdo_send_cmd_check ( ezocarrierdo_t *ctx, uint8_t *cmd );
```

## Example Description

> This example demonstrates the use of EZO Carrier DO click board by processing
  the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the click default factory reset, and high point calibration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ezocarrierdo_cfg_t ezocarrierdo_cfg;  /**< Click config object. */

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
    ezocarrierdo_cfg_setup( &ezocarrierdo_cfg );
    EZOCARRIERDO_MAP_MIKROBUS( ezocarrierdo_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ezocarrierdo_init( &ezocarrierdo, &ezocarrierdo_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "Device status \r\n" );
    ezocarrierdo_send_cmd( &ezocarrierdo, EZOCARRIERDO_CMD_STATUS );
    error_flag = ezocarrierdo_rsp_check( &ezocarrierdo, EZOCARRIERDO_RSP_OK );
    ezocarrierdo_error_check( error_flag );

    log_printf( &logger, "Factory reset \r\n" );
    ezocarrierdo_send_cmd( &ezocarrierdo, EZOCARRIERDO_CMD_FACTORY );
    error_flag = ezocarrierdo_rsp_check( &ezocarrierdo, EZOCARRIERDO_RSP_READY );
    ezocarrierdo_error_check( error_flag );

    log_printf( &logger, "Device info \r\n" );
    ezocarrierdo_send_cmd( &ezocarrierdo, EZOCARRIERDO_CMD_DEV_INFO );
    error_flag = ezocarrierdo_rsp_check( &ezocarrierdo, EZOCARRIERDO_RSP_OK );
    ezocarrierdo_error_check( error_flag );

    uint8_t n_cnt = 0;
    uint8_t last_reading[ APP_BUFFER_SIZE ] = { 0 };
    ezocarrierdo_clear_app_buf( );
    ezocarrierdo_send_cmd( &ezocarrierdo, EZOCARRIERDO_CMD_SINGLE_READ );
    ezocarrierdo_process ( &ezocarrierdo );
    strcpy( last_reading, app_buf );
    log_printf( &logger, "High point calibration \r\n" );
    log_printf( &logger, "Waiting for stable readings \r\n" );
    while ( n_cnt <= 5 )
    {
        if ( EZOCARRIERDO_OK == ezocarrierdo_process ( &ezocarrierdo ) )
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
        ezocarrierdo_clear_app_buf( );
    }
    
    log_printf( &logger, "\r\n Calibration \r\n" );
    ezocarrierdo_send_cmd( &ezocarrierdo, EZOCARRIERDO_CMD_CAL );
    error_flag = ezocarrierdo_rsp_check( &ezocarrierdo, EZOCARRIERDO_RSP_OK );
    ezocarrierdo_error_check( error_flag );

    #define DISABLE_CONT_READ   "0"
    log_printf( &logger, "Disable continuous reading mode \r\n" );
    ezocarrierdo_send_cmd_with_par( &ezocarrierdo, EZOCARRIERDO_CMD_CONT_READ, DISABLE_CONT_READ );
    error_flag = ezocarrierdo_rsp_check( &ezocarrierdo, EZOCARRIERDO_RSP_OK );
    ezocarrierdo_error_check( error_flag );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and processes all incoming dissolved oxygen data from the probe, and displays them on the USB UART in mg/L.

```c
void application_task ( void ) 
{
    log_printf( &logger, "Reading... \r\n" );
    ezocarrierdo_send_cmd( &ezocarrierdo, EZOCARRIERDO_CMD_SINGLE_READ );
    error_flag = ezocarrierdo_rsp_check( &ezocarrierdo, EZOCARRIERDO_RSP_OK );
    ezocarrierdo_error_check( error_flag );
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
- Click.EZOCarrierDO

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
