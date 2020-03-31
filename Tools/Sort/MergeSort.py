def mergeSort(start, end, data, coloum, increase=True):
    data=list(data)
    if start == end - 1:
        return data
    else:
        middle = int(int(start + end) / 2)
        data=mergeSort(start, middle, data, coloum, increase)
        data=mergeSort(middle, end, data, coloum, increase)
        leftCounter = start
        rightCounter = middle
        temp = list()
        if increase:
            while (leftCounter < middle and rightCounter < end):
                print(data[leftCounter],data[rightCounter])
                min = data[leftCounter]
                if data[leftCounter][coloum] > data[rightCounter][coloum]:
                    min = data[rightCounter]
                    rightCounter += 1
                else:
                    leftCounter += 1
                print("Min",min)
                temp.append(min)
        else:
            while (leftCounter < middle and rightCounter < end):
                print(data[leftCounter],data[rightCounter])
                max = data[leftCounter]
                if data[leftCounter][coloum] < data[rightCounter][coloum]:
                    max = data[rightCounter]
                    rightCounter += 1
                else:
                    leftCounter += 1
                print("max",max)
                temp.append(max)
        if leftCounter<middle:
            while leftCounter<middle:
                temp.append(data[leftCounter])
                leftCounter+=1
        if rightCounter<end:
            while rightCounter<end:
                temp.append(data[rightCounter])
                rightCounter+=1
        print(temp)
        for i in range(start,end):
            print(i,temp[i-start])
            data[i]=temp[i-start]
    return data
