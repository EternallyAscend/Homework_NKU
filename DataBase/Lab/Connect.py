# Localhost:3306 root

# Python3.6.6
# import pymysql as mysql
# database=mysql.connect("localhost","root","root","mysql")
# cursor=database.cursor()
#
# cursor.execute("select version();")
# data=cursor.fetchone()
# print("Database Version: %s" % data)
#
# cursor.execute("select * from mysql.user;")
# data=cursor.fetchall()
# for i in data:
#     print(i)
# cursor.execute("select host, user from mysql.user;")
# data=cursor.fetchall()
# for i in data:
#     print(i)
# cursor.execute("desc mysql.user;")
# data=cursor.fetchall()
# print(data)


# Exe 3 ------------------------------------------------------------------------------ Exe 3

import pymysql as mysql
import random
connection=mysql.connect(host='localhost',user='root',password='root',database='dbsclab2018',charset='utf8')
cursor=connection.cursor()

# Create the new table for department in MySQL database "dbsclab2018".
sql = 'create table departmentNK(' \
      'department_name varchar(20),' \
      'building varchar(15),' \
      'budget numeric(12,2) check (budget>0),' \
      'teacher_quantity tinyint unsigned check(teacher_quantity>0),' \
      'student_quantity smallint unsigned check(student_quantity>=0),' \
      'primary key (department_name)' \
      ');'
cursor.execute(sql)

# Insert 100 pieces of department information into MySQL database "dbsclab2018".

for i in range(0,100):
    sql="insert into departmentNK values" \
        " ('Department"+str(i)+"','Building"+\
        str(i)+"','"+str(float(random.randint(1,1000000))/10)+\
        "','"+str(random.randint(1,100))+"','"+str(random.randint(1,1000))+"');"
    cursor.execute(sql)
    connection.commit()
    # print(sql)

# Create the new table for student in MySQL database "dbsclab2018".

sql = 'create table studentSC(' \
      'student_ID bigint(12),' \
      'student_Name varchar(20) not null,' \
      'student_Grade smallint(4),' \
      'student_Age tinyint unsigned check(student_age>0),' \
      'student_Department_name varchar(20) not null,' \
      'student_GPA numeric(6,3) check(student_gpa>=0),' \
      'student_Credits tinyint unsigned check(student_Credits>=0),' \
      'primary key (student_ID)' \
      ');'
# print(sql)
cursor.execute(sql)

# Insert 1000 pieces of students information into MySQL database "dbsclab2018".
for i in range(0,1000):
    sql="insert into studentSC values ('"+str(20181030001+i)+"','Name"+str(i+1)+"','"+\
        str(2018)+"','"+str(random.randint(18,20))+"','Computer学院','"+\
        str(random.randint(60000,100000)/1000)+"','"+str(random.randint(20,100))+"');"
    cursor.execute(sql)
    connection.commit()
    # print(sql)

sql="select * from studentsc where student_id=(student_id>>1)<<1;"
cursor.execute(sql)
result=cursor.fetchall()
for i in result:
    print(i)
cursor.close()
connection.close()

# Exe 3 ------------------------------------------------------------------------------ Exe 3



