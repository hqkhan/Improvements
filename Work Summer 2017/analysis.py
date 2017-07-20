import numpy as np
import matplotlib.pyplot as plt
import sys
import random
import scipy
import matplotlib.mlab as mlab
from scipy.stats import norm
import warnings
import matplotlib.cbook

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


def simulate_true(max_size, process_noise):
    states = []
    true = np.array([max_size/2.0 +0.5, max_size/2.0 +0.5, 0, 0]); delta_t = 1
    F = np.array([[1, 0, delta_t, 0], [0, 1, 0, delta_t], [0, 0, 1, 0], [0, 0, 0, 1]], dtype=float)
    Q = np.multiply(process_noise, np.array([[(delta_t**3)/3, 0, (delta_t**2)/2, 0], [0, (delta_t**3)/3, 0, (delta_t**2)/2], [(delta_t**2)/2, 0, delta_t, 0], [0, (delta_t**2)/2, 0, delta_t]], dtype=float))
    sqrt_of_Q = scipy.linalg.sqrtm(Q)
    
    for time in range(60):
        if true[0] >max_size-1 or true[1] >max_size-1 or true[0] <0 or true[1] <0: #don't let it escape grid
            break
        else:
            states.append(true)
            wk = np.dot(sqrt_of_Q, np.random.normal(0, 1, size=(4,)))
            true = np.add(np.dot(F, true), wk)
            
    return states

save = False
motion = False  
scale = 2
pause_time = 1.0

#NOT DOING FAILS ANYMORE
def plot_fail_vs_npart(size_of_block, fail_rate, n_part):
    plt.figure()
    plt.xlabel('Number of Particles')
    plt.ylabel('Failure rate')
    plt.plot(n_part, fail_rate, marker='*', color='purple', ls='--')
    directory = r'C:\Users\hka0211\Documents\Practice\Images/'
    ifile = 'fail_%s.jpg'%str(size_of_block)
    plt.savefig(directory+ifile, bbox='tight')
    plt.show()
    
def plot_error_vs_npart(size_of_block, error_p, n_part):
    plt.figure()
    plt.xlabel('Number of Particles')
    plt.ylabel('Error')
    plt.plot(n_part, error_p, marker='o', color='blue', ls='--')
    directory = r'C:\Users\hka0211\Documents\Practice\Images/'
    ifile = 'error_%s.jpg'%str(size_of_block)
    plt.savefig(directory+ifile, bbox='tight')
    plt.show()
    
def plot_analysis(points, line_type, label_filter):
    plt.grid(True)
    hist, bins_k = np.histogram(points, bins=40)
    (mu, sigma) = norm.fit(points)
    gaussian_pdf = mlab.normpdf(bins_k, mu, sigma)
    cdf_curve = np.cumsum(gaussian_pdf, dtype=float)
    cdf_curve /= cdf_curve[-1]
    plt.plot(bins_k, cdf_curve, line_type, linewidth=2, label= label_filter)
    plt.legend(bbox_to_anchor=(0.95, 0.5), loc=1, borderaxespad=0.)     
    
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

def setup_plot(title, xlabel, ylabel):
     plt.figure()
     plt.title(title)
     plt.xlabel(xlabel)
     plt.ylabel(ylabel)

def run_in_parallel(sim_num, grid, process_noise, n_part):
    truth = simulate_true(256, process_noise)
    grid.set_truth(truth)
    filtered_states, smooth_states = grid.analysis_main(None, True, False)
    particle_states = Pll.parallel_test(grid.analysis_main)(n_part, kalman=False, particle=True)
    
    return [[get_errors(truth, state, True, False) for states in particle_states for state in states], get_errors(truth, filtered_states, True, False), get_errors(truth, smooth_states, True, False), [get_errors(truth, state, False, True) for states in particle_states for state in states], get_errors(truth, filtered_states, False, True), get_errors(truth, smooth_states, False, True)]
    
def parallel_setup(n_part, grid, num_testcases, process_noise):
    error_p_pos = {key: [] for key in n_part}
    error_p_vel = {key: [] for key in n_part}
    
    all_errors = Pll.parallel_test(run_in_parallel)(np.arange(0, num_testcases), grid=grid, process_noise = process_noise, n_part = n_part)
    
    error_k_pos   = [error for p, k, s, pv, kv, sv in all_errors for error in k]
    error_s_pos = [error for p, k, s, pv, kv, sv in all_errors for error in s]
    particle_pos = [error for p, k, s, pv, kv, sv in all_errors for error in p]
    
    error_k_vel   = [error for p, k, s, pv, kv, sv in all_errors for error in kv]
    error_s_vel = [error for p, k, s, pv, kv, sv in all_errors for error in sv]
    particle_vel = [error for p, k, s, pv, kv, sv in all_errors for error in pv]
    
    for i, part in enumerate(n_part):
        error_p_pos[part] = particle_pos[i]
        error_p_vel[part] = particle_vel[i]
        
    return error_p_pos, error_k_pos, error_s_pos, error_p_vel, error_k_vel, error_s_vel

def grid_parallel(grids, n_part, num_testcases, process_noise):
    
def main(): 
    random.seed(5)
    warnings.filterwarnings("ignore",category=matplotlib.cbook.mplDeprecation)
    grid_sizes = [1, 2, 4, 8]; max_size = 256
    process_noise = 1.0
    mec = ['r--', 'k--', 'c--', 'm--', 'y--', 'g:']
    n_part = [100, 300, 500, 800, 1000, 2000]
    grids = []
    
    num_testcases = 100
    
    for size in grid_sizes[:]:
        print("Working on cell size: %d"%int(size))
        grid = Main_Grid(int(size), max_size)
        grid.set_process_noise(process_noise)
        grids.append(grid)
        
        error_p_pos, error_k_pos, error_s_pos, error_p_vel, error_k_vel, error_s_vel = parallel_setup(n_part, grid, num_testcases, process_noise)
        
        #plot all positional data
        setup_plot('PvK cell size:%d '%size, 'Error (pos)', 'Percentile')
        plot_analysis(error_k_pos, 'b--', 'Kalman')
        plot_analysis(error_s_pos, 'g--', 'Smoothened')
        for i, num in enumerate(n_part): #have particle errors for tests with different particle #
            plot_analysis(error_p_pos[num], mec[i], 'Particle %d'%num)  
            
        #plot all positional data
        setup_plot('PvK cell size:%d '%size, 'Error (vel)', 'Percentile') #np.arange(0, max(max(error_k, error_s, error_p)), 0.5)
        plot_analysis(error_k_vel, 'b--', 'Kalman')
        plot_analysis(error_s_vel, 'g--', 'Smoothened')
        for i, num in enumerate(n_part): #have particle errors for tests with different particle #
            plot_analysis(error_p_vel[num], mec[i], 'Particle %d'%num)  
            
            
        """
        for noise in process_noise: #simulate targets with different process noises
            fail_total = 0
            grid.set_process_noise(noise)
            
            for testcase in range(num_testcases):
                truth = simulate_true(max_size, noise)
                grid.set_truth(truth)
                
                #for num_particles in n_part:
                grid.set_num_particles(300)
                particle_states, code, filtered_states, smooth_states = grid.analysis_main(True, True)
                
                error_p.extend(get_errors(truth, particle_states))
                error_k.extend(get_errors(truth, filtered_states))
                error_s.extend(get_errors(truth, smooth_states))
           
            #setup plot
            setup_plot('PvK cell size:%d '%size +'noise:%1.1f'%noise, 'Error', 'Percentile') #np.arange(0, max(max(error_k, error_s, error_p)), 0.5)
            print('Failed #: %d;' %fail_total+ ' Noise: %1.1f' %noise)
            plot_analysis(error_k, 'b--', 'Kalman')
            plot_analysis(error_s, 'g--', 'Smoothened')
            plot_analysis(error_p, 'r--', 'Particle')
            plt.legend(bbox_to_anchor=(0.95, 0.3), loc=1, borderaxespad=0.)
            error_p, error_k, error_s = [], [], []
        """    
        #error vs number of particles
        #plot_error_vs_npart(size, error_p, num_particles)
            
        
class Main_Grid:
    def __init__(self, size_of_block, max_grid_size):
        self.max_size = max_grid_size
        self.size_of_block = size_of_block
        self.num_blocks_hori = int(self.max_size/self.size_of_block)
        self.num_of_grid_blocks = (self.max_size/self.size_of_block)**2
        self.R = (self.size_of_block**2)/12
        self.blocks, self.grid_association = [], []
        self.num_particles = 0
        num = 0

        #create grid
        for y in range(self.num_blocks_hori):
            for x in range(self.num_blocks_hori):
                self.blocks.append(Grid_Block(num, (x,y), self.size_of_block))
                num+=1
        
    def analysis_main(self, num_particles, kalman, particle):
        if num_particles != None:
            self.num_particles = num_particles
            
        #Particle filter 
        if particle and kalman is not True:
            self.measurements = self.get_particle_measurements()
            particle_states = self.Particle_Filter()
            return [particle_states]
      
        #Kalman filter
        if kalman and particle is not True:
            self.kalman_measurements = self.get_kalman_measurements()
            filtered_states, smooth_states = self.Kalman_Filter([x for x, y in self.kalman_measurements], [y for x, y in self.kalman_measurements], True)
            return filtered_states, smooth_states
        
        elif kalman and particle:
            self.measurements = self.get_particle_measurements()
            particle_states = self.Particle_Filter()
            self.kalman_measurements = self.get_kalman_measurements()
            filtered_states, smooth_states = self.Kalman_Filter([x for x, y in self.kalman_measurements], [y for x, y in self.kalman_measurements], True)
            return  particle_states, filtered_states, smooth_states
        
         #  self.plot_results(filtered_states, particle_states)
         #  self.plot_truth('All', 'b--', 10)
    
    def set_truth (self, truth):
        self.states = truth
    
    def set_num_particles(self, num):
        self.num_particles = num
    
    def set_process_noise(self, num):
        self.process_noise = num
        
    def Particle_Filter(self):
        particles = []; state_particles = []; delta_t = 1
        weights = [1/self.num_particles for i in range(self.num_particles)]  #initial weight set to equal for all since all weights are inside the same grid
        F = np.array([[1, 0, delta_t, 0], [0, 1, 0, delta_t], [0, 0, 1, 0], [0, 0, 0, 1]], dtype=float)
        Q = np.multiply(self.process_noise, np.array([[(delta_t**3)/3, 0, (delta_t**2)/2, 0], [0, (delta_t**3)/3, 0, (delta_t**2)/2], [(delta_t**2)/2, 0, delta_t, 0], [0, (delta_t**2)/2, 0, delta_t]], dtype=float))
        sqrt_of_Q = scipy.linalg.sqrtm(Q)
        mu, sigma = 0, 1.0
        
        #Populating the first cell randomly in a uniform way
        for n in range(self.num_particles):
            particles.append(np.array([random.uniform(self.blocks[self.grid_association[0]].x_min, self.blocks[self.grid_association[0]].x_max), random.uniform(self.blocks[self.grid_association[0]].y_min, self.blocks[self.grid_association[0]].y_max), np.random.normal(mu, sigma), np.random.normal(mu, sigma)]))    
        
        x_mean, y_mean, x_vel, y_vel = map(lambda x: sum(x)/self.num_particles, [[part[0] for part in particles], [part[1] for part in particles], [part[2] for part in particles], [part[3] for part in particles]])
        state_particles.append(np.array([x_mean, y_mean, x_vel, y_vel]))
        particles_prop = [0 for o in particles]
        
        if motion:
            plt.figure()
            self.motion_plot(particles, 0, 0, x_mean, y_mean)
            
        for i, grid in enumerate(self.grid_association[1:]):
            #predict
            for l, part in enumerate(particles): 
                wk = np.dot(sqrt_of_Q, np.array([np.random.normal(mu, sigma), np.random.normal(mu, sigma), np.random.normal(mu, sigma), np.random.normal(mu, sigma)]))
                particles_prop[l] = np.add(np.dot(F, part), wk)
            
            if motion: #show predicted
                plt.clf()
                x_mean, y_mean = map(lambda x: sum(x)/self.num_particles, [[part[0] for part in particles], [part[1] for part in particles]])
                self.motion_plot(particles_prop, i+1, i+1, x_mean, y_mean)
                
            weights = [self.size_of_block**-2 if part[0] >= self.blocks[grid].x_min and part[0] < self.blocks[grid].x_max and part[1] >= self.blocks[grid].y_min and part[1] < self.blocks[grid].y_max else 0 for part in particles_prop ]
            
            #Resampling
            try:
                particles = [particles_prop[p] for p, weight in enumerate(weights) if weight != 0]
                replace = np.random.randint(0, len(particles), size= self.num_particles-len(particles))
                replacement_particles = [particles[rep_part] for rep_part in replace]
                particles.extend(replacement_particles)
                resample = True
            except:
                resample = False
            
            if resample:
                x_mean, y_mean, x_vel, y_vel = map(lambda x: sum(x)/self.num_particles, [[part[0] for part in particles], [part[1] for part in particles], [part[2] for part in particles], [part[3] for part in particles]])
                state_particles.append(np.array([x_mean, y_mean, x_vel, y_vel])) 
                weights = [1/self.num_particles for q in weights] 
            
                if motion: #show updated
                    plt.clf()
                    self.motion_plot(particles, i+1, i+1, x_mean, y_mean)
            else: #must reinitialize since filter failed
                del particles[:]
                for n in range(self.num_particles):
                    particles.append(np.array([random.uniform(self.blocks[self.grid_association[i+1]].x_min, self.blocks[self.grid_association[i+1]].x_max), random.uniform(self.blocks[self.grid_association[i+1]].y_min, self.blocks[self.grid_association[i+1]].y_max), np.random.normal(mu, sigma), np.random.normal(mu, sigma)]))    
                
                x_mean, y_mean, x_vel, y_vel = map(lambda x: sum(x)/self.num_particles, [[part[0] for part in particles], [part[1] for part in particles], [part[2] for part in particles], [part[3] for part in particles]])
                state_particles.append(np.array([x_mean, y_mean, x_vel, y_vel])) 

                if motion: #show resampled
                    plt.clf()
                    self.motion_plot(particles, i+1, i+1, x_mean, y_mean)
                
        return state_particles
    
    def motion_plot(self, particles, num, truth, x_mean, y_mean):
        plt.grid(True)
        self.plot_truth(truth, 'b*--', 10)
        self.plot_particles(particles)
       # self.plot_measurements(num)
        plt.xticks(np.arange(0, self.max_size, self.size_of_block))
        plt.yticks(np.arange(0, self.max_size, self.size_of_block))
        plt.plot(x_mean, y_mean, c='black', marker='o', markersize=5, zorder=20)
        #plt.xlim(self.max_size/2.0-(scale*self.size_of_block), self.max_size/2.0 +(scale*self.size_of_block))
        #plt.ylim(self.max_size/2.0-(scale*self.size_of_block), self.max_size/2.0 +(scale*self.size_of_block))
        plt.xlim((min([x for x, y, xvel, yvel in self.states]) -(scale*self.size_of_block), max([x for x, y, xvel, yvel in self.states]) +(scale*self.size_of_block)))
        plt.ylim((min([y for x, y, xvel, yvel in self.states]) -(scale*self.size_of_block), max([y for x, y, xvel, yvel in self.states]) +(scale*self.size_of_block)))
        plt.pause(pause_time)
        
        if save:
            directory = r'C:\Users\hka0211\Documents\Practice\Images/'
            ifile = 'time_%s.jpg'%num
            plt.savefig(directory+ifile, bbox='tight')
    
        plt.legend(bbox_to_anchor=(0.95, 0.3), loc=1, borderaxespad=0.)  
        plt.xlabel('X position')
        plt.ylabel('Y position')
        
    def plot_particles(self, particles):
        plt.plot([x for x, y, xvel, yvel in particles], [y for x, y, xvel, yvel in particles], 'go-', linestyle='none', label= 'Particles', zorder=0)
        
    def plot_results(self, kalman, particle):
        plt.figure()
        plt.grid(True)
        plt.plot([x for x, y, xvel, yvel in kalman], [y for x, y, xvel, yvel in kalman], 'ro-')
        plt.plot([x for x, y, xvel, yvel in particle], [y for x, y, xvel, yvel in particle], 'g^-')
        plt.show()
    
    def plot_measurements(self, num):
        if num == None:
            plt.plot([x for x, y in self.measurements], [y for x, y in self.measurements], linestyle='none', marker='x', c = 'red')
        else:
            plt.plot([self.measurements[num][0]], [self.measurements[num][1]], linestyle='none',marker='x', c = 'red', label = 'Measurement', zorder=5)
        
    def plot_truth(self, num, line, z):
        if num != 'All':
            plt.plot(self.states[num][0], self.states[num][1], line, label= 'Truth', zorder = z)
        elif num == 'All':
            plt.plot([x for x, y, xvel, yvel in self.states], [y for x, y, xvel, yvel in self.states], 'b*--', label= 'Truth')
        
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
            self.plot_truth('All', 'b*--', 10)
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
        
    def Kalman_Filter(self, x_pos_relevant, y_pos_relevant, smoother):
        process_noise = self.process_noise
        cov_measure = np.array([self.R, 0, 0, 0, 0, self.R, 0, 0, 0, 0, 0, 0.01, 0, 0, 0, 0.01]).reshape((4,4))
        C = np.array([[1, 0, 0, 0], [0, 1, 0, 0]]) #only looking at position of target in 2D
        state_update_forward, cov_update_forward = self.Forward_filter(cov_measure, C, x_pos_relevant, y_pos_relevant, process_noise)
        
        if smoother:
            state_pred_backward, cov_pred_backward = self.Backward_filter(cov_measure, C, x_pos_relevant, y_pos_relevant, process_noise)
            smooth_state, smooth_cov = self.Smoothen_solution(len(self.states), state_update_forward, cov_update_forward, state_pred_backward, cov_pred_backward)
            return state_update_forward, smooth_state
        else:
            return state_update_forward, None
        
    def Forward_filter(self, cov_old, C, x_pos_relevant, y_pos_relevant, process_noise):
        state_old = np.array([[x_pos_relevant[0]], [y_pos_relevant[0]], [0.], [0.]], dtype=float)
        x_pos_var = self.R
        y_pos_var = self.R
        state_update_array = []; state_update_array.append(state_old)
        cov_update_array = []; cov_update_array.append(cov_old)
        
        delta_t =1
        F = np.array([[1, 0, delta_t, 0], [0, 1, 0, delta_t], [0, 0, 1, 0], [0, 0, 0, 1]], dtype=float)
        Q = np.multiply(0.01, np.array([[(delta_t**3)/3, 0, (delta_t**2)/2, 0], [0, (delta_t**3)/3, 0, (delta_t**2)/2], [(delta_t**2)/2, 0, delta_t, 0], [0, (delta_t**2)/2, 0, delta_t]], dtype=float))
     
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
    
    def Backward_filter(self, cov_old, C, x_pos_relevant, y_pos_relevant, process_noise): #going backwards now
        state_old = np.array([[x_pos_relevant[-1]], [y_pos_relevant[-1]], [0.], [0.]], dtype=float) 
        x_pos_var = self.R 
        y_pos_var = self.R
        state_pred_array = []; state_pred_array.append(state_old); delta_t = 1
        state_update_array = []
        cov_update_array = []; cov_pred_array = []; cov_pred_array.append(cov_old); cov_update_array.append(cov_old)
        F = np.array([[1, 0, delta_t, 0], [0, 1, 0, delta_t], [0, 0, 1, 0], [0, 0, 0, 1]], dtype=float)
        Q = np.multiply(0.01, np.array([[(delta_t**3)/3, 0, (delta_t**2)/2, 0], [0, (delta_t**3)/3, 0, (delta_t**2)/2], [(delta_t**2)/2, 0, delta_t, 0], [0, (delta_t**2)/2, 0, delta_t]], dtype=float))
           
        for i in range(len(self.states)-2, -1, -delta_t):
            #predict 
            state_pred = np.dot(F, state_old)
            cov_pred = np.add(np.dot(F, np.dot(cov_old, np.transpose(F))), Q)
            
            state_pred_array.append(state_pred)
            cov_pred_array.append(cov_pred)
            
            #update
            kalman_gain = np.dot(np.dot(cov_pred, np.transpose(C)), np.linalg.inv(np.add(np.dot(C, np.dot(cov_pred, np.transpose(C))), np.array([[x_pos_var, 0], [0, y_pos_var]], dtype=float))))
            state_upd = np.add(state_pred, np.dot(kalman_gain, np.subtract(np.array([[x_pos_relevant[i]], [y_pos_relevant[i]]], dtype=float), np.dot(C, state_pred))))
            cov_upd = np.dot(np.subtract(np.identity(4), np.dot(kalman_gain, C)), cov_pred)
            state_update_array.append(state_upd)
            cov_update_array.append(cov_upd)
            #reset 
            cov_old = cov_upd
            state_old = state_upd
          
        return list(reversed(state_pred_array)), list(reversed(cov_pred_array))
        

    def Smoothen_solution(self, max_time, state_update_forward, cov_update_forward, state_pred_backward, cov_pred_backward):
         smooth_state = []
         smooth_cov = []
    
         for i in range(max_time):
             smooth_state.append(np.add(np.dot(cov_update_forward[i], np.dot(np.linalg.inv(np.add(cov_update_forward[i], cov_pred_backward[i])), state_pred_backward[i])), 
                                   np.dot(cov_pred_backward[i], np.dot(np.linalg.inv(np.add(cov_update_forward[i], cov_pred_backward[i])), state_update_forward[i]))))
             
             smooth_cov.append(np.dot(cov_update_forward[i], np.dot(np.linalg.inv(np.add(cov_update_forward[i], cov_pred_backward[i])), cov_pred_backward[i])))
             
         return smooth_state, smooth_cov
 
if __name__=="__main__":
    import Parallel as Pll
    main()
















