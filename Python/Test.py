
#lesson 1 variables
firstinfo = 'str, float, int, list\n'
mystring = 'Hello' #string
myfloat = 3.5 #float
myint = 10 #int
mylist = [] #declaring a list
mylist.append(1) #adding to a list
mylist.append(2)
mylist.append(3)
print firstinfo
print mystring 
print myfloat
print myint

#lesson 2 lists
print mylist[1] #list access is the same as arrays more or less

for x in mylist: #for loop to print a list DONT FORGET THE FUCKING COLON
	print x

secondinfo = "\nnumbers list, names list, second_name variable\n"
numbers = []
names = []
numbers.append(1)
numbers.append(2)
numbers.append(3)
names.append('Hello')
names.append('World')
second_name = names[1] #outputs as [...], [...]
print secondinfo
print numbers
print names
print second_name

#lesson 3 operators
thirdinfo ="\n1 + 1, 1.75 + 1.75, 2 + 3.5, 11 % 3,\n2 squared, 2 cubed , hello+world, hello*10, even list + odd list\n"
iSum = 1 + 1
fSum = 1.75 + 1.75
mod = 11 % 3
squared = 2**2
cubed = 2**3
helloworld = "hello"+"world"
hello = "hello"
evens = [2,4,6,8]
odds = [1,3,5,7]
allnums = evens + odds
print thirdinfo
print iSum 
print fSum 
print iSum + fSum
print mod
print squared
print cubed
print helloworld
print hello * 10
print allnums

#lesson 4 string formatting






raw_input("Press any key to continue...")


