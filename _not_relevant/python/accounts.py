class InsufficientFunds(Exception):
    def __init__(self, amount):
        super().__init__(f'Insufficient funds: Balance => {amount}')
        
class Account:
    def __init__(self, balance):
        self.balance = balance
        
    def withdraw(self, amount):
        if self.balance < amount:
            raise InsufficientFunds(self.balance)
        self.balance -= amount
        return self.balance
    
acc=Account(100)
try:
    print(acc.withdraw(200))
except InsufficientFunds as e:
    print(e)
finally:
    print("Transaction completed")
    
acc=Account(200)
try:
    print(acc.withdraw(100))        
except InsufficientFunds as e:
    print(e)    
finally:
    print("Transaction completed")
    
