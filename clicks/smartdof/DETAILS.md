
---
# Smart DOF click

SmartDOF click features a highly advanced integrated system-in-package (SiP) solution with three different sensors on-chip: triaxial accelerometer, magnetometer, and triaxial gyroscope are all integrated on the same die, along with the powerful 32-bit ARM® Cortex®-M0+ MCU. Thanks to the integrated MCU, the BN080 SiP provides extensive signal processing.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/smartdof_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/smart-dof-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the SmartDof Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for SmartDof Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void smartdof_cfg_setup ( smartdof_cfg_t *cfg ); 
 
- Initialization function.
> SMARTDOF_RETVAL smartdof_init ( smartdof_t *ctx, smartdof_cfg_t *cfg );

- Click Default Configuration function.
> void smartdof_default_cfg ( smartdof_t *ctx );


#### Example key functions :

- This function waits for INT pin to go LOW, receives 4 header bytes and than parses header bytes to get data length of entire packet and stores header bytes to header buffer
> uint8_t smartdof_receive_packet ( smartdof_t *ctx, uint32_t n_cycles_timeout )
 
- This function receives get feature response report bytes
> uint8_t smartdof_get_feature_response ( smartdof_t *ctx, smartdof_sfc_t *sfc );

- This function sends set feature request report to device
> void smartdof_set_feature_command ( smartdof_t *ctx, smartdof_sfc_t *sfc );

## Examples Description

> This click integrates a triaxial accelerometer, triaxial gyroscope and magnetometer.
> It can provide very accurate and precise 3D acceleration, magnetic, and angular velocity data, in real-time. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C driver and Smart DOF device 

```c

void application_init ( void )
{
    uint8_t p;
    log_cfg_t log_cfg;
    smartdof_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    smartdof_cfg_setup( &cfg );
    SMARTDOF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    smartdof_init( &smartdof, &cfg );

    if ( smartdof_default_cfg ( &smartdof ) !=0 )
    {
        log_info( &logger, "Error during default configuration" );
    }
}
  
```

### Application Task

> Executes one of 'smartdof_xxx_task()' additional functions 

```c

void application_task ( void )
{
    accelerometer_task( &smartdof, &smartdof_sfc );
}  

```

## Note

> <pre>
> Additional Functions :
> - accelerometer_task() - initializes accelerometer reports in 100000 micro second intervals, receives, parses and logs report data
> - gyroscope_task() - initializes gyroscope calibrated reports in 100000 micro second intervals, receives, parses and logs report data
> - magnetometer_task() - initializes magnetometer calibrated reports in 100000 micro second intervals, receives, parses and logs report data
> </pre> 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartDof

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
