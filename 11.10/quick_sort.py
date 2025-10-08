import random
import time

def generate_array(n):
    return [random.randint(0, 100000) for _ in range(n)]

swaps = 0

def quick_sort(a):
    global swaps
    if len(a) <= 1:
        return a
    pivot = a[len(a)//2]
    left = [x for x in a if x < pivot]
    middle = [x for x in a if x == pivot]
    right = [x for x in a if x > pivot]
    swaps += len(a)
    return quick_sort(left) + middle + quick_sort(right)

arr = generate_array(1000)

start = time.time()
arr = quick_sort(arr)
end = time.time()
elapsed = end - start

print(arr)
print("Время:", elapsed)
print("Количество перестановок:", swaps)
