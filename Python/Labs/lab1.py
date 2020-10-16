from enum import Enum
import pymysql
import csv


def print_title():
    print("#" * 100)
    print(" " * 35 + "南开大学软件学院通讯录管理系统v0.01a")
    print(" " * 44 + "添加数据请按[a]")
    print(" " * 44 + "查看数据请按[s]")
    print(" " * 44 + "删除数据请按[d]")
    print(" " * 44 + "修改数据请按[m]")
    print(" " * 86 + "返回菜单请按[q]")
    print("#" * 100)


class Data(Enum):
    NAME = 0
    QQ = 1
    TELEPHONE = 2
    EMAIL = 3


def execute_local(command, path):
    if "a" == command or "A" == command:
        create(path)
    elif "s" == command or "S" == command:
        query_all(path)
    elif "d" == command or "D" == command:
        delete(path)
    elif "m" == command or "M" == command:
        modify(path)
    elif "q" == command or "Q" == command:
        print_title()
    else:
        print("错误指令，请检查。")


def execute_sql(command, cursor):
    if "a" == command or "A" == command:
        return create_from_sql(cursor)
    elif "s" == command or "S" == command:
        return query_from_sql(cursor)
    elif "d" == command or "D" == command:
        return delete_from_sql(cursor)
    elif "m" == command or "M" == command:
        return modify_from_sql(cursor)
    elif "q" == command or "Q" == command:
        print_title()
    else:
        print("错误指令，请检查。")


def recall(cursor, number=None):
    if None is number:
        sql = "select * from contact order by id desc limit 1;"
    elif -1 == number:
        return
    else:
        sql = "select * from contact where id='" + number + "';"
    try:
        line = cursor.execute(sql)
        data = cursor.fetchall()
        if 1 != line:
            print("查询失败。")
        if 5 != len(data[0]):
            print("数据格式有误。")
        print("~" * 44 + "添加/修改数据" + "~" * 44)
        # print("{:<{}} {:<{}} {:<{}} {:<{}} {:<{}}".format("ID", 20, "Name", 20,
        #                                                   "QQ", 20, "Tel", 20,
        #                                                   "Email", 20))

        print("{:<{}}\t {:<{}} {:<{}} {:<{}}\t {:<{}}".format("ID", 18, "姓名\t", 20 - len("姓名".encode('UTF-8')) + 2,
                                                              "QQ", 20, "电话\t", 20 - len("姓名".encode('UTF-8')),
                                                              "   Email", 20, chr(12288)))
        print("{:<{}} {:<{}} {:<{}} {:<{}} {:<{}}".format(data[0][0], 20, data[0][1], 20,
                                                          data[0][2], 20, data[0][3], 20,
                                                          data[0][4], 20))
        print("~" * 100)
    except Exception as e:
        print(e)


def create(path):
    name = input("请输入姓名：")
    qq = input("请输入QQ：")
    telephone = input("请输入电话号码：")
    email = input("请输入电子邮件地址：")
    data = list(read_csv(path))
    data.append([name, qq, telephone, email])
    index = len(data) - 1
    print("~" * 44 + "添加/修改数据" + "~" * 44)
    print("{:<{}} {:<{}} {:<{}} {:<{}} {:<{}}".format("ID", 20, "Name", 20,
                                                      "QQ", 20, "Tel", 20,
                                                      "Email", 20))
    print("{:<{}} {:<{}} {:<{}} {:<{}} {:<{}}".format(str(index), 20,
                                                      data[index][0], 20, data[index][1], 20,
                                                      data[index][2], 20, data[index][3], 20, ))
    print("~" * 100)
    write_csv(data, path)


def create_from_sql(cursor):
    name = input("请输入姓名：")
    qq = input("请输入QQ：")
    telephone = input("请输入电话号码：")
    email = input("请输入电子邮件地址：")
    try:
        line = cursor.execute("insert into contact values(0, '"
                              + name + "', '" + qq + "', '"
                              + telephone + "', '" + email + "');")
        cursor.fetchall()
        if 1 == line:
            print("成功添加记录至数据库。")
        else:
            print("记录添加失败。")
    except Exception as e:
        print("记录添加失败。")
        print(e)


def modify(path):
    number = input("请输入要修改的数据序号: ")
    data = list(read_csv(path))
    try:
        if len(data) <= int(number) or 0 >= int(number):
            print("检索失败，请查看检索ID是否正确。")
            return
    except Exception:
        print("检索失败，请查看检索ID是否正确。")
        return
    name = input("请输入姓名：")
    qq = input("请输入QQ：")
    telephone = input("请输入电话号码：")
    email = input("请输入邮箱地址：")
    record = [name, qq, telephone, email]
    current = data[int(number)]
    for i in range(len(record)):
        if " " == record[i] or "" == record[i]:
            record[i] = str(current[i])
    data[int(number)] = record
    write_csv(data, path)


def modify_from_sql(cursor):
    number = input("请输入要修改的数据序号: ")
    try:
        line = cursor.execute("select * from contact where id =" + number + ";")
        current = cursor.fetchall()
        if 1 != line:
            print("检索失败，请查看检索ID是否正确。")
            return -1
        name = input("请输入姓名：")
        qq = input("请输入QQ：")
        telephone = input("请输入电话号码：")
        email = input("请输入邮箱地址：")
        record = [name, qq, telephone, email]
        for i in range(len(record)):
            if " " == record[i] or "" == record[i]:
                record[i] = str(current[0][i + 1])
        line = cursor.execute("update contact set name='" + str(record[0]) + "', qq='"
                              + str(record[1]) + "', tel='" + str(record[2]) + "', email='"
                              + str(record[3]) + "' where id='" + number + "';")
        if 1 != line:
            print("修改失败。")
        else:
            print("修改成功。")
            return number
    except Exception as e:
        print(e)
    return -1


def query_all(path):
    data = list(read_csv(path))
    title = True
    for item in range(len(data)):
        if title:
            print("~" * 44 + "通讯录数据列表" + "~" * 44)
            print("{:<{}} {:<{}} {:<{}} {:<{}} {:<{}}".format("ID", 20, "Name", 20,
                                                              "QQ", 20, "Tel", 20,
                                                              "Email", 20))
            title = False
            continue
        else:
            try:
                print("{:<{}} {:<{}} {:<{}} {:<{}} {:<{}}".format(str(item), 20,
                                                                  str(data[item][0]), 20,
                                                                  str(data[item][1]), 20,
                                                                  str(data[item][2]), 20,
                                                                  str(data[item][3]), 20))
            except Exception:
                print("查询失败。")
    print("~" * 100)


def query_from_sql(cursor):
    try:
        line = cursor.execute("select * from contact;")
        data = cursor.fetchall()
        if 1 > line:
            print("空数据集。")
        else:

            print("~" * 44 + "通讯录数据列表" + "~" * 44)
            print("{:<{}} {:<{}} {:<{}} {:<{}} {:<{}}".format("ID", 20, "Name", 20,
                                                              "QQ", 20, "Tel", 20,
                                                              "Email", 20))
            for i in data:
                if 5 != len(i):
                    print("数据存在错误。")
                    return
                print("{:<{}} {:<{}} {:<{}} {:<{}} {:<{}}".format(i[0], 20, i[1], 20,
                                                                  i[2], 20, i[3], 20,
                                                                  i[4], 20))
            print("~" * 100)
    except Exception as e:
        print("查询失败。")
        print(e)


def delete(path):
    number = input("请输入要的删除项目的ID: ")
    data = list(read_csv(path))
    try:
        if len(data) <= int(number) or 0 >= int(number):
            print("检索失败，请查看检索ID是否正确。")
            return
    except Exception:
        print("检索失败，请查看检索ID是否正确。")
        return
    del data[int(number)]
    print("删除成功。")
    write_csv(data, path)


def delete_from_sql(cursor):
    number = input("请输入要删除项目的ID: ")
    try:
        line = cursor.execute("select * from contact where id='" + number + "';")
        cursor.fetchall()
        if 1 > line:
            print("未找到，请检查索引。")
        else:
            cursor.execute("delete from contact where id='" + number + "';")
            cursor.fetchall()
            print("删除成功。")
            return number
    except Exception as e:
        print("删除失败。")
        print(e)


def start_sql():
    connect = pymysql.connect("localhost", "root", "root", "python")
    cursor = connect.cursor()
    print_title()
    while True:
        operator = input("请输入相应的命令(返回菜单请按q): ")
        item = execute_sql(operator, cursor)
        connect.commit()
        if "a" == operator or "A" == operator:
            recall(cursor)
        elif "m" == operator or "M" == operator:
            recall(cursor, item)


def read_csv(path):
    try:
        file = csv.reader(open(path))
        return file
    except Exception:
        out = open(path, 'w', newline='')
        csv_writer = csv.writer(out, dialect='excel')
        csv_writer.writerow(['Name', 'QQ', 'Tel', 'Email'])
        file = csv.reader(open(path))
        return file


def write_csv(data, path):
    out = open(path, 'w', newline='')
    csv_writer = csv.writer(out, dialect='excel')
    for item in data:
        csv_writer.writerow(item)


def start_local():
    path = "./contact.csv"
    print_title()
    while True:
        operator = input("请输入相应的命令(返回菜单请按q): ")
        execute_local(operator, path)


if "__main__" == __name__:
    boot = input("输入l/L选择本地文件方式，输入其他选择数据库方式: ")
    if "l" == boot or "L" == boot:
        start_local()
    else:
        start_sql()


# create table contact(id int not null primary key auto_increment, name varchar(100),
# qq varchar(100), tel varchar(100), email varchar(100));
