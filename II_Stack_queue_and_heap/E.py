def Merge(arr):
    if len(arr) == 1:
        return arr
    arr1 = Merge(arr[: len(arr) // 2]) + [[2 * 10 ** 9, -1]]
    arr2 = Merge(arr[len(arr) // 2:]) + [[2 * 10 ** 9, -1]]
    ind = 0
    jnd = 0
    arr = []
    while ind < len(arr1) - 1 or jnd < len(arr2) - 1:
        if arr2[jnd][0] >= arr1[ind][0]:
            arr.append(arr1[ind])
            inversions[arr1[ind][1]] += jnd
            ind += 1
        else:
            arr.append(arr2[jnd])
            jnd += 1
    return arr


number = int(input())
array = list(map(int, input().split()))
array = [[array[i], i] for i in range(number)]
inversions = [0] * number
Merge(array)
for result in inversions:
    print(result, end=' ')
