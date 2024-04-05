\mainpage Main Page

---
# EZO Carrier pH click

> EZO Carrier Click - pH is a compact add-on board that allows you to measure the potential of hydrogen (the power of hydrogen) in your application. This board features the EZO™ pH, a pH measurement interface circuit board from Atlas Scientific.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ezocarrierph_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ezo-carrier-click-ph)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2023.
- **Type**          : UART type


# Software Support

We provide a library for the EZO Carrier pH Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for EZO Carrier pH Click driver.

#### Standard key functions :

- `ezocarrierph_cfg_setup` Config Object Initialization function.
```c
void ezocarrierph_cfg_setup ( ezocarrierph_cfg_t *cfg );
```

- `ezocarrierph_init` Initialization function.
```c
err_t ezocarrierph_init ( ezocarrierph_t *ctx, ezocarrierph_cfg_t *cfg );
```

#### Example key functions :

- `ezocarrierph_send_cmd` Send command function.
```c
void ezocarrierph_send_cmd ( ezocarrierph_t *ctx, uint8_t *cmd );
```

- `ezocarrierph_send_cmd_with_par` Send command function with parameter.
```c
void ezocarrierph_send_cmd_with_par ( ezocarrierph_t *ctx, uint8_t *cmd, uint8_t *param_buf );
```

- `ezocarrierph_send_cmd_check` Check the sent command.
```c
void ezocarrierph_send_cmd_check ( ezocarrierph_t *ctx, uint8_t *cmd );
```

## Example Description

> This example demonstrates the use of EZO Carrier pH click board by processing
 the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the click default factory reset, and mid point calibration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ezocarrierph_cfg_t ezocarrierph_cfg;  /**< Click config object. */

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
    ezocarrierph_cfg_setup( &ezocarrierph_cfg );
    EZOCARRIERPH_MAP_MIKROBUS( ezocarrierph_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ezocarrierph_init( &ezocarrierph, &ezocarrierph_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "Device status \r\n" );
    ezocarrierph_send_cmd( &ezocarrierph, EZOCARRIERPH_CMD_STATUS );
    error_flag = ezocarrierph_rsp_check( &ezocarrierph, EZOCARRIERPH_RSP_OK );
    ezocarrierph_error_check( error_flag );

    log_printf( &logger, "Factory reset \r\n" );
    ezocarrierph_send_cmd( &ezocarrierph, EZOCARRIERPH_CMD_FACTORY );
    error_flag = ezocarrierph_rsp_check( &ezocarrierph, EZOCARRIERPH_RSP_READY );
    ezocarrierph_error_check( error_flag );

    log_printf( &logger, "Device info \r\n" );
    ezocarrierph_send_cmd( &ezocarrierph, EZOCARRIERPH_CMD_DEV_INFO );
    error_flag = ezocarrierph_rsp_check( &ezocarrierph, EZOCARRIERPH_RSP_OK );
    ezocarrierph_error_check( error_flag );

    uint8_t n_cnt = 0;
    uint8_t last_reading[ APP_BUFFER_SIZE ] = { 0 };
    ezocarrierph_clear_app_buf( );
    ezocarrierph_send_cmd( &ezocarrierph, EZOCARRIERPH_CMD_SINGLE_READ );
    ezocarrierph_process ( &ezocarrierph );
    strcpy( last_reading, app_buf );
    log_printf( &logger, "Mid point calibration \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "Place probe into pH neutral solution \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "Starting calibration \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "Waiting for stable readings \r\n" );
    while ( n_cnt <= 5 )
    {
        if ( EZOCARRIERPH_OK == ezocarrierph_process ( &ezocarrierph ) )
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
        ezocarrierph_clear_app_buf( );
    }
    
    #define MID_POINT_CALIB         "mid,7.00"
    log_printf( &logger, "\r\n Calibration \r\n" );
    ezocarrierph_send_cmd_with_par( &ezocarrierph, EZOCARRIERPH_CMD_CAL, MID_POINT_CALIB );
    error_flag = ezocarrierph_rsp_check( &ezocarrierph, EZOCARRIERPH_RSP_OK );
    ezocarrierph_error_check( error_flag );

    #define DISABLE_CONT_READ       "0"
    log_printf( &logger, "Disable continuous reading mode \r\n" );
    ezocarrierph_send_cmd_with_par( &ezocarrierph, EZOCARRIERPH_CMD_CONT_READ, DISABLE_CONT_READ );
    error_flag = ezocarrierph_rsp_check( &ezocarrierph, EZOCARRIERPH_RSP_OK );
    ezocarrierph_error_check( error_flag );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and processes all incoming pH value data and displays them on the USB UART.

```c
void application_task ( void ) 
{
    log_printf( &logger, "Reading... \r\n" );
    ezocarrierph_send_cmd( &ezocarrierph, EZOCARRIERPH_CMD_SINGLE_READ );
    error_flag = ezocarrierph_rsp_check( &ezocarrierph, EZOCARRIERPH_RSP_OK );
    ezocarrierph_error_check( error_flag );
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
- Click.EZOCarrierpH

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
