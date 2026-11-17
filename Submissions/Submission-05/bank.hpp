#pragma once

#include <ctime>
#include <random>
#include <string>
#include <string_view>

namespace BankSystem {
enum class EBankAccountType : unsigned int {
    Checking,
    Debit,
    Savings,
    Credit,
    Pension,
    Loan,
};

inline double RandomInitialBalance(EBankAccountType type) {

    static std::mt19937 rng(time(nullptr));

    switch (type) {

    case EBankAccountType::Checking:
        [[fallthrough]];

    case EBankAccountType::Debit:
        [[fallthrough]];

    case EBankAccountType::Savings:
        [[fallthrough]];

    case EBankAccountType::Pension:
        return std::uniform_real_distribution<double>(0, 1000)(rng);

    case EBankAccountType::Credit:
        return std::uniform_real_distribution<double>(-1000, 0)(rng);

    case EBankAccountType::Loan:
        return std::uniform_real_distribution<double>(-50000, -25000)(rng);

    default:
        throw std::runtime_error("Not implemented");
    }
}

class TBankAccount {
  public:
    TBankAccount(EBankAccountType type, const std::string_view firstName,
                 const std::string_view lastName, time_t dateCreated = time(nullptr))
        : m_accountNumber(std::to_string(s_accountNumberIncrement++)),
          m_type(type), m_ownerFirstName(firstName), m_ownerLastName(lastName),
          m_creationTimstamp(dateCreated),
          m_balance(RandomInitialBalance(type)) {}

    double GetBalance() const { return m_balance; }
    std::string_view GetFirstName() const { return m_ownerFirstName; }
    std::string_view GetLastName() const { return m_ownerLastName; }
    std::string_view GetAccountNumber() const { return m_accountNumber; }
    time_t GetCreationDate() const { return m_creationTimstamp; }

  private:
    std::string m_accountNumber;
    EBankAccountType m_type;
    std::string m_ownerFirstName;
    std::string m_ownerLastName;
    time_t m_creationTimstamp;
    double m_balance;

    inline static unsigned int s_accountNumberIncrement = 0;
};

// A helper function to convert a time_t timestamp to a human-readable string
// representation.
inline std::string FormatCreationDate(time_t timestamp) {
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S",
             localtime(&timestamp));
    return std::string(buffer);
}

} // namespace BankSystem
