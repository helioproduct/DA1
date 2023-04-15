import random
import string

lines_amount = random.randint(1, 1000)

file = open("test2.txt", "w")

MX_KEY = 2 ** 64 - 1
MX_VALUE_LEN = 2048

for _ in range(lines_amount):
    file.write(str(random.randint(0, MX_KEY)))
    file.write(" ")

    for _ in range(random.randint(0, 2048)):
        file.write(random.choice(string.ascii_lowercase))

    file.write("\n")

file.close()


