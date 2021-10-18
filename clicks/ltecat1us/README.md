\mainpage Main Page

---
# LTE Cat.1-US click

LTE Cat.1-US click is a Click board™ based on Thales Cinterion® ELS61 wireless module that delivers highly efficient Cat 1 LTE connectivity for M2M IoT solutions offering seamless fall back to 2G and 3G networks. The best in class solution enables M2M optimized speeds of 10Mbit/s download and 5Mbit/s uplink making it ideal for the vast number of M2M and industrial IoT applications that are not dependent on speed but that requires the longevity of LTE networks, while still providing 3G and 2G connectivity to ensure complete population and geographic coverage as LTE rolls out.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ltecat1us_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lte-cat1-us-click-for-united-states)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : UART type


# Software Support

We provide a library for the LTECat1US Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LTECat1US Click driver.

#### Standard key functions :

- `ltecat1us_cfg_setup` Config Object Initialization function.
```c
void ltecat1us_cfg_setup ( ltecat1us_cfg_t *cfg );
```

- `ltecat1us_init` Initialization function.
```c
err_t ltecat1us_init ( ltecat1us_t *ctx, ltecat1us_cfg_t *cfg );
```

#### Example key functions :

- `ltecat1us_send_cmd` This function sends the specified command to the click module.
```c
void ltecat1us_send_cmd ( ltecat1us_t *ctx, char *cmd );
```

- `ltecat1us_send_cmd_with_parameter` This function sends commands to the click module.
```c
void ltecat1us_send_cmd_with_parameter ( ltecat1us_t *ctx, char *at_cmd_buf, char *param_buf );
```

- `ltecat1us_send_text_message` This function sends text message to a phone number.
```c
void ltecat1us_send_text_message ( ltecat1us_t *ctx, char *phone_number, char *message_context );
```

## Example Description

> This example reads and processes data from LTE Cat.1-US clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and wake-up module and sets default configuration for connecting device to network.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    ltecat1us_cfg_t ltecat1us_cfg;  /**< Click config object. */

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
    Delay_ms( 1000 );
    
    // Click initialization.
    ltecat1us_cfg_setup( &ltecat1us_cfg );
    LTECAT1US_MAP_MIKROBUS( ltecat1us_cfg, MIKROBUS_1 );
    err_t init_flag  = ltecat1us_init( &ltecat1us, &ltecat1us_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Power on device... " );
    
    ltecat1us_power_on( &ltecat1us );
    
    // CFUN - restart ME
    ltecat1us_send_cmd_with_parameter( &ltecat1us, LTECAT1US_CMD_CFUN, "0" );
    app_error_flag = ltecat1us_rsp_check( RSP_SYSSTART );
    ltecat1us_error_check( app_error_flag );
    
    // AT
    ltecat1us_send_cmd( &ltecat1us, LTECAT1US_CMD_AT );
    app_error_flag = ltecat1us_rsp_check( RSP_OK );
    ltecat1us_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // ATI - product information
    ltecat1us_send_cmd( &ltecat1us, LTECAT1US_CMD_ATI );
    app_error_flag = ltecat1us_rsp_check( RSP_OK );
    ltecat1us_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGMR - firmware version
    ltecat1us_send_cmd( &ltecat1us, LTECAT1US_CMD_CGMR );
    app_error_flag = ltecat1us_rsp_check( RSP_OK );
    ltecat1us_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - deregister from network
    ltecat1us_send_cmd_with_parameter( &ltecat1us, LTECAT1US_CMD_COPS, "2" );
    app_error_flag = ltecat1us_rsp_check( RSP_OK );
    ltecat1us_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGDCONT - set sim apn
    ltecat1us_set_sim_apn( &ltecat1us, SIM_APN );
    app_error_flag = ltecat1us_rsp_check( RSP_OK );
    ltecat1us_error_check( app_error_flag );
    Delay_ms( 500 );
     
    // CFUN - full funtionality
    ltecat1us_send_cmd_with_parameter( &ltecat1us, LTECAT1US_CMD_CFUN, "1" );
    app_error_flag = ltecat1us_rsp_check( RSP_OK );
    ltecat1us_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - automatic mode
    ltecat1us_send_cmd_with_parameter( &ltecat1us, LTECAT1US_CMD_COPS, "0" );
    app_error_flag = ltecat1us_rsp_check( RSP_OK );
    ltecat1us_error_check( app_error_flag );
    Delay_ms( 2000 );
    
    // CEREG - network registration status
    ltecat1us_send_cmd_with_parameter( &ltecat1us, LTECAT1US_CMD_CEREG, "2" );
    app_error_flag = ltecat1us_rsp_check( RSP_OK );
    ltecat1us_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CIMI - request IMSI
    ltecat1us_send_cmd( &ltecat1us, LTECAT1US_CMD_CIMI );
    app_error_flag = ltecat1us_rsp_check( RSP_OK );
    ltecat1us_error_check( app_error_flag );
    Delay_ms( 500 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    app_connection_status = WAIT_FOR_CONNECTION;
    log_info( &logger, " Application Task " );
    Delay_ms( 5000 );
}

```

### Application Task

> Waits for device to connect to network and then sends SMS to selected phone number.

```c

void application_task ( void ) {
    if ( app_connection_status == WAIT_FOR_CONNECTION ) {
        // CGATT - request IMSI
        ltecat1us_send_cmd_check( &ltecat1us, LTECAT1US_CMD_CGATT );
        app_error_flag = ltecat1us_rsp_check( RSP_OK );
        ltecat1us_error_check( app_error_flag );
        Delay_ms( 500 );
        
        // CEREG - network registration status
        ltecat1us_send_cmd_check( &ltecat1us, LTECAT1US_CMD_CEREG );
        app_error_flag = ltecat1us_rsp_check( RSP_OK );
        ltecat1us_error_check( app_error_flag );
        Delay_ms( 500 );
        
        // CSQ - signal quality
        ltecat1us_send_cmd( &ltecat1us, LTECAT1US_CMD_CSQ );
        app_error_flag = ltecat1us_rsp_check( RSP_OK );
        ltecat1us_error_check( app_error_flag );
        Delay_ms( 5000 );
    } else {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        // SMS message format - text mode
        ltecat1us_send_cmd_with_parameter( &ltecat1us, "AT+CMGF", "1" );
        app_error_flag = ltecat1us_rsp_check( RSP_OK );
        ltecat1us_error_check( app_error_flag );
        Delay_ms( 3000 );
        
        for( ; ; ) {   
            log_printf( &logger, "> Sending message to phone number...\r\n" );
            ltecat1us_send_text_message( &ltecat1us, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
            app_error_flag = ltecat1us_rsp_check( RSP_OK );
            ltecat1us_error_check( app_error_flag );
            Delay_ms( 10000 );
            Delay_ms( 10000 );
            Delay_ms( 10000 );
        }
    }
}

```

## Note

> In order for the example to work, 
> user needs to set the phone number and sim apn to which he wants to send an SMS
> Enter valid data for the following macros: SIM_APN and PHONE_NUMBER_TO_MESSAGE.
>> E.g. 
   >> * SIM_APN "vipmobile"
   >> * PHONE_NUMBER_TO_MESSAGE "+381659999999"

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LTECat1US

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
