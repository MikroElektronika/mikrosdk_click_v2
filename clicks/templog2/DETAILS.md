 

---
# Temp-Log 2 click

Temp-Log 2 click is a precise ambient temperature measurement device, equipped with the additional non-volatile (EEPROM) memory that can be used
to permanently store system configuration, and 64 bits of general-purpose EEPROM, used for logging application specific or user preference data.
This click covers a range of temperatures from -55°C to +125°C with the highest accuracy of ±0.2°C

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/templog2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/temp-log-2-click>)

---


#### Click library

- **Author**        : Nemanja Medakovic
- **Date**          : Nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TempLog2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers).
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account.

## Library Description

> This library contains API for TempLog2 Click driver.

#### Standard key functions :

- Configuration Object Setup function.
> void templog2_cfg_setup( templog2_cfg_t *cfg );
 
- Click Initialization function.
> TEMPLOG2_RETVAL templog2_init( templog2_t *ctx, templog2_cfg_t *cfg );

- Click Default Configuration function.
> void templog2_default_cfg( templog2_t *ctx );


#### Example key functions :

- Write Register function.
> TEMPLOG2_RETVAL templog2_write_reg( templog2_t *ctx, uint8_t reg_addr, uint16_t transfer_data );
 
- Read Register function.
> TEMPLOG2_RETVAL templog2_read_reg( templog2_t *ctx, uint8_t reg_addr, uint16_t *data_out );

- Read Temperature function.
> float templog2_read_temp( templog2_t *ctx );

## Examples Description

>
> This example demonstrates the use of the Temp-Log 2 Click board.
>

**The demo application is composed of two sections :**

### Application Init

>
> Initializes peripherals and pins.
> Initializes I2C driver and performs device configuration.
> Sets total active conversion time to 250 ms and 8 average samples.
> Also sets Shutdown Mode as default mode, and after device reset puts device
> in Continuous Conversion Mode.
> High limit status will be set when temperature cross over the determined
> high limit temperature value.
> Low limit status will be set when temperature falls below the determined
> low limit temperature value.
>

```c

void application_init( void )
{
    templog2_cfg_t templog2_cfg;
    log_cfg_t logger_cfg;

    //  Click initialization.
    templog2_cfg_setup( &templog2_cfg );
    TEMPLOG2_MAP_MIKROBUS( templog2_cfg, MIKROBUS_1 );
    templog2_init( &templog2, &templog2_cfg );

    //  Click default configuration.
    templog2_default_config( &templog2 );

    //  Logger console initialization.
    logger_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( logger_cfg );
	logger_cfg.baud = 57600;
    log_init( &logger, &logger_cfg );
    log_info( &logger, "----  Temp-Log 2 Application Init Done  ----\r\n" );
}

```

### Application Task

>
> Reads temperature value calculated to Celsius degrees.
>

```c

void application_task( void )
{
    float temperature;
    uint8_t temp_status;
    uint8_t cnt;

    temp_status = templog2_data_ready( &templog2 );

    if (temp_status & _TEMPLOG2_DATA_READY_MASK)
    {
        temperature = templog2_read_temp( &templog2 );

        log_printf( &logger, " > Temperature : %.2f\r\n", temperature );

        if (temp_status & _TEMPLOG2_LOW_LIMIT_MASK)
        {
            log_printf( &logger, " LOW LIMIT DETECTED!\r\n" );
        }

        if (temp_status & _TEMPLOG2_HIGH_LIMIT_MASK)
        {
            log_printf( &logger, " HIGH LIMIT DETECTED!\r\n" );
        }
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TempLog2

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
