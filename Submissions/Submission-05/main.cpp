#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

#include "TLinkedList.hpp"
#include "bank.hpp"

#include "stb_json.hpp"

using namespace BankSystem;

// Parses the JSON file and returns an array of TBankAccount pointers
// If list owns the nodes, it will delete the TBankAccount objects when it goes
// out of scope. Otherwise, the caller is also responsible for deleting the
// TBankAccount objects. The caller is responsible for deleting the array of
// pointers.
static TBankAccount **ParseAccounts(std::string_view file, int &outCount,
                                    TLinkedList<TBankAccount> &list);

static TBankAccount *FindAccountByNumber(TBankAccount **accountArray,
                                         int arraySize,
                                         const std::string &accountNumber,
                                         SearchSummary &summary);

static void PrintEveryAccountInDateRange(TBankAccount **accountArray,
                                         int arraySize, time_t fromDate,
                                         time_t toDate, SearchSummary &summary);

static void PrintAccount(TBankAccount *account) {
    std::cout << "Name: " << account->GetFirstName() << " "
              << account->GetLastName()
              << ". Balance: " << account->GetBalance() << std::endl;
    std::cout << "Account Number: " << account->GetAccountNumber() << std::endl;
    std::cout << "Creation Date: " << account->GetCreationDateString()
              << std::endl;
}

int main() {

    // true -> List owns the nodes and underlying data
    TLinkedList<TBankAccount> list(true);

    int count = 0;
    TBankAccount **accountArray = ParseAccounts("accounts.json", count, list);

    SearchSummary summary{};
    if (auto account =
            FindAccountByNumber(accountArray, count, "5999", summary)) {
        PrintAccount(account);
    }
    std::cout << "Comparisons: " << summary.comparisons
              << ". Time spent: " << summary.timeSpentMs << " ms." << std::endl;

    const time_t June2024 = 1685577600; // 2024-06-01 00:00:00
    const time_t July2024 = 1711929600; // 2024-07-01 00:00:00

    SearchSummary summary2{};
    PrintEveryAccountInDateRange(accountArray, count, June2024, July2024,
                                 summary2);

    std::cout << "Comparisons: " << summary2.comparisons
              << ". Time spent: " << summary2.timeSpentMs << " ms."
              << std::endl;

    delete[] accountArray;
    return 0;
}

TBankAccount **ParseAccounts(std::string_view filename, int &outCount,
                             TLinkedList<TBankAccount> &list) {
    constexpr int MAX_NAME_LEN = 50;
    std::ifstream file(filename.data());
    std::ostringstream buf;
    buf << file.rdbuf();
    std::string contents = buf.str();

    stb_json digest(contents.c_str(), contents.length());

    if (digest.HasError())
        std::cout << "ERROR: " << digest.GetError() << std::endl;

    const int count = digest.Count();
    outCount = count;

    TBankAccount **accountArray = new TBankAccount *[count];

    for (int i = 0; i < count; i++) {
        int accountType = 0;
        char firstName[MAX_NAME_LEN] = {0};
        char lastName[MAX_NAME_LEN] = {0};
        time_t dateCreated = 0;
        stb_json account = digest.MoveCursor(i);
        if (account.HasError())
            std::cout << "ERROR: " << account.GetError() << std::endl;

        accountType = account.GetInt("type");
        account.GetString("firstName", firstName, MAX_NAME_LEN);
        account.GetString("lastName", lastName, MAX_NAME_LEN);
        dateCreated = account.GetInt("dateCreated");

        TBankAccount *accountPtr =
            new TBankAccount(static_cast<EBankAccountType>(accountType),
                             firstName, lastName, dateCreated);

        list.Append(accountPtr);
        accountArray[i] = accountPtr;
    }
    return accountArray;
}

TBankAccount *FindAccountByNumber(TBankAccount **accountArray, int arraySize,
                                  const std::string &accountNumber,
                                  SearchSummary &summary) {
    TBankAccount *foundAccount = nullptr;

    std::chrono::steady_clock::time_point start =
        std::chrono::steady_clock::now();

    for (int i = 0; i < arraySize; i++) {
        summary.comparisons++;
        if (accountArray[i]->GetAccountNumber() == accountNumber) {
            foundAccount = accountArray[i];
            break;
        }
    }
    auto elapsed = std::chrono::steady_clock::now() - start;
    summary.timeSpentMs =
        std::chrono::duration<double, std::milli>(elapsed).count();

    return foundAccount;
}

void PrintEveryAccountInDateRange(TBankAccount **accountArray, int arraySize,
                                  time_t fromDate, time_t toDate,
                                  SearchSummary &summary) {
    std::chrono::steady_clock::time_point start =
        std::chrono::steady_clock::now();
    for (int i = 0; i < arraySize; i++) {
        summary.comparisons++;
        time_t dateCreated = accountArray[i]->GetCreationDate();
        if (dateCreated >= fromDate && dateCreated <= toDate) {
            PrintAccount(accountArray[i]);
        }
    }
    auto elapsed = std::chrono::steady_clock::now() - start;
    summary.timeSpentMs =
        std::chrono::duration<double, std::milli>(elapsed).count();
}