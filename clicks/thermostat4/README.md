\mainpage Main Page

---
# Thermostat 4 click

> Thermostat 4 Click is complete solution that senses the temperature of a physical system and can performs actions so that the system's temperature is maintained near a desired setpoint. It's based on Texas Instruments TMP392, a resistor programmable temperature switch that enable protection and detection of system thermal events from 30°C to 130°C.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermostat4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermostat-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Thermostat4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thermostat4 Click driver.

#### Standard key functions :

- `thermostat4_cfg_setup` Config Object Initialization function.
```c
void thermostat4_cfg_setup ( thermostat4_cfg_t *cfg ); 
```

- `thermostat4_init` Initialization function.
```c
err_t thermostat4_init ( thermostat4_t *ctx, thermostat4_cfg_t *cfg );
```

#### Example key functions :

- `thermostat4_hot_alert_state` This function read state from OA pin
```c
uint8_t thermostat4_hot_alert_state ( thermostat4_t *ctx );
```
 
- `thermostat4_relay_ctrl` This function write desired state on RLY pin
```c
void thermostat4_relay_ctrl ( thermostat4_t *ctx, uint8_t state );
```

- `thermostat4_set_warm_hysteresis` This function write hysteresis data.
```c
void thermostat4_set_warm_hysteresis ( thermostat4_t *ctx, uint8_t hyst_data );
```

## Examples Description

> Thermostat 4 Click reads alert on the warm and hot channel, using standard SPI communication.

**The demo application is composed of two sections :**

### Application Init 

> Initializes Driver init, Relay test and
> sets hysteresis on the WARM channel ( channel B ), after that starts uploading new data.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermostat4_cfg_t thermostat4_cfg;

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
    thermostat4_cfg_setup( &thermostat4_cfg );
    THERMOSTAT4_MAP_MIKROBUS( thermostat4_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == thermostat4_init( &thermostat4, &thermostat4_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_printf( &logger, " RELAY ON\r\n" );
    thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_ON );
    Delay_ms( 1000 );
    log_printf( &logger, " RELAY OFF\r\n" );
    thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_OFF );
    Delay_ms( 500 );
    
    thermostat4_set_warm_hysteresis( &thermostat4, 0 );
    thermostat4_new_cfg_upload( &thermostat4 );
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Reads Alert on the WARM and HOT channel. 

```c

void application_task ( void )
{
    if ( THERMOSTAT4_HOT_ALERT == thermostat4_hot_alert_state( &thermostat4 ) ) 
    {
        log_printf( &logger, " HOT ALERT\r\n" );
        thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_ON );
    } 
    else if ( THERMOSTAT4_WARM_ALERT == thermostat4_warm_alert_state( &thermostat4 ) ) 
    {
        log_printf( &logger, " WARM ALERT\r\n" );
        thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_ON );
    } 
    else 
    { 
        log_printf( &logger, " TEMPERATURE OK\r\n" );
        thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_OFF );
    }  
    Delay_ms( 2000 );
}

```

## Note

> The user has the option of adjusting the hysteresis for channel B via the SPI module 
> while for channel A it is adjusted via the potentiometer. 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermostat4

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
