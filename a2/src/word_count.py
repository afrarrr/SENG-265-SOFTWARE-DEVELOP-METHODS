#!/bin/env python3

import sys
import re

new_dict={}


def main():
    new_dict.clear()
    sortflag=0
    printflag=0 
    if len(sys.argv)<3:
        print("program: missing \'--infile <filename> [--sort] [--print-words]\'\n")
        return
    if "--infile" not in sys.argv:
        print("missing infile\n") 
        return
    for i in range(len(sys.argv)):
        if sys.argv[i]=="--infile":
            if i+1 < len(sys.argv) :
                read_file(sys.argv[i+1])
            else:
                print ("missing file name\n")
                return 
        if sys.argv[i]== "--sort":
            sortflag=1
        if sys.argv[i]=="--print-words": 
            printflag=1
    if printflag==1 :
        print_c()
    elif sortflag==1:
        print_b()
    else:
        print_a()

def read_file(filename):
    try:
        file_handle = open (filename,"r")
    except FileNotFoundError:
        print("file not found\n")
        return new_dict
    
    for line in file_handle:
        line = line.rstrip()
        words = re.split('[\s,.;()]+', line)
        for word in words:
            if word != "": 
                if len(word) in new_dict:                
                    new_dict[len(word)].append(word)
                    
                else:
                    new_dict[len(word)]=[word]
    
def print_a():
    for key in sorted(new_dict): # Source: https://www.saltycrane.com/blog/2007/09/how-to-sort-python-dictionary-by-keys/ 
        print("Count[{:02d}]={:02d};".format(key,len(new_dict[key])))
      
    
def print_b():
    if bool(new_dict)==False: #bool() check the dictionary is empty or not 
        print("Median word length: 0.0")
        return;
    dict3= sorted(new_dict.keys()) #sort word length in order to calculate the median  
    if len(dict3)%2==0:
        index = len(dict3)//2
        length1=dict3[index]
        length2=dict3[index-1]
        median= (length1+length2)/2
    else:
        index = len(dict3)//2
        median = dict3[index]
    dict2= sorted(new_dict, key=lambda k:(-len(new_dict[k]),k))#Source: https://stackoverflow.com/questions/50029736/python-sorting-dictionary-by-length-of-values-and-alphabetically
    for key in dict2:
        print("Count[{:02d}]={:02d};".format(key,len(new_dict[key])))
         
    print("Median word length: {:.1f}".format(median))

def print_c():
    dict4=sorted(new_dict, key=lambda k:(-len(new_dict[k]),k))
    for key in dict4:
        without_duplicates=[]# contains word without duplicates
        for element in new_dict[key]:
            if element not in without_duplicates:
                without_duplicates.append(element)
        print("Count[{:02d}]={:02d};".format(key,len(new_dict[key])),end='')
        print(" (words: ",end='')
        without_duplicates.sort()
        length=len(without_duplicates)
        i=0
        if length==1:# only one word
            print ('\"'+without_duplicates[0]+'\"'+")")
        else:     
            while i<length-2:
                print('\"'+ without_duplicates[i]+'\"'+', ', end='')
                i += 1
            print('\"'+without_duplicates[i]+'\"'+ " and " + '\"'+without_duplicates[i+1]+'\"'+")")

#Do not change this
if __name__ == "__main__":
    main()

    
