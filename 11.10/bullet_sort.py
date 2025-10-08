import random
import time

def generate_array(n):
    return [random.randint(0, 100000) for _ in range(n)]

def bubble_sort(a):
    swaps = 0  
    for i in range(len(a) - 1):
        for j in range(len(a) - i - 1):
            if a[j] > a[j + 1]:
                a[j], a[j + 1] = a[j + 1], a[j]
                swaps += 1 
    return swaps  

arr = generate_array(1000)

start = time.time()
swap_count = bubble_sort(arr.copy())  
end = time.time()
elapsed = end - start

print(arr) 
print("Время: ", elapsed)
print("Количество перестановок:", swap_count)
