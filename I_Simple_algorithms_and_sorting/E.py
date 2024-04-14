number = int(input())
array = []
for i in range(number):
    array.append(list(map(int, input().split())))
array.sort()
result = []
previous_ind = array[0][0]
previous_jnd = array[0][1]
for i in range(1,number):
    current_ind = array[i][0]
    current_jnd = array[i][1]
    if current_ind > previous_jnd:
        result.append([previous_ind, previous_jnd])
        previous_ind, previous_jnd = current_ind, current_jnd
    else:
        previous_jnd = max(previous_jnd, current_jnd)
result.append([previous_ind, previous_jnd])
print(len(result))
for i in range(len(result)):
    print(result[i][0], result[i][1])
