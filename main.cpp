#include "display.h"
#include "transactions.h"

int main() {
    Transaction trans = { 123, DEPOSIT, "gay sex", 0.73f };
    Transaction trans2 = { 789, TRANSFER, "only fans", 0.98f };
    Transaction trans3 = { 456, WITHDRAWL, "fun times ;)", 7.6f };

    processTransaction(trans);
    processTransaction(trans2);
    processTransaction(trans3);

    return 0;
};
