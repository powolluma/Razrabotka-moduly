import random
import time

def generate_array(n):
    return [random.randint(0, 100000) for _ in range(n)]

swaps = 0

def shaker_sort(a):
    global swaps
    left = 0
    right = len(a) - 1
    while left < right:
        for i in range(left, right):
            if a[i] > a[i + 1]:
                a[i], a[i + 1] = a[i + 1], a[i]
                swaps += 1
        right -= 1
        for i in range(right, left, -1):
            if a[i] < a[i - 1]:
                a[i], a[i - 1] = a[i - 1], a[i]
                swaps += 1
        left += 1

arr = generate_array(1000)

start = time.time()
shaker_sort(arr)
end = time.time()
elapsed = end - start

print(arr)
print("Время:", elapsed)
print("Количество перестановок:", swaps)
