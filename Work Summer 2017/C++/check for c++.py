#python script to check how well I did
import csv
import matplotlib.pyplot as plt
import sys

output = r"C:\Users\hka0211\Documents\Practice\C++\output.csv"
truth = r"C:\Users\hka0211\Documents\Practice\C++\truth.csv"

def main():    
    x_k, y_k, x_vel_k, y_vel_k = [], [], [], []
    x_t, y_t, x_vel_t, y_vel_t = [], [], [], []
    
    with open(output, newline='') as csv_file:
        reader = csv.reader(csv_file, delimiter=',')
        for row in reader:
            x_k.append(float(row[0])); y_k.append((float(row[1]))); x_vel_k.append((float(row[2]))); y_vel_k.append((float(row[3])))
    
    with open(truth, newline='') as csv_file:
        reader = csv.reader(csv_file, delimiter=',')
        for row in reader:
            x_t.append(float(row[0])); y_t.append((float(row[1]))); x_vel_t.append((float(row[2]))); y_vel_t.append((float(row[3])))
    
    pos_k_error = get_errors(list(zip(x_k, y_k)), list(zip(x_t, y_t)), True, False)
    
    plt.figure()
    plt.plot(x_t, y_t, 'b*--')
    plt.plot(x_k, y_k, 'ro--')
    plt.show()

    
def get_errors(truth, pts, position, velocity):
    dist = []
    if position:
        for i, truth_pt in enumerate(truth):    
            xdist = (truth_pt[0]-pts[i][0])**2; ydist = (truth_pt[1]-pts[i][1])**2
            dist.append((xdist+ydist)**0.5)
        
        return dist
    elif velocity:
        for i, truth_pt in enumerate(truth):    
            xdist = (truth_pt[2]-pts[i][2])**2; ydist = (truth_pt[3]-pts[i][3])**2
            dist.append((xdist+ydist)**0.5) 
        return dist        



if __name__ == "__main__":
    main()