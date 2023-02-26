import random

num_citizens = 10000
citizens = []
for i in range(num_citizens):
    citizen = {
        "name": "Citizen " + str(i),
        "age": random.randint(18, 65),
        "income": random.randint(1000, 100000),
        "properties": [],
        "loan": 0
    }
    citizens.append(citizen)

properties = [
    {"address": "123 Main St", "owner": None, "price": 100000, "tax": 0.01},
    {"address": "456 Elm St", "owner": None, "price": 200000, "tax": 0.01},
    {"address": "789 Oak Ave", "owner": None, "price": 300000, "tax": 0.01},
]

loan_interest_rate = 0.05

def buy_property(property, buyer):
    property["owner"] = buyer
    buyer["properties"].append(property)
    return f"{buyer['name']} has bought {property['address']} for {property['price']}."

def sell_property(property, seller, buyer, price):
    property["owner"] = buyer
    property["price"] = price
    seller["properties"].remove(property)
    buyer["properties"].append(property)
    return f"{seller['name']} has sold {property['address']} to {buyer['name']} for {price}."

def take_loan(citizen, amount):
    citizen["loan"] += amount
    return f"{citizen['name']} has taken out a loan for {amount}."

def pay_loan(citizen, amount):
    citizen["loan"] -= amount
    return f"{citizen['name']} has paid off {amount} of their loan."

def calculate_loan_interest(citizen):
    interest = citizen["loan"] * loan_interest_rate
    citizen["loan"] += interest
    return f"{citizen['name']} has to pay {interest} in loan interest."

def calculate_property_tax(property):
    tax = property["price"] * property["tax"]
    property["tax_due"] = tax
    return f"{property['address']} has to pay {tax} in property taxes."
