### Libraries Used
import tensorflow as tf
import numpy as np
import random
import time
import matplotlib.pyplot as plt
from collections import deque# Ordered collection with ends
import warnings # This ignore all the warning messages that are normally printed during the training because of skiimage
warnings.filterwarnings('ignore')
######################################################################################
A=np.zeros(52)
B=np.zeros(52)
C=np.zeros(52)
D=np.zeros(52)
E=np.zeros(52)
F=np.zeros(52)
G=np.zeros(52)
H=np.zeros(52)
I=np.zeros(52)
J=np.zeros(52)
K=np.zeros(52)
L=np.zeros(52)
M=np.zeros(52)
N=np.zeros(52)
O=np.zeros(52)
P=np.zeros(52)
Q=np.zeros(52)
R=np.zeros(52)
S=np.zeros(52)
T=np.zeros(52)
U=np.zeros(52)
V=np.zeros(52)
W=np.zeros(52)
X=np.zeros(52)
Y=np.zeros(52)
Z=np.zeros(52)
A[0]=1
B[1]=1
C[2]=1
D[3]=1
E[4]=1
F[5]=1
G[6]=1
H[7]=1
I[8]=1
J[9]=1
K[10]=1
L[11]=1
M[12]=1
N[13]=1
O[14]=1
P[15]=1
Q[16]=1
R[17]=1
S[18]=1
T[19]=1
U[20]=1
V[21]=1
W[22]=1
X[23]=1
Y[24]=1
Z[25]=1

dict = {'A': A, 'B': B, 'C': C, 'D': D, 'E': E, 'F': F, 'G': G, 'H': H, 'I': I, 'J': J, 'K': K, 'L': L, 'M': M, 'N': N,
        'O': O, 'P': P, 'Q': Q, 'R': R, 'S': S, 'T': T, 'U': U, 'V': V, 'W': W, 'X': X, 'Y': Y, 'Z':Z}

A_Blank=np.zeros(52)
B_Blank=np.zeros(52)
C_Blank=np.zeros(52)
D_Blank=np.zeros(52)
E_Blank=np.zeros(52)
F_Blank=np.zeros(52)
G_Blank=np.zeros(52)
H_Blank=np.zeros(52)
I_Blank=np.zeros(52)
J_Blank=np.zeros(52)
K_Blank=np.zeros(52)
L_Blank=np.zeros(52)
M_Blank=np.zeros(52)
N_Blank=np.zeros(52)
O_Blank=np.zeros(52)
P_Blank=np.zeros(52)
Q_Blank=np.zeros(52)
R_Blank=np.zeros(52)
S_Blank=np.zeros(52)
T_Blank=np.zeros(52)
U_Blank=np.zeros(52)
V_Blank=np.zeros(52)
W_Blank=np.zeros(52)
X_Blank=np.zeros(52)
Y_Blank=np.zeros(52)
Z_Blank=np.zeros(52)
A_Blank[0]=1
B_Blank[1]=1
C_Blank[2]=1
D_Blank[3]=1
E_Blank[4]=1
F_Blank[5]=1
G_Blank[6]=1
H_Blank[7]=1
I_Blank[8]=1
J_Blank[9]=1
K_Blank[10]=1
L_Blank[11]=1
M_Blank[12]=1
N_Blank[13]=1
O_Blank[14]=1
P_Blank[15]=1
Q_Blank[16]=1
R_Blank[17]=1
S_Blank[18]=1
T_Blank[19]=1
U_Blank[20]=1
V_Blank[21]=1
W_Blank[22]=1
X_Blank[23]=1
Y_Blank[24]=1
Z_Blank[25]=1

######################################################################################
### MODEL HYPERPARAMETERS
# Size of State ( Include Board 15x15x52  plus Rack 7x52)
# state_size = [232,52]
# action_size= [225,52]
state_size = 12064
action_size= 11700

# Learning Rate ( To be Determined)
learning_rate =  5.0

### TRAINING HYPERPARAMETERS
# TO BE DETERMINED
total_episodes = 100        # Total episodes for training
batch_size = 20

# Exploration parameters for epsilon greedy strategy
explore_start = 1.0            # exploration probability at start
explore_stop = 0.1           # minimum exploration probability
decay_rate = 0.1           # exponential decay rate for exploration prob

# Q learning hyperparameters
gamma = 0.95               # Discounting rate

### MEMORY HYPERPARAMETERS
pretrain_length = batch_size   # Number of experiences stored in the Memory when initialized for the first time
memory_size = 1000          # Number of experiences the Memory can keep

done = False
################################################################################################################

def PreProcessing(dict):
    stateList = []
    actionList = []
    nextstateList = []
    reward = []

    f = open('ML.txt', 'r')
    lines = [line.strip() for line in f.readlines()]
    for i in range(0, len(lines), 4):
        currentBoard = lines[i].split()
        rack = lines[i + 1].split()
        move = lines[i + 2].split()
        score = int(lines[i + 3])

        state = np.zeros(12064)
        action = np.zeros(11700)
        nextstate = np.zeros(12064)

        nextBoard = []
        for j in range(225):
            if currentBoard[j] != '_':
                nextBoard.append(currentBoard[j])
            else:
                nextBoard.append(move[j])

        for j in range(len(currentBoard)):
            if (currentBoard[j] != '_'):
                state[j * 52: j * 52 + 52] = dict[currentBoard[j]]

        for j in range(len(rack)):
            if (rack[j] != '_'):
                index = j + (15 * 15)
                state[index * 52: index * 52 + 52] = dict[rack[j]]

        for j in range(len(move)):
            if (move[j] != '_'):
                action[j * 52: j * 52 + 52] = dict[move[j]]

        for j in range(len(nextBoard)):
            if (nextBoard[j] != '_'):
                nextstate[j * 52: j * 52 + 52] = dict[nextBoard[j]]

        for j in range(len(rack)):
            if (rack[j] != '_'):
                index = j + (15 * 15)
                nextstate[index * 52: index * 52 + 52] = dict[rack[j]]

        stateList.append(state)
        actionList.append(action)
        nextstateList.append(nextstate)
        reward.append(score)

    return stateList, actionList, nextstateList, reward




class DQNetwork:
    def __init__(self, state_size, action_size, learning_rate, name='DQNetwork'):
        self.state_size = state_size
        self.action_size = action_size
        self.learning_rate = learning_rate

        with tf.variable_scope(name):
            # We create the placeholders
            # *state_size means that we take each elements of state_size in tuple hence is like if we wrote
            self.inputs_ = tf.placeholder(tf.float32, [None, state_size], name="inputs")
            self.actions_ = tf.placeholder(tf.float32, [None, action_size], name="actions_")
            # Remember that target_Q is the R(s,a) + ymax Qhat(s', a')
            self.target_Q = tf.placeholder(tf.float32, [None,1], name="target")


            # now declare the weights connecting the input to the hidden layer
            self.W1 = tf.Variable(tf.random_normal([state_size, 100], stddev=0.03), name='W1')
            self.b1 = tf.Variable(tf.random_normal([100]), name='b1')
            # and the weights connecting the hidden layer to the output layer
            self.W2 = tf.Variable(tf.random_normal([100, 1], stddev=0.03), name='W2')
            self.b2 = tf.Variable(tf.random_normal([1]), name='b2')

            self.hidden_out = tf.add(tf.matmul(self.inputs_, tf.abs(self.W1)), tf.abs(self.b1))
            self.hidden_out = tf.nn.relu(self.hidden_out)

            # now calculate the hidden layer output - in this case, let's use a softmax activated
            # output layer
            self.output = tf.nn.softmax(tf.add(tf.matmul(self.hidden_out, tf.abs(self.W2)), tf.abs(self.b2)))

            # Q is our predicted Q value.
            self.Q = tf.reduce_sum(tf.multiply(self.output, self.actions_), axis=1)

            # The loss is the difference between our predicted Q_values and the Q_target
            # Sum(Qtarget - Q)^2
            self.loss = tf.reduce_mean(tf.square(self.target_Q - self.Q))

            self.optimizer = tf.train.RMSPropOptimizer(self.learning_rate).minimize(self.loss)


# Reset the graph
tf.reset_default_graph()

# Instantiate the DQNetwork
DQNetwork = DQNetwork(state_size, action_size, learning_rate)


class Memory():
    def __init__(self, max_size):
        self.buffer =[]

    def add(self, experience):
        self.buffer.append(experience)


    def sample(self, batch_size):
        buffer_size = len(self.buffer)
        print(buffer_size)
        print(batch_size)
        index = np.random.choice(np.arange(min(buffer_size,batch_size)),
                                 #batch size instead
                                 size=min(buffer_size,batch_size),
                                 replace=False)

        return [self.buffer[i] for i in index]

# Instantiate memory
memory = Memory(max_size = memory_size)


def predict_Qs(explore_start, explore_stop, decay_rate, decay_step, state, actions):
    ## EPSILON GREEDY STRATEGY
    # Choose action a from state s using epsilon greedy.
    ## First we randomize a number
    exp_exp_tradeoff = np.random.rand()

    # Here we'll use an improved version of our epsilon greedy strategy used in Q-learning notebook
    explore_probability = explore_stop + (explore_start - explore_stop) * np.exp(-decay_rate * decay_step)


    ###ASK HERE################################
    ###QS Value is what? when explore probability > exp_exp_tradeoff#####
    if (explore_probability > exp_exp_tradeoff):
        Qs=0

    else:
        # Get action from Q-network (exploitation)
        # Estimate the Qs values state
        state1=np.zeros((1,state_size))
        state1[0]=state
        Qs = sess.run(DQNetwork.output, feed_dict={DQNetwork.inputs_: state1})


    return Qs, explore_probability


with tf.Session() as sess:
    # Initialize the variables
    sess.run(tf.global_variables_initializer())

    # Initialize the decay rate (that will use to reduce epsilon)
    decay_step = 0

    for episode in range(total_episodes):
        # Set step to 0
        step = 0
        # Initialize the rewards of the episode
        episode_rewards = []

        #preprocessing
        state, action, nextstate, reward = PreProcessing(dict)
        while step < len(state):

            # Increase decay_step
            decay_step += 1
            # Predict the action to take and take it
            Qs_Value, explore_probability = predict_Qs(explore_start, explore_stop, decay_rate, decay_step, state[step],
                                                         action[step])
            # Get Reward from score of game
            # Add the reward to total reward
            episode_rewards.append(reward[step])

            if step -len(state)==1:
                done=true

            memory.add((state[step], action[step], reward[step], nextstate[step], done))

            ### LEARNING PART
            # Obtain random mini-batch from memory
            batch = memory.sample(batch_size)
            if batch != None:
                states_mb = np.array([each[0] for each in batch])
                actions_mb = np.array([each[1] for each in batch])
                rewards_mb = np.array([each[2] for each in batch])
                next_states_mb = np.array([each[3] for each in batch])
                dones_mb = np.array([each[4] for each in batch])
                target_Qs_batch = []

                Qs_next_state = sess.run(DQNetwork.output, feed_dict={DQNetwork.inputs_: next_states_mb})

                # Set Q_target = r if the episode ends at s+1, otherwise set Q_target = r + gamma*maxQ(s', a')
                for i in range(0, len(batch)):
                    terminal = dones_mb[i]

                    # If we are in a terminal state, only equals reward
                    if terminal:
                        target_Qs_batch.append(rewards_mb[i])

                    else:
                        target = rewards_mb[i] + gamma * Qs_next_state[i]
                        target_Qs_batch.append(target)

                targets_mb = np.array([each for each in target_Qs_batch])
                print(states_mb.shape)
                loss, _ = sess.run([DQNetwork.loss, DQNetwork.optimizer],
                                   feed_dict={DQNetwork.inputs_: states_mb,
                                              DQNetwork.target_Q: targets_mb,
                                              DQNetwork.actions_: actions_mb})
            step += 1
        total_reward = np.sum(episode_rewards)

        print('Episode: {}'.format(episode),
              'Total reward: {}'.format(total_reward),
              'Explore P: {:.4f}'.format(explore_probability),
              'Training Loss {:.4f}'.format(loss))
