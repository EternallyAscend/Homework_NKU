# Exe 4 ------------------------------------------------------------------------------ Exe 4
import pymysql as mysql
import numpy as np
import pandas as pd
import xlrd
import xlwt
import openpyxl

name="Exe4"
position="../"+name+"/"
writer = pd.ExcelWriter(position+name+'.xlsx')

def writeExcel(writer,data,coloums,sheetName):
    if type(data)==type(False):
        output=pd.DataFrame(np.zeros(1,int))
        output.columns=["Empty Set"]
        output.to_excel(excel_writer=writer, sheet_name=sheetName,index=False)
        return
    outputExcelDataFrame = pd.DataFrame(data)
    outputExcelDataFrame.columns = coloums
    outputExcelDataFrame.to_excel(excel_writer=writer, sheet_name=sheetName, float_format='%.5f', index=False)

def completeExcel(writer):
    writer.save()
    writer.close()

def singleSQL(sql,cursor):
    cursor.execute(sql)
    data=cursor.fetchall()
    if len(data)==0:
        return False
    return data

connection=mysql.connect(host='localhost',user='root',password='root',database='dbsclab2018',charset='utf8')
cursor=connection.cursor()

sql="select dept_name,count(*) from student group by dept_name order by dept_name desc;"
writeExcel(writer,singleSQL(sql,cursor),["dept_name","count"],'1.1')

sql="select course_id,semester,year,substring(title,1,5) as title from (select *,count(*) as count from takes group by course_id) as a natural join course where count>=310;"
writeExcel(writer,singleSQL(sql,cursor),["course_id","semester","year","subtitle"],'1.2')

sql="select distinct ID,name from takes natural join student where course_id in (select course_id from teacher,(select ID from instructor where name='Dale') as a where teacher.ID=a.ID) ;"
writeExcel(writer,singleSQL(sql,cursor),["ID","name"],'1.3')

sql="select ID,dept_name from takes natural join student where ID in (select distinct takes.ID from takes left join (select distinct ID from takes where not find_in_set('A',grade) and trim(grade)!='') as a on (takes.ID=a.ID) where a.ID is null) order by ID;"
writeExcel(writer,singleSQL(sql,cursor),["ID","title","grade"],'1.4')

sql="select avg(budget) from department;"
subData=np.array((1,2),float)
str=singleSQL(sql,cursor)[0].__str__()[8:-2][2:-2]
subData[0]=float(str)
sql="set @rowindex:=-1;"
singleSQL(sql,cursor)
sql="select avg(temp.budget) as median from (select @rowindex:=@rowindex+1 as rowindex,department.budget as budget from department order by budget) as temp where temp.rowindex in (floor(@rowindex>>1),ceil(@rowindex>>1));"
str=singleSQL(sql,cursor)[0].__str__()[8:-2][2:-2]
subData[1]=float(str)
writeExcel(writer,subData,["mean and median"],'1.5')

sql="select dept_name,count(*) from instructor group by dept_name order by dept_name desc;"
writeExcel(writer,singleSQL(sql,cursor),["dept_name","count"],'2.1')

sql="select course_id,semester,year,substring(title,1,5) as title from section natural join course where course_id in (select course_id from(select count(*) as count,course_id from teacher group by course_id) as a where count>1);"
writeExcel(writer,singleSQL(sql,cursor),["course_id","semester","year","title"],'2.2')

sql="select count(*) from student where dept_name in (select dept_name from instructor where ID=14365);"
writeExcel(writer,singleSQL(sql,cursor),["amount"],'2.3')

sql="select ID,dept_name from takes natural join student where ID in (select distinct takes.ID from takes left join (select distinct ID from takes where not find_in_set('A',grade) and trim(grade)!='') as a on (takes.ID=a.ID) where a.ID is null) order by ID;"
writeExcel(writer,singleSQL(sql,cursor),["ID","dept_name"],'2.4')

sql="select avg(salary) from instructor;"
subData=np.array((1,2),float)
str=singleSQL(sql,cursor)[0].__str__()[8:-2][2:-2]
subData[0]=float(str)
sql="set @rowindex:=-1;"
singleSQL(sql,cursor)
sql="select avg(temp.salary) as median from (select @rowindex:=@rowindex+1 as rowindex,instructor.salary as salary from instructor order by salary) as temp where temp.rowindex in (floor(@rowindex>>1),ceil(@rowindex>>1));"
str=singleSQL(sql,cursor)[0].__str__()[8:-2][2:-2]
subData[1]=float(str)
writeExcel(writer,subData,["mean and median"],'2.5')

completeExcel(writer)
# Exe 4 ------------------------------------------------------------------------------ Exe 4
