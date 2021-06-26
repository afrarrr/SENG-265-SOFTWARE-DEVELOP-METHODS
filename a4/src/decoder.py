"""
Provided for you is the encryption alphabet used to encrypt the provided files.
This inclues: a-z, A-Z, 0-9, punctuation like .(); (not the same as in a1-a3), space and newline
"""
from cipher import FileDecoder
from cipher import DecryptException
import string
import re
file_decoder=''
alphabet = string.ascii_lowercase + string.ascii_uppercase + string.digits + string.punctuation + " \n"



def main():    
    check()
   
 
def check():
    global file_decoder
    filename = input("Enter name of file: \n")
    while(filename!='q'):
        try:
            file_handle = open(filename,"r")
            break
        except FileNotFoundError:
            filename = input("Enter name of file: \n")

    if filename == 'q':
        exit()

    password = input("Enter password: \n")

    while(password!='q'):
        if not (re.match(r'^[a-zA-Z0-9]*[@#$&\!\*\-\_\.]{1}[a-zA-Z0-9]*[@#$&\!\*\-\_\.]{1}[a-zA-Z0-9]*$',password) and re.match ('^.{6,8}$',password) and re.search(r'[A-Z]',password) and re.search(r'[0-9].*[0-9]',password)):
            password = input("Enter password:\n")
        else:
            try:
                file_decoder=FileDecoder(password,filename,alphabet)
                calculate()             
            except DecryptException as e :
                print("The password is not valid")
                password = input ("Enter password:\n")
    if password =='q':
        exit()               

def calculate():
    output = {}
    monthlist = []
    month = ['01','02','03','04','05','06','07','08','09','10','11','12']
    month1 = ['1','2','3','4','5','6','7','8','9','10','11','12'] 
    cap = ['Jan','Feb','Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Dec']
    for row in file_decoder:
        if row[4] in month:
            monthlist.append(row[4])
        if row[4] in month1:
            index1= month1.index(row[4])
            monthlist.append(month[index1])
    monthlist = list(set(monthlist))
    monthlist.sort()
    for ele in monthlist:
        index=month.index(ele)
        m = str(cap[index])
        ave = "{:.2f}".format(average_delay(ele))
        output[m]=str(ave)
    print('RESULTS')
    print(file_decoder)
    print('Entries: '+str(len(file_decoder)))
    for key,value in output.items():
        print('    Average delay for '+ key +': '+ value )
    print('END')
    exit() 

def average_delay(month):
    total=0
    number=0
    for row in file_decoder:
        if row[4]!='scheduled_departure_month':
            if int(row[4])==int(month):
                number+=1
                total+= int(row[11])*60+int(row[12])-int(row[7])-int(row[6])*60
                            
    return total/number    
            
        
if __name__ =='__main__':
    main()                  
