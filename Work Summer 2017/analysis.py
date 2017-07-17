import numpy as np
import matplotlib.pyplot as plt
import sys
import random
import scipy
import matplotlib.mlab as mlab
from scipy.stats import norm

class Grid_Block:
    def __init__(self, num, vert, size_of_block):
        self.num = num
        self.size = size_of_block
        self.x = vert[0]; self.y = vert[1]
        
        self.x_min = self.x*(self.size)
        self.y_min = self.y*(self.size)
        
        if self.x_min <0:
            self.x_min = 0
       
        if self.y_min<0:
            self.y_min = 0
            
        self.x_max = (self.x+1)*(self.size)
        self.y_max = (self.y+1)*(self.size)
        
        x_center = self.x_min + (self.size/2)
        y_center = self.y_min + (self.size/2)
        self.center = (x_center, y_center)
        
    def display_boundaries(self):
        print('Grid: %d' %self.num+ ' Xmin: %d' %self.x_min+ ' Xmax: %d' %self.x_max+ ' Ymin: %d'%self.y_min+ ' Ymax: %d' %self.y_max)

save = False
motion = False  
scale = 20
def main(): #put this under main grid
    grid_sizes = [1, 2, 4, 8]
    
    #success=0.0
    #success += Main_Grid(1, 256).get_total()
    
    for size in grid_sizes[1:2]:
        print("Working on grid %d"%int(size))
        Main_Grid(int(size), 256)
        print('')
    
    #print(success/10000.0)        
    
class Main_Grid:
    def __init__(self, size_of_block, max_grid_size):
        self.max_size = max_grid_size
        self.size_of_block = size_of_block
        self.num_blocks_hori = int(self.max_size/self.size_of_block)
        self.num_of_grid_blocks = (self.max_size/self.size_of_block)**2
        self.R = (self.size_of_block**2)/12
        self.blocks, self.grid_association, self.states, error_p, error_total = [], [], [], [], []
        fail_rate = []
        num = 0
        
        #create grid
        for y in range(self.num_blocks_hori):
            for x in range(self.num_blocks_hori):
                self.blocks.append(Grid_Block(num, (x,y), self.size_of_block))
                num+=1
        
        #simulate true trajectory
        self.simulate_true()
        self.measurements = self.get_particle_measurements()
        self.kalman_measurements = self.get_kalman_measurements()
        
        #Particle filter analysis
        n_part = [10, 100, 300, 500, 1000]
        run_amount = 1000
        for part in n_part:
            self.fail_total = 0 #number of fails
            for i in range(run_amount):
                particle_states, code = self.Particle_Filter(part)
                if code == 0:
                    error_p.append(100)
                    self.fail_total+= 1
                elif code == 1:
                    euc_p = self.get_particle_errors(particle_states)
                    error_p.append(sum(euc_p))
                
            error_total.append(float(sum(error_p)/len(error_p)))
            fail_rate.append(float(self.fail_total/run_amount))
            del error_p[:]
        
        #error vs number of particles
        self.plot_error_vs_npart(error_total, n_part)
        self.plot_fail_vs_npart(fail_rate, n_part)
        
        #Kalman filter
        #filtered_states = self.Kalman_Filter([x for x, y in self.kalman_measurements], [y for x, y in self.kalman_measurements])
        
        #analysis
        #euc_k = self.get_kalman_errors(filtered_states)
        #self.plot_analysis(euc_k, euc_p)
            
        
        
    def plot_fail_vs_npart(self, fail_rate, n_part):
        plt.figure()
        plt.xlabel('Number of Particles')
        plt.ylabel('Failure rate')
        plt.plot(n_part, fail_rate, marker='*', color='purple', ls='--')
        plt.show()
        
    def plot_error_vs_npart(self, error_p, n_part):
        plt.figure()
        plt.xlabel('Number of Particles')
        plt.ylabel('Error')
        plt.plot(n_part, error_p, marker='o', color='blue', ls='--')
        plt.show()
        
    def simulate_true(self):
        true = np.array([self.max_size/2.0 +1, self.max_size/2.0 +1, 0, 0]); delta_t = 1
        F = np.array([[1, 0, delta_t, 0], [0, 1, 0, delta_t], [0, 0, 1, 0], [0, 0, 0, 1]], dtype=float)
        Q = 0.01*np.array([[(delta_t**3)/3, 0, (delta_t**2)/2, 0], [0, (delta_t**3)/3, 0, (delta_t**2)/2], [(delta_t**2)/2, 0, delta_t, 0], [0, (delta_t**2)/2, 0, delta_t]], dtype=float)
        sqrt_of_Q = scipy.linalg.sqrtm(Q)
        for time in range(120):
            if true[0] >self.max_size-1 or true[1] >self.max_size-1 or true[0] <0 or true[1] <0: #don't let it escape grid
                break
            else:
                self.states.append(true)
                wk = np.dot(sqrt_of_Q, np.random.normal(0, 1, size=(4,)))
                true = np.add(np.dot(F, true), wk)
        
    def get_total(self):
        return self.sum_total
        
    def Particle_Filter(self, num_particles):
        particles = []; particles_old = []; state_particles = []; delta_t = 1
        weights = [1/num_particles for i in range(num_particles)]  #initial weight set to equal for all since all weights are inside the same grid
        F = np.array([[1, 0, delta_t, 0], [0, 1, 0, delta_t], [0, 0, 1, 0], [0, 0, 0, 1]], dtype=float)
        Q = 0.01*np.array([[(delta_t**3)/3, 0, (delta_t**2)/2, 0], [0, (delta_t**3)/3, 0, (delta_t**2)/2], [(delta_t**2)/2, 0, delta_t, 0], [0, (delta_t**2)/2, 0, delta_t]], dtype=float)
        sqrt_of_Q = scipy.linalg.sqrtm(Q)
        mu, sigma = 0, 1.0
        
        if motion:
            plt.figure()
            plt.grid(True)
        
        #Populating the first cell randomly in a uniform way
        for n in range(num_particles):
            particles_old.append(np.array([random.uniform(self.blocks[self.grid_association[0]].x_min, self.blocks[self.grid_association[0]].x_max), random.uniform(self.blocks[self.grid_association[0]].y_min, self.blocks[self.grid_association[0]].y_max), np.random.normal(mu, sigma), np.random.normal(mu, sigma)]))    
        
        x_mean, y_mean, x_vel, y_vel = map(lambda x: sum(x)/num_particles, [[part[0] for part in particles_old], [part[1] for part in particles_old], [part[2] for part in particles_old], [part[3] for part in particles_old]])
        state_particles.append(np.array([x_mean, y_mean, x_vel, y_vel]))
        particles = [0 for o in particles_old]
        
        for i, grid in enumerate(self.grid_association[1:]):
            #predict
            for l, part in enumerate(particles_old): 
                wk = np.dot(sqrt_of_Q, np.array([np.random.normal(0, self.size_of_block), np.random.normal(0, self.size_of_block), np.random.normal(mu, sigma), np.random.normal(mu, sigma)]))
                particles[l] = np.add(np.dot(F, part), wk)
            
            particles_prop = particles
            
            weights = [1/(self.size_of_block**2) if part[0] >= self.blocks[grid].x_min and part[0] < self.blocks[grid].x_max and part[1] >= self.blocks[grid].y_min and part[1] < self.blocks[grid].y_max else 0 for part in particles ]
           
           #Resampling
            try:
                particles = [particles[p] for p, weight in enumerate(weights) if weight != 0]
                replace = np.random.randint(0, len(particles), size= num_particles-len(particles))
                replacement_particles = [np.array([particles[rep_part][0], particles[rep_part][1], particles[rep_part][2], particles[rep_part][3]]) for rep_part in replace]
                particles.extend(replacement_particles)
            except:
                return particles_old, 0
                print('Time:',str(i+1))
                print('No Particles in the correct cell')
                print(self.blocks[self.grid_association[i+1]].display_boundaries())
                x_mean, y_mean, x_vel, y_vel = map(lambda x: sum(x)/num_particles, [[part[0] for part in particles_old], [part[1] for part in particles_old], [part[2] for part in particles_old], [part[3] for part in particles_old]])
                print(x_mean, y_mean, x_vel, y_vel)
                print(self.states[i:i+2])
                
                self.motion_plot(particles_prop, i+1, i+1, x_mean, y_mean)
               # sys.exit()
            
            x_mean, y_mean, x_vel, y_vel = map(lambda x: sum(x)/num_particles, [[part[0] for part in particles], [part[1] for part in particles], [part[2] for part in particles], [part[3] for part in particles]])
            
            state_particles.append(np.array([x_mean, y_mean, x_vel, y_vel])) 
            particles_old = particles #set old to current so we can propagate current particles
            weights = [1/num_particles for q in weights] 

            if motion:
                self.motion_plot(particles_prop, i+1, i+1, x_mean, y_mean)
                plt.clf()
            
        return state_particles, 1
    
    def motion_plot(self, particles, num, truth, x_mean, y_mean):
        plt.grid(True)
        self.plot_truth(truth)
        self.plot_particles(particles)
        self.plot_measurements(num)
        plt.xticks(np.arange(0, self.max_size, self.size_of_block))
        plt.yticks(np.arange(0, self.max_size, self.size_of_block))
        plt.plot(x_mean, y_mean, c='black', marker='o', markersize=5, zorder=20)
        plt.xlim((min([x for x, y, xvel, yvel in particles]) -scale, max([x for x, y, xvel, yvel in particles]) +scale))
        plt.ylim((min([y for x, y, xvel, yvel in particles]) -scale, max([y for x, y, xvel, yvel in particles]) +scale))
        plt.pause(1.0)
        
        if save:
            directory = r'C:\Users\hka0211\Documents\Practice\Images/'
            ifile = 'time_%s.jpg'%num
            plt.savefig(directory+ifile, bbox='tight')
    
        plt.legend(bbox_to_anchor=(0.95, 0.3), loc=1, borderaxespad=0.)  
        plt.xlabel('X position')
        plt.ylabel('Y position')
        
    def get_kalman_errors(self, filtered_states):
        dist_k = []
        for i, state in enumerate(self.states):    
            dist_k.append((((state[0]-filtered_states[i][0])**2) + (state[1]-filtered_states[i][1])**2)**1/2)
        
        return dist_k
    
    def get_particle_errors(self, particle_states):
        dist_p = []
        for i, state in enumerate(self.states):    
            dist_p.append((((state[0]-particle_states[i][0])**2) + (state[1]-particle_states[i][1])**2)**1/2) 
        
        return dist_p

    def plot_analysis(self, points_for_kalman, points_for_particle):
        plt.figure()
        plt.grid(True)
        
        hist, bins_k = np.histogram(points_for_kalman, bins=40)
        (mu, sigma) = norm.fit(points_for_kalman)
        gaussian_pdf = mlab.normpdf(bins_k, mu, sigma)
        cdf_curve = np.cumsum(gaussian_pdf, dtype=float)
        cdf_curve /= cdf_curve[-1]
        plt.plot(bins_k, cdf_curve, 'b--', linewidth=2, label= 'Kalman Filter')
        
        hist, bins = np.histogram(points_for_particle, bins=40)
        (mu, sigma) = norm.fit(points_for_particle)
        gaussian_pdf = mlab.normpdf(bins, mu, sigma)
        cdf_curve_p = np.cumsum(gaussian_pdf, dtype=float)
        cdf_curve_p /= cdf_curve_p[-1]
        plt.xticks(np.arange(0, max(max(points_for_kalman, points_for_particle)), 0.5))
        plt.plot(bins, cdf_curve_p, 'g--', linewidth=2, label= 'Particle Filter')
        
        plt.legend(bbox_to_anchor=(0.95, 0.3), loc=1, borderaxespad=0.)     
        plt.title('Particle vs Kalman with cell size: %d' %self.size_of_block)
        plt.xlabel('Error')
        plt.ylabel('Percentile')
    
    def plot_particles(self, particles):
        plt.plot([x for x, y, xvel, yvel in particles], [y for x, y, xvel, yvel in particles], 'go-', linestyle='none', label= 'Particles', zorder=0)
        
    def plot_results(self, kalman, particle):
        plt.figure()
        plt.plot([x for x, y, xvel, yvel in kalman], [y for x, y, xvel, yvel in kalman], 'ro-')
        plt.plot([x for x, y, xvel, yvel in particle], [y for x, y, xvel, yvel in particle], 'g^-')
        plt.show()
    
    def plot_measurements(self, num):
        if num == None:
            plt.plot([x for x, y in self.measurements], [y for x, y in self.measurements], linestyle='none', marker='x', c = 'red')
        else:
            #print(self.measurements[num][0], self.measurements[num][1])
            plt.plot([self.measurements[num][0]], [self.measurements[num][1]], linestyle='none',marker='x', c = 'red', label = 'Measurement', zorder=5)
        
    def plot_truth(self, num):
        if num != 'All':
            plt.plot(self.states[num][0], self.states[num][1], 'b*--', label= 'Truth', zorder = 10)
        elif num == 'All':
            plt.plot([x for x, y, xvel, yvel in self.states], [y for x, y, xvel, yvel in self.states], 'b*', label= 'Truth')
        
    def plot_grid(self):
        plt.figure()
        for grid in self.blocks:
            print(grid.center[0], grid.center[1])
            plt.plot(grid.center[0], grid.center[1], marker='x', c='red')
        
        plt.show()
        
    def get_particle_measurements(self):
        measurements = []; grid_association = []; missed_state = []
        for point in self.states:
            for grid in self.blocks:
                if point[0] >= grid.x_min and point[0] < grid.x_max and point[1] >= grid.y_min and point[1] < grid.y_max:
                    measurements.append((int(round(random.uniform(grid.x_min, grid.x_max))), int(round(random.uniform(grid.y_min, grid.y_max))))) 
                    grid_association.append(grid.num)
                    missed_state.append(point)
                    break
        try: 
            assert (len(measurements) == len(self.states))
            self.grid_association = grid_association
            return measurements
        except:
            print("Problem in obtaining particle measurements")
            print(len(measurements), len(self.states))
            test2 = [(x,y,xvel,yvel) for x, y, xvel, yvel in self.states]
            test = [(a,b,c,d) for a,b,c,d in missed_state]
            print([(x,y) for x,y,xvel,yvel in test2 if (x,y,xvel,yvel) not in test])
            
            plt.figure()
            self.plot_truth('All')
            sys.exit()
        
    def get_kalman_measurements(self):
        measurements = []
        for point in self.states:
            for grid in self.blocks:
                if point[0] >= grid.x_min and point[0] < grid.x_max and point[1] >= grid.y_min and point[1] < grid.y_max:
                    measurements.append(grid.center) 
                    break
        try: 
            assert (len(measurements) == len(self.states))
            return measurements
        except:
            print(len(measurements), len(self.states))
            sys.exit()
        
    def Kalman_Filter(self, x_pos_relevant, y_pos_relevant):
        process_noise = 0.01
        cov_measure = np.array([self.R, 0, 0, 0, 0, self.R, 0, 0, 0, 0, 0, 0.01, 0, 0, 0, 0.01]).reshape((4,4))
        C = np.array([[1, 0, 0, 0], [0, 1, 0, 0]]) #only looking at position of target in 2D
        state_update_forward, cov_update_forward = self.Forward_filter(cov_measure, C, x_pos_relevant, y_pos_relevant, process_noise)
        
        return state_update_forward
        
    def Forward_filter(self,cov_old, C, x_pos_relevant, y_pos_relevant, process_noise):
        state_old = np.array([[x_pos_relevant[0]], [y_pos_relevant[0]], [0.], [0.]], dtype=float)
        x_pos_var = self.R
        y_pos_var = self.R
        state_update_array = []; state_update_array.append(state_old)
        cov_update_array = []; cov_update_array.append(cov_old)
        
        delta_t =1
        F = np.array([[1, 0, delta_t, 0], [0, 1, 0, delta_t], [0, 0, 1, 0], [0, 0, 0, 1]], dtype=float)
        Q = process_noise*np.array([[(delta_t**3)/3, 0, (delta_t**2)/2, 0], [0, (delta_t**3)/3, 0, (delta_t**2)/2], [(delta_t**2)/2, 0, delta_t, 0], [0, (delta_t**2)/2, 0, delta_t]], dtype=float)
    
        for i in range(0, len(self.states)-1, delta_t): #from 0-254 since we predict future therefore at 254 we are predicting 255 
            
            #predict
            state_pred = np.dot(F, state_old)
            cov_pred = np.add(np.dot(F, np.dot(cov_old, np.transpose(F))), Q)
            
            #update
            kalman_gain = np.dot(np.dot(cov_pred, np.transpose(C)), np.linalg.inv(np.add(np.dot(C, np.dot(cov_pred, np.transpose(C))), np.array([[x_pos_var, 0], [0, y_pos_var]], dtype=float))))
            state_upd = np.add(state_pred, np.dot(kalman_gain, np.subtract(np.array([[x_pos_relevant[i+1]], [y_pos_relevant[i+1]]], dtype=float), np.dot(C, state_pred))))
            cov_upd = np.dot(np.subtract(np.identity(4), np.dot(kalman_gain, C)), cov_pred)
            state_update_array.append(state_upd)
            cov_update_array.append(cov_upd)
           
            #reset 
            cov_old = cov_upd
            state_old = state_upd
        
        return state_update_array, cov_update_array

if __name__=="__main__":
    main()
















