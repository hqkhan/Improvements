#MBP
#random couple of frames of data
#grid of 0-255
import matplotlib.pyplot as plt
import numpy as np
import sys
import random

def create_detections(frame_1_dets, frame_2_dets, max_dets, max_size):
    num_unique_frame = 0
    while num_unique_frame < max_dets:
        frame_1_dets = fill_list(frame_1_dets, max_dets-num_unique_frame, max_size) 
        frame_1_dets = list(set(frame_1_dets))
        num_unique_frame = len(frame_1_dets)
    
    num_unique_frame = 0
    while num_unique_frame < max_dets:
        frame_2_dets = fill_list(frame_2_dets, max_dets-num_unique_frame, max_size) 
        frame_2_dets = list(set(frame_2_dets))
        num_unique_frame = len(frame_2_dets)
    
    return frame_1_dets, frame_2_dets
    
def fill_list(array_to_fill, how_many, max_size):
    for k in range(how_many):
        array_to_fill.append((random.randint(0, max_size), random.randint(0, max_size)))
    
    return array_to_fill


def perform_comparisons(frame_1_dets, frame_2_dets, num_blocks_hori, size_of_block):
    total_num_operations = 0
    for y in range(int(num_blocks_hori)):
        for x in range(int(num_blocks_hori)):
            relevant_tracks_num = look_for_tracks(x, y, frame_1_dets, size_of_block)
            relevant_detections_num = find_adjacent_detections(x, y, size_of_block, num_blocks_hori, frame_2_dets)
           # print(relevant_detections_num, relevant_tracks_num)
            total_num_operations+=(relevant_tracks_num*relevant_detections_num)
    return total_num_operations

#RELEVANT TRACKS ARE GOOD AND DETECTION NUM SEEM GOOD AS WELL CHECK TOTAL NUM OF OPERATIONS
def look_for_tracks(x, y, frame_1_dets, size_of_block):
    x_min = x*size_of_block; x_max = (x+1)*size_of_block -1
    y_min = y*size_of_block; y_max = (y+1)*size_of_block -1 
    relevant_tracks = [k for i, k in enumerate(frame_1_dets) if k[0] >= x_min and k[0] <= x_max and k[1] >= y_min and k[1] <= y_max] 
    return len(relevant_tracks)
 
def find_adjacent_detections(x, y, size_of_block, num_blocks, frame_2_dets):
    if y == 0 and x == 0: #bottom left
        return len([k for k in frame_2_dets if k[0] >= 0 and k[0] <= 2*size_of_block and k[1] >= 0 and k[1] <= 2*size_of_block])
    elif y == 0 and x > 0 and x < num_blocks-1: #bottom row but not bottom right
        return len([k for k in frame_2_dets if k[0] >= (x-1)*size_of_block and k[0] <= (x+2)*size_of_block and k[1] >= 0 and k[1] <= 2*size_of_block])
    elif y == 0 and x == num_blocks-1: #bottom right
        return len([k for k in frame_2_dets if k[0] >= (x-1)*size_of_block and k[0] <= (x+1)*size_of_block -1 and k[1] >= 0 and k[1] <= 2*size_of_block])
    elif y > 0 and y < num_blocks-1 and x == 0: #left wall
        return len([k for k in frame_2_dets if k[0] >= 0 and k[0] <= 2*size_of_block and k[1] >= (y-1)*size_of_block and k[1] <= (y+2)*size_of_block])
    elif y > 0 and y < num_blocks-1 and x > 0 and x < num_blocks-1: #middle but not right wall
        return len([k for k in frame_2_dets if k[0] >= (x-1)*size_of_block and k[0] <= (x+2)*size_of_block and k[1] >= (y-1)*size_of_block and k[1] <= (y+2)*size_of_block])
    elif y > 0 and y < num_blocks-1 and x == num_blocks-1: #right wall but not top
        return len([k for k in frame_2_dets if k[0] >= (x-1)*size_of_block and k[0] <= (x+1)*size_of_block and k[1] >= (y-1)*size_of_block and k[1] <= (y+2)*size_of_block])
    elif y == num_blocks-1 and x == 0: #top left
        return len([k for k in frame_2_dets if k[0] >= 0 and k[0] <= 2*size_of_block and k[1] >= (y-1)*size_of_block and k[1] <= (y+1)*size_of_block])
    elif y == num_blocks-1 and x > 0 and x < num_blocks-1: #top middle but not right corner
        return len([k for k in frame_2_dets if k[0] >= (x-1)*size_of_block and k[0] <= (x+2)*size_of_block and k[1] >= (y-1)*size_of_block and k[1] <= (y+1)*size_of_block])
    elif y == num_blocks-1 and x == num_blocks-1: #top right
        return len([k for k in frame_2_dets if k[0] >= (x-1)*size_of_block and k[0] <= (x+1)*size_of_block and k[1] >= (y-1)*size_of_block and k[1] <= (y+1)*size_of_block])
    else:
        print("I shouldn't be here")
        
def main():
    #arrays to hold detections
    random.seed(4)
    frame_1_dets = []; frame_2_dets = []; num_of_diff = []
    min_size = 0; max_size=256-1 #size of G
    size_of_block = [128, 64, 32, 16, 8, 4]; max_dets=[500, 1000, 1500, 2000];  num_blocks_hori = [(max_size+1)/k for k in size_of_block] 
    mec = ['red', 'black', 'purple', 'green']; ls = [':', '-', '-.', ':']
    markers = ['x', '+', 'o', '^']
    
    plt.figure()
    
   # """
    
    for k in range(len(max_dets)):
        create_detections(frame_1_dets, frame_2_dets, max_dets[k], max_size)
        for i in range(len(size_of_block)):
            total_num_operations_output = perform_comparisons(frame_1_dets, frame_2_dets, num_blocks_hori[i], size_of_block[i])
            num_of_diff.append(total_num_operations_output)
        #    print((size_of_block[i], total_num_operations))
        plt.semilogy(size_of_block, num_of_diff, ls=ls[k], c=mec[k], marker = markers[k], mec = mec[k], markersize = 10.0, label='%d Detections'%max_dets[k])
        print(list(reversed(num_of_diff)))
        del num_of_diff[:]; del frame_1_dets[:]; del frame_2_dets[:]
    
    
    plt.legend(bbox_to_anchor=(0.95, 0.3), loc=1, borderaxespad=0.)    
    plt.xlabel('Cell Size'); plt.ylabel('# of operations'); plt.title('Comparison of cell size VS # operations')
    plt.show()
    
   # """
    
    #individual testing
    """
    cur_num=0
    frame_1_dets, frame_2_dets = create_detections(frame_1_dets, frame_2_dets, max_dets[1], max_size)
    total_num_operations = perform_comparisons(frame_1_dets, frame_2_dets, num_blocks_hori[cur_num], size_of_block[cur_num])
    print(total_num_operations)
    major_ticks = np.arange(min_size, max_size+size_of_block[cur_num], size_of_block[cur_num])
    plt.plot([k[0] for k in frame_1_dets], [k[1] for k in frame_1_dets], 'o', color='blue')
    plt.plot([k[0] for k in frame_2_dets], [k[1] for k in frame_2_dets], 'x', color='red')
    plt.xticks(major_ticks); plt.yticks(major_ticks)
    plt.grid(which='major', alpha=0.3)
    plt.xlim(min_size, max_size+10); plt.ylim(min_size, max_size+10)
    """
    
if __name__=="__main__":
    main()