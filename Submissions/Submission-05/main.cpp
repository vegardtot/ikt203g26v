#include <fstream>
#include <iostream>
#include <sstream>

#include "TLinkedList.hpp"
#include "bank.hpp"

#include "stb_json.hpp"

using namespace BankSystem;

TBankAccount *FindAccountByNumber(TBankAccount **accountArray, int arraySize,
                                  const std::string &accountNumber,
                                  SearchSummary &summary);

void PrintEveryAccountInDateRange(TBankAccount **accountArray, int arraySize,
                                  time_t fromDate, time_t toDate,
                                  SearchSummary &summary);

int main() {

    // true -> List owns the nodes and underlying data
    TLinkedList<TBankAccount> list(true);

    std::ifstream file("accounts.json");
    std::ostringstream buf;
    buf << file.rdbuf();
    std::string contents = buf.str();

    stb_json digest(contents.c_str(), contents.length());
    const int count = digest.Count();

    TBankAccount **accountArray = new TBankAccount*[count];

    for (int i = 0; i < count; i++) {
        int accountType = 0;
        char firstName[50] = {0};
        char lastName[50] = {0};
        time_t dateCreated = 0;
        digest.MoveCursor(i);

        accountType = digest.GetInt("type");
        digest.GetString("firstName", firstName, 50);
        digest.GetString("lastName", lastName, 50);
        dateCreated = digest.GetInt("dateCreated");

        TBankAccount *account = new TBankAccount(static_cast<EBankAccountType>(accountType),
                                     firstName, lastName, dateCreated);

        list.Append(account);
        accountArray[i] = account;
    }

    delete[] accountArray;
    return 0;
}
