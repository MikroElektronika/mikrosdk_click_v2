/*!
 * @file main.c
 * @brief SPIExtend Click example
 *
 * # Description
 *  In this example, if the connection is established, we read Accel axis of the connected
 * Accel 14 Click boards to the SPI Extend Click ( Remote Mode ) which is connected by a LAN cable to 
 * SPI Extend Click ( Local Mode ) placed in the mikroBUS 1. Results are being sent to the Usart Terminal where you can track their
 * changes. All data logs write on USB uart changes for every 1 sec.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI, sets INT pin as input and AN, RST, CS nad PWM pins as outputs and begins to write log.
 * Also, initialization driver enables - SPI, set default configuration of the Accel 14 Click
 * connected to the SPI Extend Click ( Remote Mode ).
 *
 * ## Application Task
 * If the click is connected properly then the status becomes active and the X-axis coordinate is printed first on the UART terminal, 
 * then Y and finally Z. After 1s the process is repeated. 
 * In case an error has occurred, printed "LINK is not established" on UART Terminal.
 * 
 * Additional Functions :
 *  - void spiextend_accel14_get_axis ( uint8_t axis_out_reg ) - SPI Extend reading axis function.
 *  - void spiextend_display_status ( uint8_t check_status ) - SPI Extend check display status function.
 *
 * @author Jelena Milosavljevic
 *
 */

#include "board.h"
#include "log.h"
#include "spiextend.h"

static spiextend_t spiextend;
static log_t logger;

static int16_t axis;
spiextend_status_data_t spiextend_status;

/**
 * @brief SPI Extend reading axis function.
 * @details This function is used for reading axis.
 * @param[in] axis_out_reg : Data from the register.
 * @return Nothing. 
 */
void spiextend_accel14_get_axis ( uint8_t axis_out_reg );

/**
 * @brief SPI Extend check display status function.
 * @details This function is used for check display status.
 * @param[in] check_status : Display data.
 * @return Nothing.
 */
void spiextend_display_status ( uint8_t check_status );

void application_init ( void ) {
    
    log_cfg_t log_cfg;                /**< Logger config object. */
    spiextend_cfg_t spiextend_cfg;    /**< Click config object. */

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
    log_info( &logger, " Application Init \r\n" );

    // Click initialization.

    spiextend_cfg_setup( &spiextend_cfg );
    SPIEXTEND_MAP_MIKROBUS( spiextend_cfg, MIKROBUS_1 );
    err_t init_flag  = spiextend_init( &spiextend, &spiextend_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
       
        log_error( &logger, " Application Init Error. \r\n" );
        log_info( &logger, " Please, run program again... \r\n" );

        for ( ; ; );
    }
    spiextend_default_cfg( &spiextend);
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "   SPI Extend Click  \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 100 );
    
    spiextend_get_status( &spiextend, &spiextend_status );
    log_printf( &logger, " LINK        : " ); 
    
    spiextend_display_status( spiextend_status.nlink );
    log_printf( &logger, " INT         : " );
    
    spiextend_display_status( spiextend_status.nint );
    log_printf( &logger, " Remote INT  : " );
    spiextend_display_status( spiextend_status.rmt_nint );
    
    log_printf( &logger, " Speed Index : %d\r\n", ( uint16_t ) spiextend_status.speed_idx );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 100 );
    
    log_printf( &logger, "  >>> Accel 14 <<<   \r\n" );
    log_printf( &logger, " Set default config. \r\n" );
    spiextend_rmt_write ( &spiextend, SPIEXTEND_ACCEL14_REG_CTRL1_XL | SPIEXTEND_ACCEL14_SPI_WRITE,     
                                      SPIEXTEND_ACCEL14_CTRL1_XL_POWER_UP | 
                                      SPIEXTEND_ACCEL14_CTRL1_XL_HIGH_RES_FS | 
                                      SPIEXTEND_ACCEL14_CTRL1_XL_GSEL_4G, 
                          SPIEXTEND_SLAVE_SELECT_SS1 );
    Delay_ms ( 100 );
    
    spiextend_rmt_write ( &spiextend, SPIEXTEND_ACCEL14_REG_CTRL3_C | SPIEXTEND_ACCEL14_SPI_WRITE, 
                                      SPIEXTEND_ACCEL14_CTRL3_C_BOOT_NORMAL | 
                                      SPIEXTEND_ACCEL14_CTRL3_C_BDU_READ_UPDATE | 
                                      SPIEXTEND_ACCEL14_CTRL3_C_INT_ACTIVE_HIGH | 
                                      SPIEXTEND_ACCEL14_CTRL3_C_PP_OD_PUSH_PULL | 
                                      SPIEXTEND_ACCEL14_CTRL3_C_SIM_SPI_4_WIRE | 
                                      SPIEXTEND_ACCEL14_CTRL3_C_IF_INC_ENABLE | 
                                      SPIEXTEND_ACCEL14_CTRL3_C_SW_RESET_DIS, 
                                      SPIEXTEND_SLAVE_SELECT_SS1 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Acceleration data: \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task \r\n" );
}

void application_task ( void ) {
    
    //  Task implementation.
    
    spiextend_get_status( &spiextend, &spiextend_status );
    
    if ( spiextend_status.nlink == SPIEXTEND_STATUS_ACTIVE ) {
        
        spiextend_accel14_get_axis( SPIEXTEND_ACCEL14_REG_OUTX_L_A );
        Delay_ms ( 10 );
        log_printf( &logger, "  Accel X : %d \r\n", axis );
        
        spiextend_accel14_get_axis( SPIEXTEND_ACCEL14_REG_OUTY_L_A );
        Delay_ms ( 10 );
        log_printf( &logger, "  Accel Y : %d \r\n", axis );

        spiextend_accel14_get_axis( SPIEXTEND_ACCEL14_REG_OUTZ_L_A );
        Delay_ms ( 10 );
        log_printf( &logger, "  Accel Z : %d \r\n", axis );

        log_printf( &logger, "---------------------\r\n" );
        Delay_ms ( 1000 );
    }
    else {
        
        log_printf( &logger, " LINK not established\r\n" );
        log_printf( &logger, "---------------------\r\n" );
        Delay_ms ( 1000 );
    }
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

void spiextend_accel14_get_axis ( uint8_t axis_out_reg ) {
  
    uint16_t rx_val;
    uint8_t lbs;
    uint8_t mbs; 
    
    lbs = spiextend_rmt_read( &spiextend, axis_out_reg| SPIEXTEND_ACCEL14_SPI_READ, 
                                                        SPIEXTEND_SLAVE_SELECT_SS1 );

    axis_out_reg++;
    mbs = spiextend_rmt_read( &spiextend, axis_out_reg | SPIEXTEND_ACCEL14_SPI_READ,    
                                                         SPIEXTEND_SLAVE_SELECT_SS1 );
    rx_val = mbs;
    rx_val <<= 8;
    rx_val |= lbs;

    axis = ( int16_t ) rx_val;
}

void spiextend_display_status ( uint8_t check_status ) {
    
    if ( check_status == SPIEXTEND_STATUS_ACTIVE ) {
       log_printf( &logger, " ON \r\n" );
    } else {
        log_printf( &logger, " OFF \r\n" );
    }
}

// ------------------------------------------------------------------------ END

