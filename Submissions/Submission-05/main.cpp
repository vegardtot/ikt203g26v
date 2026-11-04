#include <iostream>

#include "bank.hpp"
#include "TLinkedList.hpp"

using namespace BankSystem;

int main() {


    auto *account1 = new TBankAccount(
        EBankAccountType::Loan,
        "Ole",
        "Nordmann"
    );



    auto node1 = new TNode<TBankAccount>(account1);

    TLinkedList<TBankAccount> list(true);

    list.Append(node1);

    std::cout << list.GetAtIndex(0)->data->GetBalance() << std::endl;

    return 0;
}
