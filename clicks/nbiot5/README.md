\mainpage Main Page

---
# NB IoT 5 click

> NB IoT 5 Click is a compact add-on board suitable as narrow-band Internet of Things universal wireless communication solution. This board features the OT01-5, a high-performance NB-IoT module with ultra-low power consumption allowing battery life of about ten years from Notioni.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nb_iot_5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/nb-iot-5-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Dec 2020.
- **Type**          : UART type


# Software Support

We provide a library for the NBIoT5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
This library contains API for NBIoT5 Click driver.
```

#### Standard key functions :

- `nbiot5_cfg_setup` Config Object Initialization function.
```c
void nbiot5_cfg_setup ( nbiot5_cfg_t *cfg );
```

- `nbiot5_init` Initialization function.
```c
nbiot5_RETVAL nbiot5_init ( nbiot5_t *ctx, nbiot5_cfg_t *cfg );
```

- `nbiot5_default_cfg` Click Default Configuration function.
```c
void nbiot5_default_cfg ( nbiot5_t *ctx );
```

#### Example key functions :

- `nbiot5_generic_read` NB IoT 5 data reading function.
```c
err_t nbiot5_generic_read ( nbiot5_t *ctx, char *data_buf, uint16_t max_len );
```

- `nbiot5_send_cmd` Send command function.
```c
void nbiot5_send_cmd ( nbiot5_t *ctx, char *cmd );
```

- `nbiot5_send_text_message` NB IoT 5 send text message.
```c
void nbiot5_send_text_message ( nbiot5_t *ctx, char *phone_number, char *message_context );
```

## Examples Description

> This example reads and processes data from NB IoT 5 clicks.\
It configures device for connection to network, and checks \
if device is connected, and signal quality. After it connects,  
it sends SMS message to phone number set in application.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and wake-up module, and sets default 
configuration for connection.

```
void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    nbiot5_cfg_t nbiot5_cfg;    /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );
    Delay_ms( 1000 );
    
    // Click initialization.
    nbiot5_cfg_setup( &nbiot5_cfg );
    NBIOT5_MAP_MIKROBUS( nbiot5_cfg, MIKROBUS_1 );
    err_t init_flag  = nbiot5_init( &nbiot5, &nbiot5_cfg );
    if ( init_flag == UART_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Power up device... " );
    nbiot5_default_cfg ( &nbiot5 );
    
    nbiot5_send_cmd( &nbiot5, NBIOT5_CMD_ATI );
    nbiot5_process(  );
    nbiot5_clear_app_buf(  );
    
    //ATI
    nbiot5_send_cmd( &nbiot5, NBIOT5_CMD_ATI );
    app_error_flag = nbiot5_rsp_check();
    nbiot5_error_check( app_error_flag );
    Delay_ms( 1000 );
    
    //CFUN
    nbiot5_send_cmd( &nbiot5, NBIOT5_SET_CFUN );
    app_error_flag = nbiot5_rsp_check();
    nbiot5_error_check( app_error_flag );
    Delay_ms( 1000 );
    
    //CEREG
    nbiot5_send_cmd( &nbiot5, NBIOT5_SET_CREG );
    app_error_flag = nbiot5_rsp_check();
    nbiot5_error_check( app_error_flag );
    Delay_ms( 1000 );
    
    //CGDCONT
    nbiot5_set_sim_apn( &nbiot5, SIM_APN );
    app_error_flag = nbiot5_rsp_check();
    nbiot5_error_check( app_error_flag );
    Delay_ms( 1000 );
    
    //COPS
    nbiot5_send_cmd( &nbiot5, NBIOT5_SET_COPS );
    app_error_flag = nbiot5_rsp_check();
    nbiot5_error_check( app_error_flag );
    Delay_ms( 1000 );
    
    //CIMI
    nbiot5_send_cmd( &nbiot5, NBIOT5_CMD_CIMI );
    app_error_flag = nbiot5_rsp_check();
    nbiot5_error_check( app_error_flag );
    Delay_ms( 500 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    app_connection_status = WAIT_FOR_CONNECTION;
    log_info( &logger, " Application Task " );
    Delay_ms( 2000 );
}
```

### Application Task

> Checks if device is connected to network, when device connects \
to network device is sending SMS message to selected phone number.

```
void application_task ( void )
{
    
    if ( app_connection_status == WAIT_FOR_CONNECTION )
    {
        nbiot5_send_cmd( &nbiot5, NBIOT5_CHECK_CGATT );
        app_error_flag = nbiot5_rsp_check();
        nbiot5_error_check( app_error_flag );
        Delay_ms( 2000 );
        
        nbiot5_send_cmd( &nbiot5, NBIOT5_CHECK_CREG );
        app_error_flag = nbiot5_rsp_check();
        nbiot5_error_check( app_error_flag );
        Delay_ms( 2000 );
        
        nbiot5_send_cmd( &nbiot5, NBIOT5_CMD_CSQ );
        app_error_flag = nbiot5_rsp_check();
        nbiot5_error_check( app_error_flag );
        Delay_ms( 2000 );
    }
    else
    {
        //Setting SMS mode
        
        nbiot5_send_cmd( &nbiot5, NBIOT5_SET_CMGF );
        app_error_flag = nbiot5_rsp_check();
        nbiot5_error_check( app_error_flag );
        Delay_ms( 3000 );
        
        for( ; ; )
        {  
            log_printf( &logger, "> Sending message to phone number...\r\n" );
            nbiot5_send_text_message( &nbiot5, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
            app_error_flag = nbiot5_rsp_check();
            nbiot5_error_check( app_error_flag );
            Delay_ms( 10000 );
        }
    }
}
```

## Note

> In order for the example to work, \
user needs to set the phone number to which he wants to \
send an SMS and correct sim apn of its SIM card.\
Enter valid data for the following macros: SIM_APN and PHONE_NUMBER_TO_MESSAGE.\
>> E.g. 
 >>>SIM_APN "vip.iot"\
 PHONE_NUMBER_TO_MESSAGE "999999999"

> ***You need to have USB connected to device in the beggining of 
the application for additional power on startup.***

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.NBIoT5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
