\mainpage Main Page

---
# Load Cell 4 Click

> Load Cell 4 Click is a compact add-on board that contains a resistive sensor signal conditioner with a fast power-up data output response. This board features the ZSC31014, a CMOS integrated circuit for highly accurate amplification and analog-to-digital conversion of differential and half-bridge input signals from Renesas. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/loadcell4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/load-cell-4-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the LoadCell4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LoadCell4 Click driver.

#### Standard key functions :

- `loadcell4_cfg_setup` Config Object Initialization function.
```c
void loadcell4_cfg_setup ( loadcell4_cfg_t *cfg );
```

- `loadcell4_init` Initialization function.
```c
err_t loadcell4_init ( loadcell4_t *ctx, loadcell4_cfg_t *cfg );
```

- `loadcell4_default_cfg` Click Default Configuration function.
```c
err_t loadcell4_default_cfg ( loadcell4_t *ctx );
```

#### Example key functions :

- `loadcell4_power_dev` Enable power function.
```c
void loadcell4_power_dev ( loadcell4_t *ctx, uint8_t power_state );
```

- `loadcell4_tare` Tare the scales function.
```c
void loadcell4_tare ( loadcell4_t *ctx, loadcell4_data_t *cell_data );
```

- `loadcell4_get_weight` Get weight function.
```c
float loadcell4_get_weight ( loadcell4_t *ctx, loadcell4_data_t *cell_data );
```

## Example Description

> This is an example that demonstrates the use of the Load Cell 4 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes I2C driver and performs the power on. Sets tare the scale, calibrate scale and start measurements.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    loadcell4_cfg_t loadcell4_cfg;  /**< Click config object. */

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
    loadcell4_cfg_setup( &loadcell4_cfg );
    LOADCELL4_MAP_MIKROBUS( loadcell4_cfg, MIKROBUS_1 );
    err_t init_flag = loadcell4_init( &loadcell4, &loadcell4_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    loadcell4_default_cfg ( &loadcell4 );
    
    loadcell4_power_dev( &loadcell4, LOADCELL4_PWR_ON );
    Delay_ms ( 500 );
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "     ~~~  STEP 1  ~~~    \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "     Tare the scale :    \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " >> Remove all object << \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " In the following 10 sec \r\n" );
    log_printf( &logger, " please remove all object\r\n" );
    log_printf( &logger, "     from the scale.     \r\n" );
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
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "    Start tare scales    \r\n" );
    loadcell4_tare( &loadcell4, &cell_data );
    Delay_ms ( 500 );

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "   Tarring is complete   \r\n" );
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "     ~~~  STEP 2  ~~~    \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "    Calibrate Scale :    \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "   >>> Load etalon <<<   \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " In the following 10 sec \r\n" );
    log_printf( &logger, "place 100 g weight etalon\r\n" );
    log_printf( &logger, "    on the scale for     \r\n" );
    log_printf( &logger, "   calibration purpose.  \r\n" );
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

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "    Start calibration    \r\n" );

    if ( loadcell4_calibration( &loadcell4, LOADCELL4_WEIGHT_100G, &cell_data ) == LOADCELL4_OK ) {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "    Calibration  Done    \r\n" );
        log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
        log_printf( &logger, "  >>> Remove etalon <<<  \r\n" );
        log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
        log_printf( &logger, " In the following 10 sec \r\n" );
        log_printf( &logger, "   remove 100 g weight   \r\n" );
        log_printf( &logger, "   etalon on the scale.  \r\n" );
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
    } else {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "   Calibration  Error   \r\n" );
        for ( ; ; );
    }

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "   Start measurements :  \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
}

```

### Application Task

> The Load Cell 4 Click board can be used to measure weight, shows the measurement of scales in grams [ g ].
> Results are being sent to the Usart Terminal where you can track their changes. All data logs write on USB uart changes for every 4 sec.

```c

void application_task ( void ) {
    weight_val = loadcell4_get_weight( &loadcell4, &cell_data );
    log_printf( &logger, "     Weight : %.2f g \r\n", weight_val );
    Delay_ms ( 100 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LoadCell4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
