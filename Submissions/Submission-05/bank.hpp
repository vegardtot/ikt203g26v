#pragma once

#include <ctime>
#include <random>
#include <string>

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
    TBankAccount(EBankAccountType type, const std::string &firstName,
                 const std::string &lastName, time_t dateCreated = time(nullptr))
        : m_accountNumber(std::to_string(s_accountNumberIncrement++)),
          m_type(type), m_ownerFirstName(firstName), m_ownerLastName(lastName),
          m_creationTimstamp(dateCreated),
          m_balance(RandomInitialBalance(type)) {}

    double GetBalance() const { return m_balance; }

  private:
    std::string m_accountNumber;
    EBankAccountType m_type;
    std::string m_ownerFirstName;
    std::string m_ownerLastName;
    time_t m_creationTimstamp;
    double m_balance;

    inline static unsigned int s_accountNumberIncrement = 0;
};

} // namespace BankSystem
