#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Mar 22 00:44:00 2020

@author: huzhiwei
"""


#基本是Yves Hilpisch大神的代码，略作一点修改
import math
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl

'''蒙特卡洛方法产生模拟路径'''
def CIR_generate_paths(x0, kappa, theta, sigma, T, M, I, x_disc='exact'):
    dt = T / M
    x = np.zeros((M + 1, I), dtype=np.float)
    x[0] = x0
    xh = np.zeros_like(x)
    xh[0] = x0
    ran = np.random.standard_normal((M + 1, I))
    #高精度模拟
    if x_disc is 'exact':
        d = 4 * kappa * theta / sigma ** 2 #自由度
        c = (sigma ** 2 * (1 - math.exp(-kappa * dt))) / (4 * kappa) #公式1中卡方随机变量前的系数
        if d > 1:
            for t in range(1, M + 1):
                l = x[t - 1] * math.exp(-kappa * dt) / c
                chi = np.random.chisquare(d - 1, I) #计算卡方随机变量
                x[t] = c * ((ran[t] + np.sqrt(l)) ** 2 + chi)
        else:
            for t in range(1, M + 1):
                l = x[t - 1] * math.exp(-kappa * dt) / c
                N = np.random.poisson(l / 2, I)
                chi = np.random.chisquare(d + 2 * N, I) #计算卡方随机变量
                x[t] = c * chi
    #低精度模拟
    else:
        for t in range(1, M + 1):
            xh[t] = (xh[t - 1] + kappa * (theta - np.maximum(0, xh[t - 1])) *
                     dt + np.sqrt(np.maximum(0, xh[t - 1])) *
                     sigma * ran[t] * math.sqrt(dt)) #公式2
            x[t] = np.maximum(0, xh[t]) #公式3
    return x

'''绘制利率路径'''
def plot_paths():
    plt.figure(figsize=(20, 10))
    plt.plot(range(len(r)), r[:, :100])
    plt.xlabel('Time Steps')
    plt.ylabel('Short Interest Rate')
    plt.show()
    
r0, kappa_r, theta_r, sigma_r = [0.0326, 0.1, 0.03, 0.1929]
T = 5.0  # time horizon
M = 500  # time steps
dt = T / M
I = 50000  # number of MCS paths
#np.random.seed(50000)  # seed for RNG

r = CIR_generate_paths(r0, kappa_r, theta_r, sigma_r, T, M, I)
plot_paths()
#print((sum(r))/I)


'''根据路径进行定价'''
def zcb_estimator(M=50, x_disc='exact'):
    dt = T / M
    #模拟路径
    r = CIR_generate_paths(r0, kappa_r, theta_r, sigma_r, T, M, I, x_disc)
    zcb = np.zeros((M + 1, I), dtype=np.float)
    zcb[-1] = 1.0  # final value
    #逐步折现
    for t in range(M, 0, -1):
        zcb[t - 1] = zcb[t] * np.exp(-(r[t] + r[t - 1]) / 2 * dt)
    #取均值作为债券价格
    return np.sum(zcb, axis=1) / I

