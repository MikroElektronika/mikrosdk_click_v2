

---
# LOAD CELL click

Load cell click is a weight measurement click which utilizes a load cell element, in order to precisely measure the weight of an object. The Load Cell click can be used with the strain gauge type of load cells and can measure up to ±20V or ±40V of differential voltage.

The click is designed to run on either 3.3V or 5V power supply. It communicates with the target microcontroller over SPI interface.>

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/loadcell_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/load-cell-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the LoadCell Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LoadCell Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void loadcell_cfg_setup ( loadcell_cfg_t *cfg ); 
 
- Initialization function.
> LOADCELL_RETVAL loadcell_init ( loadcell_t *ctx, loadcell_cfg_t *cfg );

- Click Default Configuration function.
> void loadcell_default_cfg ( loadcell_t *ctx );


#### Example key functions :

- Read results of function.
> uint8_t loadcell_read_results ( loadcell_t *ctx, uint8_t input_sel, uint32_t *data_out );
 
- Set rate function.
> void loadcell_set_rate ( loadcell_t *ctx, uint8_t rate_sel );

- Check status of pin DO (do_pin).
> uint8_t loadcell_check_out ( loadcell_t *ctx );

- Reset clock function.
> void loadcell_reset ( loadcell_t *ctx );
 
- Set clock mode function.
> void loadcell_set_mode ( loadcell_t *ctx, uint8_t pwr_mode );

- Function of messure and read results.
> void loadcell_tare ( loadcell_t *ctx, uint8_t input_sel, loadcell_data_t *cell_data );

- Calibration function.
> uint8_t loadcell_calibration ( loadcell_t *ctx, uint8_t input_sel, uint16_t cal_val, loadcell_data_t *cell_data );

- Get weight function.
> float loadcell_get_weight ( loadcell_t *ctx, uint8_t input_sel, loadcell_data_t *cell_data );

## Examples Description

> 
> Load cell click is a weight measurement click which utilizes a load cell element, 
> in order to precisely measure the weight of an object. 
> The Load Cell click can be used with the strain gauge type of load cells 
> and can measure up to ±20V or ±40V of differential voltage. 
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initializes GPIO driver and performs the device reset, 
> after which the next conversion cycle will be for channel B with 32 gate value.
> This function also selects the frequency of internal oscillator to 10Hz.
> Sets tare the scale, calibrate scale and start measurements.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    loadcell_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    loadcell_cfg_setup( &cfg );
    LOADCELL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    loadcell_init( &loadcell, &cfg );
    
    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, "     Load cell click     \r\n");
    log_printf(&logger, "-------------------------\r\n");
    Delay_ms( 100 );
    
    loadcell_set_mode( &loadcell, LOADCELL_POWER_UP );
    Delay_ms( 100 );

    loadcell_reset( &loadcell );
    Delay_ms( 100 );

    loadcell_set_rate( &loadcell, LOADCELL_10HZ_INTERNAL_OSC );
    Delay_ms( 100 );

    log_printf(&logger, "    Tare the scale :   Channel B,  Gate 32  \r\n");
    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, " In the following 10 seconds please REMOVE all object from the scale.\r\n");
    Delay_ms( 10000 );

    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, "    Start tare scales    \r\n");
    loadcell_tare ( &loadcell, LOADCELL_CHANN_B_GATE_32_NEXT, &cell_data );
    Delay_ms( 500 );

    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, "    Tarring completed \r\n");

    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, " In the following 10 seconds place 100g weight etalon on the scale for calibration purpose.\r\n");
    Delay_ms( 10000 );

    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, "    Start calibration    \r\n");

    if ( loadcell_calibration ( &loadcell, LOADCELL_CHANN_B_GATE_32_NEXT, LOADCELL_WEIGHT_100G, &cell_data ) == LOADCELL_GET_RESULT_OK )
    {
        log_printf(&logger, "-------------------------\r\n");
        log_printf(&logger, "    Calibration  Done    \r\n");

        log_printf(&logger, "- - - - - - - - - - - - -\r\n");
        log_printf(&logger, " In the following 10 seconds please REMOVE all object from the scale.\r\n");
        Delay_ms( 10000 );
    }
    else
    {
        log_printf(&logger, "-------------------------\r\n");
        log_printf(&logger, "   Calibration  Error   \r\n");
        for ( ; ; );
    }

    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, "   Start measurements :  \r\n");
    log_printf(&logger, "-------------------------\r\n");
}
  
```

### Application Task

>
> This is an example which demonstrates the use of Load Cell Click board.
> Display the measurement of scales in grams [ g ].
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB uart changes for every 1 sec.
> 

```c

void application_task ( void )
{
    weight_val = loadcell_get_weight( &loadcell, LOADCELL_CHANN_B_GATE_32_NEXT, &cell_data );

    log_printf(&logger, "     Weight : %.2f\r\n", weight_val );

    Delay_ms( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LoadCell

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
