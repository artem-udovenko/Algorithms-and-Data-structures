def Check(length, kolvo):
    lx = arr[0]
    for i in range(len(arr)):
        if arr[i] > lx + length:
            if kolvo == 0:
                return False
            lx = arr[i]
            kolvo -= 1
    return True


number, kolvo = map(int, input().split())
arr = list(map(int, input().split()))
arr.sort()
left = - 1
right = arr[-1] - arr[0] + 1
while right != left + 1:
    length = (left + right) // 2
    if Check(length, kolvo - 1):
        right = length
    else:
        left = length
print(right)
