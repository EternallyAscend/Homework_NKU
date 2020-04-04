import pymysql as mysql
import numpy as np
import pandas as pd
import xlrd
import xlwt
import openpyxl
import sys
import re

name = "Exe5"
position = "../" + name + "/"
writer = pd.ExcelWriter(position + name + '.xlsx')

def disposalWithRank(sql,cursor,increase=True,sortColoum="",groupIncrease=True,groupColoum="",rankSortIncrease=True,rankSortColoum="",rankGroupIncrease=True,rankGroupColoum=""):
    data=SQL_Query(sql,cursor)
    if type(data)==type(False):
        return False
    else:
        data=list(data)
        data=dropNoneType(data)
    if sortColoum!="":
        coloumIndex=getColoumNumber(sql,sortColoum)
        if type(coloumIndex)==type(False):
            return False
        else:
            data=mergeSort(0,len(data),data,coloumIndex,increase)
    if groupColoum!="":
        groupIndex=getColoumNumber(sql,groupColoum)
        if type(groupIndex)==type(False):
            return False
        else:
            data=groupBy(0,len(data),data,groupIndex,groupIncrease)
    data=rank(sql,0,len(data),data,rankSortColoum,rankSortIncrease,rankGroupColoum,rankGroupIncrease)
    return data


def disposal(sql,cursor,increase=True,sortColoum="",groupIncrease=True,groupColoum=""):
    data=SQL_Query(sql,cursor)
    if type(data)==type(False):
        return False
    if sortColoum=="" and groupColoum=="":
        return data
    else:
        data=list(data)
        if sortColoum!="":
            sortColoumIndex=getColoumNumber(sql,sortColoum)
            # print(sortColoumIndex)
            if type(sortColoumIndex)==type(False):
                return False
            data=mergeSort(0,len(data),data,sortColoumIndex,increase)
        if groupColoum!="":
            groupColoumIndex=getColoumNumber(sql,groupColoum)
            # print(groupColoumIndex)
            if type(groupColoumIndex)==type(False):
                return False
            data=groupBy(0,len(data),data,groupColoumIndex,groupIncrease)
        return data

def disposalList(sql,cursor,increase=True,sortColoum=[],groupIncrease=True,groupColoum=[]):
    data=SQL_Query(sql,cursor)
    sortLength=len(sortColoum)
    groupLength=len(groupColoum)
    data=list(data)
    if sortLength>0:
        sortIndex=list()
        for i in sortColoum:
            sortIndex.append(getColoumNumber(sql,i))
        if type(increase)==type(True):
            for i in range(0,sortLength):
                data=mergeSort(0,len(data),data,sortIndex[sortLength-1-i],increase)
        else:
            if len(increase)!=sortLength:
                return False
            for i in range(0,sortLength):
                data=mergeSort(0,len(data),data,sortIndex[sortLength-1-i],increase[sortLength-1-i])

    if groupLength>0:
        groupIndex=list()
        for i in groupColoum:
            groupIndex.append(getColoumNumber(sql,i))
        if type(groupIndex)==type(True):
            for i in range(0,groupLength):
                data=groupBy(0,len(data),data,groupIndex[groupLength-1-i],groupIncrease)
        else:
            if len(groupIncrease)!=groupLength:
                return False
            for i in range(0,groupLength):
                data=groupBy(0,len(data),data,groupIndex[groupLength-1-i],groupIncrease[groupLength-1-i])
    return data
    pass

# def rank(sql,cursor,increase=True,sortColoum=[],groupIncrease=True,groupColoum=[],rankSortIncrease=True,rankSortColoum=[],rankgroupIncrease=True,rankgroupColoum=[]):
#     ranks=list()
#
#     pass

# def tryDimension(data):
#     try:
#         length=len(data)
#         if length>0:
#             return True
#         else:
#             return False
#     except:
#         return False
def dropNoneType(data):
    try:
        length=len(data)
        data=list(data)
    except:
        print("single")
        return data
    nanList=list()
    try:
        length=len(data[0])
    except:
        print("line")
        for i in range(0,len(data)):
            if data[len(data)-i-1] is None:
                del data[len(data)-i-1]
        return data
    try:
        for i in range(0,len(data)):
            data[i]=list(data[i])
            for j in range(0,len(data[i])):
                if data[i][j] is None:
                    nanList.append(i)
    except:
        return data
    for i in range(0,len(nanList)):
        print("drop",data[len(nanList)-1-i])
        del data[nanList[len(nanList)-1-i]]
    return data

def rank(sql,start,end,data,coloum,increase=True,groupColoum="",groupIncrease=True):
    data=list(data)
    group=True
    if groupColoum=="":
        group=False
    sortIndex=getColoumNumber(sql,coloum)
    if group:
        groupIndex=getColoumNumber(sql,groupColoum)
    else:
        groupIndex=groupColoum
    index=rankAddIndex(start,end,data,sortIndex,groupIndex)
    index=mergeSort(0,len(index),index,2,increase)
    index,limit=groupWithColoumPosition(0,len(index),index,3,groupIncrease)
    temp=0
    cache=0
    now=0
    # for i in limit:
    #     print(i)
    for i in range(0,len(index)):
        index[i]=list(index[i])
        # print(i,temp,limit[cache])
        if temp!=limit[cache][1]:
            temp+=1
            if now==0:
                now+=1
            else:
                if index[i][2]!=index[i-1][2]:
                    now=temp
            index[i][1]=(now)
        else:
            cache+=1
            temp=1
            now=1
            index[i][1]=(now)
    index=mergeSort(0,len(index),index,0)
    for i in range(0,len(data)):
        data[i]=list(data[i])
        data[i].append(index[i][1])
    return data

def rankAddIndex(start,end,data,coloum,groupColoum=""):
    group=True
    if groupColoum=="":
        group=False
    index=list()
    if group:
        for i in range(start,end):
            index.append((i,0,data[i][coloum],data[i][groupColoum]))
    else:
        for i in range(start,end):
            index.append((i,0,data[i][coloum],"-1"))
    return index

def getColoumNumber(sql,Name):
    sql=sql[7:]
    index=sql.lower().find("from")
    if index==-1:
        return False
    else:
        sql=sql[:index]
    index=sql.find(Name)
    if index==-1:
        return False
    sql=sql[:index]
    index=0
    for i in sql:
        if i==",":
            index+=1
    return index

def getAllColoumNameWithNumber(sql):
    pass

def groupBy(start, end, data, coloum, increase=True):
    data = list(data)
    if coloum > len(data) or coloum < 0:
        return False
    position = list()
    for i in range(start, end):
        index = -1
        for j in range(0, len(position)):
            try:
                position[j].index(data[i][coloum])
                index = j
            except ValueError:
                pass
        if index != -1:
            position[index][1] += 1
        else:
            position.append([data[i][coloum], 1, 0])
    position = mergeSort(0, len(position), position, 0, increase)
    for i in range(0, len(position) - 1):
        position[i + 1][2] = position[i][1] + position[i][2]
    for i in range(0, len(position)):
        break
    temp = data.copy()
    for i in range(start, end):
        pos = -1
        for j in range(0, len(position)):
            try:
                pos = position[j].index(data[i][coloum])
                pos = j
            except ValueError:
                pass
        if pos != -1:
            temp[position[pos][2]] = data[i]
            position[pos][2] += 1
    return temp

def grouByList(start,end,data,coloum,increase=True):
    coloum=list(coloum)
    length=len(coloum)
    if type(increase)==type(True):
        for i in range(0,length):
            # index=getColoumNumber(coloum[length-1-i])
            data=groupBy(start,end,data,coloum[length-1-i],increase)
    else:
        if len(increase)!=length:
            return False
        for i in range(0,length):
            # index=getColoumNumber(coloum[length-1-i])
            data=groupBy(start,end,data,coloum[length-1-i],increase[length-1-i])
    return data

def groupWithColoumPosition(start, end, data, coloum, increase=True):
    data = list(data)
    if coloum > len(data) or coloum < 0:
        return False
    position = list()
    for i in range(start, end):
        index = -1
        for j in range(0, len(position)):
            try:
                position[j].index(data[i][coloum])
                index = j
            except ValueError:
                pass
        if index != -1:
            position[index][1] += 1
        else:
            position.append([data[i][coloum], 1, 0])
    position = mergeSort(0, len(position), position, 0, increase)
    for i in range(0, len(position) - 1):
        position[i + 1][2] = position[i][1] + position[i][2]
    for i in range(0, len(position)):
        break
    temp = data.copy()
    for i in range(start, end):
        pos = -1
        for j in range(0, len(position)):
            try:
                pos = position[j].index(data[i][coloum])
                pos = j
            except ValueError:
                pass
        if pos != -1:
            temp[position[pos][2]] = data[i]
            position[pos][2] += 1
    return temp,position

def bubbleSort(start, end, data, coloum, increase=True):
    data = list(data)
    if coloum > len(data) or coloum < 0:
        return False
    if increase:
        for i in range(start, end):
            for j in range(start, end - 1):
                if data[j][coloum] > data[j + 1][coloum]:
                    temp = data[j]
                    data[j] = data[j + 1]
                    data[j + 1] = temp
    else:
        for i in range(start, end):
            for j in range(start, end - 1):
                if data[j][coloum] < data[j + 1][coloum]:
                    temp = data[j]
                    data[j] = data[j + 1]
                    data[j + 1] = temp
    return data


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
                # print(data[leftCounter],data[rightCounter])
                min = data[leftCounter]
                if data[leftCounter][coloum] > data[rightCounter][coloum]:
                    min = data[rightCounter]
                    rightCounter += 1
                else:
                    leftCounter += 1
                # print("Min",min)
                temp.append(min)
        else:
            while (leftCounter < middle and rightCounter < end):
                # print(data[leftCounter],data[rightCounter])
                max = data[leftCounter]
                if data[leftCounter][coloum] < data[rightCounter][coloum]:
                    max = data[rightCounter]
                    rightCounter += 1
                else:
                    leftCounter += 1
                # print("max",max)
                temp.append(max)
        if leftCounter<middle:
            while leftCounter<middle:
                temp.append(data[leftCounter])
                leftCounter+=1
        if rightCounter<end:
            while rightCounter<end:
                temp.append(data[rightCounter])
                rightCounter+=1
        # print(temp)
        for i in range(start,end):
            # print(i,temp[i-start])
            data[i]=temp[i-start]
    return data

def mergeSortList(start,end,data,coloum,increase=True):
    coloum=list(coloum)
    length=len(coloum)
    if type(increase)==type(True):
        for i in range(0,length):
            data=mergeSort(start,end,data,coloum[length-1-i],increase)
    else:
        if len(increase)!=length:
            return False
        for i in range(0,length):
            data=mergeSort(start,end,data,coloum[length-1-i],increase[length-1-i])
    return data

#     sys.setrecursionlimit(20000)

def SQL_Query(sql, cursor):
    cursor.execute(sql)
    data = cursor.fetchall()
    if len(data) == 0:
        return False
    return data


def SQL_Insert(sql,cursor):

    return True


def writeExcel(writer, data, coloums, sheetName):
    if type(data) == type(False):
        output = pd.DataFrame(np.zeros(1, int))
        output.columns = ["Empty Set"]
        output.to_excel(excel_writer=writer, sheet_name=sheetName, index=False)
        return
    outputExcelDataFrame = pd.DataFrame(data)
    outputExcelDataFrame.columns = coloums
    outputExcelDataFrame.to_excel(excel_writer=writer, sheet_name=sheetName, float_format='%.5f', index=False)


def completeExcel(writer):
    writer.save()
    writer.close()


def singleSQL(sql, cursor):
    cursor.execute(sql)
    data = cursor.fetchall()
    if len(data) == 0:
        return False
    return data


connection = mysql.connect(host='localhost', user='root', password='root', database='dbsclab2018', charset='utf8')
cursor = connection.cursor()
# sql="select name,dept_name,salary from instructor;"
# print(disposalWithRank(sql,cursor,sortColoum="salary",groupColoum="dept_name",rankSortIncrease=False,rankSortColoum="salary",rankGroupColoum="dept_name"))

sql="select ID,name,dept_name,tot_cred from student;"
print(disposalWithRank(sql,cursor,sortColoum="tot_cred",increase=False,groupColoum="dept_name",rankSortColoum="tot_cred",rankSortIncrease=False,rankGroupColoum="dept_name"))
connection.close()
