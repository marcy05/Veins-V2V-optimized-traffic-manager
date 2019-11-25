import random

signal_random = []
cars_id = []

number_of_cars = int(input('How many vehicles? '))

for i in range(number_of_cars):
    cars_id.append(i+1)

for r in range(number_of_cars):
    signal_random.append(random.randint(2,4))

print(cars_id)
print(signal_random)


