import random
import time

def generate_array(n):
    return [random.randint(0, 100000) for _ in range(n)]

swaps = 0

def merge_sort(a):
    global swaps
    if len(a) > 1:
        mid = len(a)//2
        left = a[:mid]
        right = a[mid:]
        merge_sort(left)
        merge_sort(right)

        i = j = k = 0
        while i < len(left) and j < len(right):
            swaps += 1
            if left[i] < right[j]:
                a[k] = left[i]
                i += 1
            else:
                a[k] = right[j]
                j += 1
            k += 1

        while i < len(left):
            a[k] = left[i]
            i += 1
            k += 1
            swaps += 1

        while j < len(right):
            a[k] = right[j]
            j += 1
            k += 1
            swaps += 1

arr = generate_array(1000)

start = time.time()
merge_sort(arr)
end = time.time()
elapsed = end - start

print(arr)
print("Время:", elapsed,)
print("Количество перестановок:", swaps)
