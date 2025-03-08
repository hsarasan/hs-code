class CircularBuffer:
    
    def __init__(self,N):
        self.N=N
        self.write_index=0
        self.log=[None]*N
        
        
    def record(self,id):
        self.log[self.write_index]=id
        self.write_index=(self.write_index+1)%self.N
    
    def get_last(self,prev):
        read_index=(self.write_index-prev)%self.N
        return self.log[read_index]
    

log= CircularBuffer(5)  # Store last 5 orders
log.record(101)
log.record(102)
log.record(103)
log.record(104)
log.record(105)
print(log.get_last(1))  # Output: 105
print(log.get_last(2))  # Output: 104
log.record(106)
print(log.get_last(5))  # Output: 102 