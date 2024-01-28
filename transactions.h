#pragma once

#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>


// * ====================
// * Transaction Types
// * ====================

enum TransType {
    DEPOSIT,
    WITHDRAWL,
    TRANSFER
};

typedef struct {
    uint32_t accID; // The unique ID for the account associated with this transaction.
    TransType type; // The type of transaction that occurred.
    const char* name; // The merchant information of the transaction.
    float amount; // The amount of money handled in this transaction.
} Transaction;


// * ===========================
// * Transactional Functions
// * ===========================

// todo come back and ensure inputs are valid
// todo also force round to 2 decimal places

/**
 * @brief Process and log a parsed transaction.
 * 
 * @param trans The data parsed from the received transaction.
 */
static inline void processTransaction(const Transaction trans) {
    switch(trans.type) {
        case DEPOSIT: {
            // deposit the specified amount
            std::ifstream f("accounts.txt", std::ios::in);
            std::string line;
            std::vector<std::string> lines;

            bool flag = 1;

            // grab the data
            while (getline(f, line)) {
                if (flag && !line.rfind(std::to_string(trans.accID))) {
                    size_t i = line.find(' ') + 1;
                    line = line.substr(0, i) + std::to_string(trans.amount + std::stof(line.substr(i, line.find('\n') - i)));
                    flag = 0;
                }

                lines.push_back(line);
            }

            f.close();

            // rewrite the data
            std::ofstream out("accounts.txt", std::ios::out | std::ios::trunc);
            for (size_t i = 0; i < lines.size(); ++i) { out << lines[i] << "\n"; }
            out.close();

            // log the data
            FILE* fptr;
            fptr = fopen("log.txt", "a");
            fprintf(fptr, "Account %u depositted $%f for %s.\n", trans.accID, trans.amount, trans.name);
            fclose(fptr);

            break;
        }

        case WITHDRAWL: {
            // withdraw the specified amount
            std::ifstream f("accounts.txt", std::ios::in);
            std::string line;
            std::vector<std::string> lines;

            bool flag = 1;

            // grab the data
            while (getline(f, line)) {
                if (flag && !line.rfind(std::to_string(trans.accID))) {
                    size_t i = line.find(' ') + 1;
                    line = line.substr(0, i) + std::to_string(std::stof(line.substr(i, line.find('\n') - i)) - trans.amount);
                    flag = 0;
                }

                lines.push_back(line);
            }

            f.close();

            // rewrite the data
            std::ofstream out("accounts.txt", std::ios::out | std::ios::trunc);
            for (size_t i = 0; i < lines.size(); ++i) { out << lines[i] << "\n"; }
            out.close();

            // log the data
            FILE* fptr;
            fptr = fopen("log.txt", "a");
            fprintf(fptr, "Account %u withdrew $%f to merchant account.\n", trans.accID, trans.amount);
            fclose(fptr);

            break;
        }

        case TRANSFER: {
            // transfer the specified amount
            std::ifstream f("accounts.txt", std::ios::in);
            std::string line;
            std::vector<std::string> lines;

            bool flag = 1;

            // grab the data
            while (getline(f, line)) {
                if (flag && !line.rfind(std::to_string(trans.accID))) {
                    size_t i = line.find(' ') + 1;
                    line = line.substr(0, i) + std::to_string(std::stof(line.substr(i, line.find('\n') - i)) - trans.amount);
                    flag = 0;
                }

                lines.push_back(line);
            }

            f.close();

            // rewrite the data
            std::ofstream out("accounts.txt", std::ios::out | std::ios::trunc);
            for (size_t i = 0; i < lines.size(); ++i) { out << lines[i] << "\n"; }
            out.close();

            // log the data
            FILE* fptr;
            fptr = fopen("log.txt", "a");
            fprintf(fptr, "Account %u transferred $%f to savings.\n", trans.accID, trans.amount);
            fclose(fptr);
            
            break;
        }

        default: { printf("Unrecognized transaction type '%d.'", trans.type); break; }
    }
};

// todo these guys are for parsing
// static inline Transaction receiveTransaction(void);
// static inline Transaction sendTransaction(void);
