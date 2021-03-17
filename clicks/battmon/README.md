\mainpage Main Page
 
 

---
# BATT-MON click

BATT-MON Click is a very versatile, high accuracy, multiple-chemistry battery gauge for applications single-cell batteries.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/battmon_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/batt-mon-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the BattMon Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for BattMon Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void battmon_cfg_setup ( battmon_cfg_t *cfg ); 
 
- Initialization function.
> BATTMON_RETVAL battmon_init ( battmon_t *ctx, battmon_cfg_t *cfg );

- Click Default Configuration function.
> void battmon_default_cfg ( battmon_t *ctx );


#### Example key functions :

- Data Get function
> float battmon_get_data ( battmon_t *ctx, uint8_t data_addr );
 
- ALM Pin Get function
> uint8_t battmon_get_alm_pin ( battmon_t *ctx );

- Conversion Counter Reset function
> void battmon_reset_conv_cnt ( battmon_t *ctx );

## Examples Description

> This application is battery charger.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C serial interface, reads the part ID and
> performs a device configuration and alarm setting.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    battmon_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    battmon_cfg_setup( &cfg );
    BATTMON_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    battmon_init( &battmon, &cfg );

    Delay_ms( 500 );

    battmon_read_bytes( &battmon, BATTMON_REG_ID, &reg_read, 1 );
    log_printf( &logger, " ** Part ID: 0x%d \r\n", (uint16_t) reg_read );

    battmon_default_cfg( &battmon );
    
    log_printf( &logger, "** BattMon initialization done ** \r\n" );
    log_printf( &logger, "********************************* \r\n" );
}
  
```

### Application Task

> Checks the conversion counter value and when conversion was done
> reads data calculated to the properly unit and checks the alarm status.
> All results will be sent to the uart terminal.

```c

void application_task ( void )
{
    char cels_symbol[ 3 ] = { 176, 'C', 0 };
    float data_read;
    uint16_t conv_cnt;

    conv_cnt = battmon_get_data( &battmon, BATTMON_REG_COUNTER );

    if ( ( ( conv_cnt % 4 ) == 0 ) && ( conv_cnt > 0 ) )
    {
        data_read = battmon_get_data( &battmon, BATTMON_REG_SOC );
        log_printf( &logger, "** Gas Gauge Relative SOC : %.2f %% \r\n ", data_read );
    
        data_read = battmon_get_data( &battmon, BATTMON_REG_CURRENT );
        log_printf( &logger, "** Battery Current : %.2f mA \r\n", data_read );

        
        data_read = battmon_get_data( &battmon, BATTMON_REG_VOLTAGE );
        log_printf( &logger, "** Battery Voltage : %.2f mV \r\n", data_read );
        
        if ( ( conv_cnt % 16 ) == 0 )
        {
            data_read = battmon_get_data( &battmon, BATTMON_REG_TEMPERATURE );
            battmon_reset_conv_cnt( &battmon );
            log_printf( &logger, "** Temperature :  %.2f %s\r\n", data_read, cels_symbol );
        }
        
        reg_read = battmon_check_clear_alarm( &battmon );

        if ( ( reg_read & BATTMON_ALM_SOC_DET_MASK ) != BATTMON_LOG_LOW )
        {
            log_printf( &logger,  "** Low-SOC Condition! \r\n" );
        }
        if ( ( reg_read & BATTMON_ALM_VOLT_DET_MASK ) != BATTMON_LOG_LOW )
        {
            log_printf( &logger,  "** Low-Voltage Condition! \r\n" ); 
        }
        
        log_printf( &logger, "********************************* \r\n" );
        Delay_ms( 1000 );
    }
    else
    {
        Delay_ms( 200 );
    }
}

```

## Note

> Voltage and current conversion will be done after 4 seconds.
> Temperature conversion will be done after 16 seconds.
> After temperature reading the conversion counter will be cleared.
> Clearing the alarm while the corresponding low-voltage or low-SOC condition is still in progress 
> does not generate another interrupt. This condition must disappear first and must be detected again 
> before another interrupt (ALM pin driven low or alarm interrupt bits are set high) is generated for this alarm.
> Another alarm condition, if not yet triggered, can still generate an interrupt.
> Input voltage must be in the range from 2.7V to 4.5V.
> Maximal battery current is 5A.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.BattMon

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
