import random
import string

# количество строк в тесте

n = int(input('lines amount: '))

# Множество слов для тестирования
words = ['word'+str(i) for i in range(n)]

# Операции: '+', '-' или 'поиск'
operations = ['+', '-', 'search']

for _ in range(n):
    # выберите случайное слово из списка
    word = random.choice(words)
    
    # выберите случайную операцию
    operation = random.choice(operations)
    
    if operation == '+':
        # выберите случайное число от 0 до 264 - 1
        number = random.randint(0, 2**64 - 1)
        print(f'+ {word} {number}')
    elif operation == '-':
        print(f'- {word}')
    else: # операция поиска
        print(word)
