\mainpage Main Page
 
---
# Load Cell 2 click

Load cell 2 Click is a weight measurement click which utilizes a load cell element, in order to precisely measure the weight of an object. The Load Cell 2 Click can be used with the strain gauge type of load cells with external differential reference voltage range from 0.1V to 5V. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/loadcell2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/load-cell-2-click)

---


#### Click library 

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the LoadCell2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LoadCell2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void loadcell2_cfg_setup ( loadcell2_cfg_t *cfg ); 
 
- Initialization function.
> LOADCELL2_RETVAL loadcell2_init ( loadcell2_t *ctx, loadcell2_cfg_t *cfg );

- Click Default Configuration function.
> void loadcell2_default_cfg ( loadcell2_t *ctx );


#### Example key functions :

- Get weight function.
> float loadcell2_get_weight ( loadcell2_t *ctx, loadcell2_data_t *cell_data );
 
- Get results function.
> uint32_t loadcell2_get_result ( loadcell2_t *ctx );

- Calibration function.
> uint8_t loadcell2_calibration ( loadcell2_t *ctx, uint16_t cal_val, loadcell2_data_t *cell_data );

## Examples Description

> 
> Load Cell 2 click is a weight measurement click 
> which utilizes a load cell element, 
> in order to precisely measure the weight of an object.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initializes I2C driver and performs the device reset, 
> and performs the device reset, set power on and default configuration.
> Sets tare the scale, calibrate scale and start measurements.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    loadcell2_cfg_t cfg;

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
    log_printf( &logger, "  - Application Init -   \r\n" );

    //  Click initialization.

    loadcell2_cfg_setup( &cfg );
    LOADCELL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    loadcell2_init( &loadcell2, &cfg );
    
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "     Load cell click     \r\n");
    log_printf( &logger, "-------------------------\r\n");
    Delay_ms ( 100 );
    
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "   Reset all registers   \r\n");
    loadcell2_reset( &loadcell2 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "        Power On         \r\n");
    loadcell2_power_on( &loadcell2 );
    Delay_ms ( 100 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "   Set default config.   \r\n");
    loadcell2_default_cfg( &loadcell2 );
    Delay_ms ( 100 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "      Calibrate AFE      \r\n");
    loadcell2_calibrate_afe( &loadcell2 );
    Delay_ms ( 1000 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "     Tare the scale :    \r\n");
    log_printf( &logger, "- - - - - - - - - - - - -\r\n");
    log_printf( &logger, " >> Remove all object << \r\n");
    log_printf( &logger, "- - - - - - - - - - - - -\r\n");
    log_printf( &logger, " In the following 10 sec \r\n");
    log_printf( &logger, " please remove all object\r\n");
    log_printf( &logger, "     from the scale.     \r\n");
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "    Start tare scales    \r\n");
    loadcell2_tare ( &loadcell2, &cell_data );
    Delay_ms ( 500 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "   Tarring is complete   \r\n");
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "    Calibrate Scale :    \r\n");
    log_printf( &logger, "- - - - - - - - - - - - -\r\n");
    log_printf( &logger, "   >>> Load etalon <<<   \r\n");
    log_printf( &logger, "- - - - - - - - - - - - -\r\n");
    log_printf( &logger, " In the following 10 sec \r\n");
    log_printf( &logger, "place 1000g weight etalon\r\n");
    log_printf( &logger, "    on the scale for     \r\n");
    log_printf( &logger, "   calibration purpose.  \r\n");
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "    Start calibration    \r\n");

    if ( loadcell2_calibration ( &loadcell2, LOADCELL2_WEIGHT_1000G, &cell_data ) == LOADCELL2_GET_RESULT_OK )
    {
        log_printf( &logger, "-------------------------\r\n");
        log_printf( &logger, "    Calibration  Done    \r\n");

        log_printf( &logger, "- - - - - - - - - - - - -\r\n");
        log_printf( &logger, "  >>> Remove etalon <<<  \r\n");
        log_printf( &logger, "- - - - - - - - - - - - -\r\n");
        log_printf( &logger, " In the following 10 sec \r\n");
        log_printf( &logger, "   remove 1000g weight   \r\n");
        log_printf( &logger, "   etalon on the scale.  \r\n");
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else
    {
        log_printf( &logger, "-------------------------\r\n");
        log_printf( &logger, "   Calibration  Error   \r\n");
        for ( ; ; );
    }

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "   Start measurements :  \r\n");
    log_printf( &logger, "-------------------------\r\n");
}
  
```

### Application Task

>
> This is an example which demonstrates the 
> use of Load Cell 2 Click board. 
> Display the measurement of scales in grams [g].
> Results are being sent to the Usart Terminal 
> where you can track their changes.
> All data logs write on USB uart changes for every 1 sec.
> 

```c

void application_task ( void )
{
    weight_val = loadcell2_get_weight( &loadcell2, &cell_data );

    log_printf(&logger, "   Weight : %5.2f g\r\n", weight_val );

    Delay_ms ( 1000 );
}  

```

## Note


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LoadCell2

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
