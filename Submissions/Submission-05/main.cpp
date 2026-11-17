#include <chrono>
#include <fstream>
#include <iostream>
#include <ratio>
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

static bool IsAccountNumber(TBankAccount *account, void *key);

static bool IsAccountInDateRange(TBankAccount *account, void *key);

static void PrintAccount(TBankAccount *account);

static void PrintSummary(const SearchSummary &summary);

int main() {

    // true -> List owns the nodes and underlying data
    TLinkedList<TBankAccount> list(true);

    int count = 0;
    TBankAccount **accountArray = ParseAccounts("accounts.json", count, list);

    SearchSummary summary{};
    if (auto account =
            FindAccountByNumber(accountArray, count, "5999", summary)) {
        PrintAccount(account);
        PrintSummary(summary);
    }

    constexpr time_t June2024_start = 1685577600;      // 2024-06-01 00:00:00
    constexpr time_t June2024_end = 1688169599;        // 2024-06-30 23:59:59
    constexpr time_t January2024_start = 1704067200;   // 2024-01-01 00:00:00
    constexpr time_t EndFirstQuarter2024 = 1706745599; // 2024-03-31 23:59:59

    SearchSummary summary2{};
    PrintEveryAccountInDateRange(accountArray, count, June2024_start,
                                 June2024_end, summary2);

    PrintSummary(summary2);

    SearchSummary summary3{};
    if (TBankAccount *account =
            list.Find(&IsAccountNumber, (void *)"5999", summary3)) {
        PrintAccount(account);
    }
    PrintSummary(summary3);

    SearchSummary summary4{};
    if (TBankAccount *account =
            list.Find(&IsAccountNumber, (void *)"9000", summary4)) {
        PrintAccount(account);
    }
    PrintSummary(summary4);

    SearchSummary summary5{};
    time_t dateRange[2] = {June2024_start, June2024_end};
    auto subList =
        list.Every(&IsAccountInDateRange, (void *)dateRange, summary5);
    for (auto node = subList->GetAtIndex(0); node != nullptr;
         node = node->next) {
        PrintAccount(node->data);
    }
    PrintSummary(summary5);

    SearchSummary summary6{};
    PrintEveryAccountInDateRange(accountArray, count, January2024_start,
                                 EndFirstQuarter2024, summary6);
    PrintSummary(summary6);

    // Analysis: TLinkedList<T>::Find demostrates O(n) time complexity, as it
    // iterates through the list to find the matching criteria.
    // At worst case, it will traverse the entire list, resulting in linear time
    // complexity.
    //
    // The difference in flexibility between the generic Find and
    // PrintEveryAccountInDateRange is that the generic Find allows for custom
    // comparison functions to be passed in, enabling searches based on various
    // criteria. In contrast, PrintEveryAccountInDateRange is specifically
    // designed to print accounts within a date range, limiting its use to that
    // specific case.

    delete[] accountArray;
    delete subList;
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

bool IsAccountNumber(TBankAccount *account, void *key) {
    std::string_view accountNumberKey(static_cast<const char *>(key));
    return account->GetAccountNumber() == accountNumberKey;
}

bool IsAccountInDateRange(TBankAccount *account, void *key) {
    time_t *dateRange = static_cast<time_t *>(key);
    time_t fromDate = dateRange[0];
    time_t toDate = dateRange[1];
    time_t accountDate = account->GetCreationDate();
    return accountDate >= fromDate && accountDate <= toDate;
}

void PrintAccount(TBankAccount *account) {
    std::cout << "Name: " << account->GetFirstName() << " "
              << account->GetLastName()
              << ". Balance: " << account->GetBalance() << std::endl;
    std::cout << "Account Number: " << account->GetAccountNumber() << std::endl;
    std::cout << "Creation Date: "
              << FormatCreationDate(account->GetCreationDate()) << std::endl;
}

static void PrintSummary(const SearchSummary &summary) {
    std::cout << "Comparisons: " << summary.comparisons
              << ". Time spent: " << summary.timeSpentMs << " ms." << std::endl;
}