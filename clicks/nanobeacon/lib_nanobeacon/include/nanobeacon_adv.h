#include "stdint.h"

#define RET_OK                  0
#define RET_ERROR              -1
#define RET_INVALID_PARAMETER  -2

typedef struct 
{
    uint8_t addr_not_present;
    uint8_t header_len;
    uint8_t header[ 4 ];
    
} pkt_f0_t;

typedef union 
{
    uint8_t timer_sel;
    uint8_t rand_num_sel;
    uint8_t sensor_idx;
    uint8_t mts_offset;
    uint8_t gpio_sel;
    uint8_t plsdtct_sel;
    uint16_t reg_addr;
    
} pkt_fx_private_t;

typedef struct 
{
    uint8_t data_src;
    uint8_t endian;
    uint8_t encryption;
    uint8_t encryption_last;

    uint8_t length;
    uint8_t msb_lsb_sel;
    uint8_t encryption_output_order;

    pkt_fx_private_t uni;

    uint8_t data_offset;
    
} pkt_f1to7_t;

typedef union 
{
    struct 
    {
        uint8_t preamble : 1;
        uint8_t num_fields : 4;
        uint8_t sync_pattern_en : 1;
        uint8_t rsv : 2;
    } uni;
    uint8_t data_buf;
    
} pkt_ctl_byte0_t;

typedef union 
{
    struct 
    {
        uint8_t cte_en : 1;
        uint8_t cte_len : 5;
        uint8_t phy_rate : 2;
    } uni;
    uint8_t data_buf;
    
} pkt_ctl_byte1_t;

typedef union 
{
    struct 
    {
        uint8_t eax_en : 1;
        uint8_t key_sel : 2;
        uint8_t rot_exp : 5;
    } uni;
    uint8_t data_buf;
    
} pkt_ctl_byte2_t;

typedef struct 
{
    pkt_ctl_byte0_t byte0;
    pkt_ctl_byte1_t byte1;
    pkt_ctl_byte2_t byte2;
    uint32_t sync_pattern;
    pkt_f0_t pkt_f0;
    uint8_t f1to7_cnt;
    uint8_t cur_pos;
    uint8_t *data_buffer;
    pkt_f1to7_t pkt_f[ 7 ];
    
} pkt_ctl_t;

typedef union 
{
    struct 
    {
        uint8_t adv_type : 1;
        uint8_t trig_source : 6;
    } uni;
    uint8_t data_buf;
    
} adv_ctl_byte0_t;

typedef union 
{
    struct 
    {
        uint8_t adv_trig_mode : 2;
        uint8_t adv_ext_en : 1;
        uint8_t secondary_adv_exist : 2;
        uint8_t adv_channel_control : 3;
    } uni;
    uint8_t data_buf;
    
} adv_ctl_byte8_t;

typedef union 
{
    struct 
    {
        uint8_t adv_addr_type : 3;
        uint8_t addr_key_sel : 5;
    } uni;
    uint8_t data_buf;
    
} addr_private_data_t;

typedef struct 
{
    adv_ctl_byte0_t byte0;
    uint8_t gpio_source;
    uint8_t byte2;
    uint8_t adv_interval[ 3 ];
    uint16_t packet_table_location;
    adv_ctl_byte8_t byte8;
    uint8_t evnt_wakeup_period[ 3 ];
    uint8_t num_event_control[ 2 ];
    addr_private_data_t addr_private_data;
    uint8_t adv_addr[ 6 ];
    uint8_t addr_gen_interval[ 2 ];
    pkt_ctl_t pkt_ctl;
    
} adv_ctl_t;

typedef enum 
{
    ADV_DATA_TYPE_PREDEF = 0,
    ADV_DATA_TYPE_TIMER = 1,
    ADV_DATA_TYPE_RAND = 2,
    ADV_DATA_TYPE_TEMP = 3,
    ADV_DATA_TYPE_VBAT = 4,
    ADV_DATA_TYPE_SENSOR = 5,
    ADV_DATA_TYPE_TAG = 7,
    ADV_DATA_TYPE_MTS_DATA = 8,
    ADV_DATA_TYPE_TX_PWR_0M = 9,
    ADV_DATA_TYPE_INP_UUID = 10,
    ADV_DATA_TYPE_CUS_UUID = 11,
    ADV_DATA_TYPE_EID = 12,
    ADV_DATA_TYPE_ADV_EVNT_CNT = 13,
    ADV_DATA_TYPE_AUXPTR = 14,
    ADV_DATA_TYPE_SLEEP_CNT = 15,
    ADV_DATA_TYPE_GPIO_VAL = 27,
    ADV_DATA_TYPE_PLSDTCT = 28,
    ADV_DATA_TYPE_GPIO_CNT = 29,
    ADV_DATA_TYPE_REG_DATA = 31
    
} adv_data_t;

typedef enum 
{
    ADV_MODE_CONTINUOUS = 0,
    ADV_MODE_EVENT
    
} adv_mode_t;

typedef enum 
{
    ADDR_PUBLIC = 0,
    ADDR_RANDOM_NON_RESOLVABLE,
    ADDR_RANDOM_RESOLVABLE,
    ADDR_RANDOM_STATIC,
    ADDR_NOT_PRESENT
    
} address_type_t;

typedef enum 
{
    ADV_CH_37_38_39 = 0,
    ADV_CH_38_39,
    ADV_CH_37_39,
    ADV_CH_39,
    ADC_CH_37_38,
    ADV_CH_38,
    ADV_CH_37
    
} adv_channel_ctl_t;

void nanobeacon_adv_data_reset ( void );

void nanobeacon_adv_tx_set ( uint32_t tx_interval, adv_channel_ctl_t ch_ctl, adv_mode_t mode );

void nanobeacon_adv_address_set ( address_type_t addr_type, uint8_t *mac_addr, 
                                  uint16_t addr_gen_interval, uint8_t key_idx );

int32_t nanobeacon_adv_add_data ( uint8_t* data_in, uint8_t length, uint8_t encrypt_en );

int32_t nanobeacon_adv_add_cnt ( uint8_t length, uint8_t big_endian, uint8_t encrypt_en );

int32_t nanobeacon_adv_add_sec_cnt ( uint8_t length, uint8_t big_endian, uint8_t encrypt_en );

int32_t nanobeacon_adv_add_100ms_cnt ( uint8_t length, uint8_t big_endian, uint8_t encrypt_en );

int32_t nanobeacon_adv_add_gpio_stat ( uint8_t encrypt_en );

int32_t nanobeacon_adv_add_vcc ( uint8_t length, uint8_t big_endian, uint8_t encrypt_en );

int32_t nanobeacon_adv_add_temp ( uint8_t length, uint8_t big_endian, uint8_t encrypt_en );

uint16_t nanobeacon_adv_data_to_raw ( uint8_t *buffer );
