import random
import time

def generate_array(n):
    return [random.randint(0, 100000) for _ in range(n)]

def selection_sort(a):
    swaps = 0  
    for i in range(len(a)):
        min_index = i
        for j in range(i + 1, len(a)):
            if a[j] < a[min_index]:
                min_index = j
        if min_index != i:
            a[i], a[min_index] = a[min_index], a[i]
            swaps += 1  
    return swaps  
arr = generate_array(1000)

start = time.time()
swap_count = selection_sort(arr.copy())  
end = time.time()
elapsed = end - start

print(arr)  
print("Время: ", elapsed)
print("Количество перестановок:", swap_count)

