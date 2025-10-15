import random

def generate_array(n):
    return [random.randint(0, 100) for _ in range(n)]

def sortirovka(a):
    for i in range(len(a) - 1):
        if a[i] < a[i + 1]:
            return False
    return True

def bullet_sort(a):
    swaps = 0
    for i in range(len(a) - 1):
        for j in range(len(a) - i - 1):
            if a[j] < a[j + 1]:
                a[j], a[j + 1] = a[j + 1], a[j]
                swaps += 1
    return swaps

def ne_chet_number(a):
    ne_chetnyu = [i for i in range(len(a)) if a[i] % 2 == 0]
    chetnyu = [a[i] for i in ne_chetnyu]
    for i in range(len(chetnyu) - 1):
        for j in range(len(chetnyu) - i - 1):
            if chetnyu[j] > chetnyu[j + 1]:
                chetnyu[j], chetnyu[j + 1] = chetnyu[j + 1], chetnyu[j]
    for idx, val in zip(ne_chetnyu, chetnyu):
        a[idx] = val

def chet_and_nechet(a):
    chet_id = [i for i in range(0, len(a), 2)]
    nechet_id = [i for i in range(1, len(a), 2)]
    chet_vals = sorted([a[i] for i in chet_id])
    nechet_vals = sorted([a[i] for i in nechet_id], reverse=True)
    for i, v in zip(chet_id, chet_vals):
        a[i] = v
    for i, v in zip(nechet_id, nechet_vals):
        a[i] = v

def remove_duplicates(a):
    b = []
    for x in a:
        if x not in b:
            b.append(x)
    return b

def number_012(a):
    low, mid, high = 0, 0, len(a) - 1
    while mid <= high:
        if a[mid] == 1:
            a[low], a[mid] = a[mid], a[low]
            low += 1
            mid += 1
        elif a[mid] == 2:
            mid += 1
        else:
            a[mid], a[high] = a[high], a[mid]
            high -= 1
    return a

arr = generate_array(20)
print("Исходный массив:", arr)

if not sortirovka(arr):
    swap_count = bullet_sort(arr)
else:
    swap_count = 0

print("По убыванию:", arr)
print("Перестановок:", swap_count)

ne_chet_number(arr)
print("Четные элементы по возрастанию:", arr)

chet_and_nechet(arr)
print("Нечетные ↑, четные ↓:", arr)

arr = remove_duplicates(arr)
print("Без дубликатов:", arr)

arr_012 = [random.choice([0, 1, 2]) for _ in range(20)]
print("Массив 0/1/2 до:", arr_012)
print("После:", number_012(arr_012))
