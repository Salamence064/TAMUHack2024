#pragma once

#include <stdint.h>
#include <stdio.h>

// todo temp value for now
float accounts[3] = {3.47f, 9.25f, 0.31f};


// * ====================
// * Transaction Types
// * ====================

enum TransType {
    DEPOSIT,
    WITHDRAWL,
    TRANSFER
};

typedef struct {
    uint32_t accID; // The unique ID for the account associated with this transaction (doubles as the index for this demo).
    TransType type; // The type of transaction that occurred.
    char* name; // The merchant information of the transaction.
    float amount; // The amount of money handled in this transaction.
} Transaction;


// * ===========================
// * Transactional Functions
// * ===========================

// todo update for when I add file pointer shit
/**
 * @brief Process and log a parsed transaction.
 * 
 * @param trans The data parsed from the received transaction.
 */
static inline void processTransaction(const Transaction trans) {
    switch(trans.type) {
        case DEPOSIT: { // deposit the specified amount
            accounts[trans.accID] += trans.amount;
            // todo add thing to log
            break;
        }

        case WITHDRAWL: { // withdraw the specified amount
            accounts[trans.accID] -= trans.amount;
            // todo add thing to log
            break;
        }

        case TRANSFER: { // transfer the specified amount
            accounts[trans.accID] -= trans.amount;
            // todo add thing to log
            break;
        }

        default: { printf("Unrecognized transaction type '%d.'", trans.type); break; }
    }
};

// todo these guys are for parsing
// static inline Transaction receiveTransaction(void);
// static inline Transaction sendTransaction(void);
