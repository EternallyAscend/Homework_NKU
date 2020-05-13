def copyDirInLinux(connection,cursor,originPath,newPath,size=0
    namePath=originPath[:-1]
    name=originPath[namePath.rfind('/')+1:-1]
    print(name)
    originCode=getParentDirCodeInLinux(cursor,originPath)
    insertDirInLinux(connection,cursor,newPath,name)
    cursor.execute("select name,size from file where parent="+str(originCode)+";")
    dataSet=cursor.fetchall()
    for Name,size in dataSet:
        if size!=0:
            insertFileInLinux(connection,cursor,newPath+name+"/",Name,size)
        else:
            copyDirInLinux(connection,cursor,originPath+Name+"/",newPath+name+"/")
                   
def copyFileInLinux(connection,cursor,originPath,newPath):
    originCode=getParentDirCodeInLinux(cursor,originPath[:originPath.rfind('/')+1])
    newCode=getParentDirCodeInLinux(cursor,newPath)
    name=originPath[originPath.rfind('/')+1:]
    cursor.execute("select name,size from file where parent="+str(originCode)+" and name='"+name+"';")
    info=cursor.fetchall()
    for Name,Size in info:
        insertFileInLinux(connection,cursor,newPath,Name,Size)
        
def moveFileOrDir(connection,cursor,name,originPath,newPath):
    originCode=getParentDirCodeInLinux(cursor,originPath)
    newCode=getParentDirCodeInLinux(cursor,newPath)
    cursor.execute("update file set parent="+str(newCode)+" where name='"+str(name)+"' and parent="+str(originCode)+";")
    cursor.fetchall()
    connection.commit()


def getMostFiles(cursor,path,max):
    print(path[path[:-1].rfind('/')+1:-1])
    sigmoid=getParentDirCodeInLinux(cursor,path)
    if sigmoid!=0:
        showDirMax(cursor,sigmoid,path,max)
    else:
        return
    
def showDirMax(cursor,dirCode,path,max):
    sql="select name, code, size from file where parent='"+str(dirCode)+"' order by name;"
    lines=cursor.execute(sql)
    result=cursor.fetchall()
    lines=0
    for name,code,size in result:
        if size!=0:
            lines+=1
        else:
            temp=showDirMax(cursor,code,path+name+"/",max)
            if temp<=max:
                print(path+name," Contains Files: ",temp)
            lines+=temp
    return lines



def deleteFileOrDirInLinux(connection,cursor,path,name):
	parentCode=getParentDirCodeInLinux(cursor,path)
    cursor.execute("delete from file where name='"+str(name)+"' and parent="+str(parentCode)+";")
    cursor.fetchall()
    connection.commit()
    
    





dirRoot="D:\\databaseLab\\Local\\ExeX\\sqlite-autoconf-3230100\\"
rootDir='/home/linux/Project/Database/sqlite-autoconf-323100'
rootDir=dirRoot
print(dirRoot)
tempRoot='/sqlite-autoconf'
for (dirName, dirs, files) in os.walk(rootDir):
    for dir in dirs:
        print(dir)
    for fileName in files:
        filePath = os.path.join(dirName, fileName)
        path=filePath[25:].replace('\\','/')
        path=path[:path.rfind('/')]+"/"
        tryGetDirCodeInLinuxOrCreateNewDir(connection,cursor,path)
        insertFileInLinux(connection,cursor,path,fileName,os.path.getsize(filePath))
        parentFileName=os.path.basename(dirName)
        print(fileName,':',parentFileName,':',os.path.getsize(filePath))
print('exit')

def tree(cursor,path):
    print(path[path[:-1].rfind('/')+1:-1])
    sigmoid=getParentDirCodeInLinux(cursor,path)
    if sigmoid!=0:
        fdn=[0,0]
        endList=[]
        showDir(cursor,sigmoid,0,endList,fdn)
        print("Total Dirs: "+str(fdn[1])+" Total Files: "+str(fdn[0]))
    else:
        return
        
def getParentDirCodeInLinux(cursor,dir):
    subDirHead=0
    if dir[subDirHead]=='/':
        subDirHead=subDirHead+1
    subDirTail=subDirHead
    cursor.execute("select code from file where name='/';")
    parentDir=cursor.fetchall()[0][0]
    currentDir=''
    while subDirTail!=len(dir):
        subDirTail=subDirTail+1
        if subDirTail!=len(dir) and dir[subDirTail]!='/':
            pass
        else:
            currentDir=dir[subDirHead:subDirTail]
            cursor.execute("select code from file where name='"+str(currentDir)+"' and parent='"+str(parentDir)+"';")
            parentDir=cursor.fetchall()[0][0]
            currentDir=parentDir
            subDirHead=subDirTail+1
            subDirTail=subDirTail+1
    return currentDir


def tryGetDirCodeInLinuxOrCreateNewDir(connection,cursor,dir):
    subDirHead = 0
    if dir[subDirHead] == '/':
        subDirHead = subDirHead + 1
    subDirTail = subDirHead
    cursor.execute("select code from file where name='/';")
    parentDir = cursor.fetchall()[0][0]
    currentDir = ''
    print(len(dir))
    while subDirTail != len(dir):
        subDirTail = subDirTail + 1
        if subDirTail != len(dir) and dir[subDirTail] != '/':
            pass
        else:
            currentDir = dir[subDirHead:subDirTail]
            lines=cursor.execute("select code from file where name='" + str(currentDir) + "' and parent='" + str(parentDir) + "';")
            if lines==0:
                cursor.execute("insert into file values(0,'"+str(currentDir)+"',"+str(parentDir)+",0);")
                cursor.fetchall()
                connection.commit()
                cursor.execute("select code from file where name='" + str(currentDir) + "' and parent='" + str(parentDir) + "';")
            parentDir = cursor.fetchall()[0][0]
            currentDir = parentDir
            subDirHead = subDirTail + 1
            subDirTail = subDirTail + 1
    return currentDir

def insertDirInLinux(connection,cursor,path,dir):
    parentCode=getParentDirCodeInLinux(cursor,path)
    if len(parentCode)==0:
        cursor.execute("select code from file where name='/';")
        parentCode=cursor.fetchall()[0][0]
    print("insert into file values(0,'"+str(dir)+"',"+str(parentCode)+",0);")
    cursor.execute("insert into file values(0,'"+str(dir)+"',"+str(parentCode)+",0);")
    cursor.fetchall()
    connection.commit()

def insertFileInLinux(connection,cursor,path,file,size):
    parentCode=getParentDirCodeInLinux(cursor,path)
    if len(str(parentCode))==0:
        cursor.execute("select code from file where name='/';")
        parentCode=cursor.fetchall()[0][0]
    cursor.execute("insert into file values(0,'"+str(file)+"',"+str(parentCode)+","+str(size)+");")
    cursor.fetchall()
    connection.commit()
    
def showDir(cursor,dirCode,now,layer,fdn):
    sql="select name, code, size from file where parent='"+str(dirCode)+"' order by name;"
    lines=cursor.execute(sql)
    result=cursor.fetchall()
    space="    "
    backspace=""
    for i in range(0,len(layer)):
        if layer[i]==0:
            backspace=backspace+space
        else:
            backspace=backspace+"|   "
    backspace+="|----"
    layer.append(1)
    counter=0
    for name,code,size in result:
        counter+=1
        if counter==len(result):
            layer[now]=0
        if size!=0:
            print(backspace,name,size)
            fdn[0]+=1
        else:
            print(backspace,name)
            showDir(cursor,code,now+1,layer,fdn)
            fdn[1]+=1
    layer.pop()
    return lines



print("0 Tree ------------------------------------------------")
tree(cursor,"/sqlite-autoconf-3230100/")
getMostFiles(cursor,"/sqlite-autoconf-3230100/",2)
print("1 Copy ------------------------------------------------")
# 1 Copy
copyFileInLinux(connection,cursor,"/sqlite-autoconf-3230100/tea/Makefile.in","/sqlite-autoconf-3230100/tea/doc/")
tree(cursor,"/sqlite-autoconf-3230100/")
print("2 Move ------------------------------------------------")
# 2 Move
moveFileOrDir(connection,cursor,"doc","/sqlite-autoconf-3230100/tea/","/sqlite-autoconf-3230100/tea/tclconfig/")
moveFileOrDir(connection,cursor,"win","/sqlite-autoconf-3230100/tea/","/sqlite-autoconf-3230100/tea/tclconfig/")
tree(cursor,"/sqlite-autoconf-3230100/")
print("3 GeMa ------------------------------------------------")
# 3 Get Max
getMostFiles(cursor,"/sqlite-autoconf-3230100/",2)
print("4 Dele ------------------------------------------------")
# 4 Delete
deleteFileOrDirInLinux(connection,cursor,"/sqlite-autoconf-3230100/","tea")
tree(cursor,"/sqlite-autoconf-3230100/")
