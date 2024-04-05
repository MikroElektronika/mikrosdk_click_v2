\mainpage Main Page
 

---
# NB IoT click

NB IoT click is a Click board™ that allows LTE Cat NB1 connectivity by utilizing Quectel BC95-G, a specialized multi-band IoT module with very low power requirements and compact form factor, making it perfectly suited for various IoT-based applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nbiot_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/nb-iot-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the NbIot Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for NbIot Click driver.

#### Standard key functions :

- NB IoT configuration object setup function.
> void nbiot_cfg_setup ( nbiot_cfg_t *cfg ); 
 
- NB IoT initialization function.
> err_t nbiot_init ( nbiot_t *ctx, nbiot_cfg_t *cfg );


#### Example key functions :

- Send command function.
> void nbiot_send_cmd ( nbiot_t *ctx, char *cmd );
 
- NB IoT module power on.
> void nbiot_power_on ( nbiot_t *ctx );

- NB IoT data writing function.
> err_t nbiot_generic_write ( nbiot_t *ctx, char *data_buf, uint16_t len );

## Examples Description

> This example reads and processes data from NB IoT clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver, wake-up module and sets default configuration for connecting device to network.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nbiot_cfg_t nbiot_cfg;  /**< Click config object. */

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
    Delay_ms ( 1000 );
    
    // Click initialization.
    nbiot_cfg_setup( &nbiot_cfg );
    NBIOT_MAP_MIKROBUS( nbiot_cfg, MIKROBUS_1 );
    err_t init_flag  = nbiot_init( &nbiot, &nbiot_cfg );
    if ( init_flag == UART_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Power on device... " );
    nbiot_power_on( &nbiot );
    // dummy read
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    
    // AT
    nbiot_send_cmd( &nbiot, NBIOT_CMD_AT );
    app_error_flag = nbiot_rsp_check( );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // ATI - product information
    nbiot_send_cmd( &nbiot, NBIOT_CMD_ATI );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGMR - firmware version
    nbiot_send_cmd( &nbiot, NBIOT_CMD_CGMR );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 1000 );
    
    // COPS - deregister from network
    nbiot_send_cmd_with_parameter( &nbiot, NBIOT_CMD_COPS, "2" );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 1000 );
     
    // CFUN - full funtionality
    nbiot_send_cmd_with_parameter( &nbiot, NBIOT_CMD_CFUN, "1" );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - automatic mode
    nbiot_send_cmd_with_parameter( &nbiot, NBIOT_CMD_COPS, "0" );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // CEREG - network registration status
    nbiot_send_cmd_with_parameter( &nbiot, NBIOT_CMD_CEREG, "2" );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CIMI - request IMSI
    nbiot_send_cmd( &nbiot, NBIOT_CMD_CIMI );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    app_connection_status = WAIT_FOR_CONNECTION;
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
  
```

### Application Task

> Waits for device to connect to network and then checks the signal quality 
> every 5 seconds. All data is being logged on USB UART where you can track their changes.

```c

void application_task ( void )
{
    if ( app_connection_status == WAIT_FOR_CONNECTION )
    {
        // CGATT - request IMSI
        nbiot_send_cmd_check( &nbiot, NBIOT_CMD_CGATT );
        app_error_flag = nbiot_rsp_check(  );
        nbiot_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        // CEREG - network registration status
        nbiot_send_cmd_check( &nbiot, NBIOT_CMD_CEREG );
        app_error_flag = nbiot_rsp_check(  );
        nbiot_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        // CSQ - signal quality
        nbiot_send_cmd( &nbiot, NBIOT_CMD_CSQ );
        app_error_flag = nbiot_rsp_check(  );
        nbiot_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else
    {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        log_info( &logger, "CHECKING SIGNAL QUALITY" );
        nbiot_send_cmd( &nbiot, NBIOT_CMD_CSQ );
        app_error_flag = nbiot_rsp_check(  );
        nbiot_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
} 

```

## Note

> In order for the example to work, a valid SIM card needs to be entered.

The full application code, and ready to use projects can be installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.NbIot

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
