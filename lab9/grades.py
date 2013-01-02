import sys


fileName = sys.argv[1]
fp = open(fileName)
fp.readline() #skip first line
sum = 0 
count = 0 #number of students
gradesDic = {}
idDic = {}
for line in fp:
  print line
  arr = line.split(',')
  grade = int(arr[2])
  ID = arr[0]
  sum += grade
  count+= 1
  if grade in gradesDic:
    gradesDic[grade] += 1
    idDic[grade].append(ID) 
  else:
    gradesDic[grade] = 1
    idDic[grade] = [ID]
print "*********************************"
print "Average: " + str(float(sum) / float(count))
for g in gradesDic.keys():
  print str(g) + ": " + str(gradesDic[g]) + "   ID's:  " + str(idDic[g])
  
