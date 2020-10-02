
---
# XSENS MTi 3 click

<PRVE_2_RECENICE_SA_PRODUCT_PAGE>

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>

[click Product page](<CLICK_PRODUCT_PAGE_LINK>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the XsensMti3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for XsensMti3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void xsensmti3_cfg_setup ( xsensmti3_cfg_t *cfg ); 
 
- Initialization function.
> XSENSMTI3_RETVAL xsensmti3_init ( xsensmti3_t *ctx, xsensmti3_cfg_t *cfg );

#### Example key functions :

- This function check for the starting elements.
> uint8_t xsensmti3_check_package( uint8_t *package_buf, uint8_t *start_package );
 
- This function parses object for collecting data.
> void xsensmti3_parser ( uint8_t *rsp_buf, uint8_t start_cnt, xsensmti3_parse_t *obj );

- This function get roll, pitch and yaw values.
> void xsensmti3_get_data( xsensmti3_quat_t *quat_obj, xsensmti3_data_t *data_obj );

## Examples Description

> This example reads and processes data from XSENS MTi 3 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initialize driver init and uart interrupt.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    xsensmti3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    xsensmti3_cfg_setup( &cfg );
    XSENSMTI3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    xsensmti3_init( &xsensmti3, &cfg );

    parser_buf_cnt = 0;
    active_flag = 0;
    start_rsp = 0;
}
  
```

### Application Task

> Reads the received data and parses it. Shows Roll, Pitch and Yaw data.

```c

void application_task ( void )
{
    uint8_t check_data = 0;
    uint8_t cnt = 0;

    xsensmti3_process( );

    // STARTS COLLECTING DATA
    if ( active_flag == XSENSMTI3_WAIT_FOR_START )
    {
        memset( &current_parser_buf[ 0 ], 0 , 110 );
        parser_buf_cnt = 0;
        active_flag = XSENSMTI3_START_PROCESS;
    }

    // CHECKS RECEIVED DATA
    if ( ( parser_buf_cnt > 100 ) && ( active_flag == XSENSMTI3_START_PROCESS ) )
    {
       active_flag = XSENSMTI3_DATA_PROCESSING;
    }

    // CHECKS IF THE VALID PACKAGE IS RECEIVED
    if ( active_flag == XSENSMTI3_DATA_PROCESSING )
    {
        check_data = xsensmti3_check_package( &current_parser_buf[ 0 ], &start_rsp );
        if ( check_data == 1 )
        {
            active_flag = XSENSMTI3_PARSER_DATA;
        }
        else
        {
            active_flag = XSENSMTI3_WAIT_FOR_START;
        }
    }

    // PARSING DATA AND DISPLAY
    if ( active_flag == XSENSMTI3_PARSER_DATA )
    {
       xsensmti3_parser( &current_parser_buf[ 0 ], start_rsp, &parse_data_obj );

       log_printf( &logger, ">> Quaternion data <<\r\n" );

       for ( cnt = 0; cnt < 4; cnt++ )
       {
           log_printf( &logger, ">> Q: %e\r\n", parse_data_obj.quat_obj.quat_data[ cnt ] );
       }

       log_printf( &logger, "--------------\r\n" );

       xsensmti3_get_data( &parse_data_obj.quat_obj, &data_obj );

       log_printf( &logger, ">> ROLL: %.4f\r\n", data_obj.roll );

       log_printf( &logger, ">> PITCH: %.4f\r\n", data_obj.pitch );

       log_printf( &logger, ">> YAW: %.4f\r\n", data_obj.yaw );

       Delay_ms( 1000 );
       active_flag = XSENSMTI3_WAIT_FOR_START;

       log_printf( &logger, " \r\n--------------" );
    }
}
  

```
 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.XsensMti3

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
