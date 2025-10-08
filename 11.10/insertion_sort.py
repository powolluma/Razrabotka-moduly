import random
import time

def generate_array(n):
    return [random.randint(0, 100000) for _ in range(n)]

def insertion_sort(a):
    swaps = 0
    for i in range(1, len(a)):
        key = a[i]
        j = i - 1
        while j >= 0 and key < a[j]:
            a[j + 1] = a[j]
            swaps += 1
            j -= 1
        a[j + 1] = key
    return swaps

arr = generate_array(1000)

start = time.time()
swap_count = insertion_sort(arr.copy())
end = time.time()
elapsed = end - start

print(arr)
print("Время:", elapsed)
print("Количество перестановок:", swap_count)
