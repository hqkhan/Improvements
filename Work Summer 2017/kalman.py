# Kalman filter & smoothing
import numpy as np
import sys
import random
import matplotlib.pyplot as plt
import scipy

def Kalman_Filter(time, delta_t, t_max, pos, q, R):
    x = np.array([[0.], [0.1]])
    std_pos = 1
    std_velocity = 0.3
    Q = q*np.array([[(delta_t**4)/4 , (delta_t**3)/3] ,[(delta_t**3)/3, (delta_t**2)]])
    H = np.array([[1, 0]])
    cov_x = np.array([[std_pos**2, 0], [0, std_velocity**2]]) # the p matrix
    F = np.array([[1, delta_t], [0, 1]]) #prediction matrix; delta_t*velocity
    
    x_kalman = []
    error_y = []
    covariance_matrices = []; cov_pred = []
    x_new_smooth = []
    x_pos_val = [] ; x_pred = []
    error_kalman = []
    error_smooth = []
    x_measured = []
    
    print("Starting Kalman Filter")
    loop_count=0
    for t in time: 
        x_pred_val, cov_pred_val = Kalman_predict(x, F, cov_x, Q) #predict
        kalman_gain = Kalman_gain(cov_pred_val, H, R) #gain calculation
        x_new, cov_new, x_measured_val = Kalman_update(x_pred_val, kalman_gain, pos[loop_count], H, cov_pred_val, Q, F) #update
        
        cov_pred.append(cov_pred_val)
        x_measured.append(x_measured_val)
        x_pred.append(x_pred_val)
        x_kalman.append(x_new[0])
        x_pos_val.append(x_new)
        error_y.append(np.sqrt(cov_new[0,0])) #saving every pt's standard deviation
        #print("At time: " + str(t) + " ; Real Position: " + str(pos[loop_count]) + " ; Position: " + str(x_new[0]) + " ; Error: " + str((np.sqrt((x_new[0]-pos[loop_count])**2))))
        error_kalman.append(np.sqrt((x_new[0]-pos[loop_count])**2))
        loop_count+=1
        covariance_matrices.append(cov_x)
        cov_x = cov_new 
        x = x_new
    
    #smoothing
    print("Starting Kalman Strieber's")
    x_new_smooth.append(x[0]) #appending last position 
    error_smooth.append(np.sqrt((x[0]-pos[-1])**2)) #appending error of last pt
    old_smooth_val = x
    old_cov = cov_x
    loop_count=len(time)
    for t in range(loop_count-2, 0, -1):     
        C = np.dot(covariance_matrices[t], np.dot(np.transpose(F), np.linalg.inv(cov_pred[t+1])))
        x_new_smooth_val = np.add(x_pos_val[t], np.dot(C, np.subtract(old_smooth_val, x_pred[t+1])))
        old_smooth_val = x_new_smooth_val
        error_smooth.append(np.sqrt((x_new_smooth_val[0]-pos[t])**2))
        x_new_smooth.append(x_new_smooth_val[0])
        cov_new_smooth = np.add(covariance_matrices[t], np.dot(C, np.dot(np.subtract(old_cov, cov_pred[t+1]), np.transpose(C)))) 
        old_cov = cov_new_smooth
    
    error_smooth.append(np.sqrt((x_kalman[0]-pos[0])**2))
    x_new_smooth.append(x_kalman[0])
    
    return x_kalman, error_y, x_new_smooth, error_smooth, error_kalman, x_measured

def Kalman_predict(x, F, cov_x, Q): #prediction step
    x_new = np.dot(F, x)
    
    cov_new = np.add(np.dot(F, np.dot(cov_x, np.transpose(F))), Q)
    return x_new, cov_new

def Kalman_update(x_new, kalman_gain, pos_sensor, H, cov_new, Q, F): #update step
    x_measured_val = np.add(np.dot(F, np.array([pos_sensor, 0])), np.dot(scipy.linalg.sqrtm(Q), np.array([np.random.normal(0, 1),np.random.normal(0, 1)])))
    x_new = np.add(x_new, np.dot(kalman_gain, np.subtract(x_measured_val[0], np.dot(H, x_new))))
    cov_new = np.subtract(cov_new, np.dot(kalman_gain, np.dot(H, cov_new)))
    return x_new, cov_new, x_measured_val[0]

def Kalman_gain(cov_new, H, R): #calculate Kalman gain
    kalman_gain = np.dot(cov_new, np.transpose(H))
    kalman_gain = np.dot(kalman_gain, np.linalg.inv(np.add(np.dot(H, np.dot(cov_new, np.transpose(H))), R)))
    return kalman_gain
    
def random_walk(p, t_max, time): # no moving down only up
    pos = []
    cur_pos=0
    
    for t in time:
        test = random.uniform(0,1)
        if (test > 1-p): #we move
           cur_pos+=1
           pos.append(cur_pos)
        elif (test >1-p-0.2): #make big jump
           cur_pos+=50
           pos.append(cur_pos)
        else: #stay where we are
           pos.append(cur_pos)
    
    return pos

def printing_error(error_smooth, error_kalman, time):
    for i, t in enumerate(time):
        print("time: "+ str(t) +" is: " + str(error_kalman[i]) +" "+ str(error_smooth[(len(error_kalman)-i-1)]))
        
def main(): #only taking into account position; H takes care of that
    
    delta_t = 1
    t_max = 15
    R = 2 #variance of sensor 
    q = 0.5 #process noise
    #random.seed(5)
    
    #random walk & Kalman_filter
    time = np.arange(0, t_max+1, delta_t)
    pos = random_walk(0.4, t_max, time)
    x_kalman, error_y, x_new_smooth, error_smooth, error_kalman, x_measured = Kalman_Filter(time, delta_t, t_max, pos, q, R) #Kalman Filter
    
    printing_error(error_smooth, error_kalman, time)
    #for i, x in enumerate(x_new_smooth):
    #    print(str(x) + " " + str(x_kalman[len(x_kalman)-i-1]))
        
    #plotting
    plt.figure()
    plt.title("Kalman filter with q= %2.1f & R= %2.1f" %(q,R), x=0.3)
    plt.xlabel("time")
    plt.ylabel("position")
    plt.plot(time, pos, 'ro:', label= 'truth data')
    plt.plot(time, x_measured, 'black', label= 'measured data')
    plt.errorbar(time, x_kalman, yerr=error_y, ecolor='b', barsabove=True, linestyle=':', fmt='<', capsize=5, label= 'Kalman upd data')
    plt.plot(time, list(reversed(x_new_smooth)), 'g^:', label= 'smoothened data' )
    plt.legend(bbox_to_anchor=(0.68, 1.02, 1., .102), loc=3, borderaxespad=0.)    
    plt.show()

if (__name__=="__main__"):
    main()
    
