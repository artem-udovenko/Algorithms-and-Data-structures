def Merge(arr):
    if len(arr) == 1:
        return arr
    global inversions
    arr1 = Merge(arr[: len(arr) // 2])
    arr2 = Merge(arr[len(arr) // 2:])
    ind = len(arr1) - 1
    jnd = len(arr2) - 1
    arr = []
    while ind > -1 and jnd > -1:
        if arr2[jnd] >= arr1[ind]:
            arr.append(arr2[jnd])
            jnd -= 1
        else:
            inversions += jnd + 1
            arr.append(arr1[ind])
            ind -= 1
    while ind > -1:
        arr.append(arr1[ind])
        ind -= 1
    while jnd > -1:
        arr.append(arr2[jnd])
        jnd -= 1
    return arr[::-1]


number = int(input())
array = list(map(int, input().split()))
inversions = 0
Merge(array)
print(inversions)