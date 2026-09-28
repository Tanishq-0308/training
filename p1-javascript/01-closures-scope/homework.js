function createBankAccount(initialBalance) {
    let balance=initialBalance;
    // console.log(balance)
    const deposit = (amount) => {
        balance += amount;
        return balance;
    }

    const withdraw = (amount)=> {
        if (amount > balance){
            return { success: false, message: "Insufficient funds" };
        }
        balance -= amount;
        return balance;
    }

    const getBalance=()=> {
        return balance;
    }

    return {
        deposit,
        withdraw,
        getBalance
    }
}

const bankAccount = createBankAccount(2000);
const addMoney = bankAccount.deposit(3000);
const balanceAmount = bankAccount.getBalance();
console.log(balanceAmount);
