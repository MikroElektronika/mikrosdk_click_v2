\mainpage Main Page

---
# XSENS MTi-3 click

> XSENS MTi-3 Click is a compact add-on board that contains a fully functional module that can be configured as an Inertial Measurement Unit, Vertical reference Unit, or even an Attitude & Heading Reference System. This board features the MTi-3, a module outputting 3D orientation, 3D rate of turn, 3D accelerations, and 3D magnetic field, depending on the product configuration from Xsens.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/xsensmti3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/xsens-mti-3-click)

---


#### Click library

- **Author**        : Mikroe Team
- **Date**          : Sep 2021.
- **Type**          : UART type


# Software Support

We provide a library for the XSENSMTi3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for XSENSMTi3 Click driver.

#### Standard key functions :

- `xsensmti3_cfg_setup` Config Object Initialization function.
```c
void xsensmti3_cfg_setup ( xsensmti3_cfg_t *cfg );
```

- `xsensmti3_init` Initialization function.
```c
err_t xsensmti3_init ( xsensmti3_t *ctx, xsensmti3_cfg_t *cfg );
```

#### Example key functions :

- `xsensmti3_parser` XSENS MTi-3 general parser.
```c
void xsensmti3_parser ( uint8_t *rsp_buf, uint8_t start_cnt, xsensmti3_parse_t *obj );
```

- `xsensmti3_get_data` XSENS MTi-3 get Roll, Pitch and Yaw.
```c
void xsensmti3_get_data( xsensmti3_quat_t *quat_obj, xsensmti3_data_t *data_obj );
```

- `xsensmti3_check_package` XSENS MTi-3 checks package.
```c
err_t xsensmti3_check_package( uint8_t *package_buf, uint8_t *start_package );
```

## Example Description

> This example reads and processes data from XSENS MTi-3 clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and wake-up module.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    xsensmti3_cfg_t xsensmti3_cfg;  /**< Click config object. */

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
    xsensmti3_cfg_setup( &xsensmti3_cfg );
    XSENSMTI3_MAP_MIKROBUS( xsensmti3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == xsensmti3_init( &xsensmti3, &xsensmti3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
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
        Delay_ms( 25 );
        memset( &current_parser_buf[ 0 ], 0 , PROCESS_PARSER_BUFFER_SIZE );
        parser_buf_cnt = 0;
        active_flag = 0;
        start_rsp = 0;
        rsp_cnt = 0;
        active_flag = XSENSMTI3_START_PROCESS;
    }

    if ( ( parser_buf_cnt > 100 ) && ( active_flag == XSENSMTI3_START_PROCESS ) )
    {
       active_flag = XSENSMTI3_DATA_PROCESSING;
    }

    if ( active_flag == XSENSMTI3_DATA_PROCESSING )
    {
        check_data = xsensmti3_check_package( &current_parser_buf[ 0 ], &start_rsp );
        if ( check_data == XSENSMTI3_OK )
        {
            active_flag = XSENSMTI3_PARSER_DATA;
        }
        else
        {
            active_flag = XSENSMTI3_WAIT_FOR_START;
        }
    }

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

       log_printf( &logger, ">> ROLL:  %.4f \r\n", data_obj.roll );
       log_printf( &logger, ">> PITCH: %.4f \r\n", data_obj.pitch );
       log_printf( &logger, ">> YAW:   %.4f \r\n", data_obj.yaw );

       active_flag = XSENSMTI3_WAIT_FOR_START;

       log_printf( &logger, "--------------\r\n" );
    }
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.XSENSMTi3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
