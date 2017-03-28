# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
import matplotlib

wind = np.linspace(0.1, 5.0, 50)
angle = np.asarray([ 0.97, 1.93, 2.89, 3.84, 4.79, 5.74, 6.69, 7.63, 8.57, 9.51, 10.44, 11.36, 12.28, 13.19, 14.10, 14.99, 15.89, 16.77, 17.64, 18.51, 19.37, 20.20, 21.04, 21.87, 22.69, 23.51, 24.31, 25.10, 25.88, 26.65, 27.41, 28.16, 28.90, 29.63, 30.35, 31.06, 31.75, 32.44, 33.12, 33.79, 34.44, 35.09, 35.73, 36.35, 36.97, 37.58, 38.17, 38.76, 39.34, 39.91 ]);

coef = np.polyfit(angle, wind, 2)

f_inc=np.poly1d(coef)

print(coef)

# Chinese
zhfont = matplotlib.font_manager.FontProperties(fname='../scripts/simkai.ttf')
fig = plt.figure(figsize=(6,4))
ax = fig.add_subplot(111)

ax.plot(angle, f_inc(angle), lw=2, c = 'r', label=u'拟合曲线')
ax.scatter(angle, wind, s = 20, c = 'b', alpha=0.6, label=u'测试数据')
ax.text(0, 4, r'$f_{inc}(\alpha)=$'+'{:.5f}'.format(coef[0])+r'$\alpha^2 + $'+'{:.5f}'.format(coef[1])+r'$\alpha + $'+'{:.5f}'.format(coef[2]))

ax.set_ylabel(u"风速 (m/s)", fontproperties=zhfont)
ax.set_xlabel(u'倾角 ('+r'$^\circ$)', fontproperties=zhfont)
ax.legend(prop=zhfont)

plt.savefig('wind-est_f_inc.pdf', format='pdf', bbox='tight')

plt.show()

