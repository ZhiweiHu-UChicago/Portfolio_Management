#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Mar 21 16:39:53 2020

@author: huzhiwei
"""

import math
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from scipy.integrate import quad
mpl.rcParams['font.family'] = 'serif'

# CRR欧式期权
def CRR_european_option_value(S0, K, T, r, sigma, otype, M=5):
    ''' Cox-Ross-Rubinstein European option valuation.
    Parameters
    ==========
    S0 : float
        stock/index level at time 0
    K : float
        strike price
    T : float
        date of maturity
    r : float
        constant, risk-less short rate
    sigma : float
        volatility
    otype : string
        either 'call' or 'put'
    M : int
        number of time intervals
    '''
    # 生成二叉树
    dt = T / M  # length of time interval
    df = math.exp(-r * dt)  # discount per interval

    # 计算udp
    u = math.exp(sigma * math.sqrt(dt))  # up movement
    d = 1 / u  # down movement
    q = (math.exp(r * dt) - d) / (u - d)  # martingale branch probability

    # 初始化幂矩阵
    mu = np.arange(M + 1)
    mu = np.resize(mu, (M + 1, M + 1))
    #print(mu)
    md = np.transpose(mu)
    #print(md)
    #print(mu - md)
    mu = u ** (mu - md)
    md = d ** md
    #print(mu)
    #print(md)
    
    #得到各节点价格
    S = S0 * mu * md
    #print(S)

    # 得到叶子结点的期权价值
    if otype == 'call':
        V = np.maximum(S - K, 0)  # inner values for European call option
    else:
        V = np.maximum(K - S, 0)  # inner values for European put option

    #逐步向前加权平均并折现，得到期初期权价值
    for z in range(0, M):  # backwards iteration
        #逐列更新期权价值，相当于二叉树中的逐层向前折算
        V[0:M - z, M - z - 1] = (q * V[0:M - z, M - z] +
                         (1 - q) * V[1:M - z + 1, M - z]) * df
    return V[0, 0]

# 输入参数
S0 = 4.69  # index level
K = 8.46  # option strike
T = 5.0  # maturity date
r = 0.0329 # risk-less short rate
sigma = 0.4439 # volatility

mmin=2
mmax=500
step_size=1
print(CRR_european_option_value(S0, K, T, r, sigma, 'call', 100))


m = range(mmin, mmax, step_size)
CRR_values = [CRR_european_option_value(S0, K, T, r, sigma, 'call', M) for M in m]
plt.figure(figsize=(9, 5))
plt.plot(m, CRR_values, label='Binominal Trees')
plt.xlabel('Steps')
plt.ylabel('The Indenture European Call Option in 101555017.IB')
plt.legend(loc=4)
plt.xlim(0, mmax)
plt.show()
