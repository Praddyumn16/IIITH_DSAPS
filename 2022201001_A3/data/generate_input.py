'''
    RUNNING INSTRUCTIONS:
    $ python3 generate_input.py <seed_value> <unsorted_file_name> <number_of_values> <no_of_digits>

    PARAMETER DESCRIPTION:
    <seed_value> : It is an integer value that dictates the random number generation. For some fixed seed value, the sequence of random numbers generated will always be same.
    <unsorted_file_name> : This is the filename that you would like to give to the unsorted file that is being generated.
    <number_of_values> : This denotes the number of values that need to be written into the generated file.
    <no_of_digits> : This parameter sets the max number of digits in the values generated by Random Number Generator.

    EXAMPLE:
    $ python3 generate_input.py 69420 input.txt 100000000 10
    
    This will generate file named "input.txt" which has 100000000 numbers with each having maximum of 10 digits. This file will be around 1GB in size. 
    You can play around with the values to generate different files.
'''
from random import seed, randint
from math import ceil
import sys
import time

n_values = 10_000_000
n_digits = 4
default_seed = 69420
BUFFER_SIZE = 100_000
out_fname = "unsorted_file.txt"

if __name__ == '__main__':
    try:
        default_seed = int(sys.argv[1])
    except:
        pass

    try:
        out_fname = sys.argv[2]
    except:
        pass
    
    try:
        n_values = int(sys.argv[3])
    except:
        pass

    try:
        n_digits = int(sys.argv[4])
    except:
        pass

    seed(default_seed)
    start_range = 1#10**(n_digits-1)
    end_range = 10**n_digits

    start_time = time.time()

    o_file = open(out_fname, "w")

    out_count = ceil(n_values / BUFFER_SIZE) 
    written_count = 0 
    for o_loop in range(out_count):
        if o_loop != out_count-1:
            buffer = [str(randint(start_range, end_range)) for _ in range(BUFFER_SIZE)]
            written_count += len(buffer)
            o_file.write(" ".join(buffer) + " ")
        else:
            remaining = n_values % BUFFER_SIZE
            if remaining == 0:
                remaining = BUFFER_SIZE
            buffer = [str(randint(start_range, end_range)) for _ in range(remaining)]
            written_count += len(buffer)
            o_file.write(" ".join(buffer))
            
    o_file.close()
    end_time = time.time()
    print("Number written : ", written_count)
    print("Time taken : ", end_time-start_time)
