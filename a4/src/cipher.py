
class FileDecoder:    

    def __init__(self,key,filename,alphabet):
        self.key=key
        self.filename=filename
        self.alphabet = alphabet
        file = open(filename,"r")
        content = file.read()
        i=1
        result="" 
        for character in content:
            index1 = alphabet.find(character)
            kindex= i%len(key)
            if (kindex==0):
                kindex=len(key)
            s = key[kindex-1] 
            index2 = alphabet.find(s)
            if (index1<index2):
                index3=index1+96-index2
            else :
                index3=index1-index2

            letter=alphabet[index3]
            result+=letter
            i+=1
    
        result = result.rstrip()
        result = result.split('\n')
        self.result=result

        string = 'departure_terminal,arrival_terminal,vessel_name,scheduled_departure_year,scheduled_departure_month,scheduled_departure_day,scheduled_departure_hour,scheduled_departure_minute,actual_departure_year,actual_departure_month,actual_departure_day,actual_departure_hour,actual_departure_minute,arrival_year,arrival_month,arrival_day,arrival_hour,arrival_minute'
        
        if string not in result:
            raise DecryptException

        for row in result:
            ele = row.split(',')
            if len(ele)!=18:
                raise DecryptException
 
    def __str__(self):
        return 'FileDecoder: FileDecoder(key='+'\''+self.key+'\''+', file=\''+self.filename+'\')'

    def __len__(self):
        entry=0
        for line in self.result:
            entry+=1
        return entry
        
    def __iter__(self):
        for ele in self.result:
            parts=ele.split(',')
            yield parts

                     
class DecryptException(Exception):
    pass
        

