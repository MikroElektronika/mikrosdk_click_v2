//
// Created by rprzybyla on 1/12/2021.
//

#ifndef SHASTA_TEST_SHASTA_ATP_FORMAT_H
#define SHASTA_TEST_SHASTA_ATP_FORMAT_H
#define TPEN_MAX    (7)
#define TPSEL_MAX   (7)
typedef struct atp {
    volatile uint8_t tpen;
    volatile uint8_t tpsel;
} atp_t;
#endif //SHASTA_TEST_SHASTA_ATP_FORMAT_H
