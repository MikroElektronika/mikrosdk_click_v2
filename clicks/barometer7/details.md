
---
# Barometer 7 click

> Barometer 7 Click is a compact add-on board used to measure air pressure in a specific environment. This board features the KP264XTMA1, a high-accuracy digital barometric air pressure sensor based on a capacitive principle from Infineon Technologies. The KP264XTMA1 is surface micromachined with a monolithic integrated signal conditioning circuit implemented in BiCMOS technology that converts pressure into a 10-bit digital value and sends the information via the SPI interface. It measures pressure from 40kPa up to 115kPa with an accuracy of ±1.5kPa over a wide operating temperature range. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/barometer7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/barometer-7-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Barometer 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Barometer 7 Click driver.

#### Standard key functions :

- `barometer7_cfg_setup` Config Object Initialization function.
```c
void barometer7_cfg_setup ( barometer7_cfg_t *cfg );
```

- `barometer7_init` Initialization function.
```c
err_t barometer7_init ( barometer7_t *ctx, barometer7_cfg_t *cfg );
```

- `barometer7_default_cfg` Click Default Configuration function.
```c
err_t barometer7_default_cfg ( barometer7_t *ctx );
```

#### Example key functions :

- `barometer7_get_pressure` Barometer 7 get pressure function.
```c
err_t barometer7_get_pressure ( barometer7_t *ctx, float *pressure );
```

- `barometer7_get_temperature` Barometer 7 get temperature function.
```c
err_t barometer7_get_temperature ( barometer7_t *ctx, float *temperature );
```

## Example Description

> This library contains API for Barometer 7 Click driver.
> The demo application reads and calculate temperature and pressure data.

**The demo application is composed of two sections :**

### Application Init

> Initializes SPI driver and log UART.
> After driver initialization the app set default settings 
> and display sensor identifier data.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer7_cfg_t barometer7_cfg;  /**< Click config object. */

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
    barometer7_cfg_setup( &barometer7_cfg );
    BAROMETER7_MAP_MIKROBUS( barometer7_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == barometer7_init( &barometer7, &barometer7_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    BAROMETER7_SET_DATA_SAMPLE_EDGE;
    
    if ( BAROMETER7_ERROR == barometer7_default_cfg ( &barometer7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );;
    
    static barometer7_identifier_t id_data;
    barometer7_get_identifier ( &barometer7, &id_data );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " > Supplier         : %d <\r\n", ( uint16_t ) id_data.supplier );
    log_printf( &logger, " > Silicon Version  : %d <\r\n", ( uint16_t ) id_data.silicon_version );
    log_printf( &logger, " > Metal Version    : %d <\r\n", ( uint16_t ) id_data.metal_version );
    log_printf( &logger, " > ASCI Name        : %c <\r\n", id_data.asic_name );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1000 );
}

```

### Application Task

> This is an example that demonstrates the use of the Barometer 7 Click board™.
> In this example, display the Pressure ( mBar ) and Temperature ( degree Celsius ) data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    static float pressure; 
    static float temperature;
    
    barometer7_get_pressure( &barometer7, &pressure );
    if ( BAROMETER7_NO_ERROR != barometer7.diagnosis )
    {
        display_error( );
    }
    log_printf( &logger, " Pressure     : %.0f mbar\r\n", pressure );
    
    barometer7_get_temperature( &barometer7, &temperature );
    if ( BAROMETER7_NO_ERROR != barometer7.diagnosis )
    {
        display_error( );   
    }
    log_printf( &logger, " Temperature  : %.2f C\r\n", temperature );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 2000 );
}
```

## Additional Function

- `display_error` This function displays diagnosis error messages.
```c
static void display_error ( void );
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
